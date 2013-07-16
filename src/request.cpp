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
    /*
     * Each of these signals also causes the generic reply() signal to be emitted.
     */
    connect(this, SIGNAL(bulk(QByteArray)),        SIGNAL(reply()));
    connect(this, SIGNAL(error(QString,QString)),  SIGNAL(reply()));
    connect(this, SIGNAL(integer(qlonglong)),      SIGNAL(reply()));
    connect(this, SIGNAL(multiBulk(QVariantList)), SIGNAL(reply()));
    connect(this, SIGNAL(status(QString)),         SIGNAL(reply()));

    /*
     * We also need to ensure that this object is deleted when the reply is received.
     */
    connect(this, SIGNAL(reply()), SLOT(deleteLater()));
}

Request::~Request()
{
}

bool Request::waitForReply(int msecs)
{
    QTimer timer;
    timer.setInterval(msecs);
    timer.setSingleShot(true);

    connect(&timer, SIGNAL(timeout()), &d->loop, SLOT(quit()));
    connect(this,   SIGNAL(reply()),   d.data(), SLOT(quitEventLoop()));

    /*
     * If the timer fires, the return value will be 0.
     * Otherwise, quitEventLoop() will terminate the loop with 1.
     */
    return d->loop.exec();
}
