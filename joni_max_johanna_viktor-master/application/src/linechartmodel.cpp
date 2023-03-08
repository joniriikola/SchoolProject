#include "linechartmodel.h"

LineChartModel::LineChartModel(QObject* parent) : BaseChartModel(parent)
{
}

void LineChartModel::addGraph(const LineChart::LineChartGraph& graph)
{
    m_graph = graph;
    setTitle(graph.title);
    setAxisLabels(graph.xLabel, graph.yLabel);
}

LineChart::LineChartGraph LineChartModel::getGraph() const
{
    return m_graph;
}

void LineChartModel::clear()
{
    m_graph = {};
    setError("");
}

quint64 LineChartModel::graphCount() const
{
    return m_graph.lines.size();
}

QDateTime LineChartModel::xAxisMax() const
{
    auto& maxLine = *std::max_element(m_graph.lines.begin(),
            m_graph.lines.end(),
            [](const LineChart& a, const LineChart& b) { return a.xMax() < b.xMax(); });
    return m_graph.lines.empty() ? QDateTime() : maxLine.xMax();
}

QDateTime LineChartModel::xAxisMin() const
{
    auto& minLine = *std::max_element(m_graph.lines.begin(),
            m_graph.lines.end(),
            [](const LineChart& a, const LineChart& b) { return a.xMin() > b.xMin(); });
    return m_graph.lines.empty() ? QDateTime() : minLine.xMin();
}

double LineChartModel::yAxisMax() const
{
    auto& maxLine = *std::max_element(m_graph.lines.begin(),
            m_graph.lines.end(),
            [](const LineChart& a, const LineChart& b) { return a.yMax() < b.yMax(); });
    return m_graph.lines.empty() ? 0 : maxLine.yMax();
}

double LineChartModel::yAxisMin() const
{
    auto& minLine = *std::max_element(m_graph.lines.begin(),
            m_graph.lines.end(),
            [](const LineChart& a, const LineChart& b) { return a.yMin() > b.yMin(); });
    return m_graph.lines.empty() ? 0 : minLine.yMin();
}

void LineChartModel::transferSeries(QtCharts::QLineSeries* series, int index)
{
    series->blockSignals(true); // To stop chart view from refreshing between each point added
    series->append(m_graph.lines.at(index).values());
    series->blockSignals(false);
    emit series->pointsReplaced();
    series->setName(m_graph.lines.at(index).name());
    series->setUseOpenGL();
}
