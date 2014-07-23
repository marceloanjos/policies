#ifndef DOWNLOADMANAGER_H
#define DOWNLOADMANAGER_H

#include <QObject>
#include <QDebug>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QSslConfiguration>
#include <QMetaEnum>
#include <QFileInfo>
#include <QAuthenticator>

/**
 * @brief The HTTPManager class downloads mutliple files simutaniously
 */
class DownloadManager : public QObject
{
    Q_OBJECT
public:
    explicit DownloadManager(QObject *parent = 0);

    /**
     * @brief Returns the error message
     * @return QString
     */
    QString ErrorMessage();

    /**
     * @brief Downloads a file to the local disk
     * @param URL The file to download (Http://something.com/a/b/file.ext)
     * @param Filename The name of the local file to save to
     */
    void Get(QString URL,QString Filename);

    /**
     * @brief Downloads a file to the local disk
     * @param URL The file to download (Http://something.com/a/b/file.ext)
     * @param Data The data to post to the server
     * @param Filename The name of the local file to save to
     */
    void Post(QString URL,QByteArray Data,QString Filename);

    /**
     * @brief Determines if local files will be overwritten
     * @param Overwrite Boolean
     */
    void setOverwrite(bool Overwrite);

    /**
     * @brief Determines if SSL errors will be ignored
     * @param Ignore Boolean
     */
    void setIgnoreSSLErrors(bool Ignore);

    /**
     * @brief Returns the file associated with a network reply
     * @param Reply The QNetworkReply object
     * @return QString
     */
    QString getFilename(QNetworkReply* Reply);

signals:

    /**
     * @brief Emitted when an error occurs
     * @param Error Message
     */
    void OnError(QString Message);

    /**
     * @brief Emitted when an error occurs
     * @param reply The reply from the server
     * @param Error Message
     */
    void OnNetworkError(QNetworkReply* reply,QString Message);

    /**
     * @brief Emitted when SSL errors occur
     * @param reply The reply from the server
     * @param errors
     */
    void OnSSLErrors(QNetworkReply* reply,const QList<QSslError> & errors);

    /**
     * @brief Emitted when the connection is encrypted
     * @param reply The reply from the server
     */
    void OnEncrypted(QNetworkReply* reply);

    /**
     * @brief Emitted when authentication is required
     * @param reply The reply from the server
     * @param authenticator The authenticator
     */
    void OnAuthentication(QNetworkReply *reply, QAuthenticator *authenticator);

    /**
     * @brief Emitted when the download starts
     * @param reply The reply from the server
     */
    void OnStarted(QNetworkReply* reply);

    /**
     * @brief Emitted when the download finishes
     * @param reply The reply from the server
     */
    void OnFinished(QNetworkReply* reply);

    /**
     * @brief Emitted when a file is downloaded
     * @param File The path to the file that was downloaded
     */
    void OnFileDownloaded(QString File);

    /**
     * @brief Emitted when there is progress
     * @param reply The reply from the server
     * @param bytesReceived
     * @param bytesTotal
     */
    void OnProgress(QNetworkReply* reply,qint64 bytesReceived, qint64 bytesTotal);

    /**
     * @brief Emitted when all the transfers have been completed
     */
    void OnAllFinished();

public slots:

    /**
     * @brief Slot used when the reply is finished
     */
    void NetworkFinished();

    /**
     * @brief Slot used when the Reply is ready for reading
     */
    void NetworkReadyRead();

    /**
     * @brief Slot used when there was an error
     * @param NetError
     */
    void NetworkError(QNetworkReply::NetworkError NetError);

    /**
     * @brief Slot to trap the encypted signal
     * @param reply The reply from the server
     */
    void NetworkEncrypted(QNetworkReply* reply);

    /**
     * @brief Slot used to trap SSL errors
     * @param reply The reply from the server
     * @param errors List of errors
     */
    void NetworkSSLErrors(QNetworkReply* reply, const QList<QSslError> & errors);

    /**
     * @brief Slot used to trap the SSL authenticationRequired signal
     * @param reply
     * @param authenticator
     */
    void NetworkAuthenticationRequired(QNetworkReply* reply, QAuthenticator* authenticator);

    /**
     * @brief Download Progress
     * @param bytesReceived
     * @param bytesTotal
     */
    void NetworkDownloadProgress(qint64 bytesReceived, qint64 bytesTotal);

private:

    /**
     * @brief Map of Replies and the files they map to
     */
    QMap<QNetworkReply*, QString> mConnections;

    /**
     * @brief Error message
     */
    QString mErrorMessage;

    /**
     * @brief The URL to download
     */
    QString mURL;

    /**
     * @brief Ignores SSL Errors
     */
    bool mIgnoreSSLErrors;

    /**
     * @brief Localfiles are overwritten
     */
    bool mOverwriteFiles;

    /**
     * @brief The network access manager
     */
    QNetworkAccessManager *mNetworkManager;

    /**
     * @brief Handle an error
     * @param Error
     */
    void HandleError(QString Error);

    /**
     * @brief Gets the network connection request
     * @param URL The URL to connect to
     * @return QNetworkRequest
     */
    QNetworkRequest* getRequest(QString URL);

    /**
     * @brief Determines if we can write to the local file
     * @param Filename The file to write to
     * @return Boolean
     */
    bool canWriteFile(QString Filename);

    /**
     * @brief Setups up the signals and slots for the
     * @param Reply
     */
    void SetupReplySignals(QNetworkReply* Reply);
};

#endif // DOWNLOADMANAGER_H
