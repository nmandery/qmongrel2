#include "main.h"
#include <QtCore/QCoreApplication>

#include <QByteArray>
#include <QDebug>
#include <QFile>


void
Webapp::receive(QMongrel2::Request req)
{
    qDebug() << req.getHeaders();
//    qDebug() << "user agent: " << req.getHeader("User-Agent");

    QMongrel2::Response resp = req.getResponse();
    QFile cpufile("/proc/cpuinfo");
    if (cpufile.open(QFile::ReadOnly)) {
        resp.getBodyRef() = cpufile.readAll();
        cpufile.close();
    }
    else {
        resp.getBodyRef() = "could not open file";
    }

    resp.setHeader("Content-Type", "text/plain");
    emit reply(resp);
}


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QMongrel2::Mongrel2 m2("1278389173", "tcp://127.0.0.1:9008", "tcp://127.0.0.1:9009");
    Webapp webapp;

    QObject::connect(&m2, SIGNAL(received(QMongrel2::Request)), &webapp, SLOT(receive(QMongrel2::Request)));
    QObject::connect(&webapp, SIGNAL(reply(QMongrel2::Response)), &m2, SLOT(sendHttp(QMongrel2::Response)));


    return a.exec();

}
