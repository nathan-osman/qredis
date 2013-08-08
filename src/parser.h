#ifndef QREDIS_PARSER_H
#define QREDIS_PARSER_H

#include <QList>
#include <QObject>
#include <QPair>
#include <QVariant>

#include <qredis/reply.h>
#include "lexer.h"

namespace QRedis
{
    class Parser : public QObject
    {
        Q_OBJECT

        public:

            Parser(Lexer *, QObject * = 0);
            virtual ~Parser();

        Q_SIGNALS:

            void reply(const Reply &);

        private Q_SLOTS:

            void readCharacter(char);
            void readUnsafeString(const QString &);
            void readSafeString(const QByteArray &);

        private:

            void descend();

            class Task
            {
                public:

                    enum { Unknown = -2 };

                    Task(Reply::Type type) : reply(type), count(Unknown) {}

                    Reply reply;
                    int count;
            };

            QList<Task> stack;

            Task & tos() { return stack.last(); }
    };
}

#endif // QREDIS_PARSER_H
