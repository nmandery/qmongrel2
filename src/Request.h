#ifndef __qmongrel2_request_h__
#define __qmongrel2_request_h__

#include "QObject"
#include "QSharedData"
#include "QByteArray"
#include "QMap"
#include "QString"
#include "Response.h"

namespace QMongrel2 {


class RequestData : public QSharedData {

     public:
        int conn_id;
        QByteArray sender_ident;
        QMap<QString, QByteArray> headers;
        QByteArray body;
        bool is_ok;

        RequestData()
            :   conn_id(0), sender_ident(),
                headers(), body(), is_ok(false)
            {};

        RequestData(const RequestData &other)
            :   QSharedData(other), conn_id(other.conn_id),
                sender_ident(other.sender_ident),
                headers(other.headers),
                body(other.body), is_ok(other.is_ok)
            {};

};

class Request {

    private:
        QSharedDataPointer<RequestData>req_data;

    protected:
        bool is_ok;

    public:
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
};

}
#endif
