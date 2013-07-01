#ifndef QREDIS_CLIENT_P_H
#define QREDIS_CLIENT_P_H

#include <QQueue>
#include <QTcpSocket>

#include <qredis/request.h>

namespace QRedis
{
    class ClientPrivate
    {
        public:

            QTcpSocket socket;
            QQueue<Request *> queue;
    };
}

#endif // QREDIS_CLIENT_H
