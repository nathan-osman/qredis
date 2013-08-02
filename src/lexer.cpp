#include "lexer.h"

using namespace QRedis;

Lexer::Lexer(QIODevice * device, QObject * parent)
    : QObject(parent), device(device), state(DoingNothing), crlf(0)
{
    connect(device, SIGNAL(readyRead()), SLOT(readData()));
}

Lexer::~Lexer()
{
}

void Lexer::readData()
{
    buffer.append(device->readAll());

    while(true)
    {
        if(state == DoingNothing && !readCharacter())
            break;

        switch(state)
        {
            case ReadingLength:
            case ReadingUnsafeString: if(!readUnsafeString()) return;
            case ReadingSafeString:   if(!readSafeString())   return;
        }

        if(state != ReadingSafeString)
            state = DoingNothing;
    }
}


bool Lexer::readCharacter()
{
    if(!buffer.size())
        return false;

    char c = buffer.at(0);
    buffer.remove(0, 1);

    switch(c)
    {
        case '+':
        case '-':
        case ':':
        case '*': state = ReadingUnsafeString; break;
        case '$': state = ReadingLength;       break;
    }

    emit character(c);
    return true;
}

bool Lexer::readUnsafeString()
{
    crlf = buffer.indexOf("\r\n", crlf);
    if(crlf == -1)
    {
        crlf = buffer.size();
        return false;
    }

    QString s = buffer.mid(0, crlf);
    buffer.remove(0, crlf + 2);

    if(state == ReadingLength)
    {
        length = s.toInt();
        state = ReadingSafeString;
    }
    else
        emit unsafeString(s);

    crlf = 0;
    return true;
}

bool Lexer::readSafeString()
{
    if(buffer.size() < length + 2)
        return false;

    QByteArray d = buffer.mid(0, length);
    buffer.remove(0, length + 2);

    emit safeString(d);

    state = DoingNothing;
    return true;
}
