#include "piechartmodel.h"

PieChartModel::PieChartModel(QObject* parent) : BaseChartModel(parent)
{
}

void PieChartModel::addSlice(const Slice& slice)
{
    m_slices.append(slice);
}

QList<PieChartModel::Slice> PieChartModel::slices() const
{
    return m_slices;
}

void PieChartModel::transferSeries(QtCharts::QPieSeries* series)
{
    for (const auto& slice : m_slices)
    {
        series->append(slice.name, slice.value);
    }
    series->setUseOpenGL();
}

quint64 PieChartModel::graphCount() const
{
    return m_slices.size();
}

void PieChartModel::clear()
{
    m_slices.clear();
    setError("");
}
