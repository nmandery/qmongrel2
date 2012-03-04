#include "Request.h"
#include <QDebug>
#include <QList>
#include <QVariant>
#include <QRegExp>
#include "qtnetstring/QTNetString.h"

using namespace QMongrel2;


Request::Request(const QByteArray &msgdata)
        : is_ok(false)
{

    req_data = QSharedPointer<RequestData>(new RequestData());
    req_data->is_ok = false;

    int end_sender_ident = msgdata.indexOf(' ');
    if (end_sender_ident < 1) {
        qDebug() << "space after sender_ident not found";
        return;
    }
    req_data->sender_ident = msgdata.mid(1, end_sender_ident);

    int end_conn_pos = msgdata.indexOf(' ', end_sender_ident+1);
    if ((end_conn_pos == -1)) {
        qDebug() << "no space after conn_id found";
        return;
    }

    QByteArray byte_conn = msgdata.mid(end_sender_ident+1, end_conn_pos-end_sender_ident-1);
    req_data->conn_id = byte_conn.toInt(&(req_data->is_ok));
    if (!req_data->is_ok) {
        qDebug() << "conn_id is no number";
        return;
    }

    int end_path = msgdata.indexOf(' ', end_conn_pos + 1);
    if (end_path == -1) {
        qDebug() << "no space at edn of path found";
        return;
    }

    int header_end;
    QVariant hdrs = QTNetString:: parse(msgdata, end_path, header_end, req_data->is_ok);
    if (!req_data->is_ok) {
        qDebug() << "could not parse headers tns";
        return;
    }
    if (!hdrs.canConvert(QVariant::Map)) {
        qDebug() << "headers are not a map";
        return;
    }
    QMap<QString, QVariant> hdr_variantmap = hdrs.toMap();
    QMap<QString, QVariant>::const_iterator iter_variant = hdr_variantmap.constBegin();
    while (iter_variant != hdr_variantmap.constEnd()) {
        if (iter_variant.value().canConvert(QVariant::ByteArray)) {
            req_data->headers[iter_variant.key()] = iter_variant.value().toByteArray();
        }
        ++iter_variant;
    }

    int end_msgdata;
    QVariant body_variant = QTNetString:: parse(msgdata, header_end, end_msgdata, req_data->is_ok);
    if (!req_data->is_ok) {
        qDebug() << "could not parse body tns";
        return;
    }
    if (!body_variant.canConvert(QVariant::ByteArray)) {
        qDebug() << "body is not a bytearray";
        return;
    }
    req_data->body = body_variant.toByteArray();
    req_data->is_ok = true;
}


Request::Method
Request::getMethod()
{
    Request::Method method = OTHER;

    if (req_data) {
        QString mtd = getHeaderCaseSensitive("METHOD");

        if (mtd == "POST") {
            method = POST;
        }
        else if (mtd == "GET") {
            method = GET;
        }
        else if (mtd == "JSON") {
            method = JSON;
        }
        else if (mtd == "OPTIONS") {
            method = OPTIONS;
        }
        else if (mtd == "HEAD") {
            method = HEAD;
        }
        else if (mtd == "DELETE") {
            method = DELETE;
        }
        else if (mtd == "TRACE") {
            method = TRACE;
        }
        else if (mtd == "CONNECT") {
            method = CONNECT;
        }
        else {
            qWarning() << "Unsupported request method: " << mtd;
        }
    }

    return method;
}


bool
Request::isDisconnect()
{
    /*
      TODO: use real json parser
      for now mongrel2 implements only this response - also hardcoded.

      possible parser: jsonqt
     */
    return req_data->body == "{\"type\":\"disconnect\"}";
}
