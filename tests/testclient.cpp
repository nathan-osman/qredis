#include <QSignalSpy>
#include <QTest>

#include <qredis/request.h>
#include "testclient.h"

void TestClient::initTestCase()
{
    client.connectToHost("localhost");
    QVERIFY(client.waitForConnected());
}

void TestClient::cleanupTestCase()
{
    client.disconnectFromHost();

    if(client.isConnected())
        QVERIFY(client.waitForDisconnected());
}

void TestClient::testPing()
{
    QRedis::Request * request = client.sendCommand("PING");
    QSignalSpy spy(request, SIGNAL(status(QString)));

    QVERIFY(request->waitForReply());
    QCOMPARE(spy.count(), 1);
    QCOMPARE(spy[0][0].toString(), QString("PONG"));
}
