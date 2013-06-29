#ifndef QREDIS_CLIENT_H
#define QREDIS_CLIENT_H

#include <QObject>
#include <QScopedPointer>

#include <qredis/command.h>
#include "qredis_export.h"

namespace QRedis
{
    class QREDIS_EXPORT ClientPrivate;

    /**
     * @brief Provides access to a Redis server.
     */
    class QREDIS_EXPORT Client : public QObject
    {
        Q_OBJECT
        
        public:
            
            /**
             * @brief Connects to a Redis server.
             */
            Client();

            /**
             * @brief Disconnects from the Redis server.
             */
            virtual ~Client();

            void connectToHost();
            void disconnectFromHost();

            Command * sendCommand();

        signals:

            void connected();

        private:

            const QScopedPointer<ClientPrivate> d;
    };
}

#endif // QREDIS_CLIENT_H
