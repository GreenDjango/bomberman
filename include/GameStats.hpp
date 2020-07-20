/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** GameStats
*/

#ifndef GAMESTATS_HPP_
#define GAMESTATS_HPP_

#include "irrlicht/irrlicht.h"

struct PlayerStats
{
    int life;
    int modelNum;
    irr::f32 wallPassTimer;
    irr::f32 speedTimer;
    int capacityBomb;
    int rangeBomb;
    int maxBomb;
};

struct GameStats
{
    bool isFinish;
    bool isVersus;
    const wchar_t* savePath;
    irr::u32 size;
    //Time in ms
    irr::u32 remainingTime;
    std::size_t nbPlayer;
    PlayerStats players[2];
    irr::u32 nbMob;
};

#endif /* !GAMESTATS_HPP_ */
