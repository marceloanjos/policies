#include "commandaction.h"

CommandAction::CommandAction(QObject *parent) : QObject(parent)
{
    try
    {
        m_errorString = "";

        mShellPath = QDir(QDir::currentPath()).absolutePath();

        StartShell();


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

CommandAction::~CommandAction()
{
    try
    {
        if(mShell)
        {
            mShell->close();
            delete mShell;
        }
    }
    catch(...)
    {
        m_errorString = "Unknown error in: " + QString(Q_FUNC_INFO);
    }
}

QString CommandAction::name()
{
    try
    {
        return "Command";
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

bool CommandAction::hasError()
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

QString CommandAction::errorString()
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

bool CommandAction::performAction(QMap<QString, QVariant> params)
{
    try
    {

        qDebug() << " - checking action: " + name();

        foreach(QString key, params.keys())
        {
            qDebug() << " - key: " + key + " = " + params.value(key).toString();
        }

        if(!params.keys().contains("command")) throw QString("Command paramater missing!");

        QString Command = params.value("command").toString();

        //see if they want to switch directories
        if(Command.toUpper().startsWith("CD "))
        {
            QString NewDir = Command.mid(3).replace("\"","");
            QDir dir(NewDir);
            if(dir.exists())
            {
                mShellPath = NewDir;
                mShell->close();
                delete mShell;
                StartShell();
            }
        }

        //Send the command to the shell
        if(mShell)
        {
    #ifdef Q_OS_WIN
        mShell->write(Command.toLatin1().trimmed() + "\r\n");
    #else
         mShell->write(Command.toLatin1().trimmed() + "\n");
    #endif

        }
        else
        {
            throw QString("System shell not started!");
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

void CommandAction::ShellReadyRead()
{
    try
    {
        //Read the response from the shell
        QByteArray cBuffer = mShell->readAll();
        QString cTemp(cBuffer);
        cTemp = cTemp.remove("\r");
        QStringList cList = cTemp.split("\n");

        //get each line of the buffer
        foreach(QString cLine, cList)
        {
           qDebug() << "\t" << cLine;
        }
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

void CommandAction::StartShell()
{
    try
    {
        //Start the shell


        //Create a new process for them
        mShell = new  QProcess(this);
        mShell->setReadChannelMode(QProcess::MergedChannels);
        mShell->setWorkingDirectory(mShellPath);

        connect(mShell,SIGNAL(readyReadStandardOutput()), this,SLOT(ShellReadyRead()));
        connect(mShell,SIGNAL(readyReadStandardError()), this,SLOT(ShellReadyRead()));
        connect(mShell,SIGNAL(readyRead()), this,SLOT(ShellReadyRead()));

        //Start the shell based on the OS type
    #ifdef Q_OS_WIN
        mShell->start("cmd");
    #else
        mShell->start("bash");
    #endif
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

