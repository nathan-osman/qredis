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
    QVERIFY(client.waitForDisconnected());
}
