#include "core/logging/loggers.hpp"

#include <ranges>

namespace echo::core::logging
{

std::unique_ptr<Loggers> Loggers::s_instance = nullptr;
std::mutex Loggers::s_loggers_mutex = {};

Loggers *Loggers::get_instance()
{
    if (!s_instance)
    {
        s_instance = std::unique_ptr<Loggers>(new Loggers());
    }

    return s_instance.get();
}

void Loggers::cleanup()
{
    auto lock = std::lock_guard<std::mutex>(s_loggers_mutex);

    if (s_instance)
    {
        s_instance.reset(nullptr);
        s_instance = nullptr;
    }
}

void Loggers::add(const std::shared_ptr<interfaces::ILogger> &logger, const std::string &name)
{
    auto lock = std::lock_guard<std::mutex>(s_loggers_mutex);

    if (auto it = m_loggers.find(name); it == m_loggers.end())
    {
        m_loggers[name] = std::pair<bool, std::shared_ptr<interfaces::ILogger>>(true, std::move(logger));
    }
}

void Loggers::remove(const std::string &name)
{
    auto lock = std::lock_guard<std::mutex>(s_loggers_mutex);

    if (auto it = m_loggers.find(name); it != m_loggers.end())
    {
        m_loggers.erase(it);
    }
}

void Loggers::enable_one(const std::string &name)
{
    auto lock = std::lock_guard<std::mutex>(s_loggers_mutex);

    if (auto it = m_loggers.find(name); it != m_loggers.end())
    {
        it->second.first = true;
    }
}

void Loggers::disable_one(const std::string &name)
{
    auto lock = std::lock_guard<std::mutex>(s_loggers_mutex);

    if (auto it = m_loggers.find(name); it != m_loggers.end())
    {
        it->second.first = false;
    }
}

void Loggers::enable_all()
{
    auto lock = std::lock_guard<std::mutex>(s_loggers_mutex);

    for (auto &[key, value] : m_loggers)
    {
        value.first = true;
    }
}

void Loggers::disable_all()
{
    auto lock = std::lock_guard<std::mutex>(s_loggers_mutex);

    for (auto &[key, value] : m_loggers)
    {
        value.first = false;
    }
}

bool Loggers::is_enable(const std::string &name) const
{
    for (const auto &[key, value] : m_loggers)
    {
        if (name == key)
        {
            return value.first;
        }
    }
    return false;
}

std::shared_ptr<interfaces::ILogger> Loggers::find(const std::string &name) const
{
    for (const auto &[key, value] : m_loggers)
    {
        if (name == key)
        {
            return value.second;
        }
    }
    return nullptr;
}

} // namespace echo::core::logging
