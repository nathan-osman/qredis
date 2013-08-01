#include <qredis/client.h>
#include "client_p.h"

using namespace QRedis;

ClientPrivate::ClientPrivate(Client * client)
    : lexer(&socket), parser(&lexer)
{
    connect(&socket, SIGNAL(connected()),    client, SIGNAL(connected()));
    connect(&socket, SIGNAL(disconnected()), client, SIGNAL(disconnected()));
    connect(&parser, SIGNAL(reply(QRedis::Reply&)),  SLOT(sendReply(Reply&)));
}

void ClientPrivate::sendReply(Reply & reply)
{
    emit queue.dequeue()->reply(reply);
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
