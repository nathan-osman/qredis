#ifndef QREDIS_REQUEST_H
#define QREDIS_REQUEST_H

#include <QObject>
#include <QScopedPointer>

#include <qredis/reply.h>
#include "qredis_export.h"

namespace QRedis
{
    class QREDIS_EXPORT RequestPrivate;

    /**
     * @brief Represents a Redis command and its response
     */
    class QREDIS_EXPORT Request : public QObject
    {
        Q_OBJECT

        public:

            /**
             * @brief Initializes the request
             * @param parent the parent QObject
             */
            explicit Request(QObject * parent = 0);

            /**
             * @brief Destroys the request
             */
            virtual ~Request();

            /**
             * @brief Waits for the reply to be received
             * @param msecs the amount of time in milliseconds to wait
             * @return true if the reply was received
             */
            bool waitForReply(int msecs = 30000);

        Q_SIGNALS:

            /**
             * @brief Emitted when a reply is received
             * @param reply the reply received
             */
            void reply(Reply & reply);

        private:

            const QScopedPointer<RequestPrivate> d;
    };
}

#endif // QREDIS_REQUEST_H
