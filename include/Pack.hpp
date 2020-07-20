/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Pack
*/

#ifndef PACK_HPP_
#define PACK_HPP_

#include <irrlicht/irrlicht.h>
#include <array>

namespace staticText {
    constexpr const wchar_t *helpMob = L"--- Player 1\n arrow : move\n space : place bomb\n--- Player 2\n Z Q S D : move\n A : place bomb\n--- Rules : \nYou win when all mobs are killed\nYou loose when a player die\n";
    constexpr const wchar_t *helpVs = L"--- Player 1\n arrow : move\n space : place bomb\n--- Player 2\n Z Q S D : move\n A : place bomb\n--- Rules : \nYou win when you kill opponents\n";
};

class Pack
{
public:
    static irr::SIrrlichtCreationParameters deviceParameters(
        irr::core::dimension2d<irr::u32> dim,
        irr::video::E_DRIVER_TYPE driver_type,
        irr::u8 AA,
        irr::u8 bits,
        bool stencilbuffer,
        irr::ELOG_LEVEL log
    );

    static std::array<irr::EKEY_CODE, 5> playerKeys(
        irr::EKEY_CODE forward,
        irr::EKEY_CODE back,
        irr::EKEY_CODE left,
        irr::EKEY_CODE right,
        irr::EKEY_CODE place_bomb
    );

    static irr::SIrrlichtCreationParameters default_deviceParameters();
    static irr::SIrrlichtCreationParameters windows10_deviceParameters();
    static std::array<irr::EKEY_CODE, 5> default_playerKeys(int num);
};

#endif /* !PACK_HPP_ */
