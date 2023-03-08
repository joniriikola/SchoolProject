#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "linechart.h"
#include "linechartmodel.h"

#include <QDebug>
#include <QRandomGenerator>

QDateTime qdt(int days)
{
    return QDateTime::currentDateTime().addDays(days);
}

TEST(LineChartModel_Test, addClearLengthTest)
{
    LineChartModel model;
    EXPECT_EQ(model.graphCount(), 0);
    LineChart::LineChartGraph graph;
    LineChart chart1;
    chart1.addPoint(QDateTime::currentDateTime(), 2);
    graph.lines.push_back(chart1);
    LineChart chart2;
    chart2.addPoint(QDateTime::currentDateTime(), 2);
    graph.lines.push_back(chart2);
    LineChart chart3;
    chart3.addPoint(QDateTime::currentDateTime(), 2);
    graph.lines.push_back(chart3);
    LineChart chart4;
    chart4.addPoint(QDateTime::currentDateTime(), 2);
    graph.lines.push_back(chart4);
    model.addGraph(graph);

    EXPECT_EQ(model.graphCount(), 4);
    model.clear();
    EXPECT_EQ(model.graphCount(), 0);
}

TEST(LineChartModel_Test, accessTest)
{
    LineChartModel model;

    LineChart chart1;
    chart1.setName("name1");
    QList<QDateTime> x1 = {qdt(1), qdt(5), qdt(-34), qdt(453)};
    QList<double> y1 = {5.6, 432, 234.5, -342.432};
    QList<QPointF> result1;
    for (auto i = 0; i < 4; ++i)
    {
        chart1.addPoint(x1.at(i), y1.at(i));
        result1.append(QPointF(x1.at(i).toMSecsSinceEpoch(), y1.at(i)));
    }

    LineChart::LineChartGraph graph;
    graph.lines.push_back(chart1);
    model.addGraph(graph);

    LineChart chart2;
    chart2.setName("name2");
    QList<QDateTime> x2 = {qdt(3), qdt(-5), qdt(321), qdt(-3253)};
    QList<double> y2 = {5, 445.213, -234.5, 12342.432};
    QList<QPointF> result2;
    for (auto i = 0; i < 4; ++i)
    {
        chart2.addPoint(x2.at(i), y2.at(i));
        result1.append(QPointF(x2.at(i).toMSecsSinceEpoch(), y2.at(i)));
    }

    graph.lines.push_back(chart2);
    model.addGraph(graph);
}

TEST(LineChartModel_Test, minMaxTest)
{
    LineChartModel model;

    LineChart::LineChartGraph graph;
    LineChart chart1;
    QList<QDateTime> x1 = {qdt(1), qdt(5), qdt(-34), qdt(1453)};
    QList<double> y1 = {5.6, 432, 234.5, -42.432};

    for (auto i = 0; i < 4; ++i)
    {
        chart1.addPoint(x1.at(i), y1.at(i));
    }

    graph.lines.push_back(chart1);
    model.addGraph(graph);

    LineChart chart2;
    QList<QDateTime> x2 = {qdt(3), qdt(-5), qdt(321), qdt(-3253)};
    QList<double> y2 = {5, 445.213, -234.5, 12342.432};

    for (auto i = 0; i < 4; ++i)
    {
        chart2.addPoint(x2.at(i), y2.at(i));
    }

    graph.lines.push_back(chart2);
    model.addGraph(graph);

    EXPECT_EQ(model.xAxisMax(), chart1.xMax());
    EXPECT_EQ(model.xAxisMin(), chart2.xMin());
    EXPECT_EQ(model.yAxisMax(), chart2.yMax());
    EXPECT_EQ(model.yAxisMin(), chart2.yMin());
}
