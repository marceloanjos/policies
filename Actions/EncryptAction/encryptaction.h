#ifndef ENCRYPTACTION_H
#define ENCRYPTACTION_H

#include <QObject>
#include <QtPlugin>
#include <QString>
#include <QDebug>
#include <QFileInfo>

#include "iAction.h"
#include "../../../Libs/Encryption/encryption.h"

class EncryptAction : public QObject, public iAction
{
    Q_OBJECT
    Q_INTERFACES(iAction)
    Q_PLUGIN_METADATA(IID "PluginService.Action.Encrypt")

public:
    explicit EncryptAction(QObject *parent = 0);


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

#endif // ENCRYPTACTION_H
