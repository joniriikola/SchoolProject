#pragma once

#include <QObject>

/**
 * @brief BaseChartModel is a implementation of common features of for different chart models.
 */
class BaseChartModel : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString title READ title NOTIFY titleChanged)
    Q_PROPERTY(QString labelX READ labelX NOTIFY axisLabelsChanged)
    Q_PROPERTY(QString labelY READ labelY NOTIFY axisLabelsChanged)
    Q_PROPERTY(QString error MEMBER m_error NOTIFY errorChanged)
    Q_PROPERTY(quint64 graphCount READ graphCount NOTIFY graphsChanged)

public:
    /**
     * @brief Constructor.
     * @param parent: Pointer to parent QObject.
     */
    explicit BaseChartModel(QObject* parent = nullptr);

    /**
     * @brief Sets title to chart model and emits an signal of title changed.
     */
    void setTitle(const QString& title);

    /**
     * @brief returns title of chart model
     * @return QString: Title.
     */
    QString title() const;

    /**
     * @brief Sets axis labels.
     * @param LabelX: X axis label.
     * @param labelY: Y axis label.
     */
    void setAxisLabels(const QString& labelX, const QString& labelY);

    /**
     * @brief Returns x axis label.
     * @return QString: X axis label.
     */
    QString labelX() const;

    /**
     * @brief Return y axis label.
     * @return QString: Y axis label.
     */
    QString labelY() const;

    /**
     * @brief Emits a signal that models internal state is ready for displaying in view.
     */
    void publish() const;

    /**
     * @brief Sets model to be in error mode and adds a error description.
     * @param error:  Error discription.
     */
    void setError(const QString& error);

    /**
     * @brief Pure virtual function that shall returns how many graphs model has.
     */
    virtual quint64 graphCount() const = 0;

    /**
     * @brief Pure virtual function that shall clears all graphs and sets error state to false.
     */
    virtual void clear() = 0;

signals:
    void titleChanged() const;
    void axisLabelsChanged() const;
    void graphsChanged() const;
    void errorChanged() const;

private:
    QString m_title;
    QString m_labelX;
    QString m_labelY;
    QString m_error;
};
