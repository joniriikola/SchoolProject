#include "basechartmodel.h"

BaseChartModel::BaseChartModel(QObject* parent) : QObject(parent)
{
}

void BaseChartModel::setTitle(const QString& title)
{
    m_title = title;
    emit titleChanged();
}

QString BaseChartModel::title() const
{
    return m_title;
}

void BaseChartModel::setAxisLabels(const QString& labelX, const QString& labelY)
{
    m_labelX = labelX;
    m_labelY = labelY;
    emit axisLabelsChanged();
}

QString BaseChartModel::labelX() const
{
    return m_labelX;
}

QString BaseChartModel::labelY() const
{
    return m_labelY;
}

void BaseChartModel::publish() const
{
    emit graphsChanged();
}

void BaseChartModel::setError(const QString& error)
{
    m_error = error;
    emit errorChanged();
}
