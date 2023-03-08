#ifndef FINGRIDCLIENT_H
#define FINGRIDCLIENT_H
#include "httpclient.h"
#include "linechart.h"
#include "piechartmodel.h"
#include <QDate>
#include <QDebug>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QObject>
#include <QString>

/**
 * @brief The FingridClient class fetches and parses electricity market and power system data from
 * Fingrid api https://data.fingrid.fi/en/
 */
class FingridClient : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief Response format for client. Allows error messages to be passed upstream.
     */
    struct Response
    {
        bool error = false;
        LineChart::LineChartGraph lineGraph;
        PieChartModel::PieChartGraph pieGraph;
        QString errorMessage;
    };

    /**
     * @brief Constructor
     * @param parent: Pointer to parent QObject.
     */
    explicit FingridClient(QObject* parent = nullptr);

    /**
     * @brief Fetches and parses electricity consumption and production forecast for next 24 hours.
     * @param production: Is production graph fetched and parsed to response.
     * @param consumption: Is consumption graph fetched and parsed to response.
     * @return Response: Parsed Response with lineGraph or error state and message
     */
    Response energyThroughputForecast24h(bool production = true, bool consuption = true);

    /**
     * @brief Fetches and parses energy production and consumption history for given time range.
     * @param startDate: Beginning of time range.
     * @param endDate: End of time range.
     * @param production: Is production graph fetched and parsed to response.
     * @param consumption: Is consumption graph fetched and parsed to response.
     * @return Response: Parsed Response with lineGraph or error state and message
     */
    Response energyThroughputHistory(const QDate& startDate,
            const QDate& endDate,
            bool production = true,
            bool consuption = true);

    /**
     * @brief Fetches and parses solar and wind electricity production forecast for next 24 hours.
     * @param wind: Is wind energy production graph fetched and parsed to response.
     * @param solar: Is solar energy produciton graph fetched and parsed to response.
     * @return Response: Parsed Response with lineGraph or error state and message.
     */
    Response renewableEnergyProductionForecast24h(bool wind = true, bool solar = true);

    /**
     * @brief Fetches and parses nuclear, hydro and wind power production history for given time range.
     * @param startDate: Beginning of time range.
     * @param endDate: End of time range.
     * @param nuclear: Is nuclear graph fetched and parsed to response.
     * @param hydro: Is hydro graph fetched and parsed to response.
     * @param wind: Is wind graph fetched and parsed to response.
     * @return Response: Parsed Response with lineGraph or error state and message.
     */
    Response energyProductionMethods(const QDate& startDate,
            const QDate& endDate,
            bool nuclear = true,
            bool hydro = true,
            bool wind = true);

    /**
     * @brief Fetches and parses pie chart from data fetched from renewableEnergyProductionForecast24h.
     * @param startDate: Beginning of time range.
     * @param endDate: End of time range.
     * @return Response: Parsed Response with pieGraph or error state and message.
     */
    Response energyProductionDistribution(const QDate& startDate, const QDate& endDate);

    /**
     * @brief Provides real time monitoring for electric grid frequency. This application fetches
     * data from api that is updated every 3 minutes.
     * @param previous: When previous == std::nullopt new LineChart::LineChartGraph is created and
     * populated with last ~20 minutes of frequency data else if api provides newer data than
     * previous contains, new data is appended to previous either way graph is returned in Response.
     * @return Response: Parsed Response with pieGraph or error state and message.
     */
    Response realTimeFrequency(std::optional<LineChart::LineChartGraph> previous);

    /**
     * @brief Provides real time monitoring for electricity consumption.
     * data from api that is updated every 3 minutes.
     * @param previous: When previous == std::nullopt new LineChart::LineChartGraph is created and
     * populated with last ~20 minutes of consumption data else if api provides newer data than
     * previous contains, new data is appended to previous either way graph is returned in Response.
     * @return Response: Parsed Response with pieGraph or error state and message.
     */
    Response realTimeConsumption(std::optional<LineChart::LineChartGraph> previous);

    /**
     * @brief Provides real time monitoring for electricity exrport/import.
     * data from api that is updated every 3 minutes.
     * @param previous: When previous == std::nullopt new LineChart::LineChartGraph is created and
     * populated with last ~20 minutes of exrport/import data else if api provides newer data than
     * previous contains, new data is appended to previous either way graph is returned in Response.
     * @return Response: Parsed Response with pieGraph or error state and message.
     */
    Response realTimeEnergyImport(std::optional<LineChart::LineChartGraph> previous);

private:
    /**
     * @brief combineQuery formulates api query.
     * @param id: api specific id for data set.
     * @param startDate: Beginning of time range.
     * @param endDate: End of time range.
     * @param event: Type of request (event or events).
     * @return QString: Parsed query.
     */
    QString combineQuery(const QString& id,
            const QDateTime& startTime,
            const QDateTime& endTime,
            const QString& event = "events");

    /**
     * @brief Parses json received from api to LineChart.
     * @param data: Json array received from api query.
     * @return LineChart: Parsed data.
     */
    LineChart parseData(const QJsonArray& data);

    /**
     * @brief Parses error message from json received from api ro error description.
     * @param data: Json array received from api query.
     * @return QString: Description of error
     */
    QString parseError(const QJsonDocument& data) const;

    /**
     * @brief Fetches data from real time apis. If no previous Graph is given, fetches values from
     * last 20 min Is previoud is given fetches realtime value and adds it to previous and returns
     * previous.
     * @param variableId: Api Variable Id.
     * @param lineName: Name of the line.
     * @param unit:  Unit of the line.
     * @param previous:  If not std::nullopt new value is added to this graph.
     * @return Response: Contains lineGraphs with last 20 minutes of values or with previoud graphs
     * with new value appended.
     */
    Response realTimeData(const QString& variableId,
            const QString& lineName,
            const QString& unit,
            std::optional<LineChart::LineChartGraph> previous);

    HTTPClient m_httpClient;
    const QString m_baseAdress = "https://api.fingrid.fi/v1/variable/"
                                 "%1/%2/json?start_time=%3Z&end_time=%4Z";
};

#endif // FINGRIDCLIENT_H
