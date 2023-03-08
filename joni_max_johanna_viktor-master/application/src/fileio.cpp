#include "fileio.h"

FileIO::FileIO(QObject* parent) : QObject(parent)
{
    auto currentPath = QCoreApplication::applicationDirPath();

    m_datasetDir.setPath(currentPath + "/datasets/");
    if (!m_datasetDir.exists())
        m_datasetDir.mkpath(m_datasetDir.path());

    m_presetDir.setPath(currentPath + "/presets/");
    if (!m_presetDir.exists())
        m_presetDir.mkpath(m_presetDir.path());
}

bool FileIO::saveDataset(QString name, LineChart::LineChartGraph dataset)
{
    if (name.isEmpty())
        return false;

    QString fileName(m_datasetDir.path() + "/" + name);
    QFile file(fileName);

    if (!file.open(QIODevice::WriteOnly))
        return false;

    QJsonObject master;
    master.insert("title", dataset.title);
    master.insert("xLabel", dataset.xLabel);
    master.insert("yLabel", dataset.yLabel);

    QJsonArray lines;

    for (const auto& lineChart : dataset.lines)
    {
        QJsonObject lineObject;

        lineObject.insert("name", lineChart.name());
        QJsonArray pointsArray;
        for (const auto& point : lineChart.values())
        {
            QJsonObject pointsObject;
            pointsObject.insert("x", point.x());
            pointsObject.insert("y", point.y());
            pointsArray.append(pointsObject);
        }
        lineObject.insert("values", pointsArray);
        lines.append(lineObject);
    }
    master.insert("lines", lines);

    QJsonDocument jsonDoc;
    jsonDoc.setObject(master);
    file.write(jsonDoc.toJson(QJsonDocument::JsonFormat::Compact));
    emit newFileCreated();
    return true;
}

LineChart::LineChartGraph FileIO::readDataset(QString name)
{
    QFile file(m_datasetDir.path().append("/").append(name));
    file.open(QIODevice::ReadOnly);
    auto json = QJsonDocument::fromJson(file.readAll()).object();

    LineChart::LineChartGraph graph;
    graph.title = json.value("name").toString();
    graph.xLabel = json.value("xLabel").toString();
    graph.yLabel = json.value("yLabel").toString();

    auto lines = json.value("lines").toArray();

    for (const auto& element : lines)
    {
        LineChart line;
        line.setName(element.toObject().value("name").toString());
        for (const auto& points : element.toObject().value("values").toArray())
        {
            auto pointX = points.toObject().value("x").toDouble();
            auto pointY = points.toObject().value("y").toDouble();
            line.addPoint(QDateTime::fromMSecsSinceEpoch(pointX), pointY);
        }
        graph.lines.push_back(line);
    }
    return graph;
}

QStringList FileIO::savedDatasets()
{
    return m_datasetDir.entryList(QStringList(), QDir::Files);
}

bool FileIO::savePreset(const QString& name, const PresetController::Preset& preset)
{
    QString fileName(m_presetDir.path() + "/" + name);
    QFile file(fileName);

    if (!file.open(QIODevice::WriteOnly))
        return false;

    auto stateToJson = [](const auto& state) -> QJsonObject {
        QJsonObject json;
        json.insert("chartType", state.chartType);
        json.insert("location", state.location);
        json.insert("fileName", state.fileName);
        json.insert("checkBox0", state.checkBox0);
        json.insert("checkBox1", state.checkBox1);
        json.insert("checkBox2", state.checkBox2);
        return json;
    };

    QJsonObject left = stateToJson(preset.left);
    QJsonObject right = stateToJson(preset.right);

    QJsonObject json;
    json.insert("left", left);
    json.insert("right", right);

    file.write(QJsonDocument(json).toJson(QJsonDocument::JsonFormat::Compact));
    emit newFileCreated();
    return true;
}

PresetController::Preset FileIO::readPreset(const QString& name)
{
    QFile file(m_presetDir.path().append("/").append(name));
    file.open(QIODevice::ReadOnly);
    auto json = QJsonDocument::fromJson(file.readAll()).object();

    auto jsonToPreset = [](const QJsonObject& json) -> PresetController::UIControllerState {
        PresetController::UIControllerState state;
        state.chartType = json.value("chartType").toString();
        state.location = json.value("location").toString();
        state.fileName = json.value("fileName").toString();
        state.checkBox0 = json.value("checkBox0").toBool();
        state.checkBox1 = json.value("checkBox1").toBool();
        state.checkBox2 = json.value("checkBox2").toBool();
        return state;
    };

    auto left = jsonToPreset(json.value("left").toObject());
    auto right = jsonToPreset(json.value("right").toObject());
    return PresetController::Preset{left, right};
}

QStringList FileIO::savedPresets()
{
    return m_presetDir.entryList(QStringList(), QDir::Files);
}
