#include "parser.h"

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
        case '+': stack.append(Task(Task::ReadStatus));    break;
        case '-': stack.append(Task(Task::ReadError));     break;
        case ':': stack.append(Task(Task::ReadInteger));   break;
        case '$': stack.append(Task(Task::ReadBulk));      break;
        case '*': stack.append(Task(Task::ReadMultiBulk)); break;
        default:
            emit warning(tr("Skipping unexpected character '%1'").arg(static_cast<int>(c), 0, 16));
            break;
    }
}

void Parser::readUnsafeString(const QString & value)
{
    if(tos().action == Task::ReadMultiBulk)
        tos().count = value.toInt();
    else
    {
        stack.removeLast();

        if(tos().action == Task::ReadStatus)
            emit status(value);
        else if(tos().action == Task::ReadError)
        {
            int pos = value.indexOf(' ');
            emit error(value.left(pos), value.right(pos + 1));
        }
        else if(!stack.count())
            emit integer(value.toLongLong());
        else
        {
            tos().value.toList().append(value);
            descend();
        }
    }
}

void Parser::readSafeString(const QByteArray & value)
{
    stack.removeLast();

    if(!stack.count())
        emit bulk(value);
    else
    {
        tos().value.toList().append(value);
        descend();
    }
}

void Parser::descend()
{
    while(true)
    {
        if(tos().value.toList().count() < tos().count)
            break;

        if(stack.count() == 1)
        {
            emit multiBulk(tos().value.toList());
            stack.removeLast();
            break;
        }

        Task task = stack.takeLast();
        tos().value.toList().append(task.value);
    }
}
