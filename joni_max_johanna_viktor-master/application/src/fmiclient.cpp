#include "fmiclient.h"

#include <xml2json.hpp>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

FmiClient::FmiClient(QObject* parent) : QObject(parent)
{
}

FmiClient::Response FmiClient::weatherForecast24h(const QString& location,
        bool temperature,
        bool windSpeed)
{
    QString query = get24hWeatherForecastQuery(location);

    auto response = m_httpclient.get(query);
    auto json = QJsonDocument::fromJson(QByteArray::fromStdString(xml2json(response.data)));

    if (response.error)
    {
        return Response{true, {}, parseErrorMessage(json)};
    }

    QJsonObject forecastObject = json["FeatureCollection"].toObject();
    QJsonArray forecastArray = forecastObject["member"].toArray();

    QStringList keys;
    QStringList names;
    if (temperature)
    {
        keys.append("temperature");
        names.append("Temperature (°C)");
    }
    if (windSpeed)
    {
        keys.append("windspeedms");
        names.append("Wind speed (m/s)");
    }

    return Response{false, createWeatherCharts(forecastArray, keys, names), ""};
}

// Currently the function gets data from startDate's 00:00:00
// to endDate's 23:59:59
FmiClient::Response FmiClient::weatherHistory(const QDate& startDate,
        const QDate& endDate,
        const QString& location,
        bool temperature,
        bool windSpeed,
        bool cloudiness)
{
    QString query = getWeatherHistoryQuery(startDate, endDate, location);

    auto response = m_httpclient.get(query);
    auto json = QJsonDocument::fromJson(QByteArray::fromStdString(xml2json(response.data)));
    if (response.error)
    {
        return Response{true, {}, parseErrorMessage(json)};
    }

    QJsonObject weatherObject = json["FeatureCollection"].toObject();
    QJsonArray weatherArray = weatherObject["member"].toArray();

    QStringList keys;
    QStringList names;
    if (temperature)
    {
        keys.append("t2m");
        names.append("Temperature (°C)");
    }
    if (windSpeed)
    {
        keys.append("ws_10min");
        names.append("Wind speed (m/s)");
    }
    if (cloudiness)
    {
        keys.append("n_man");
        names.append("Cloudiness (1-8)");
    }

    return Response{false, createWeatherCharts(weatherArray, keys, names), ""};
}

FmiClient::Response FmiClient::monthlyTemperatureAverages(const unsigned int month,
        const unsigned int year,
        const QString& location,
        bool avg,
        bool min,
        bool max)
{
    QString query = getMonthlyTempStatsQuery(month, year, location);

    auto response = m_httpclient.get(query);
    auto json = QJsonDocument::fromJson(QByteArray::fromStdString(xml2json(response.data)));

    if (response.error)
    {
        return Response{true, {}, parseErrorMessage(json)};
    }

    QJsonObject tempObject = json["FeatureCollection"].toObject();
    QJsonArray tempArray = tempObject["member"].toArray();

    QStringList keys;
    QStringList names;
    if (avg)
    {
        keys.append("TA_PT1H_AVG");
        names.append("Average");
    }
    if (min)
    {
        keys.append("TA_PT1H_MAX");
        names.append("Maximum");
    }
    if (max)
    {
        keys.append("TA_PT1H_MIN");
        names.append("Minimum");
    }

    LineChart::LineChartGraph charts = createWeatherCharts(tempArray, keys, names);
    charts.yLabel = "°C";
    return Response{false, charts, ""};
}

QString FmiClient::get24hWeatherForecastQuery(const QString& location)
{
    QString URLtemplate = "?request=getFeature&version=2.0.0&storedquery_id="
                          "fmi::forecast::hirlam::surface::point::simple"
                          "&place=%1&timestep=%2"
                          "&starttime=%3Z&endtime=%4Z"
                          "&parameters=temperature,windspeedms";

    const QDateTime startTime = QDateTime::currentDateTime();
    const QDateTime endTime = startTime.addDays(1);

    QString query = m_apiaddress
            + URLtemplate.arg(location)
                      .arg(m_timestep)
                      .arg(startTime.toString(Qt::DateFormat::ISODate))
                      .arg(endTime.toString(Qt::DateFormat::ISODate));

    return query;
}

QString FmiClient::getWeatherHistoryQuery(const QDate& startDate,
        const QDate& endDate,
        const QString& location)
{
    QString URLtemplate = "?request=getFeature&version=2.0.0&storedquery_id="
                          "fmi::observations::weather::simple&place=%1&timestep=%2"
                          "&starttime=%3T00:00:00Z&endtime=%4T23:59:59Z"
                          "&parameters=t2m,ws_10min,n_man";

    QString query = m_apiaddress
            + URLtemplate.arg(location)
                      .arg(m_timestep)
                      .arg(startDate.toString(Qt::DateFormat::ISODate))
                      .arg(endDate.toString(Qt::DateFormat::ISODate));

    return query;
}

QString FmiClient::getMonthlyTempStatsQuery(const unsigned int month,
        const unsigned int year,
        const QString& location)

{
    QString URLtemplate = "?request=getFeature&version=2.0.0&storedquery_id="
                          "fmi::observations::weather::daily::simple&place=%1&timestep=1440"
                          "&starttime=%2T00:00:00Z&endtime=%3T23:59:59Z"
                          "&parameters=TA_PT1H_AVG,TA_PT1H_MAX,TA_PT1H_MIN";

    QDate startDate = QDate(year, month, 1);
    QDate endDate = QDate(year, month, startDate.daysInMonth());

    QString query = m_apiaddress
            + URLtemplate.arg(location)
                      .arg(startDate.toString(Qt::DateFormat::ISODate))
                      .arg(endDate.toString(Qt::DateFormat::ISODate));

    return query;
}

LineChart::LineChartGraph FmiClient::createWeatherCharts(const QJsonArray& array,
        const QStringList& parameters,
        const QStringList& chartNames)
{
    Q_ASSERT(parameters.length() == chartNames.length());

    std::vector<LineChart> charts;

    for (auto i = 0; i < parameters.length(); ++i)
    {
        LineChart line;
        line.setName(chartNames.at(i));
        charts.push_back(line);
    }

    for (const auto& element : array)
    {
        QJsonObject parameter = element.toObject().value("BsWfsElement").toObject();
        QJsonValue parameterName = parameter["ParameterName"];
        double parameterValue = parameter["ParameterValue"].toString().toDouble();
        QDateTime parameterTime = QDateTime::fromString(
                parameter["Time"].toString(), Qt::DateFormat::ISODate);

        for (auto i = 0; i < parameters.length(); ++i)
        {
            if (parameters.at(i) == parameterName.toString() && !qIsNaN(parameterValue))
            {
                charts[i].addPoint(parameterTime, parameterValue);
            }
        }
    }

    LineChart::LineChartGraph graph;
    for (const auto& chart : charts)
    {
        graph.addLine(chart);
    }

    return graph;
}

QString FmiClient::parseErrorMessage(const QJsonDocument& message) const
{
    return message.object()
            .value("ExceptionReport")
            .toObject()
            .value("Exception")
            .toObject()
            .value("ExceptionText")
            .toArray()
            .first()
            .toString();
}
