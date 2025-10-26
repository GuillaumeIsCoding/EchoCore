#pragma once
#ifndef ECHO_CORE_CONCAT_HPP
#define ECHO_CORE_CONCAT_HPP

#define ECHO_CONCAT_IMPL(x, y) x##y

#define ECHO_CONCAT(x, y) ECHO_CONCAT_IMPL(x, y)

#endif // ECHO_CORE_CONCAT_HPP