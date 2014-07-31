#include "datetrigger.h"

DateTrigger::DateTrigger(QObject *parent) : QObject(parent)
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

QString DateTrigger::name()
{
    try
    {
        return "Date";
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

bool DateTrigger::hasError()
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

QString DateTrigger::errorString()
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

bool DateTrigger::triggered(QMap<QString,QVariant> params)
{
    try
    {
        m_errorString.clear();

        qDebug() << " - checking trigger: " + name();

        foreach(QString key, params.keys())
        {
            qDebug() << " - key: " + key + " = " + params.value(key).toString();
        }

        //Make sure we have the required parameters
        if(!params.keys().contains("date")) return false;

        //Get the parameter
        QDate date = params.value("date").toDate();
        QDate current = QDate::currentDate();

        //See if it is the same date
        if(current == date)return true;

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

