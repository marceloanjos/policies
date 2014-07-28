#include "copyaction.h"

CopyAction::CopyAction(QObject *parent) : QObject(parent)
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

QString CopyAction::name()
{
    try
    {
        return "Copy";
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

bool CopyAction::hasError()
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

QString CopyAction::errorString()
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

bool CopyAction::performAction(QMap<QString, QVariant> params)
{
    try
    {

        qDebug() << " - checking action: " + name();

        foreach(QString key, params.keys())
        {
            qDebug() << " - key: " + key + " = " + params.value(key).toString();
        }

        //Make sure the params exist
        if(!params.keys().contains("source")) throw QString("Source paramater missing!");
        if(!params.keys().contains("destination")) throw QString("Destination paramater missing!");

        //Make sure the source and destination exist
        QFileInfo fiSource(params.value("source").toString());
        QFileInfo fiDestination(params.value("destination").toString());

        if(!fiSource.exists()) throw QString("Source does not exist!");

        //Check to see if we are copying a file or a directory
        if(fiSource.isFile())
        {
            //copy the file
            return copyFile(fiSource,fiDestination);
        }
        else
        {
            //copy the directory
            return copyDirectory(fiSource,fiDestination);
        }

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

bool CopyAction::copyFile(QFileInfo source, QFileInfo destination)
{
    try
    {
        //Make sure the destination does not exist
        if(destination.exists()) throw QString("Destination file already exists!");

        QFile file(source.absoluteFilePath());
        if(!file.copy(destination.absoluteFilePath())) throw file.errorString();

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

bool CopyAction::copyDirectory(QFileInfo source, QFileInfo destination)
{
    QString m_errorString = "";
    try
    {
        //Make sure the destination does not exist
        if(destination.exists()) throw QString("Destination directory already exists!");;

        //Create the destination
        if(!destination.dir().mkdir(destination.absoluteFilePath())) throw QString("Failed to create destination!");

        //Get a list of files
        QList<QFileInfo> list;
        QDirIterator dirIt(source.absoluteFilePath(),QDirIterator::Subdirectories);
        while (dirIt.hasNext())
        {
            dirIt.next();
            if (dirIt.fileInfo().isFile())
            {
                list.append(dirIt.fileInfo());
            }
        }

        //Create the destination directory while we copy files
        foreach(QFileInfo fi, list)
        {

            //Get the new filename
             QFileInfo fiNew(fi.absoluteFilePath().replace(source.absoluteFilePath(),destination.absoluteFilePath()));

            //Create the path
            QDir dir(fiNew.absolutePath());
            if(!dir.exists())
            {
                qDebug() << "Creating: " << fiNew.absolutePath();
                dir.mkpath(fiNew.absolutePath());
            }

            //copy the file
            QFile fileNew(fiNew.absoluteFilePath());
            if(!fileNew.exists())
            {
                //Show the debug info
                qDebug() << fi.absoluteFilePath();
                if(!fileNew.copy(fi.absoluteFilePath(),fiNew.absoluteFilePath())) throw QString(fileNew.errorString());
            }
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
