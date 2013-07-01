#include <qredis/request.h>
#include "request_p.h"

using namespace QRedis;

Request::Request(QObject * parent)
    : QObject(parent), d(new RequestPrivate)
{
}

Request::~Request()
{
}
