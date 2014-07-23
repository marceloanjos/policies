#ifndef COMPRESSACTION_H
#define COMPRESSACTION_H

#include <QObject>
#include <QtPlugin>
#include <QString>
#include <QDebug>
#include <QFileInfo>
#include <QFile>
#include <QDirIterator>

#include "iAction.h"
#include "../../../Libs/Zip/zipwriter.h"
#include "../../../Libs/Zip/zlib.h"
#include "../../../Libs/Zip/zconf.h"

class CompressAction : public QObject, public iAction
{
    Q_OBJECT
    Q_INTERFACES(iAction)
    Q_PLUGIN_METADATA(IID "PluginService.Action.Compress")

public:
    explicit CompressAction(QObject *parent = 0);


    /**
    * Returns the name of the plugin
    */
    QString name();

    /**
     * @brief Determines if the trigger had an error
     * @return bool
     */
    bool hasError();

    /**
     * @brief Returns the error message as a QString
     * @return QString
     */\
    QString errorString();

    /**
     * @brief Performs the action
     * @param Params The parameters
     * @return bool
     */
     bool performAction(QMap<QString,QVariant> params);

signals:

public slots:

private:

     /**
      * @brief The Error string;
      */
     QString m_errorString;

     /**
      * @brief Compress File
      * @param Source
      * @param Zip
      * @return bool
      */
     bool CompressFile(QFileInfo Source, QFileInfo Zip);

     /**
      * @brief Compress Folder
      * @param Source
      * @param Zip
      * @return bool
      */
     bool CompressFolder(QFileInfo Source, QFileInfo Zip);
};

#endif // COMPRESSACTION_H
