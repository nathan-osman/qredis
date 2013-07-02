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
    QVERIFY(request->waitForReply());
}
