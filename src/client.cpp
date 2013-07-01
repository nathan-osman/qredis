#include <qredis/client.h>
#include "client_p.h"

using namespace QRedis;

Client::Client(QObject * parent)
    : QObject(parent), d(new ClientPrivate)
{
    connect(&d->socket, &QTcpSocket::connected,    this, &Client::connected);
    connect(&d->socket, &QTcpSocket::disconnected, this, &Client::disconnected);
}

Client::~Client()
{
}

void Client::connectToHost(const QHostAddress & address, quint16 port)
{
    d->socket.connectToHost(address, port);
}

void Client::disconnectFromHost()
{
    d->socket.disconnectFromHost();
}

Request * Client::sendCommand(const QString & command)
{
    Request * request = new Request(this);
    d->queue.enqueue(request);
}
