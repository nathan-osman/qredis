#include <qredis/client.h>
#include "client_p.h"

using namespace QRedis;

ClientPrivate::ClientPrivate(Client * client)
    : q(client)
{
    connect(&socket, &QTcpSocket::connected,    q,    &Client::connected);
    connect(&socket, &QTcpSocket::disconnected, q,    &Client::disconnected);
    connect(&socket, &QTcpSocket::disconnected, this, &ClientPrivate::reset);
    connect(&socket, &QTcpSocket::readyRead,    this, &ClientPrivate::readReply);
}

/*
 * Note: error replies actually contain a type and then the error description
 * but we just combine them here for simplicity.
 */

bool ClientPrivate::readStatusOrError()
{
    /* Check if the reply contains \r\n. */
    int pos = buffer.indexOf("\r\n");
    if(pos != -1)
    {
        Request * request = queue.dequeue();

        if(buffer[0] == '+')
            emit request->status(buffer.mid(1, pos - 1));
        else
            emit request->error(buffer.mid(1, pos - 1));

        buffer.remove(0, pos + 2);
        return true;
    }

    return false;
}

bool ClientPrivate::readInteger()
{
    /* Check if the reply contains \r\n. */
    int pos = buffer.indexOf("\r\n");
    if(pos != -1)
    {
        emit queue.dequeue()->integer(buffer.mid(1, pos -1).toLongLong());

        buffer.remove(0, pos + 2);
        return true;
    }

    return false;
}

bool ClientPrivate::readBulk()
{
    return false;
}

bool ClientPrivate::readMultiBulk()
{
    return false;
}

void ClientPrivate::reset()
{
    foreach(Request * request, queue)
        request->deleteLater();
    queue.clear();
}

// TODO: unrecognized replies in the switch should be handled.

void ClientPrivate::readReply()
{
    buffer.append(socket.readAll());
    while(!buffer.isEmpty())
    {
        bool finished;
        switch(buffer[0])
        {
            case '+':
            case '-':
                finished = readStatusOrError();
                break;
            case ':':
                finished = readInteger();
                break;
            case '$':
                finished = readBulk();
                break;
            case '*':
                finished = readMultiBulk();
                break;
        }

        if(!finished)
            break;
    }
}

Client::Client(QObject * parent)
    : QObject(parent), d(new ClientPrivate(this))
{
}

Client::~Client()
{
}

void Client::connectToHost(const QString & hostName, quint16 port)
{
    d->socket.connectToHost(hostName, port);
}

void Client::disconnectFromHost()
{
    d->socket.disconnectFromHost();
}

bool Client::isConnected() const
{
    return d->socket.state() == QAbstractSocket::ConnectedState;
}

Request * Client::sendCommand(const QString & command)
{
    d->socket.write(QString("%1\r\n").arg(command).toUtf8());

    Request * request = new Request(this);
    d->queue.enqueue(request);
    return request;
}

bool Client::waitForConnected(int msecs)
{
    return d->socket.waitForConnected(msecs);
}

bool Client::waitForDisconnected(int msecs)
{
    return d->socket.waitForDisconnected(msecs);
}
