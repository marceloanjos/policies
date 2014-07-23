#include "downloadaction.h"

DownloadAction::DownloadAction(QObject *parent) : QObject(parent)
{
    try
    {
        m_errorString = "";

        mDownloader.setOverwrite(false);
        mDownloader.setIgnoreSSLErrors(true);

        connect(&mDownloader,SIGNAL(OnAllFinished()),this, SLOT(OnAllFinished()));
        connect(&mDownloader,SIGNAL(OnNetworkError(QNetworkReply*,QString)),this, SLOT(OnNetworkError(QNetworkReply*,QString)));
        connect(&mDownloader,SIGNAL(OnStarted(QNetworkReply*)),this,SLOT(OnStarted(QNetworkReply*)));
        connect(&mDownloader,SIGNAL(OnFinished(QNetworkReply*)),this,SLOT(OnFinished(QNetworkReply*)));
        connect(&mDownloader,SIGNAL(OnFileDownloaded(QString)),this,SLOT(OnFileDownloaded(QString)));
        connect(&mDownloader,SIGNAL(OnProgress(QNetworkReply*,qint64,qint64)),this,SLOT(OnProgress(QNetworkReply*,qint64,qint64)));
        connect(&mDownloader,SIGNAL(OnAllFinished()),SLOT(OnAllFinished()));

    }
    catch(QString err)
    {
        m_errorString = err;
    }
    catch(...)
    {
        m_errorString = "Unknown error in: " + QString(Q_FUNC_INFO);
    }
}

QString DownloadAction::name()
{
    try
    {
        return "Download";
    }
    catch(QString err)
    {
        m_errorString = err;
        return "";
    }
    catch(...)
    {
        m_errorString = "Unknown error in: " + QString(Q_FUNC_INFO);
        return "";
    }
}

bool DownloadAction::hasError()
{
    try
    {
        if(m_errorString.isEmpty()) return false;
        return true;
    }
    catch(...)
    {
        return true;
    }
}

QString DownloadAction::errorString()
{
    try
    {
        return m_errorString;
    }
    catch(...)
    {
        return "Unknown error in: " + QString(Q_FUNC_INFO);
    }
}

bool DownloadAction::performAction(QMap<QString, QVariant> params)
{
    try
    {
        //Make sure the params exist
        if(!params.keys().contains("source")) throw QString("Source paramater missing!");
        if(!params.keys().contains("destination")) throw QString("Destination paramater missing!");

        //Make sure the source and destination exist
        QFileInfo fiDestination(params.value("destination").toString());

        if(fiDestination.exists()) throw QString("Destination file already exists!");

        QString URL = params.value("source").toString();


        mDownloader.Get(URL, fiDestination.absoluteFilePath());

        return true;
    }
    catch(QString err)
    {
        m_errorString = err;
        return false;
    }
    catch(...)
    {
        m_errorString = "Unknown error in: " + QString(Q_FUNC_INFO);
        return false;
    }
}

void DownloadAction::OnError(QString Message)
{
    try
    {
        m_errorString = Message;
        qDebug() << Message;
    }
    catch(QString err)
    {
        m_errorString = err;
    }
    catch(...)
    {
        m_errorString = "Unknown error in: " + QString(Q_FUNC_INFO);
    }
}

void DownloadAction::OnNetworkError(QNetworkReply *reply, QString Message)
{
    try
    {
        if(!reply) return;
        m_errorString = Message;
        qDebug() << Message;
    }
    catch(QString err)
    {
        m_errorString = err;
    }
    catch(...)
    {
        m_errorString = "Unknown error in: " + QString(Q_FUNC_INFO);
    }
}

void DownloadAction::OnStarted(QNetworkReply *reply)
{
    try
    {
        if(!reply) return;
        qDebug() << "Starting download";
        m_errorString = "";
    }
    catch(QString err)
    {
        m_errorString = err;
    }
    catch(...)
    {
        m_errorString = "Unknown error in: " + QString(Q_FUNC_INFO);
    }
}

void DownloadAction::OnFinished(QNetworkReply *reply)
{
    try
    {
        if(!reply) return;
        qDebug() << "Finished download";
        m_errorString = "";
    }
    catch(QString err)
    {
        m_errorString = err;
    }
    catch(...)
    {
        m_errorString = "Unknown error in: " + QString(Q_FUNC_INFO);
    }
}

void DownloadAction::OnFileDownloaded(QString File)
{
    try
    {
        qDebug() << "File downloaded: " <<  File;
        m_errorString = "";
    }
    catch(QString err)
    {
        m_errorString = err;
    }
    catch(...)
    {
        m_errorString = "Unknown error in: " + QString(Q_FUNC_INFO);
    }
}

void DownloadAction::OnProgress(QNetworkReply *reply, qint64 bytesReceived, qint64 bytesTotal)
{
    try
    {
        if(!reply) return;
        qDebug() << "Download: " <<  bytesReceived << " of " << bytesTotal;
        m_errorString = "";
    }
    catch(QString err)
    {
        m_errorString = err;
    }
    catch(...)
    {
        m_errorString = "Unknown error in: " + QString(Q_FUNC_INFO);
    }
}

void DownloadAction::OnAllFinished()
{
    try
    {
        qDebug() << "All downloads are complete.";
        m_errorString = "";
    }
    catch(QString err)
    {
        m_errorString = err;
    }
    catch(...)
    {
        m_errorString = "Unknown error in: " + QString(Q_FUNC_INFO);
    }
}

