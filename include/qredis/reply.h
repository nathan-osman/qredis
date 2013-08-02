#ifndef QREDIS_REPLY_H
#define QREDIS_REPLY_H

#include <QVariant>

#include "qredis_export.h"

namespace QRedis
{
    /**
     * @brief Represents a Redis reply
     */
    class QREDIS_EXPORT Reply
    {
        public:

            /**
             * @brief Reply types
             */
            enum Type {

                /**
                 * @brief A status reply
                 *
                 * The value property will contain the status message returned
                 * by the server as a QString.
                 */
                Status,

                /**
                 * @brief An error reply
                 *
                 * The value property will contain the error message returned by
                 * the server as a QString.
                 */
                Error,

                /**
                 * @brief An integer reply
                 *
                 * The value property will contain the integer value returned by
                 * the server as a qlonglong.
                 */
                Integer,

                /**
                 * @brief A bulk reply
                 *
                 * The value property will contain the bulk reply returned by
                 * the server as a QByteArray.
                 */
                Bulk,

                /**
                 * @brief A multi-bulk reply
                 *
                 * The value property will contain the multi-bulk reply returned
                 * by the server as a QVariantList. Each entry in the list is of
                 * type Reply.
                 */
                MultiBulk
            };

            /**
             * @brief Initializes the reply
             * @param type the type of the reply
             * @param value the value of the reply
             */
            Reply(Type type) : _type(type) {}

            /**
             * @brief Returns the type of the reply
             * @return the reply type
             */
            Type type() const { return _type; }

            /**
             * @brief Returns the value of the reply
             * @return the reply value
             */
            QVariant & value() { return _value; }

        private:

            Type _type;
            QVariant _value;
    };
}

#endif // QREDIS_REPLY_H
