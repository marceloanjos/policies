#include "launchaction.h"

LaunchAction::LaunchAction(QObject *parent) : QObject(parent)
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

QString LaunchAction::name()
{
    try
    {
        return "Launch";
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

bool LaunchAction::hasError()
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

QString LaunchAction::errorString()
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

bool LaunchAction::performAction(QMap<QString, QVariant> params)
{
    try
    {
         if(!params.keys().contains("launch")) throw QString("Launch paramater missing!");

         QProcess proc;
         proc.startDetached(params.value("launch").toString());
        //proc.waitForFinished();

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

