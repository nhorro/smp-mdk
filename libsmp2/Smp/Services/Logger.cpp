#include "Logger.h"

#include <iostream>

#include "spdlog/spdlog.h"

namespace Smp {
namespace Services {

Logger::Logger( ::Smp::String8 name,
                ::Smp::String8 description,
                ::Smp::IComposite* parent)
    :
          Service(name,description,parent)
{
    try 
    {   
        spdlog::info("Hello");
    }
    catch (const spdlog::spdlog_ex& ex)
    {
        std::cerr << "Logger initialization failed: " << ex.what() << std::endl;
    }
}

Logger::~Logger()
{

}

Smp::Services::LogMessageKind Logger::GetLogMessageKind(Smp::String8 messageKindName)
{
    return m_logMessageKind;
}

void Logger::Log(const IObject* sender, String8 message, const LogMessageKind kind)
{
    String8 senderName = sender ? sender->GetName() : "user";
    switch(kind)
    {
        case LMK_Information:
        {
            spdlog::info("{}: {}", senderName, message);
        } break;

        case LMK_Event:
        {
            spdlog::info("{}: {}", senderName, message);
        } break;

        case LMK_Warning:
        {
            spdlog::warn("{}: {}", senderName, message);
        } break;

        case LMK_Error:
        {
            spdlog::error("{}: {}", senderName, message);
        } break;

        case LMK_Debug:
        {
            spdlog::debug("{}: {}", senderName, message);
        } break;
    }
}

} // end namespace Services
} // end namespace Smp