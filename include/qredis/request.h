#ifndef QREDIS_REQUEST_H
#define QREDIS_REQUEST_H

#include <QObject>
#include <QScopedPointer>
#include <QVariant>
#include <QVariantList>

#include "qredis_export.h"

namespace QRedis
{
    class QREDIS_EXPORT RequestPrivate;

    /**
     * @brief Represents a request and its response
     */
    class QREDIS_EXPORT Request : public QObject
    {
        Q_OBJECT

        public:

            /**
             * @brief Creates a request
             * @param parent
             */
            explicit Request(QObject * parent = nullptr);

            /**
             * @brief Destroys the request
             */
            virtual ~Request();

        signals:

            /**
             * @brief Emitted when a bulk reply is received
             * @param value the bulk value
             */
            void bulk(const QVariant & value);

            /**
             * @brief Emitted when an error reply is received
             * @param message a descriptive error message
             */
            void error(const QString & message);

            /**
             * @brief Emitted when an integer reply is received
             * @param value the integer value
             */
            void integer(qint64 value);

            /**
             * @brief Emitted when a multi-bulk reply is received
             * @param value the multi-bulk value
             */
            void multiBulk(const QVariantList & value);

            /**
             * @brief Emitted when a status reply is received
             * @param message a descriptive status message
             */
            void status(const QString & message);

        private:

            const QScopedPointer<RequestPrivate> d;
    };
}

#endif // QREDIS_REQUEST_H
