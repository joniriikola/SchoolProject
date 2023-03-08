#pragma once

#include <QDateTime>
#include <QDebug>
#include <QList>
#include <QObject>
#include <QPointF>

/**
 * @brief LineChart is a abstraction for 2d line chart that uses timeline x axis and real y axis.
 * Internally x axis values are stored as milliseconds since epoch.
 */
class LineChart : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief LineChartGraph is a abstraction for 2d graph with multiple line charts.
     */
    struct LineChartGraph
    {
        QString title;
        QString xLabel;
        QString yLabel;
        std::vector<LineChart> lines;

        /**
         * @brief Adds line to graph if given line is not empty.
         * @param line: LineChart to be added.
         */
        void addLine(const LineChart& line)
        {
            if (line.length() != 0)
            {
                lines.push_back(line);
            }
        }
    };

    /**
     * @brief Constructor.
     * @param parent: Pointer to parent QObject.
     */
    explicit LineChart(QObject* parent = nullptr);

    /**
     * @brief Copy Constructor.
     * @param obj: Object to copy.
     */
    LineChart(const LineChart& obj);

    /**
     * @brief Copy Constructor.
     * @param obj: Object to copy.
     */
    LineChart& operator=(const LineChart& obj);

    /**
     * @brief Sets name to the chart.
     * @param name: name to be set.
     */
    void setName(const QString& name);

    /**
     * @brief Returns the name of the chart.
     * @return QString: Name of the linechart.
     */
    QString name() const;

    /**
     * @brief Adds a point to LineChart.
     * @param x: X value of the point.
     * @param y: Y value of the point.
     */
    void addPoint(const QDateTime& x, const double& y);

    /**
     * @brief Returns largest X value held by linechart.
     * @return QDateTime: Maximum X value.
     */
    QDateTime xMax() const;

    /**
     * @brief Returns smalles X value held by linechart.
     * @return QDateTime: Minimum X Value.
     */
    QDateTime xMin() const;

    /**
     * @brief Returns largest Y value held by linechart.
     * @return QDateTime: Maximum Y value.
     */
    double yMax() const;

    /**
     * @brief Returns smalles Y value held by linechart.
     * @return double: Minimum Y Value.
     */
    double yMin() const;

    /**
     * @brief Returns number of points held by linechart.
     * @return quint64: Number of points.
     */
    quint64 length() const;

    /**
     * @brief Returns list of points. Points are in format QPointF<MsecSinceEpoch, value>.
     * @return QList<QPointF>>: List of added points.
     */
    QList<QPointF> values() const;

private:
    QString m_name;
    QList<QPointF> m_values;
};
