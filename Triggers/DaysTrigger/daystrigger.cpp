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

        m_errorString.clear();
        qDebug() << " - checking trigger: " << name();
        foreach(QString key, params.keys())
        {
            qDebug() << " - key: " << key << " = " << params.value(key).toString();
        }

        //See if this has already ran
        if(params.keys().contains("triggerdate"))
        {
            QDateTime lastrun = params.value("triggerdate").toDateTime();
            if(lastrun.daysTo(QDateTime::currentDateTime()) == 0)
            {
                qDebug() << name() << " skipping, has already run";
                return false;
            }
        }

        bool bOK;
        int days = params.value("days").toInt(&bOK);
        if(!bOK) throw QString("Days not a valid number!");

        if(!params.keys().contains("dateupdated")) throw QString("DateUpdated not found in params!");
        if(!params.keys().contains("days")) throw QString("Days not found in params!");

        QDateTime lastupdate = QDateTime::fromString(params.value("dateupdated").toString(),"MM-dd-yyyy hh:mm:ss");
        QDateTime current = QDateTime::currentDateTime();
        qint64 daysSince = lastupdate.daysTo(current);


        qDebug() << " - lastupdate: " << lastupdate.toString();
        qDebug() << " - current: " << current.toString();
        qDebug() << " - Days: " << days;
        qDebug() << " - DaysSince: " << daysSince;

        if(daysSince >= days) return true;


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

