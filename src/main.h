#ifndef __main_h__
#define __main_h__


#include <QObject>
#include "Mongrel2.h"
#include "Response.h"

class Webapp : public QObject
{

    Q_OBJECT

    public:
        Webapp(QObject * parent = 0) : QObject(parent) {};

    signals:
        void reply(QMongrel2::Response);

    public slots:
        void receive(QMongrel2::Request);
};

#endif
