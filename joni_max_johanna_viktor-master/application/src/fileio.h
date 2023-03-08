#pragma once

#include "linechart.h"
#include "presetcontroller.h"

#include <QApplication>
#include <QDateTime>
#include <QDebug>
#include <QDir>
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>
#include <QJsonValue>
#include <QObject>
#include <QString>

/**
 * @brief FileIO provides reading and writing data types to and from file.
 * File format is JSON and class also provides list of all saved files.
 */
class FileIO : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief Constructor
     * @param parent: Pointer to parent QObject.
     */
    explicit FileIO(QObject* parent = nullptr);

    /**
     * @brief Saves a dataset into a file.
     * @param name: Name for the saved file.
     * @param dataset: Data for the saved file.
     * @return bool: True if saving a dateset was successful, False if it couldn't be saved.
     */
    bool saveDataset(QString name, LineChart::LineChartGraph dataset);

    /**
     * @brief Reads dataset with given name from a file.
     * @param name: Name of the dataset.
     * @return LineChart::LineChartGraph: Graph parsed from a file.
     */
    LineChart::LineChartGraph readDataset(QString name);

    /**
     * @brief Returns all saved dataset names.
     * @return QStringList: List of names.
     */
    QStringList savedDatasets();

    /**
     * @brief Saves given preset with given name.
     * @param name: Name of the preset.
     * @param preset: Preset to save.
     * @return bool: True if succeess else false.
     */
    bool savePreset(const QString& name, const PresetController::Preset& preset);

    /**
     * @brief Returns a saved preset with given name.
     * @param name: Name of the preset.
     * @return PresetController::Preset: Preset parsed from file.
     */
    PresetController::Preset readPreset(const QString& name);

    /**
     * @brief Returns all saved preset names.
     * @return QStringList: List of names.
     */
    QStringList savedPresets();

signals:
    void newFileCreated();

private:
    QDir m_datasetDir;
    QDir m_presetDir;
};
