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
}

Request::~Request()
{
}

bool Request::waitForReply(int msecs)
{
    QTimer timer;
    timer.setInterval(msecs);
    timer.setSingleShot(true);

    connect(&timer, SIGNAL(timeout()),               &d->loop, SLOT(quit()));
    connect(this,   SIGNAL(bulk(QByteArray)),        d.data(), SLOT(quitEventLoop()));
    connect(this,   SIGNAL(error(QString)),          d.data(), SLOT(quitEventLoop()));
    connect(this,   SIGNAL(integer(qlonglong)),      d.data(), SLOT(quitEventLoop()));
    connect(this,   SIGNAL(multiBulk(QVariantList)), d.data(), SLOT(quitEventLoop()));
    connect(this,   SIGNAL(status(QString)),         d.data(), SLOT(quitEventLoop()));

    /*
     * If the timer fires, the return value will be 0.
     * Otherwise, quitEventLoop() will terminate the loop with 1.
     */
    return d->loop.exec();
}
