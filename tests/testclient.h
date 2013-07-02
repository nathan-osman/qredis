#ifndef TEST_CLIENT_H
#define TEST_CLIENT_H

#include <QObject>

#include <qredis/client.h>

class TestClient : public QObject
{
    Q_OBJECT

    public Q_SLOTS:

        void initTestCase();
        void cleanupTestCase();

    private:

        QRedis::Client client;
};

#endif // TEST_CLIENT_H
