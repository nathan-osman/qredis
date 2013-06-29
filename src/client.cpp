#include <qredis/client.h>
#include "client_p.h"

using namespace QRedis;

Client::Client()
    : d(new ClientPrivate)
{
}

Client::~Client()
{
}

void Client::connectToHost()
{
}

void Client::disconnectFromHost()
{
}
