#ifndef QREDIS_REQUEST_P_H
#define QREDIS_REQUEST_P_H

#include <QEventLoop>
#include <QObject>

namespace QRedis
{
    class RequestPrivate : public QObject
    {
        Q_OBJECT

        public:

            QEventLoop loop;

        public Q_SLOTS:

            void quitEventLoop();
    };
}

#endif // QREDIS_REQUEST_P_H
