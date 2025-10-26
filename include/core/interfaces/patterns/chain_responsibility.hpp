#pragma once
#ifndef ECHO_CORE_CHAIN_RESPONSIBILITY_HPP
#define ECHO_CORE_CHAIN_RESPONSIBILITY_HPP

#include "core/macros/export.hpp"

#include <memory>

namespace echo::core::interfaces::patterns
{

class IHandler;
class IRequest;

class ECHO_CORE_EXPORT IHandler
{
  public:
    inline virtual ~IHandler() = 0;

    inline virtual void set_next(const std::shared_ptr<IHandler> &handler) = 0;

    inline virtual std::shared_ptr<IHandler> get_next() const = 0;

    inline virtual void handle(const std::shared_ptr<IRequest> &request) = 0;
    inline virtual void handle(std::unique_ptr<IRequest> request) = 0;
};

class ECHO_CORE_EXPORT IRequest
{
  public:
    inline virtual ~IRequest() = 0;

    inline virtual void request(IHandler *handler) = 0;
    inline virtual void request(const std::shared_ptr<IHandler> &handler) = 0;
    inline virtual void request(std::unique_ptr<IHandler> handler) = 0;
};

IHandler::~IHandler() = default;

IRequest::~IRequest() = default;

} // namespace echo::core::interfaces::patterns

#endif // ECHO_CORE_CHAIN_RESPONSIBILITY_HPP