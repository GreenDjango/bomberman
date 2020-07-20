/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** save
*/

#ifndef SAVE_HPP_
#define SAVE_HPP_

#include <irrlicht/irrlicht.h>

struct savePlayer
{
    bool alive;
    int posY;
    int posX;
    int bombCapacity;
    int bombRange;
    int life;
    int model;
    irr::core::vector3df spawn;
};

struct saveMob
{
    irr::core::vector2d<irr::u32> pos;
};

struct saveBomberman
{
    irr::u32 magicNum;
    bool isVersus;
    irr::u32 nbPlayers;
    savePlayer player[4];
    irr::u32 nbBlobk;
    irr::core::vector2d<irr::u32> mapSize;
    char block[2000]; // max 26 * 38 (with border)
    irr::u32 nbMob;
    saveMob mob[1000];
    irr::u32 remain_time;
};

#endif /* !SAVE_HPP_ */
