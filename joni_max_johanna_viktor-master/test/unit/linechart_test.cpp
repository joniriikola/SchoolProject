#include "gtest/gtest.h"

#include "linechart.h"

#include <QDateTime>
#include <QRandomGenerator>

static QDateTime qdt(int days)
{
    return QDateTime::currentDateTime().addDays(days);
}

TEST(LineChart_Test, lengthTest)
{
    LineChart chart1;
    int length = 100;
    QList<QDateTime> x;
    QList<QVariant> y;

    for (auto i = 0; i < length; ++i)
    {
        chart1.addPoint(qdt(i), i);
    }

    EXPECT_EQ(chart1.length(), length);

    LineChart chart2;
    EXPECT_EQ(chart2.length(), 0);

    LineChart chart3;
    chart3.addPoint(qdt(1), 2);
    chart3.addPoint(qdt(3), 9);
    chart3.addPoint(qdt(2), 3);
    chart3.addPoint(qdt(7), 4);
    EXPECT_EQ(chart3.length(), 4);
}

TEST(LineChart_Test, nameTest)
{
    LineChart chart;
    EXPECT_EQ(chart.name(), "");
    chart.setName("name");
    EXPECT_EQ(chart.name(), "name");
}

TEST(LineChart_Test, minMaxTest)
{
    LineChart chart1;
    QList<QDateTime> x1 = {qdt(1), qdt(5), qdt(-34), qdt(453)};
    QList<double> y1 = {5.6, 432, 234.5, -342.432};

    for (auto i = 0; i < 4; ++i)
    {
        chart1.addPoint(x1.at(i), y1.at(i));
    }

    EXPECT_EQ(chart1.xMin(), qdt(-34));
    EXPECT_EQ(chart1.xMax(), qdt(453));
    EXPECT_EQ(chart1.yMin(), -342.432);
    EXPECT_EQ(chart1.yMax(), 432);

    LineChart chart2;
    EXPECT_EQ(chart2.xMin(), QDateTime());
    EXPECT_EQ(chart2.xMax(), QDateTime());
    EXPECT_EQ(chart2.yMin(), 0);
    EXPECT_EQ(chart2.yMax(), 0);
}

TEST(LineChart_Test, minMaxTime)
{
    auto d1 = qdt(0);
    auto d2 = qdt(0);
    auto d3 = qdt(0);

    d1.setTime(QTime(12, 00, 01));
    d2.setTime(QTime(12, 00, 02));
    d3.setTime(QTime(12, 00, 03));

    LineChart c;
    c.addPoint(d1, 1);
    c.addPoint(d2, 1);
    c.addPoint(d3, 1);

    EXPECT_EQ(c.xMin(), d1);
    EXPECT_EQ(c.xMax(), d3);
}
