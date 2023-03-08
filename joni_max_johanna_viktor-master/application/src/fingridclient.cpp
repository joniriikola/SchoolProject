#include "fingridclient.h"

FingridClient::FingridClient(QObject* parent) : QObject(parent)
{
    m_httpClient.addHeader("x-api-key", "Bgjr7m4AQe1REFNmhoje25w1lcevKfza8ySp8XP4");
}

FingridClient::Response FingridClient::energyThroughputForecast24h(bool production, bool consuption)
{
    QDateTime startTime = QDateTime::currentDateTime();
    QDateTime endTime = startTime.addDays(1);

    LineChart::LineChartGraph graph;
    graph.yLabel = "MW/h";

    if (production)
    {
        auto productionQuery = combineQuery("242", startTime, endTime);
        auto productionResponse = m_httpClient.get(productionQuery);
        auto productionJson = QJsonDocument::fromJson(productionResponse.data);
        if (productionResponse.error)
            return Response{true, {}, {}, parseError(productionJson)};
        auto productionChart = parseData(productionJson.array());
        productionChart.setName("Tentative Production");
        graph.addLine(productionChart);
    }
    if (consuption)
    {
        auto consumptionQuery = combineQuery("166", startTime, endTime);
        auto consumptionResponse = m_httpClient.get(consumptionQuery);
        auto consumptionJson = QJsonDocument::fromJson(consumptionResponse.data);
        if (consumptionResponse.error)
            return Response{true, {}, {}, parseError(consumptionJson)};
        auto consuptionChart = parseData(consumptionJson.array());
        consuptionChart.setName("Consumption");
        graph.addLine(consuptionChart);
    }

    return Response{false, graph, {}, ""};
}

FingridClient::Response FingridClient::energyThroughputHistory(const QDate& startDate,
        const QDate& endDate,
        bool production,
        bool consuption)
{
    QDateTime startTime = QDateTime(startDate, QTime(00, 01));
    QDateTime endTime = QDateTime(endDate, QTime(23, 59));

    LineChart::LineChartGraph graph;
    graph.yLabel = "MW/h";

    if (production)
    {
        auto productionQuery = combineQuery("74", startTime, endTime);
        auto productionResponse = m_httpClient.get(productionQuery);
        auto productionJson = QJsonDocument::fromJson(productionResponse.data);
        if (productionResponse.error)
            return Response{true, {}, {}, parseError(productionJson)};
        auto productionChart = parseData(productionJson.array());
        productionChart.setName("Production");
        graph.addLine(productionChart);
    }
    if (consuption)
    {
        auto consumptionQuery = combineQuery("124", startTime, endTime);
        auto consumptionResponse = m_httpClient.get(consumptionQuery);
        auto consumptionJson = QJsonDocument::fromJson(consumptionResponse.data);
        if (consumptionResponse.error)
            return Response{true, {}, {}, parseError(consumptionJson)};
        auto consumptionChart = parseData(consumptionJson.array());
        consumptionChart.setName("Consumption");
        graph.addLine(consumptionChart);
    }

    return Response{false, graph, {}, ""};
}

FingridClient::Response FingridClient::renewableEnergyProductionForecast24h(bool wind, bool solar)
{
    QDateTime startTime = QDateTime::currentDateTime();
    QDateTime endTime = startTime.addDays(1);

    LineChart::LineChartGraph graph;
    graph.yLabel = "MW/h";

    if (wind)
    {
        auto windQuery = combineQuery("245", startTime, endTime);
        auto windResponse = m_httpClient.get(windQuery);
        auto windJson = QJsonDocument::fromJson(windResponse.data);
        if (windResponse.error)
            return Response{true, {}, {}, parseError(windJson)};
        auto windPower = parseData(windJson.array());
        windPower.setName("Wind");
        graph.addLine(windPower);
    }
    if (solar)
    {
        auto solarQuery = combineQuery("248", startTime, endTime);
        auto solarResponse = m_httpClient.get(solarQuery);
        auto solarJson = QJsonDocument::fromJson(solarResponse.data);
        if (solarResponse.error)
            return Response{true, {}, {}, parseError(solarJson)};
        auto solarPower = parseData(solarJson.array());
        solarPower.setName("Solar");
        graph.addLine(solarPower);
    }

    return Response{false, graph, {}, ""};
}

FingridClient::Response FingridClient::energyProductionMethods(const QDate& startDate,
        const QDate& endDate,
        bool nuclear,
        bool hydro,
        bool wind)
{
    QDateTime startTime = QDateTime(startDate, QTime(00, 01));
    QDateTime endTime = QDateTime(endDate, QTime(23, 59));

    LineChart::LineChartGraph graph;
    graph.yLabel = "MW/h";

    if (nuclear)
    {
        auto nuclearQuery = combineQuery("188", startTime, endTime);
        auto nuclearResponse = m_httpClient.get(nuclearQuery);
        auto nuclearJson = QJsonDocument::fromJson(nuclearResponse.data);
        if (nuclearResponse.error)
            return Response{true, {}, {}, parseError(nuclearJson)};
        auto nuclearChart = parseData(nuclearJson.array());
        nuclearChart.setName("Nuclear");
        graph.addLine(nuclearChart);
    }
    if (hydro)
    {
        auto hydroQuery = combineQuery("191", startTime, endTime);
        auto hydroResponse = m_httpClient.get(hydroQuery);
        auto hydroJson = QJsonDocument::fromJson(hydroResponse.data);
        if (hydroResponse.error)
            return Response{true, {}, {}, parseError(hydroJson)};
        auto hydroChart = parseData(hydroJson.array());
        hydroChart.setName("Hydro");
        graph.addLine(hydroChart);
    }
    if (wind)
    {
        auto windQuery = combineQuery("75", startTime, endTime);
        auto windResponse = m_httpClient.get(windQuery);
        auto windJson = QJsonDocument::fromJson(windResponse.data);
        if (windResponse.error)
            return Response{true, {}, {}, parseError(windJson)};
        auto windChart = parseData(windJson.array());
        windChart.setName("Wind");
        graph.addLine(windChart);
    }

    return Response{false, graph, {}, ""};
}

FingridClient::Response FingridClient::energyProductionDistribution(const QDate& startDate,
        const QDate& endDate)
{
    auto data = energyProductionMethods(startDate, endDate);

    if (data.error)
    {
        return data;
    }

    PieChartModel::PieChartGraph graph;

    for (auto& line : data.lineGraph.lines)
    {
        if (line.values().size() == 0)
        {
            continue;
        }

        PieChartModel::Slice slice;

        const auto& values = line.values();
        for (const auto& value : values)
        {
            slice.value += value.y();
        }

        slice.value = slice.value / line.values().size();
        slice.name = line.name();
        graph.slices.append(slice);
    }

    return Response{false, {}, graph, ""};
}

FingridClient::Response FingridClient::realTimeFrequency(
        std::optional<LineChart::LineChartGraph> previous)
{
    return realTimeData("177", "Frequency", "HZ", previous);
}

FingridClient::Response FingridClient::realTimeConsumption(
        std::optional<LineChart::LineChartGraph> previous)
{
    return realTimeData("193", "Consumption", "MW", previous);
}

FingridClient::Response FingridClient::realTimeEnergyImport(
        std::optional<LineChart::LineChartGraph> previous)
{
    return realTimeData("194", "Import/Export", "MW", previous);
}

QString FingridClient::combineQuery(const QString& id,
        const QDateTime& startTime,
        const QDateTime& endTime,
        const QString& event)
{
    const QString query = m_baseAdress.arg(id)
                                  .arg(event)
                                  .arg(startTime.toString(Qt::DateFormat::ISODate))
                                  .arg(endTime.toString(Qt::DateFormat::ISODate));

    return query;
}

LineChart FingridClient::parseData(const QJsonArray& data)
{
    QJsonArray array = data;
    LineChart lineChart;
    QDateTime timeObject;
    for (const auto& element : array)
    {
        QJsonObject object = element.toObject();

        auto value = object.value("value").toDouble();
        auto time = object.value("start_time").toString();

        timeObject = QDateTime::fromString(time, Qt::ISODate);
        lineChart.addPoint(timeObject, value);
    }

    return lineChart;
}

QString FingridClient::parseError(const QJsonDocument& error) const
{
    if (!error.array().first().toString().isEmpty())
        return error.array().first().toString();
    else if (!error.object().value("message").toString().isEmpty())
        return error.object().value("message").toString();
    return "";
}

FingridClient::Response FingridClient::realTimeData(const QString& variableId,
        const QString& lineName,
        const QString& unit,
        std::optional<LineChart::LineChartGraph> previous)
{
    if (!previous.has_value())
    {
        LineChart::LineChartGraph graph;
        graph.yLabel = unit;

        auto query = combineQuery(variableId,
                QDateTime::currentDateTime().addSecs(-12000),
                QDateTime::currentDateTime());

        auto response = m_httpClient.get(query);
        auto json = QJsonDocument::fromJson(response.data);
        if (response.error)
            return Response{true, {}, {}, "Error in real time data acquisition"};
        auto chart = parseData(json.array());
        chart.setName(lineName);
        graph.addLine(chart);
        return Response{false, graph, {}, ""};
    }

    Q_ASSERT(previous.value().lines.size() == 1);

    auto frequencyQuery = combineQuery(
            variableId, QDateTime::currentDateTime(), QDateTime::currentDateTime(), "event");
    auto frequencyResponse = m_httpClient.get(frequencyQuery);
    auto frequencyJson = QJsonDocument::fromJson(frequencyResponse.data);
    if (frequencyResponse.error)
        return Response{true, {}, {}, "Error in real time data acquisition"};

    auto time = QDateTime::fromString(
            frequencyJson.object().value("start_time").toString(), Qt::ISODate);
    auto value = frequencyJson.object().value("value").toDouble();

    if (time.toMSecsSinceEpoch() > previous.value().lines.at(0).values().back().x())
        previous.value().lines.at(0).addPoint(time, value);

    return Response{false, previous.value(), {}, ""};
}
