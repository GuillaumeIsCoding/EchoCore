#pragma once
#ifndef ECHO_CORE_MOUSE_CODES_HPP
#define ECHO_CORE_MOUSE_CODES_HPP

#include "types.hpp"

namespace echo::core
{

using MouseCode = uint16;

namespace mouse
{

enum : MouseCode
{
    // From glfw3.h
    Button0 = 0,
    Button1 = 1,
    Button2 = 2,
    Button3 = 3,
    Button4 = 4,
    Button5 = 5,
    Button6 = 6,
    Button7 = 7,

    ButtonLast = Button7,
    ButtonLeft = Button0,
    ButtonRight = Button1,
    ButtonMiddle = Button2
};

} // namespace mouse

} // namespace echo::core

#endif // ECHO_CORE_MOUSE_CODES_HPP