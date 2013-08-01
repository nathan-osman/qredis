#ifndef PARSER_H
#define PARSER_H

#include <QList>
#include <QObject>
#include <QVariant>
#include <QVariantList>

#include "lexer.h"

class Parser : public QObject
{
    Q_OBJECT

    public:

        Parser(Lexer *, QObject * = 0);
        virtual ~Parser();

    Q_SIGNALS:

        void status(const QString &);
        void error(const QString &, const QString &);
        void integer(qlonglong);
        void bulk(const QByteArray &);
        void multiBulk(const QVariantList &);

    private Q_SLOTS:

        void readCharacter(char);
        void readUnsafeString(const QString &);
        void readSafeString(const QByteArray &);

    private:

        void descend();

        class Task
        {
            public:

                enum Action {
                    ReadStatus,
                    ReadError,
                    ReadInteger,
                    ReadBulk,
                    ReadMultiBulk
                };

                enum { Unknown = -2 };

                Task(Action action) : action(action), count(Unknown) {}

                Action action;
                int count;
                QVariant value;
        };

        QList<Task> stack;

        inline Task & tos() { return stack.last(); }
};

#endif // PARSER_H
