#ifndef QREDIS_REQUEST_H
#define QREDIS_REQUEST_H

#include <QObject>
#include <QScopedPointer>
#include <QVariantList>

#include "qredis_export.h"

namespace QRedis
{
    class QREDIS_EXPORT RequestPrivate;

    /**
     * @brief Represents a request and its reply
     */
    class QREDIS_EXPORT Request : public QObject
    {
        Q_OBJECT

        public:

            /**
             * @brief Creates a request
             * @param parent
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
             * @brief Emitted when a status reply is received
             * @param message a descriptive status message
             */
            void status(const QString & message);

            /**
             * @brief Emitted when an error reply is received
             * @param generic a generic error identifer
             * @param specific a more specific error message
             */
            void error(const QString & generic, const QString & specific);

            /**
             * @brief Emitted when an integer reply is received
             * @param value the integer value
             */
            void integer(qlonglong value);

            /**
             * @brief Emitted when a bulk reply is received
             * @param value the value as a byte array
             */
            void bulk(const QByteArray & value);

            /**
             * @brief Emitted when a multi-bulk reply is received
             * @param a list of bulk values
             */
            void multiBulk(const QVariantList & values);

            /**
             * @brief Emitted when any reply is received
             */
            void reply();

        private:

            const QScopedPointer<RequestPrivate> d;
    };
}

#endif // QREDIS_REQUEST_H
