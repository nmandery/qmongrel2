#include "Response.h"
#include "QVariant"
#include "QDebug"
#include "QMap"
#include "QString"
#include "qtnetstring/QTNetString.h"

using namespace QMongrel2;

static QMap<int, QString> http_stati;
static QString http_status_unknown = "Unknown";


void
_initHttpStati()
{
    if (http_stati.empty()) {
        http_stati.insert(100, "Continue");
        http_stati.insert(101, "Switching Protocols");
        http_stati.insert(200, "OK");
        http_stati.insert(201, "Created");
        http_stati.insert(202, "Accepted");
        http_stati.insert(203, "Non-Authoritative Information");
        http_stati.insert(204, "No Content");
        http_stati.insert(205, "Reset Content");
        http_stati.insert(206, "Partial Content");
        http_stati.insert(300, "Multiple Choices");
        http_stati.insert(301, "Moved Permanently");
        http_stati.insert(302, "Found");
        http_stati.insert(303, "See Other");
        http_stati.insert(304, "Not Modified");
        http_stati.insert(305, "Use Proxy");
        http_stati.insert(307, "Temporary Redirect");
        http_stati.insert(400, "Bad Request");
        http_stati.insert(401, "Unauthorized");
        http_stati.insert(402, "Payment Required");
        http_stati.insert(403, "Forbidden");
        http_stati.insert(404, "Not Found");
        http_stati.insert(405, "Method Not Allowed");
        http_stati.insert(406, "Not Acceptable");
        http_stati.insert(407, "Proxy Authentication Required");
        http_stati.insert(408, "Request Time-out");
        http_stati.insert(409, "Conflict");
        http_stati.insert(410, "Gone");
        http_stati.insert(411, "Length Required");
        http_stati.insert(412, "Precondition Failed");
        http_stati.insert(413, "Request Entity Too Large");
        http_stati.insert(414, "Request-URI Too Large");
        http_stati.insert(415, "Unsupported Media Type");
        http_stati.insert(416, "Requested range not satisfiable");
        http_stati.insert(417, "Expectation Failed");
        http_stati.insert(500, "Internal Server Error");
        http_stati.insert(501, "Not Implemented");
        http_stati.insert(502, "Bad Gateway");
        http_stati.insert(503, "Service Unavailable");
        http_stati.insert(504, "Gateway Time-out");
        http_stati.insert(505, "HTTP Version not supported");
    }
}


Response::Response(int conn_id)
{
    resp_data = QSharedPointer<ResponseData>(new ResponseData);

    resp_data->conn_ids.append(conn_id);
}



QByteArray
Response::toByteArray(const QByteArray & identity, Format format)
{
    // format: UUID SIZE:ID ID ID, BODY

    QByteArray serialized;

    if (resp_data) {
        serialized.append(identity);
        serialized.append(" ");

        QByteArray conn_ids;
        QList<int>::const_iterator conn_ids_iter = resp_data->conn_ids.constBegin();
        while (conn_ids_iter != resp_data->conn_ids.constEnd()) {
            if (conn_ids.size() != 0) {
                conn_ids.append(" ");
            }
            conn_ids.append(QByteArray::number(*conn_ids_iter));
            ++conn_ids_iter;
        }

        QVariant conn_ids_variant(conn_ids);
        bool ok;
        serialized.append(QTNetString::dump(conn_ids_variant, ok));
        serialized.append(" ");

        if (format == PLAIN) {
            serialized.append(resp_data->body);
        }
        else if (format == HTTP) {
            serialized.append(getHttpResponse());
        }
        else {
            qWarning() << "unkown response format: " << format;
        }
    }
    return serialized;
}


const QString &
Response::getHttpStatus()
{
    if (http_stati.empty()) {
        _initHttpStati();
    }
    if (http_stati.contains(resp_data->http_code)) {
        return http_stati[resp_data->http_code];
    }
    return http_status_unknown;
};


QByteArray
Response::getHttpResponse()
{
    QByteArray data = "HTTP/1.1 ";
    data.append(QByteArray::number(getHttpCode()));
    data.append(" ");
    data.append(getHttpStatus());
    data.append("\r\n");

    // set content length headers
    resp_data->headers["Content-Length"] = QByteArray::number(resp_data->body.size());

    // headers
    QMap<QByteArray, QByteArray>::const_iterator headeriter = resp_data->headers.constBegin();
    while (headeriter != resp_data->headers.constEnd()) {
        data.append(headeriter.key());
        data.append(": ");
        data.append(headeriter.value());
        data.append("\r\n");
        ++headeriter;
    }
    data.append("\r\n");
    data.append(resp_data->body);

    return data;
}
