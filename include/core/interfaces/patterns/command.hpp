#pragma once
#ifndef ECHO_CORE_COMMAND_HPP
#define ECHO_CORE_COMMAND_HPP

#include "core/macros/export.hpp"

#include <memory>

namespace echo::core::interfaces::patterns
{

class ECHO_CORE_EXPORT ICommand
{
  public:
    inline virtual ~ICommand() = 0;

    inline virtual void execute() = 0;
    inline virtual void undo() = 0;
    inline virtual void saveBackup() = 0;
};

class ECHO_CORE_EXPORT IInvoker
{
  public:
    inline virtual ~IInvoker() = 0;

    inline virtual void execute(const std::shared_ptr<ICommand> &command) = 0;
    inline virtual void undo() = 0;
};

class ECHO_CORE_EXPORT ICommandHistory
{
  public:
    inline virtual ~ICommandHistory() = 0;

    inline virtual void push(const std::shared_ptr<ICommand> &command) = 0;
    inline virtual std::shared_ptr<ICommand> pop() = 0;
};

ICommand::~ICommand() = default;

IInvoker::~IInvoker() = default;

ICommandHistory::~ICommandHistory() = default;

} // namespace echo::core::interfaces::patterns

#endif // ECHO_CORE_COMMAND_HPP