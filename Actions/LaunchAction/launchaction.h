#ifndef LAUNCHACTION_H
#define LAUNCHACTION_H

#include <QObject>
#include <QtPlugin>
#include <QString>
#include <QDebug>
#include <QProcess>
#include <QThread>
#include "iAction.h"

class LaunchAction : public QObject, public iAction
{
    Q_OBJECT
    Q_INTERFACES(iAction)
    Q_PLUGIN_METADATA(IID "PluginService.Action.Launch")

public:
    explicit LaunchAction(QObject *parent = 0);


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
};

#endif // LAUNCHACTION_H
