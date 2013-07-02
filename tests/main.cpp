#include <QCoreApplication>
#include <QTest>

#include "testclient.h"

int main(int argc, char * argv[])
{
    QCoreApplication app(argc, argv);
    Q_UNUSED(app)

    TestClient test;
    return QTest::qExec(&test);
}
