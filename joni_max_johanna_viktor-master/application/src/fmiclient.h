#ifndef FMIAPI_H
#define FMIAPI_H

#include "httpclient.h"
#include "linechart.h"
#include <QObject>

/**
 * @brief The FmiClient class fetches and parses weather data from The Finnish Meteorological
 * Institute api https://en.ilmatieteenlaitos.fi/open-data-manual
 */
class FmiClient : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief Response format for client. Allows error messages to be passed upstream.
     */
    struct Response
    {
        bool error;
        LineChart::LineChartGraph graph;
        QString errorMessage;
    };

    /**
     * @brief Constructor
     * @param parent: Pointer to parent QObject.
     */
    explicit FmiClient(QObject* parent = nullptr);

    /**
     * @brief Fetches and parses temperature and wind speed forecast for next 24 hours.
     * @param location: Location of queried forecast.
     * @param temperature: Is temperature graph fetched and parsed to response.
     * @param windSpeed: Is windSpeed graph fetched and parsed to response.
     * @return Response: Response with Parsed lineGraph or error state and message.
     */
    Response weatherForecast24h(const QString& location,
            bool temperature = true,
            bool windSpeed = true);

    /**
     * @brief Fetches and parses temperature, wind speed and cloudiness history for given time range.
     * @param start: Start date of the time range.
     * @param end: End date of the time range.
     * @param location: Location of queried forecast.
     * @param temperature: Is temperature graph fetched and parsed to response.
     * @param windSpeed: Is windSpeed graph fetched and parsed to response.
     * @param cloudiness: Is cloudiness graph fetched and parsed to response.
     * @return Response: Response with Parsed lineGraph or error state and message.
     */
    Response weatherHistory(const QDate& start,
            const QDate& end,
            const QString& location,
            bool temperature = true,
            bool windSpeed = true,
            bool cloudiness = true);

    /**
     * @brief Fetches and parses min, max and avg temperature for given month.
     * @param month: Month.
     * @param year: Year.
     * @param location: Location of queried forecast.
     * @param avg: Is avg graph fetched and parsed to response.
     * @param min: Is min graph fetched and parsed to response.
     * @param max: Is max graph fetched and parsed to response.
     * @return Response: Response with Parsed lineGraph or error state and message.
     */
    Response monthlyTemperatureAverages(const unsigned int month,
            const unsigned int year,
            const QString& location,
            bool avg = true,
            bool min = true,
            bool max = true);

private:
    HTTPClient m_httpclient;
    const unsigned int m_timestep = 60;
    const QString m_apiaddress = "https://opendata.fmi.fi/wfs";

    /**
     * @brief Parses query string for weather forecast.
     * @param location: Name of the city/town.
     * @return QString: Query.
     */
    QString get24hWeatherForecastQuery(const QString& location);

    /**
     * @brief Parses query string for weather history.
     * @param startDate: Start of time range.
     * @param endDate: End of timerange.
     * @param location: Name of the city/town.
     * @return QString: Query.
     */
    QString getWeatherHistoryQuery(const QDate& startDate,
            const QDate& endDate,
            const QString& location);

    /**
     * @brief Parses query string for monthly temperature query.
     * @param month: Month of query.
     * @param year:  Year of query.
     * @param location: Name of the city/town.
     * @return QString: Query.
     */
    QString getMonthlyTempStatsQuery(const unsigned int month,
            const unsigned int year,
            const QString& location);

    /**
     * @brief Parses json received from api in to LineChart::LineChartGraph. Takes lists of
     * parametes and chart names as parameter. These lists must have same size. Each element in
     * parameters and lineNames describe one  chart to be parsed. Charts are added to return Graph
     * in same order as they are defined in parameter and chartNames lists.
     * @param array: a json array received from api.
     * @param parameters: List of search parameter names (must be as long as chartNames).
     * @param chartNames: List of chart names (must be as long as parameters).
     * @return  LineChart::LineChartGraph: Graph parsed from given data
     */
    LineChart::LineChartGraph createWeatherCharts(const QJsonArray& array,
            const QStringList& parameters,
            const QStringList& chartNames);

    /**
     * @brief parses error received from api to error string.
     * @param message: json received from api query.
     * @return QString: Description of the error.
     */
    QString parseErrorMessage(const QJsonDocument& message) const;
};

#endif // FMIAPI_H
