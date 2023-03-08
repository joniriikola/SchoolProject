#pragma once

#include "basechartmodel.h"
#include <QObject>
#include <QPieSeries>

/**
 * @brief The PieChart is used display a pie chart in a view.
 */
class PieChartModel : public BaseChartModel
{
    Q_OBJECT

public:
    /**
     * @brief Abstraction for pie slice.
     */
    struct Slice
    {
        QString name;
        double value;
    };

    /**
     * @brief Abstraction for pie graph.
     */
    struct PieChartGraph
    {
        QString title;
        QList<Slice> slices;
    };

    /**
     * @brief Constructor.
     * @param parent: Pointer to parent QObject.
     */
    explicit PieChartModel(QObject* parent = nullptr);

    /**
     * @brief adds a pie slice to pie chart.
     * @param Slice: Slice to be added.
     */
    void addSlice(const Slice& slice);

    /**
     * @brief returns list of Slices in pie chart.
     */
    QList<Slice> slices() const;

    /**
     * @brief transfers contained pieslices to series given ad parameter.
     * @param series: Pointer to a QPieSeries to be filled.
     */
    Q_INVOKABLE void transferSeries(QtCharts::QPieSeries* series);

    /**
     * @brief Returns the slice count of the model.
     * @return quint64: Slice count of the model.
     */
    quint64 graphCount() const override;

    /**
     * @brief Removes all slices and resets all parameters to default.
     */
    void clear() override;

private:
    QList<Slice> m_slices;
};
