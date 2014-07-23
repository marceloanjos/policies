#include "decryptaction.h"

DecryptAction::DecryptAction(QObject *parent) : QObject(parent)
{
    try
    {
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

QString DecryptAction::name()
{
    try
    {
        return "Decrypt";
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

bool DecryptAction::hasError()
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

QString DecryptAction::errorString()
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

bool DecryptAction::performAction(QMap<QString, QVariant> params)
{
    try
    {
        if(!params.keys().contains("source")) throw QString("Source paramater missing!");
        if(!params.keys().contains("destination")) throw QString("Destination paramater missing!");

        //Make sure the source and destination exist
        QFileInfo fiSource(params.value("source").toString());
        QFileInfo fiDestination(params.value("destination").toString());

        if(!fiSource.exists()) throw QString("Source does not exist!");
        if(fiDestination.exists()) throw QString("Destination exists!");

        Encryption cCrypt;
        return cCrypt.DecryptFile(fiSource.absoluteFilePath(), fiDestination.absoluteFilePath());
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

