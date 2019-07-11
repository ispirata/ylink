#ifndef HTTP_H
#define HTTP_H

#include <QtNetwork>

class HttpRequest {
public:
    HttpRequest() : operation(QNetworkAccessManager::GetOperation), offset(0) {}
    QUrl url;
    QNetworkAccessManager::Operation operation;
    QByteArray body;
    uint offset;
    QMap<QByteArray, QByteArray> headers;
};

class HttpReply : public QObject {
    Q_OBJECT

public:
    HttpReply(QObject *parent = nullptr) : QObject(parent) {}
    virtual QUrl url() const = 0;
    virtual int statusCode() const = 0;
    int isSuccessful() const { return statusCode() >= 200 && statusCode() < 300; }
    virtual QString reasonPhrase() const { return QString(); }
    virtual const QList<QNetworkReply::RawHeaderPair> headers() const {
        return QList<QNetworkReply::RawHeaderPair>();
    }
    virtual QByteArray header(const QByteArray &headerName) const {
        Q_UNUSED(headerName);
        return QByteArray();
    }

    virtual QByteArray body() const = 0;

signals:
    void data(const QByteArray &bytes);
    void error(const QString &message);
    void finished(const HttpReply &reply);
};

class Http {
public:
    static Http &instance();
    static const QMap<QByteArray, QByteArray> &getDefaultRequestHeaders();
    static void setDefaultReadTimeout(int timeout);

    Http();

    void setRequestHeaders(const QMap<QByteArray, QByteArray> &headers);
    QMap<QByteArray, QByteArray> &getRequestHeaders();
    void addRequestHeader(const QByteArray &name, const QByteArray &value);

    void setReadTimeout(int timeout);
    int getReadTimeout() { return readTimeout; }

    QNetworkReply *networkReply(const HttpRequest &req);
    virtual HttpReply *request(const HttpRequest &req);
    HttpReply *
    request(const QUrl &url,
            QNetworkAccessManager::Operation operation = QNetworkAccessManager::GetOperation,
            const QByteArray &body = QByteArray(),
            uint offset = 0);
    HttpReply *get(const QUrl &url);
    HttpReply *head(const QUrl &url);
    HttpReply *post(const QUrl &url, const QMap<QString, QString> &params);
    HttpReply *post(const QUrl &url, const QByteArray &body, const QByteArray &contentType);

private:
    QMap<QByteArray, QByteArray> requestHeaders;
    int readTimeout;
};

class NetworkHttpReply : public HttpReply {
    Q_OBJECT

public:
    NetworkHttpReply(const HttpRequest &req, Http &http);
    QUrl url() const;
    int statusCode() const;
    QString reasonPhrase() const;
    const QList<QNetworkReply::RawHeaderPair> headers() const;
    QByteArray header(const QByteArray &headerName) const;
    QByteArray body() const;

private slots:
    void replyFinished();
    void replyError(QNetworkReply::NetworkError);
    void downloadProgress(qint64 bytesReceived, qint64 bytesTotal);
    void readTimeout();

private:
    void setupReply();
    QString errorMessage();
    void emitError();
    void emitFinished();

    Http &http;
    HttpRequest req;
    QNetworkReply *networkReply;
    QTimer *readTimeoutTimer;
    int retryCount;
    QByteArray bytes;
};

#endif // HTTP_H
