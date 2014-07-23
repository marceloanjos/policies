
#ifndef ITRIGGER_H
#define ITRIGGER_H

#include <QObject>
#include <QString>
#include <QMap>

/**
 * @brief Interface for Triggers
 */
class iTrigger
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
     * @brief Determines if the trigger has been met
     * @param params The parameters
     * @return bool
     */
     virtual bool triggered(QMap<QString,QVariant> params) = 0;

};

Q_DECLARE_INTERFACE( iTrigger, "iTrigger/0.1" )

#endif // ITRIGGER_H
