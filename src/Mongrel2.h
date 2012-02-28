#ifndef __qmongrel2_mongrel2_h__
#define __qmongrel2_mongrel2_h__

#include "QObject"
#include "QByteArray"
#include "zeromqt/ZmqSocket.h"
#include "Request.h"

namespace QMongrel2 {

class Mongrel2 : public QObject {

    Q_OBJECT

    protected:

        QByteArray identity;

        QByteArray socket_in_addr;
        QByteArray socket_out_addr;

        ZmqSocket socket_in;
        ZmqSocket socket_out;


    protected slots:
        void handleInMsg();


 //   public signals:
//        void recieved(Request request);

    public:
        Mongrel2(const QByteArray identity_, const QByteArray socket_in_addr_, const QByteArray socket_out_addr_, QObject * parent = 0);

};


}
#endif
