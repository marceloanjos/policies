#ifndef TRIGGERTEMPLATE_H
#define TRIGGERTEMPLATE_H

#include <QObject>
#include <QtPlugin>
#include <QString>
#include <QDebug>

#include "iTrigger.h"

class TriggerTemplate : public QObject, public iTrigger
{
    Q_OBJECT
    Q_INTERFACES(iTrigger)
    Q_PLUGIN_METADATA(IID "PluginService.Trigger.Template")

public:
    explicit TriggerTemplate(QObject *parent = 0);


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
     * @brief Determines if the trigger has been met
     * @param Params The parameters
     * @return bool
     */
     bool triggered(QMap<QString,QVariant> params);

signals:

public slots:

private:

     /**
      * @brief The Error string;
      */
     QString m_errorString;

};

#endif // TRIGGERTEMPLATE_H
