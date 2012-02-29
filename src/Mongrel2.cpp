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
        socket_in(ZMQ_PULL), socket_out(ZMQ_PUB)
{
    socket_in.connectTo(socket_in_addr);

    socket_out.setOpt(ZMQ_IDENTITY, identity);
    socket_out.connectTo(socket_out_addr);


    connect(&socket_in, SIGNAL(readyRead()), this, SLOT(handleInMsg()));

}


void
Mongrel2::handleInMsg()
{
    QList<QByteArray> r = socket_in.recv();
    for(QList<QByteArray>::const_iterator i=r.constBegin(); i!=r.constEnd(); ++i) {
        QMongrel2::Request req(*i);
        emit received(req);
    }
}


void
Mongrel2::send(Response resp)
{
    QByteArray data = resp.toByteArray(identity, Response::PLAIN);
    socket_out.send(data);
}


void
Mongrel2::sendHttp(Response resp)
{
    QByteArray data = resp.toByteArray(identity, Response::HTTP);
    socket_out.send(data);
}
