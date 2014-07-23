

#ifndef IACTION_H
#define IACTION_H

#include <QObject>
#include <QString>
#include <QMap>

/**
 * @brief Interface for Actions
 */
class iAction
{

public:

    /**
    * @brief Returns the name of the plugin
    */
    virtual QString name() = 0;

    /**
     * @brief Determines if the trigger had an error
     * @return bool
     */
    virtual bool hasError() = 0;

    /**
     * @brief Returns the error message as a QString
     * @return QString
     */\
    virtual QString errorString() = 0;

    /**
     * @brief Performs the action
     * @param params The parameters
     * @return bool
     */
     virtual bool performAction(QMap<QString,QVariant> params) = 0;

};

Q_DECLARE_INTERFACE( iAction, "iAction/0.1" )

#endif // IACTION_H
