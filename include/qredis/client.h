#ifndef QREDIS_CLIENT_H
#define QREDIS_CLIENT_H

#include <QHostAddress>
#include <QObject>
#include <QScopedPointer>

#include <qredis/request.h>
#include "qredis_export.h"

namespace QRedis
{
    class QREDIS_EXPORT ClientPrivate;

    /**
     * @brief Provides access to a Redis server
     */
    class QREDIS_EXPORT Client : public QObject
    {
        Q_OBJECT
        
        public:
            
            /**
             * @brief Creates a Redis client
             * @param parent the parent QObject
             */
            explicit Client(QObject * parent = nullptr);

            /**
             * @brief Destroys the client
             */
            virtual ~Client();

            /**
             * @brief Attempts to connect to the specified Redis server
             * @param address the address of the Redis server
             * @param port the port that the Redis server is listening on
             *
             * If the connection was successful, the connected() signal will be
             * emitted.
             */
            void connectToHost(const QHostAddress & address, quint16 port = 6379);

            /**
             * @brief Disconnects from the Redis server
             */
            void disconnectFromHost();

            /**
             * @brief Sends the specified command to the Redis server
             * @param command the command to execute
             * @return an object representing the request
             */
            Request * sendCommand(const QString & command);

        signals:

            /**
             * @brief Emitted when the client establishes a connection with the Redis server
             */
            void connected();

            /**
             * @brief Emitted when the client disconnects from the Redis server
             */
            void disconnected();

        private:

            const QScopedPointer<ClientPrivate> d;
    };
}

#endif // QREDIS_CLIENT_H
