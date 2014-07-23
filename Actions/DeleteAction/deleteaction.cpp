#include "deleteaction.h"

DeletAction::DeletAction(QObject *parent) : QObject(parent)
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

QString DeletAction::name()
{
    try
    {
        return "Delete";
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

bool DeletAction::hasError()
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

QString DeletAction::errorString()
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

bool DeletAction::performAction(QMap<QString, QVariant> params)
{
    try
    {
        //Make sure the params exist
        if(!params.keys().contains("delete")) throw QString("Source paramater missing!");

        //Make sure the source and destination exist
        QFileInfo fiSource(params.value("delete").toString());

        if(!fiSource.exists()) throw QString("Source does not exist!");

        //Check to see if we are copying a file or a directory
        if(fiSource.isFile())
        {
            //delete the file
            QFile file(fiSource.absoluteFilePath());
            if(!file.remove()) throw file.errorString();
        }
        else
        {
            //delete the directory
            QDir dir(fiSource.absoluteFilePath());
            if(!dir.removeRecursively()) throw QString("Could not remove: " + fiSource.absoluteFilePath());
        }
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

