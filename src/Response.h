#ifndef __qmongrel2_response_h__
#define __qmongrel2_response_h__

#include "QObject"
#include "QByteArray"
#include "QList"
#include <QSharedData>

namespace QMongrel2 {


class ResponseData : public QSharedData
{

    public:

        QList<int> conn_ids;
        QByteArray body;

        ResponseData()
            :   conn_ids(),
                body() 
            {};

        ResponseData(const ResponseData &other)
            :   QSharedData(other),
                conn_ids(other.conn_ids),
                body(other.body)
            {};

};


class Response
{
    private:
        QSharedDataPointer<ResponseData> resp_data;

    public:

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

        QByteArray toByteArray(const QByteArray & identity);

};

}

#endif
