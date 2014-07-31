#include "datetimetrigger.h"

DateTimeTrigger::DateTimeTrigger(QObject *parent) : QObject(parent)
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

QString DateTimeTrigger::name()
{
    try
    {
        return "DateTime";
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

bool DateTimeTrigger::hasError()
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

QString DateTimeTrigger::errorString()
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

bool DateTimeTrigger::triggered(QMap<QString,QVariant> params)
{
    try
    {
        m_errorString.clear();
        qDebug() << " - checking trigger: " + name();

        foreach(QString key, params.keys())
        {
            qDebug() << " - key: " + key + " = " + params.value(key).toString();
        }

        if(!params.keys().contains("datetime")) return false;

        //Get the parameter
        QDateTime date = params.value("datetime").toDateTime();
        QDateTime current = QDateTime::currentDateTime();

        qDebug() << " - Date: " <<  date.toString();
        qDebug() << " - Curent: " <<  current.toString();

        //See if it is the same date and hour / minute
        if(date <= current) return true;

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

