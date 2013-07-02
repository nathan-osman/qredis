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

bool ClientPrivate::readStatusOrError()
{
    return false;
}

bool ClientPrivate::readInteger()
{
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
