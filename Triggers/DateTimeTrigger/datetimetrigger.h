#ifndef DATETIMETRIGGER_H
#define DATETIMETRIGGER_H

#include <QObject>
#include <QtPlugin>
#include <QString>
#include <QDateTime>
#include <QDebug>

#include "iTrigger.h"

/**
 * @brief Triggers a policy based on a specific date and time
 */
class DateTimeTrigger : public QObject, public iTrigger
{
    Q_OBJECT
    Q_INTERFACES(iTrigger)
    Q_PLUGIN_METADATA(IID "PluginService.Trigger.DateTimeTrigger")

public:
    explicit DateTimeTrigger(QObject *parent = 0);


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

#endif // DATETIMETRIGGER_H
