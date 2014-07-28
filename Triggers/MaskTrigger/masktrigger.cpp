#include "masktrigger.h"

MaskTrigger::MaskTrigger(QObject *parent) : QObject(parent)
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

QString MaskTrigger::name()
{
    try
    {
        return "Mask";
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

bool MaskTrigger::hasError()
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

QString MaskTrigger::errorString()
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

bool MaskTrigger::triggered(QMap<QString,QVariant> params)
{
    try
    {
        qDebug() << " - checking trigger: " + name();

        foreach(QString key, params.keys())
        {
            qDebug() << " - key: " + key + " = " + params.value(key).toString();
        }

        if(!params.keys().contains("ipaddress")) throw QString("IPaddress not in params.");
        if(!params.keys().contains("mask")) throw QString("Mask not in params.");

        //get the IP address
        QStringList ipList = params.value("ipaddress").toString().split(".");

        //Get the mask
        QStringList maskList = params.value("mask").toString().split(".");

        if(ipList.count() < maskList.count()) throw QString("IPaddress and Mask have different lengths!");

        //make sure the octets match
        for(int i = 0 ; i < ipList.count(); i++)
        {

            //make sure the octets match
            QString ipOct = ipList.at(i);
            QString maskOct = maskList.at(i);

            //Make sure it is not a wild card
            if(maskOct != "*")
            {
                //If the octets dont match, then raise the trigger
                if(ipOct != maskOct) return true;
            }
        }


        return false;
    }
    catch(QString err)
    {
        qDebug() << "error";
        m_errorString = err;
        return false;
    }
    catch(...)
    {
        qDebug() << "error2";
        m_errorString = "Unknown error in: " + QString(Q_FUNC_INFO);
        return false;
    }
}

