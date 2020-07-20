/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Map
*/

#ifndef MAP_HPP_
#define MAP_HPP_

#include "save.hpp"
#include "entity/Block.hpp"
#include "entity/Player.hpp"
#include "entity/Mob.hpp"
#include "entity/Bomb.hpp"
#include <irrlicht/irrlicht.h>
#include <vector>

class Map
{
private:
    irr::core::vector2d<irr::u32> _size;
    irr::scene::ISceneManager *_smgr;
    irr::video::IVideoDriver *_driver;
    std::vector<Block *> _map;
    std::vector<Mob *>_mobs;
public:
    Map(irr::core::vector2d<irr::u32> size, irr::scene::ISceneManager *smgr, irr::video::IVideoDriver *driver);
    ~Map() { };
    void appendEntities(std::vector<IEntityComponent *> &e);
    void setInteraction(std::vector<Player *> &players, irr::scene::ISceneManager *smgr);
    std::array<int, 4> applyExplosion(irr::core::vector2d<irr::u32> pos, irr::u32 range, irr::u32 strength, std::vector<Player *> &p, std::vector<IEntityComponent *> &e, std::vector<Bomb *> &b);
    bool block_explosion(irr::s32 y, irr::s32 x, int &tmp_st, int &res, std::vector<Player *> &player, int direction, std::vector<IEntityComponent *> &e, std::vector<Bomb *> &b);
    std::size_t getObjIndex(irr::s32 y, irr::s32 x);
    void generateMob(irr::scene::ISceneManager *smgr, int mobSpwan);
    void mobIA(std::vector<Player *> &p);
    bool isOnWall(Player *p);
    void disableWallPass(Player *p);
    void applyWallPass(Player *p);
    irr::core::vector3df getPosCorner(int num);
    std::vector<Mob *> &getMobs() { return _mobs; };
    void save(saveBomberman *);
    void load(saveBomberman *);
    void reSetInteraction(Player *p);
    void dropMob();
    irr::u32 getNbMob();
};

#endif /* !MAP_HPP_ */
