#include "daystrigger.h"

DaysTrigger::DaysTrigger(QObject *parent) : QObject(parent)
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

QString DaysTrigger::name()
{
    try
    {
        return "Days";
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

bool DaysTrigger::hasError()
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

QString DaysTrigger::errorString()
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

bool DaysTrigger::triggered(QMap<QString,QVariant> params)
{
    try
    {
        if(!params.keys().contains("dateupdated")) return false;
        if(!params.keys().contains("days")) throw QString("Days not found in params!");

        QDateTime lastupdate = params.value("dateupdated").toDateTime();
        QDateTime current = QDateTime::currentDateTime();

        bool bOK;
        int days = params.value("days").toInt(&bOK);

        if(!bOK) throw QString("Days not a valid number!");

        if(lastupdate.daysTo(current) >= days) return true;


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

