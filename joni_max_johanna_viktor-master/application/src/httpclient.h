#pragma once

#include <QDebug>
#include <QEventLoop>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QObject>
/**
 * @brief HTTPClient is a synchronous http client that supports get request and passing http headers.
 */
class HTTPClient : public QObject
{
public:
    /**
     * @brief Response format for client. Allows error state to be passed upstream.
     */
    struct Response
    {
        bool error;
        QByteArray data;
    };

    /**
     * @brief Constructor.
     * @param parent: Pointer to parent QObject.
     */
    HTTPClient(QObject* parent = nullptr);

    /**
     * @brief Makes http get request and returns received data and error state. Added headers are
     * added to request.
     * @param query: Http(s) query for get request.
     * @return Response: Data and error state from response to query made.
     */
    Response get(const QString& query);

    /**
     * @brief Adds a header, these headers are included in request made after addind.
     * @param headerName: Name of the header.
     * @param value: Value of the header.
     */
    void addHeader(const QByteArray& headerName, const QByteArray& value);

    /**
     * @brief Clears all headers.
     */
    void clearHeaders();

private:
    QNetworkAccessManager m_networkManager;
    QEventLoop m_eventLoop;
    QList<QPair<QByteArray, QByteArray>> m_headers;
};
