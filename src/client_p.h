#ifndef QREDIS_CLIENT_P_H
#define QREDIS_CLIENT_P_H

#include <QObject>
#include <QQueue>
#include <QTcpSocket>

#include <qredis/client.h>
#include <qredis/reply.h>
#include <qredis/request.h>
#include "lexer.h"
#include "parser.h"

namespace QRedis
{
    class ClientPrivate : public QObject
    {
        Q_OBJECT

        public:

            ClientPrivate(Client *);

            QTcpSocket socket;
            QQueue<Request *> queue;

            Lexer lexer;
            Parser parser;

        private Q_SLOTS:

            void sendReply(Reply &);
    };
}

#endif // QREDIS_CLIENT_H
