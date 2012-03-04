#ifndef __qmongrel2_request_h__
#define __qmongrel2_request_h__

#include "QObject"
#include "QSharedPointer"
#include "QByteArray"
#include "QMap"
#include "QString"
#include "Response.h"

namespace QMongrel2 {


class RequestData
{

     public:
        int conn_id;
        QByteArray sender_ident;
        QMap<QString, QByteArray> headers;
        QByteArray body;
        bool is_ok;

        RequestData()
            :   conn_id(0),
                sender_ident(),
                headers(),
                body(),
                is_ok(false)
            {};

        RequestData(const RequestData &other)
            :   conn_id(other.conn_id),
                sender_ident(other.sender_ident),
                headers(other.headers),
                body(other.body),
                is_ok(other.is_ok)
            {};

};

class Request
{

    private:
        QSharedPointer<RequestData>req_data;

    protected:
        bool is_ok;

        const QString getHeaderCaseSensitive(const QString & header_name)
        {
            return QString(req_data->headers.value(header_name));
        }


    public:

        /**
         * HTTP Method
         */
        enum Method {
            OPTIONS,
            GET,
            POST,
            PUT,
            HEAD,
            DELETE,
            TRACE,
            CONNECT,
            OTHER,
            JSON
        };

        Request(const QByteArray &msgdata);
        Request(const Request &other)
            : req_data(other.req_data)
            {};

        Response getResponse()
        {
            int conn_id = 0;
            if (req_data) {
                conn_id = req_data->conn_id;
            }
            return Response(conn_id);
        };

        const QMap<QString, QByteArray> & getHeaders()
        {
            return req_data->headers;
        }

        Method getMethod();


        const QString getHeader(const QString & header_name)
        {
            // mongrel2 returns http headers always in lowercase
            return req_data->headers.value(header_name.toLower());
        }


        const inline QString getPattern()
        {
            return getHeaderCaseSensitive("PATTERN");
        }


        const inline QString getPath()
        {
            return getHeaderCaseSensitive("PATH");
        }

        const inline QString getHttpVersion()
        {
            return getHeaderCaseSensitive("VERSION");
        }


        const inline QString getUri()
        {
            return getHeaderCaseSensitive("URI");
        }


        const inline QByteArray & getBodyRef()
        {
            return req_data->body;
        }

        bool isDisconnect();

};

}
#endif
