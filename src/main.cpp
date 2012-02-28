#include <QtCore/QCoreApplication>

#include "qtnetstring/qtnetstring.h"
#include <QVariant>
#include <QByteArray>
#include <QMap>
#include <QList>
#include <QDebug>
#include <QDateTime>

#include "Mongrel2.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QMongrel2::Mongrel2 m2("1278389173", "tcp://127.0.0.1:9008", "tcp://127.0.0.1:9009");

    return a.exec();

}
