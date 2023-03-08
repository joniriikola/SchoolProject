#include "linechart.h"

LineChart::LineChart(QObject* parent) : QObject(parent)
{
}

LineChart::LineChart(const LineChart& obj) : QObject(nullptr)
{
    m_values = obj.values();
    m_name = obj.name();
}

LineChart& LineChart::operator=(const LineChart& obj)
{
    m_values = obj.values();
    m_name = obj.name();
    return *this;
}

void LineChart::setName(const QString& name)
{
    m_name = name;
}

QString LineChart::name() const
{
    return m_name;
}

void LineChart::addPoint(const QDateTime& x, const double& y)
{
    m_values.append(QPointF(x.toMSecsSinceEpoch(), y));
}

QList<QPointF> LineChart::values() const
{
    return m_values;
}

QDateTime LineChart::xMax() const
{
    auto& max = *std::max_element(m_values.begin(),
            m_values.end(),
            [](const QPointF& a, const QPointF& b) { return a.x() < b.x(); });
    return m_values.empty() ? QDateTime() : QDateTime::fromMSecsSinceEpoch(max.x());
}

QDateTime LineChart::xMin() const
{
    auto& min = *std::min_element(m_values.begin(),
            m_values.end(),
            [](const QPointF& a, const QPointF& b) { return a.x() < b.x(); });
    return m_values.empty() ? QDateTime() : QDateTime::fromMSecsSinceEpoch(min.x());
}

double LineChart::yMax() const
{
    auto& max = *std::max_element(m_values.begin(),
            m_values.end(),
            [](const QPointF& a, const QPointF& b) { return a.y() < b.y(); });
    return m_values.empty() ? 0 : max.y();
}

double LineChart::yMin() const
{
    auto& min = *std::min_element(m_values.begin(),
            m_values.end(),
            [](const QPointF& a, const QPointF& b) { return a.y() < b.y(); });
    return m_values.empty() ? 0 : min.y();
}

quint64 LineChart::length() const
{
    return m_values.length();
}
