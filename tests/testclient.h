#ifndef TEST_CLIENT_H
#define TEST_CLIENT_H

#include <QObject>

#include <qredis/client.h>

class TestClient : public QObject
{
    Q_OBJECT

    private Q_SLOTS:

        void initTestCase();
        void cleanupTestCase();

        void testPing();
        void testStorage();

    private:

        QRedis::Client client;
};

#endif // TEST_CLIENT_H
