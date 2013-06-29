#ifndef QREDIS_CLIENT_P_H
#define QREDIS_CLIENT_P_H

#include <QTcpSocket>

namespace QRedis
{
    class ClientPrivate
    {
        public:

            QTcpSocket socket;
    };
}

#endif // QREDIS_CLIENT_H
