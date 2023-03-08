#include "httpclient.h"

HTTPClient::HTTPClient(QObject* parent) : QObject(parent)
{
}

HTTPClient::Response HTTPClient::get(const QString& query)
{
    QNetworkRequest networkRequest;
    networkRequest.setUrl(QUrl(query));

    for (const auto& header : m_headers)
    {
        networkRequest.setRawHeader(header.first, header.second);
    }

    auto reply = m_networkManager.get(networkRequest);

    connect(reply, &QNetworkReply::finished, &m_eventLoop, &QEventLoop::quit);
    m_eventLoop.exec();

    if (!reply->error())
    {
        return Response{false, reply->readAll()};
    }
    return Response{true, reply->readAll()};
}

void HTTPClient::addHeader(const QByteArray& headerName, const QByteArray& value)
{
    m_headers.append(QPair(headerName, value));
}

void HTTPClient::clearHeaders()
{
    m_headers.clear();
}
