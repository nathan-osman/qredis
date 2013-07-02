#include <QTest>

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
