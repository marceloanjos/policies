#ifndef COPYACTION_H
#define COPYACTION_H

#include <QObject>
#include <QtPlugin>
#include <QString>
#include <QFileInfo>
#include <QFile>
#include <QDir>
#include <QDirIterator>
#include <QDebug>

#include "iAction.h"

class CopyAction : public QObject, public iAction
{
    Q_OBJECT
    Q_INTERFACES(iAction)
    Q_PLUGIN_METADATA(IID "PluginService.Action.Copy")

public:
    explicit CopyAction(QObject *parent = 0);


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
      * @brief Copy a single file
      * @param source The source QFileInfo
      * @param destination The destination QFileInfo
      * @return
      */
     bool copyFile(QFileInfo source, QFileInfo destination);

     /**
      * @brief Copy an entire directory
      * @param source The source QFileInfo
      * @param destination The destination QFileInfo
      * @return
      */
     bool copyDirectory(QFileInfo source, QFileInfo destination);
};

#endif // COPYACTION_H
