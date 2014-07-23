#include "triggertemplate.h"

TriggerTemplate::TriggerTemplate(QObject *parent) : QObject(parent)
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

QString TriggerTemplate::name()
{
    try
    {
        return "Template";
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

bool TriggerTemplate::hasError()
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

QString TriggerTemplate::errorString()
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

bool TriggerTemplate::triggered(QMap<QString,QVariant> params)
{
    try
    {
        //TO DO - Determine if the trigger has been met

        foreach(QString key, params.keys())
        {
            qDebug() << key << ": " << params.value(key);
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

