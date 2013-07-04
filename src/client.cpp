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

int ClientPrivate::readInteger(qlonglong & value)
{
    int pos = buffer.indexOf("\r\n");
    if(pos != -1)
    {
        value = buffer.mid(0, pos).toLongLong();
        buffer.remove(0, pos + 2);
    }
    return pos;
}

/*
 * Note: error replies actually contain a type and then the error description
 * but we just combine them here for simplicity.
 */

bool ClientPrivate::readStatusOrErrorReply()
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

bool ClientPrivate::readIntegerReply()
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

bool ClientPrivate::readBulkReply()
{
    /* Check if the reply contains \r\n. */
    int pos = buffer.indexOf("\r\n");
    if(pos != -1)
    {
        int length = buffer.mid(1, pos -1).toInt();
        if(buffer.size() >= pos + length + 4)
        {
            emit queue.dequeue()->bulk(buffer.mid(pos + 2, length));

            buffer.remove(0, pos + length + 4);
            return true;
        }
    }

    return false;
}

bool ClientPrivate::readMultiBulkReply()
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
                finished = readStatusOrErrorReply();
                break;
            case ':':
                finished = readIntegerReply();
                break;
            case '$':
                finished = readBulkReply();
                break;
            case '*':
                finished = readMultiBulkReply();
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

Request * Client::sendCommand(const QByteArray & command)
{
    d->socket.write(command + "\r\n");

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
