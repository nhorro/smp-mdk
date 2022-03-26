#ifndef SMP_LOGGER_H
#define SMP_LOGGER_H

#include "ILogger.h"
#include "Service.h"

#include "spdlog/spdlog.h"
#include <memory>

namespace Smp {
namespace Services {

class Logger: public ILogger, public Service 
{
public:
    Logger( ::Smp::String8 name,
            ::Smp::String8 description,
            ::Smp::IComposite* parent);
    ~Logger();

    /// Return identifier of log message kind by name.
    /// This method can be used for pre-defined log message kinds,
    /// but is especially useful for user-defined log message kinds.
    /// @param   messageKindName Name of log message kind.
    /// @return  Identifier of log message kind.
    /// @remarks It is guaranteed that this method always returns
    ///          the same id for the same messageKindName string.
    Smp::Services::LogMessageKind GetLogMessageKind(
        Smp::String8 messageKindName);

    /// Mechanism to log a messages.
    /// This function logs a message to the simulation log file.
    /// @param   sender Object that sends the message.
    /// @param   message The message to log.
    /// @param   kind Kind of message.
    virtual void Log(
        const IObject* sender,
        String8 message,
        const LogMessageKind kind = LMK_Information);
    
private:
    Smp::Services::LogMessageKind m_logMessageKind;
};

} // end namespace Services
} // end namespace Smp

#endif // SMP_LOGGER_H