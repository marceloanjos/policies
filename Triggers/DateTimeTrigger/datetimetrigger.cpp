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
        //Make sure we have the required parameters
        if(!params.keys().contains("datetime")) return false;

        //Get the parameter
        QDateTime date = params.value("datetime").toDateTime();
        QDateTime current = QDateTime::currentDateTime();

        //qDebug() << "params: " <<  params.value("datetime").toString();
        //qDebug() << "Date: " <<  date;
        //qDebug() << "Curent: " <<  current;

        //See if it is the same date and hour / minute
         if(current.date() == date.date() && current.time().hour() == date.time().hour() && current.time().minute() == date.time().minute())return true;

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

