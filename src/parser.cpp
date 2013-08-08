#include "parser.h"

using namespace QRedis;

Parser::Parser(Lexer * lexer, QObject * parent)
    : QObject(parent)
{
    connect(lexer, SIGNAL(character(char)),        SLOT(readCharacter(char)));
    connect(lexer, SIGNAL(unsafeString(QString)),  SLOT(readUnsafeString(QString)));
    connect(lexer, SIGNAL(safeString(QByteArray)), SLOT(readSafeString(QByteArray)));
}

Parser::~Parser()
{
}

void Parser::readCharacter(char c)
{
    switch(c)
    {
        case '+': stack.append(Task(Reply::Status));    break;
        case '-': stack.append(Task(Reply::Error));     break;
        case ':': stack.append(Task(Reply::Integer));   break;
        case '$': stack.append(Task(Reply::Bulk));      break;
        case '*': stack.append(Task(Reply::MultiBulk)); break;
        default:
            qWarning("Skipping unexpected character '%x'", static_cast<int>(c));
            break;
    }
}

void Parser::readUnsafeString(const QString & value)
{
    if(tos().reply.type() == Reply::MultiBulk)
        tos().count = value.toInt();
    else
        tos().reply.value() = value;

    descend();
}

void Parser::readSafeString(const QByteArray & value)
{
    tos().reply.value() = value;
    descend();
}

void Parser::descend()
{
    while(true)
    {
        if(tos().reply.type() == Reply::MultiBulk &&
           tos().reply.value().toList().count() < tos().count)
            return;

        if(stack.count() == 1)
        {
            emit reply(stack.takeLast().reply);
            return;
        }

        Reply r = stack.takeLast().reply;
        tos().reply.value().toList().append(QVariant::fromValue(r));
    }
}
