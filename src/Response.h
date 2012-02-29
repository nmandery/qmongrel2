#ifndef __qmongrel2_response_h__
#define __qmongrel2_response_h__

#include "QObject"
#include "QByteArray"
#include "QList"
#include "QMap"
#include <QSharedData>

namespace QMongrel2 {


class ResponseData : public QSharedData
{

    public:

        QList<int> conn_ids;
        QByteArray body;
        QMap<QByteArray, QByteArray> headers;
        int http_code;

        ResponseData()
            :   conn_ids(),
                body(),
                headers(),
                http_code(200)
            {};

        ResponseData(const ResponseData &other)
            :   QSharedData(other),
                conn_ids(other.conn_ids),
                body(other.body),
                headers(other.headers),
                http_code(other.http_code)
            {};
};


class Response
{

    private:
        QSharedDataPointer<ResponseData> resp_data;

    protected:
        QByteArray getHttpResponse();

    public:

        /** response serialization format */
        enum Format {
            PLAIN,
            HTTP
        };

        Response(int conn_id);
        Response(const Response &other)
            : resp_data(other.resp_data)
            {};

        void addConnId(int conn_id)
        {
            if (resp_data) {
                resp_data->conn_ids.append(conn_id);
            }
        };

        void setHeader(QByteArray hdr_name, QByteArray hdr_content)
        {
            resp_data->headers[hdr_name] = hdr_content;
        }

        void setHttpCode(int http_code_)
        {
            resp_data->http_code = http_code_;
        }

        int getHttpCode()
        {
            return resp_data->http_code;
        }

        const QString & getHttpStatus();


        QByteArray & getBodyRef()
        {
            return resp_data->body;
        }

        QByteArray toByteArray(const QByteArray & identity, Format format=PLAIN);

};

}

#endif
