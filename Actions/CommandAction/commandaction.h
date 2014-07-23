#ifndef COMMANDACTION_H
#define COMMANDACTION_H

#include <QObject>
#include <QtPlugin>
#include <QString>
#include <QDebug>
#include <QDir>
#include <QProcess>

#include "iAction.h"

class CommandAction : public QObject, public iAction
{
    Q_OBJECT
    Q_INTERFACES(iAction)
    Q_PLUGIN_METADATA(IID "PluginService.Action.Command")

public:
    explicit CommandAction(QObject *parent = 0);

    ~CommandAction();

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
     /**
     * Reads the output from the system shell
     */
     void ShellReadyRead();

private:

     /**
      * @brief The Error string;
      */
     QString m_errorString;

     /*!
     * The QProcess that controls the system shell
     */
     QProcess* mShell;

     /*!
     * The path for the system shell
     */
     QString mShellPath;

     /*!
     * Finds the Plugin Directory
     */
     void StartShell();
};

#endif // COMMANDACTION_H
