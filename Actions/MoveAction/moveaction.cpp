#include "moveaction.h"

MoveAction::MoveAction(QObject *parent) : QObject(parent)
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

QString MoveAction::name()
{
    try
    {
        return "Move";
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

bool MoveAction::hasError()
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

QString MoveAction::errorString()
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

bool MoveAction::performAction(QMap<QString, QVariant> params)
{
    try
    {
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
            return moveFile(fiSource,fiDestination);
        }
        else
        {
            //copy the directory
            return moveDirectory(fiSource,fiDestination);
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

bool MoveAction::moveFile(QFileInfo source, QFileInfo destination)
{
    try
    {
        //Make sure the destination does not exist
        if(destination.exists()) throw QString("Destination file already exists!");

        QFile file(source.absoluteFilePath());
        if(!file.copy(destination.absoluteFilePath()))
        {
            throw file.errorString();
            if(!file.remove()) throw file.errorString();
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


bool MoveAction::moveDirectory(QFileInfo source, QFileInfo destination)
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
            if(!dir.exists()) dir.mkpath(fiNew.absolutePath());

            //copy the file
            QFile fileNew(fiNew.absoluteFilePath());
            QFile fileOld(fi.absoluteFilePath());

            if(!fileNew.exists())
            {
                //Show the debug info
                if(!fileNew.copy(fi.absoluteFilePath(),fiNew.absoluteFilePath())) throw fileNew.errorString();
                if(!fileOld.remove()) throw fileOld.errorString();
            }
        }

        //Remove the orginal (empty) directory
        QDir dir(source.absoluteFilePath());
        if(!dir.removeRecursively()) throw QString("Could not remove: " + source.absoluteFilePath());

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
