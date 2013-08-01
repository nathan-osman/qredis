#include <QTimer>

#include <qredis/request.h>
#include "request_p.h"

using namespace QRedis;

void RequestPrivate::quitEventLoop()
{
    loop.exit(1);
}

Request::Request(QObject * parent)
    : QObject(parent), d(new RequestPrivate)
{
    connect(this, SIGNAL(reply(Reply&)), SLOT(deleteLater()));
}

Request::~Request()
{
}

bool Request::waitForReply(int msecs)
{
    QTimer timer;
    timer.setInterval(msecs);
    timer.setSingleShot(true);

    connect(&timer, SIGNAL(timeout()),     &d->loop, SLOT(quit()));
    connect(this,   SIGNAL(reply(Reply&)), d.data(), SLOT(quitEventLoop()));

    /*
     * If the timer fires, the return value will be 0.
     * Otherwise, quitEventLoop() will terminate the loop with 1.
     */
    return d->loop.exec();
}
