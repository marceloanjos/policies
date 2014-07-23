#include "decompressaction.h"

DecompressAction::DecompressAction(QObject *parent) : QObject(parent)
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

QString DecompressAction::name()
{
    try
    {
        return "Decompress";
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

bool DecompressAction::hasError()
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

QString DecompressAction::errorString()
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

bool DecompressAction::performAction(QMap<QString, QVariant> params)
{
    try
    {
        if(!params.keys().contains("destination")) throw QString("Destination paramater missing!");
        if(!params.keys().contains("zip")) throw QString("Zip paramater missing!");

        //Make sure the source and destination exist
        QFileInfo fiDestination(params.value("destination").toString());
        QFileInfo fiSource(params.value("zip").toString());

        if(!fiSource.exists()) throw QString("Source does not exist!");
        if(fiDestination.exists()) throw QString("Destination already exists!");

        ZipReader cZip(fiSource.absoluteFilePath());
        if(!cZip.isReadable()) throw QString("Can not read zip file!");

        cZip.extractAll(fiDestination.absoluteFilePath());

        cZip.close();

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

