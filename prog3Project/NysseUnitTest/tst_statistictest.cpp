#include <QtTest>

#include "Core/tilasto.hh"

// add necessary includes here

class statisticTest : public QObject
{
    Q_OBJECT

public:
    statisticTest();
    ~statisticTest();

private slots:
    void initTestCase();
    void cleanupTestCase();
    void test_case1();

};

statisticTest::statisticTest()
{

}

statisticTest::~statisticTest()
{

}

void statisticTest::initTestCase()
{

}

void statisticTest::cleanupTestCase()
{

}

void statisticTest::test_case1()
{
    QVERIFY2(true, "Failure");
    std::shared_ptr<tilasto> stats = std::make_shared<tilasto>(tilasto());
    stats->morePassengers(1);
    QVERIFY(1 == stats->get_passengers());

}

QTEST_APPLESS_MAIN(statisticTest)

#include "tst_statistictest.moc"
