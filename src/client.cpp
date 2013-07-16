#include <qredis/client.h>
#include "client_p.h"

using namespace QRedis;

ClientPrivate::ClientPrivate(Client * client)
    : lexer(&socket), parser(&lexer)
{
    connect(&socket, SIGNAL(connected()),    client, SIGNAL(connected()));
    connect(&socket, SIGNAL(disconnected()), client, SIGNAL(disconnected()));

    connect(&parser, SIGNAL(status(QString)),         SLOT(sendStatus(QString)));
    connect(&parser, SIGNAL(error(QString,QString)),  SLOT(sendError(QString,QString)));
    connect(&parser, SIGNAL(integer(qlonglong)),      SLOT(sendInteger(qlonglong)));
    connect(&parser, SIGNAL(bulk(QByteArray)),        SLOT(sendBulk(QByteArray)));
    connect(&parser, SIGNAL(multiBulk(QVariantList)), SLOT(sendMultiBulk(QVariantList)));
}

void ClientPrivate::sendStatus(const QString & message)
{
    emit queue.dequeue()->status(message);
}

void ClientPrivate::sendError(const QString & generic, const QString & specific)
{
    emit queue.dequeue()->error(generic, specific);
}

void ClientPrivate::sendInteger(qlonglong value)
{
    emit queue.dequeue()->integer(value);
}

void ClientPrivate::sendBulk(const QByteArray & value)
{
    emit queue.dequeue()->bulk(value);
}

void ClientPrivate::sendMultiBulk(const QVariantList & values)
{
    emit queue.dequeue()->multiBulk(values);
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
