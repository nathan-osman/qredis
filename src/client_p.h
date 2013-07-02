#ifndef QREDIS_CLIENT_P_H
#define QREDIS_CLIENT_P_H

#include <QObject>
#include <QQueue>
#include <QTcpSocket>

#include <qredis/client.h>
#include <qredis/request.h>

namespace QRedis
{
    class ClientPrivate : public QObject
    {
        Q_OBJECT

        public:

            ClientPrivate(Client *);

            bool readStatusOrError();
            bool readInteger();
            bool readBulk();
            bool readMultiBulk();

            QTcpSocket socket;

            QQueue<Request *> queue;
            QByteArray buffer;

        public Q_SLOTS:

            void reset();
            void readReply();

        private:

            Client * const q;
    };
}

#endif // QREDIS_CLIENT_H
