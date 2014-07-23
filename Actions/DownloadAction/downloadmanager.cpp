#include "downloadmanager.h"

DownloadManager::DownloadManager(QObject *parent) :
    QObject(parent)
{
    try
    {
        mOverwriteFiles = false;
        mIgnoreSSLErrors = true;

        mNetworkManager = new QNetworkAccessManager(this);
        connect(mNetworkManager,SIGNAL(encrypted(QNetworkReply*)), this, SLOT(NetworkEncrypted(QNetworkReply*)));
        connect(mNetworkManager,SIGNAL(sslErrors(QNetworkReply*,QList<QSslError>)), this, SLOT(NetworkSSLErrors(QNetworkReply*,QList<QSslError>)));
        connect(mNetworkManager,SIGNAL(authenticationRequired(QNetworkReply*,QAuthenticator*)),this, SLOT(NetworkAuthenticationRequired(QNetworkReply*,QAuthenticator*)));
    }
    catch(QString err)
    {
        HandleError(err);
    }
    catch(...)
    {
        HandleError("Unknown error in: " + QString(Q_FUNC_INFO));
    }
}

QString DownloadManager::ErrorMessage()
{
    try
    {
        return mErrorMessage;
    }
    catch(QString err)
    {
        HandleError(err);
        return "";
    }
    catch(...)
    {
        HandleError("Unknown error in: " + QString(Q_FUNC_INFO));
        return "";
    }
}

void DownloadManager::Get(QString URL, QString Filename)
{
    try
    {
        //Make sure we can write to the file
       if(!canWriteFile(Filename)) return;

        //Setup the connection and begin the transfer;
        QNetworkRequest* request = getRequest(URL);
        QNetworkReply* reply = mNetworkManager->get(*request);
        delete request;

        //Update the map
        mConnections.insert(reply,Filename);

        //Setup the signals and slots
        SetupReplySignals(reply);

    }
    catch(QString err)
    {
        HandleError(err);
    }
    catch(...)
    {
        HandleError("Unknown error in: " + QString(Q_FUNC_INFO));
    }
}

void DownloadManager::Post(QString URL, QByteArray Data, QString Filename)
{
    try
    {
        //Make sure we can write to the file
       if(!canWriteFile(Filename)) return;

        //Setup the connection and begin the transfer;
        QNetworkRequest* request = getRequest(URL);
        request->setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
        QNetworkReply* reply = mNetworkManager->post(*request,Data);
        delete request;

        //Update the map
        mConnections.insert(reply,Filename);

        //Setup the signals and slots
        SetupReplySignals(reply);

    }
    catch(QString err)
    {
        HandleError(err);
    }
    catch(...)
    {
        HandleError("Unknown error in: " + QString(Q_FUNC_INFO));
    }
}

void DownloadManager::setOverwrite(bool Overwrite)
{
    try
    {
        mOverwriteFiles = Overwrite;
    }
    catch(QString err)
    {
        HandleError(err);
    }
    catch(...)
    {
        HandleError("Unknown error in: " + QString(Q_FUNC_INFO));
    }
}

void DownloadManager::setIgnoreSSLErrors(bool Ignore)
{
    try
    {
        mIgnoreSSLErrors = Ignore;
    }
    catch(QString err)
    {
        HandleError(err);
    }
    catch(...)
    {
        HandleError("Unknown error in: " + QString(Q_FUNC_INFO));
    }
}

QString DownloadManager::getFilename(QNetworkReply *Reply)
{
    try
    {
        if(!mConnections.contains(Reply)) return "";

        return mConnections.value(Reply);
    }
    catch(QString err)
    {
        HandleError(err);
        return "";
    }
    catch(...)
    {
        HandleError("Unknown error in: " + QString(Q_FUNC_INFO));
        return "";
    }
}

void DownloadManager::NetworkFinished()
{
    try
    {
        //Get the calling object
        QNetworkReply* reply = 0;
        if(this->sender()) reply = qobject_cast<QNetworkReply*>(this->sender());
        if(!reply) return;

        //Emit the signal
        emit OnFinished(reply);

        //Cleanup the map
       if(mConnections.contains(reply))
       {
           emit OnFileDownloaded(mConnections.value(reply));
           mConnections.remove(reply);
       }

        //Clean up
        reply->deleteLater();

        //see if we are all done
        if(mConnections.count() == 0)
        {
            emit OnAllFinished();
        }

    }
    catch(QString err)
    {
        HandleError(err);
    }
    catch(...)
    {
        HandleError("Unknown error in: " + QString(Q_FUNC_INFO));
    }
}

void DownloadManager::NetworkReadyRead()
{
    try
    {
        //Get the calling object
        QNetworkReply* reply = 0;
        if(this->sender()) reply = qobject_cast<QNetworkReply*>(this->sender());

        //Make sure we have a valid connection
        if(!mConnections.contains(reply)) throw QString("Invalid connection!");

        //Write the content to disk
        QString Filename = mConnections.value(reply,"");
        QFile file(Filename);
        if(!file.open(QIODevice::Append)) throw file.errorString();
        file.write(reply->readAll());
        file.close();

    }
    catch(QString err)
    {
        HandleError(err);
    }
    catch(...)
    {
        HandleError("Unknown error in: " + QString(Q_FUNC_INFO));
    }
}

void DownloadManager::NetworkError(QNetworkReply::NetworkError NetError)
{
    try
    {
        //Get the calling object
        QNetworkReply* reply = 0;
        if(this->sender()) reply = qobject_cast<QNetworkReply*>(this->sender());

        QMetaObject MetaObject = QNetworkReply::staticMetaObject;
        QMetaEnum MetaEnum = MetaObject.enumerator(MetaObject.indexOfEnumerator("NetworkError"));

        emit OnNetworkError(reply,MetaEnum.valueToKey(NetError));

        throw QString(MetaEnum.valueToKey(NetError));

    }
    catch(QString err)
    {
        HandleError(err);
    }
    catch(...)
    {
        HandleError("Unknown error in: " + QString(Q_FUNC_INFO));
    }
}

void DownloadManager::NetworkEncrypted(QNetworkReply *reply)
{
    try
    {
        emit OnEncrypted(reply);
    }
    catch(QString err)
    {
        HandleError(err);
    }
    catch(...)
    {
        HandleError("Unknown error in: " + QString(Q_FUNC_INFO));
    }
}

void DownloadManager::NetworkSSLErrors(QNetworkReply *reply, const QList<QSslError> &errors)
{
    try
    {
        if(mIgnoreSSLErrors)
        {
            reply->ignoreSslErrors(errors);
        }
        else
        {
            emit OnSSLErrors(reply,errors);

            throw QString("SSL Errors!");
        }
    }
    catch(QString err)
    {
        HandleError(err);
    }
    catch(...)
    {
        HandleError("Unknown error in: " + QString(Q_FUNC_INFO));
    }
}

void DownloadManager::NetworkAuthenticationRequired(QNetworkReply *reply, QAuthenticator *authenticator)
{
    try
    {
        emit OnAuthentication(reply,authenticator);
    }
    catch(QString err)
    {
        HandleError(err);
    }
    catch(...)
    {
        HandleError("Unknown error in: " + QString(Q_FUNC_INFO));
    }
}

void DownloadManager::NetworkDownloadProgress(qint64 bytesReceived, qint64 bytesTotal)
{
    try
    {
        //Get the calling object
        QNetworkReply* reply = 0;
        if(this->sender()) reply = qobject_cast<QNetworkReply*>(this->sender());
        if(!reply) return;

        emit OnProgress(reply,bytesReceived,bytesTotal);
    }
    catch(QString err)
    {
        HandleError(err);
    }
    catch(...)
    {
        HandleError("Unknown error in: " + QString(Q_FUNC_INFO));
    }
}

void DownloadManager::HandleError(QString Error)
{
    try
    {
        mErrorMessage = Error;
        emit OnError(Error);
        qDebug() << Error;
    }
    catch(...)
    {
        qDebug() << "Unknown error in: " << QString(Q_FUNC_INFO);
    }
}

QNetworkRequest* DownloadManager::getRequest(QString URL)
{
    try
    {
        QUrl cUrl(URL);
        QNetworkRequest* cRequest = new QNetworkRequest(cUrl);
        QSslConfiguration cSSL = cRequest->sslConfiguration();
        cSSL.setProtocol(QSsl::AnyProtocol);

        return cRequest;
    }
    catch(QString err)
    {
        HandleError(err);
        return 0;
    }
    catch(...)
    {
        HandleError("Unknown error in: " + QString(Q_FUNC_INFO));
        return 0;
    }
}

bool DownloadManager::canWriteFile(QString Filename)
{
    try
    {
        QFile file(Filename);
        if(file.exists())
        {
            if(mOverwriteFiles)
            {
                if(!file.remove()) throw QString("File could not be overwritten!");
            }
            else
            {
               throw QString("Destination file exists!");
            }
        }

        return true;
    }
    catch(QString err)
    {
        HandleError(err);
        return false;
    }
    catch(...)
    {
        HandleError("Unknown error in: " + QString(Q_FUNC_INFO));
        return false;
    }
}

void DownloadManager::SetupReplySignals(QNetworkReply* Reply)
{
    try
    {
        //Get the reply back form the server
        connect(Reply, SIGNAL(readyRead()), this, SLOT(NetworkReadyRead()));
        connect(Reply, SIGNAL(error(QNetworkReply::NetworkError)),this, SLOT(NetworkError(QNetworkReply::NetworkError)));
        connect(Reply,SIGNAL(finished()),this,SLOT(NetworkFinished()));
        connect(Reply,SIGNAL(downloadProgress(qint64,qint64)),this,SLOT(NetworkDownloadProgress(qint64,qint64)));

        emit OnStarted(Reply);
    }
    catch(QString err)
    {
        HandleError(err);
    }
    catch(...)
    {
        HandleError("Unknown error in: " + QString(Q_FUNC_INFO));
    }
}
