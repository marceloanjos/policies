#ifndef DOWNLOADACTION_H
#define DOWNLOADACTION_H

#include <QObject>
#include <QtPlugin>
#include <QString>
#include <QDebug>
#include <QFileInfo>

#include "iAction.h"
#include "downloadmanager.h"

class DownloadAction : public QObject, public iAction
{
    Q_OBJECT
    Q_INTERFACES(iAction)
    Q_PLUGIN_METADATA(IID "PluginService.Action.Download")

public:
    explicit DownloadAction(QObject *parent = 0);


    /**
    * Returns the name of the plugin
    */
    QString name();

    /**
     * @brief Determines if the trigger had an error
     * @return bool
     */
    bool hasError();

    /**
     * @brief Returns the error message as a QString
     * @return QString
     */\
    QString errorString();

    /**
     * @brief Performs the action
     * @param Params The parameters
     * @return bool
     */
     bool performAction(QMap<QString,QVariant> params);

signals:

public slots:

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

private:

     /**
      * @brief The Error string;
      */
     QString m_errorString;

     /**
      * @brief Download manager
      */
     DownloadManager mDownloader;
};

#endif // DOWNLOADACTION_H
