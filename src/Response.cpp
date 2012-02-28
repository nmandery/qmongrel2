#include "Response.h"
#include "QVariant"
#include "qtnetstring/qtnetstring.h"

using namespace QMongrel2;

Response::Response(int conn_id)
{
    resp_data = new ResponseData;

    resp_data->conn_ids.append(conn_id);
}



QByteArray
Response::toByteArray(const QByteArray & identity)
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
        serialized.append(resp_data->body);
    }
    return serialized;
}

