/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Pack
*/

#include "Pack.hpp"
#include <stdexcept>

using namespace irr;
using namespace core;
using namespace video;

SIrrlichtCreationParameters Pack::default_deviceParameters()
{
    return deviceParameters(dimension2d<u32>(1920,1080), E_DRIVER_TYPE::EDT_OPENGL, 4, 32, true, ELOG_LEVEL::ELL_ERROR);
}

SIrrlichtCreationParameters Pack::windows10_deviceParameters()
{
    return deviceParameters(dimension2d<u32>(1920,1080), E_DRIVER_TYPE::EDT_DIRECT3D9, 4, 32, true, ELOG_LEVEL::ELL_ERROR);
}

std::array<EKEY_CODE, 5> Pack::default_playerKeys(int num)
{
    switch (num)
    {
    case 0:
        return playerKeys(KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT, KEY_SPACE);
    case 1:
        return playerKeys(KEY_KEY_Z, KEY_KEY_S, KEY_KEY_Q, KEY_KEY_D, KEY_KEY_A);
    }
    throw std::invalid_argument("Bad player number, can't find keys config.");
}


// Generique
SIrrlichtCreationParameters Pack::deviceParameters(dimension2d<u32> dim, E_DRIVER_TYPE type, u8 AA, u8 bits, bool sb, ELOG_LEVEL log)
{
    SIrrlichtCreationParameters params{ SIrrlichtCreationParameters() };

    params.WindowSize = dim;
    params.DriverType = type;
    params.AntiAlias = AA;
    params.Bits = bits;
    params.Stencilbuffer = sb;
    params.LoggingLevel = log;
    return params;
}

std::array<EKEY_CODE, 5> Pack::playerKeys(EKEY_CODE f, EKEY_CODE b, EKEY_CODE l, EKEY_CODE r, EKEY_CODE p)
{
    return std::array<EKEY_CODE, 5>{ f, b, l, r, p };
}