#include "Mongrel2.h"
#include "QDebug"
#include "QList"
#include "Request.h"
#include "Response.h"

using namespace QMongrel2;


Mongrel2::Mongrel2(const QByteArray identity_, const QByteArray socket_in_addr_, const QByteArray socket_out_addr_, QObject *parent):
        QObject(parent),
        identity(identity_),
        socket_in_addr(socket_in_addr_), socket_out_addr(socket_out_addr_),
        socket_in(ZMQ_PULL), socket_out(ZMQ_SUB)
{
    socket_in.connectTo(socket_in_addr);
    socket_out.connectTo(socket_out_addr);

    socket_out.setOpt(ZMQ_IDENTITY, identity);


    connect(&socket_in, SIGNAL(readyRead()), this, SLOT(handleInMsg()));

}


void
Mongrel2::handleInMsg()
{
    qDebug() << "Inmsg";
    QList<QByteArray> r = socket_in.recv();
    for(QList<QByteArray>::const_iterator i=r.constBegin(); i!=r.constEnd(); ++i) {
        QMongrel2::Request req(*i);
        QMongrel2::Response resp = req.getResponse();
        qDebug() << "Responding " << resp.toByteArray(identity);
    }
}
