#ifndef MOVEACTON_H
#define MOVEACTON_H

#include <QObject>
#include <QtPlugin>
#include <QString>
#include <QFileInfo>
#include <QFile>
#include <QDir>
#include <QDirIterator>
#include <QDebug>

#include "iAction.h"

class MoveAction : public QObject, public iAction
{
    Q_OBJECT
    Q_INTERFACES(iAction)
    Q_PLUGIN_METADATA(IID "PluginService.Action.Move")

public:
    explicit MoveAction(QObject *parent = 0);


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
      * @brief Moves a file
      * @param source
      * @param destination
      * @return boolean
      */
     bool moveFile(QFileInfo source, QFileInfo destination);

     /**
      * @brief Moves a directory
      * @param source
      * @param destination
      * @return
      */
     bool moveDirectory(QFileInfo source, QFileInfo destination);
};

#endif // MOVEACTON_H
