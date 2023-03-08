#pragma once

#include "basechartmodel.h"
#include "linechart.h"

#include <QDebug>
#include <QLineSeries>

#include <QObject>
#include <QQmlEngine>

/**
 * @brief LineChartModel is used display LineChart::LineChartGraph in view.
 */
class LineChartModel : public BaseChartModel
{
    Q_OBJECT

    Q_PROPERTY(QVariant xAxisMax READ xAxisMax NOTIFY graphsChanged)
    Q_PROPERTY(QVariant xAxisMin READ xAxisMin NOTIFY graphsChanged)
    Q_PROPERTY(QVariant yAxisMax READ yAxisMax NOTIFY graphsChanged)
    Q_PROPERTY(QVariant yAxisMin READ yAxisMin NOTIFY graphsChanged)

public:
    /**
     * @brief Constructor.
     * @param parent: Pointer to parent QObject.
     */
    explicit LineChartModel(QObject* parent = nullptr);

    /**
     * @brief Adds graph to model and updates title and axis labels.
     * @param graph: LineChartGraph to be added.
     */
    void addGraph(const LineChart::LineChartGraph& graph);

    /**
     * @brief Returns currently held graph.
     * @return LineChartGraph: Current LineChartGraph.
     */
    LineChart::LineChartGraph getGraph() const;

    /**
     * @brief Removes graph and resets all attributes to default.
     */
    void clear() override;

    /**
     * @brief Returns how many lines currently held graph has.
     * @return quint64: Line count of currently held graph.
     */
    quint64 graphCount() const override;

    /**
     * @brief Transfer LineChart that is stored in currently held graph with given index to series
     * given as parameter.
     * @param series: Pointer to QLineSeries.
     * @param index: Index of LineChart in currently held graph.
     */
    Q_INVOKABLE void transferSeries(QtCharts::QLineSeries* series, int index);

    /**
     * @brief Returns maximum X value of any line in currently held graph.
     * @return QDateTime: Maximum value for X-axis.
     */
    QDateTime xAxisMax() const;

    /**
     * @brief Returns minimum X value of any line in currently held graph.
     * @return QDateTime: Minimum value for X-axis.
     */
    QDateTime xAxisMin() const;

    /**
     * @brief Returns maximum Y value of any line in currently held graph.
     * @return double: Maximum value for Y-axis.
     */
    double yAxisMax() const;

    /**
     * @brief Returns minimum Y value of any line in currently held graph.
     * @return double: Minimum value for Y-axis.
     */
    double yAxisMin() const;

private:
    LineChart::LineChartGraph m_graph;
};
