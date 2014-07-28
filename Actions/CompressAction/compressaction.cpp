#include "compressaction.h"

CompressAction::CompressAction(QObject *parent) : QObject(parent)
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

QString CompressAction::name()
{
    try
    {
        return "Compress";
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

bool CompressAction::hasError()
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

QString CompressAction::errorString()
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

bool CompressAction::performAction(QMap<QString, QVariant> params)
{
    try
    {
        qDebug() << " - checking action: " + name();

        foreach(QString key, params.keys())
        {
            qDebug() << " - key: " + key + " = " + params.value(key).toString();
        }

        if(!params.keys().contains("source")) throw QString("Source paramater missing!");
        if(!params.keys().contains("zip")) throw QString("Zip paramater missing!");

        //Make sure the source and destination exist
        QFileInfo fiSource(params.value("source").toString());
        QFileInfo fiDestination(params.value("zip").toString());

        if(!fiSource.exists()) throw QString("Source does not exist!");
        if(fiDestination.exists()) throw QString("Zip already exists!");

        if(fiSource.isFile())
        {
            //Compress a single file
            return CompressFile(fiSource,fiDestination);
        }
        else
        {
            //Compress a folder
            return CompressFolder(fiSource,fiDestination);
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

bool CompressAction::CompressFile(QFileInfo Source, QFileInfo Zip)
{
    try
    {
        if(!Source.exists()) throw QString("Source file not found!");
        if(Zip.exists()) throw QString("Zip file already exists!");

        QFile file(Source.absoluteFilePath());
        if(!file.open(QIODevice::ReadOnly)) throw QString("Could not open source file");

        //Open the zip
        ZipWriter cZip(Zip.absoluteFilePath(),QIODevice::WriteOnly);
        if(!cZip.isWritable())
        {
            cZip.close();
            throw QString("can not write to the zip file!");
        }

        //Add the file
        cZip.addFile(Source.fileName(),&file);

        //Close the zip
        cZip.close();

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

bool CompressAction::CompressFolder(QFileInfo Source, QFileInfo Zip)
{
    try
    {
        if(!Source.exists()) throw QString("Source directory not found!");
        if(Zip.exists()) throw QString("Zip file already exists!");

        //Get the file list
        QStringList files;

        QDirIterator::IteratorFlag Flags = QDirIterator::Subdirectories;

        QDirIterator dirIt(Source.absoluteFilePath(),Flags);
        while (dirIt.hasNext())
        {
            dirIt.next();
            if (dirIt.fileInfo().isFile())
            {
                files.append(dirIt.fileInfo().absoluteFilePath());
            }
        }

        //if there are no files to add simply exit
        if(files.count() < 1) throw QString("No files to add!");

        //Open the zip
        ZipWriter cZip(Zip.absoluteFilePath(),QIODevice::WriteOnly);
        if(!cZip.isWritable())
        {
            cZip.close();
            throw QString("can not write to the zip file!");
        }

        foreach(QString filename, files)
        {

            QFileInfo fi(filename);

            QFile file(filename);
            if(file.open(QIODevice::ReadOnly))
            {
                cZip.addFile(filename,file.readAll());
            }
        }

        cZip.close();

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

