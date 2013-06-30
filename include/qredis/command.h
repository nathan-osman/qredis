#ifndef QREDIS_COMMAND_H
#define QREDIS_COMMAND_H

#include <QObject>
#include <QScopedPointer>

#include "qredis_export.h"

namespace QRedis
{
    class QREDIS_EXPORT CommandPrivate;

    /**
     * @brief Represents a specific command and its response.
     */
    class QREDIS_EXPORT Command : public QObject
    {
        public:

            /**
             * @brief Creates a command
             * @param parent
             */
            explicit Command(QObject * parent = nullptr);

            /**
             * @brief Destroys the command
             */
            virtual ~Command();

        signals:

            void completed();

        private:

            const QScopedPointer<CommandPrivate> d;
    };
}

#endif // QREDIS_COMMAND_H
