#include "example.h"
#include <QtCore/QCoreApplication>

#include <QByteArray>
#include <QString>

static QString html_template("<!DOCTYPE html><html><head><title>qmongrel2 handler "
    "example</title></head><body><h1>Request headers</h1><table>%1</table></body></html>");
static QString row_template("<tr><td>%1</td><td>%2</td></tr>");

void
Webapp::receive(QMongrel2::Request req)
{
    QMongrel2::Response resp = req.getResponse();

    QString rows;
    QMap<QString, QByteArray> headers = req.getHeaders();
    QMap<QString, QByteArray>::const_iterator headeriter = headers.constBegin();
    while (headeriter != headers.constEnd()) {
        rows.append(row_template.arg(headeriter.key(), QString(headeriter.value())));
        ++headeriter;
    }

    resp.getBodyRef() = html_template.arg(rows).toUtf8();
    resp.setHeader("Content-Type", "text/html");
    emit reply(resp);
}


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QMongrel2::Mongrel2 m2("1278389173", "tcp://127.0.0.1:9008", "tcp://127.0.0.1:9009");
    Webapp webapp;

    QObject::connect(&m2, SIGNAL(received(QMongrel2::Request)),
                &webapp, SLOT(receive(QMongrel2::Request)));
    QObject::connect(&webapp, SIGNAL(reply(QMongrel2::Response)),
                &m2, SLOT(sendHttp(QMongrel2::Response)));


    return a.exec();

}
