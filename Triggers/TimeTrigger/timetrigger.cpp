#include "timetrigger.h"

TimeTrigger::TimeTrigger(QObject *parent) : QObject(parent)
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

QString TimeTrigger::name()
{
    try
    {
        return "Time";
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

bool TimeTrigger::hasError()
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

QString TimeTrigger::errorString()
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

bool TimeTrigger::triggered(QMap<QString,QVariant> params)
{
    try
    {
        qDebug() << " - checking trigger: " + name();

        foreach(QString key, params.keys())
        {
            qDebug() << " - key: " + key + " = " + params.value(key).toString();
        }

        //Make sure we have the required parameters
        if(!params.keys().contains("time")) return false;

        //Get the parameter
        QTime time = params.value("time").toTime();
        QTime current = QTime::currentTime();

        qDebug() << " - time " << current.toString("hh:mm:ss");

        //See if the hour and minutes match
        if(current.hour() == time.hour() && current.minute() == time.minute()) return true;

        //Otherwise return false
        return false;
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

