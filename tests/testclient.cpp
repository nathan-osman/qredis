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

void TestClient::testStorage()
{
    QRedis::Request * request1 = client.sendCommand("SET value 10");
    QSignalSpy spy1(request1, SIGNAL(status(QString)));

    QVERIFY(request1->waitForReply());
    QCOMPARE(spy1.count(), 1);
    QCOMPARE(spy1[0][0].toString(), QString("OK"));

    QRedis::Request * request2 = client.sendCommand("GET value");
    QSignalSpy spy2(request2, SIGNAL(bulk(QByteArray)));

    QVERIFY(request2->waitForReply());
    QCOMPARE(spy2.count(), 1);
    QCOMPARE(spy2[0][0].toByteArray(), QByteArray("10"));
}
