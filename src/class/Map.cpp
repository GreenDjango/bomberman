/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Map
*/

#include "class/Map.hpp"
#include "entity/Item.hpp"
#include <stdexcept>

using namespace irr;

Map::Map(core::vector2d<u32> size, scene::ISceneManager *smgr, video::IVideoDriver *driver)
    : _size{ size }, _smgr{ smgr }, _driver{ driver }
{
    for (u32 i = 0; i < (_size.Y * _size.X); i++) {
        u32 y = i / _size.X;
        u32 x = i % _size.X;
        // Border
        if (!y || !x || y == _size.Y - 1 || x == _size.X - 1) {
            if (!y && !x)
                _map.push_back(new Block('|', { x, y }, smgr, 270, -1));
            else if (y == _size.Y - 1 && x == _size.X - 1)
                _map.push_back(new Block('|', { x, y }, smgr, 90, -1));
            else if (y == _size.Y - 1 && !x)
                _map.push_back(new Block('|', { x, y }, smgr, 0));
            else if (!y && x == _size.X - 1)
                _map.push_back(new Block('|', { x, y }, smgr, 180));
            else if (!y || y == _size.Y - 1)
                _map.push_back(new Block('|', { x, y }, smgr, -1, (!y) ? 180 : 0));
            else
                _map.push_back(new Block('|', { x, y }, smgr, -1, (!x) ? 270 : 90));
        }
        // Pillar
        else if (!(y % 2) && !(x % 2))
            _map.push_back(new Block('o', { x, y }, smgr));
        // Spawn
        else if ((y < 3 && x < 3) || (y < 3 && x > _size.X - 4)
        || (y > (_size.Y - 4) && x < 3) || (y > (_size.Y - 4) && x > _size.X - 4))
            _map.push_back(new Block('.', { x, y }, smgr));
        else if ((y == 3 && x == 1) || (y == 3 && x == _size.X - 2)
        || (x == 3 && y == 1) || (y == 1 && x == _size.X - 4)
        || (y == _size.Y - 4 && x == 1) || (y == _size.Y - 2 && x == 3)
        || (y == _size.Y - 4 && x == _size.X - 2) || (y == _size.Y - 2 && x == _size.X - 4)
        )
            _map.push_back(new Block('x', { x, y }, smgr));
        // Brick
        else
            _map.push_back(new Block((rand() % 8 < 4) ? '.' : 'x', { x, y }, smgr));
    }
}

void Map::setInteraction(std::vector<Player *> &players, scene::ISceneManager *smgr)
{
    for (auto *p : players)
        for (std::size_t i = 0; i < _map.size(); i++)
            if (_map[i]->getBlockType() == '|' || _map[i]->getBlockType() == 'o' || _map[i]->getBlockType() == 'x')
                p->ICollision::createCollision((ICollision *)_map[i], smgr);
}

#include <iostream>
void Map::reSetInteraction(Player *p)
{
    if (!p->ICollision::reset())
        return;
    for (std::size_t i = 0; i < _map.size(); i++)
        if (_map[i]->getBlockType() == '|' || _map[i]->getBlockType() == 'o' || _map[i]->getBlockType() == 'x')
            p->ICollision::createCollision((ICollision *)_map[i], _smgr);
}

void Map::appendEntities(std::vector<IEntityComponent *> &e)
{
    for (auto *b : _map)
        e.push_back(b);
    for (auto *m : _mobs)
        e.push_back(m);
}

std::array<int, 4> Map::applyExplosion(core::vector2d<u32> pos, u32 range, u32 strength, std::vector<Player *> &p, std::vector<IEntityComponent *> &e, std::vector<Bomb *> &b)
{
    std::array<int, 4> res{ 0,0,0,0 };
    if (_size.Y <= pos.Y || _size.X <= pos.X)
        return res;
    int tmp_st = strength;
    block_explosion(pos.Y, pos.X, tmp_st, tmp_st, p, 0, e, b);
    tmp_st = strength;
    for (s32 cx = pos.X - 1; cx >= (s32)(pos.X - range) && tmp_st; cx--)
        if (block_explosion(pos.Y, cx, tmp_st, res[0], p, 0, e, b))
            break;
    tmp_st = strength;
     for (s32 cx = pos.X + 1; cx <= (s32)(pos.X + range) && cx < (s32)_size.X && tmp_st; cx++)
        if (block_explosion(pos.Y, cx, tmp_st, res[1], p, 1, e, b))
            break;
    tmp_st = strength;
    for (s32 cy = pos.Y + 1; cy <= (s32)(pos.Y + range) && cy < (s32)_size.Y && tmp_st; cy++)
        if (block_explosion(cy, pos.X, tmp_st, res[3], p, 3, e, b))
            break;
    tmp_st = strength;
    for (s32 cy = pos.Y - 1; (cy >= (s32)(pos.Y - range)) && tmp_st; cy--)
        if (block_explosion(cy, pos.X, tmp_st, res[2], p, 2, e, b))
            break;
    return res;
}

std::size_t Map::getObjIndex(s32 y, s32 x)
{
    return y * _size.X + x;
}

bool Map::block_explosion(s32 y, s32 x, int &tmp_st, int &res, std::vector<Player *> &player, int direction, std::vector<IEntityComponent *> &e, std::vector<Bomb *> &bbs)
{
    if (_map[getObjIndex(y, x)]->getBlockType() == 'o' || _map[getObjIndex(y, x)]->getBlockType() == '|')
        return true;
    for (auto *en : e)
        if (en->getType() == IEntity::EType::ITEM && en->isAlive() && ((Item *)en->getObj())->getMapPos().Y == y
        && ((Item *)en->getObj())->getMapPos().X == x) {
            ((Item *)en->getObj())->drop();
            en->setAlive(false);
        }
    if (_map[getObjIndex(y, x)]->getBlockType() == 'x') {
        _map[getObjIndex(y, x)]->explose();
        if (std::rand() % 4 == 0)
            e.push_back(new Item{ _smgr, Item::ttype::FIRE_UP, (int)y, (int)x, _driver } );
        tmp_st -= 1;
    }
    res++;
    for (auto *p : player)
        p->receiveExplosion(y, x, direction);
    for (auto it = _mobs.begin(); it != _mobs.end(); )
        if ((*it)->receiveExplosion(y, x) || !(*it)->isAlive())
            it = _mobs.erase(it);
        else
            it++;
    for (auto *b : bbs) {
        if (b->getMapPos().Y == (s32)y && b->getMapPos().X == (s32)x)
            b->updateTimer(0.15, Bomb::timeEvent::Explose);
    }
    return false;
}

void Map::generateMob(irr::scene::ISceneManager *smgr, int mobSpwan)
{
    bool first = true;
    for (std::size_t i = 0; i < _map.size(); i++) {
        u32 y = i / _size.X;
        u32 x = i % _size.X;
        if ((y < 3 && x < 3) || (y < 3 && x > _size.X - 4)
        || (y > (_size.Y - 4) && x < 3) || (y > (_size.Y - 4) && x > _size.X - 4))
            continue;
        if (_map[i]->getBlockType() == '.' && (std::rand() % 100 < mobSpwan || (mobSpwan > 0 && first))) {
            _mobs.push_back(new Mob{ smgr, (int)_map[i]->get2DPos().Y, (int)_map[i]->get2DPos().X });
            first = false;
        }
    }
}

void Map::mobIA(std::vector<Player *> &players)
{
    for (auto *m : _mobs) {
        if (!m->isAlive())
            continue;
        auto p = m->getMap2D();
        std::array<std::size_t, 4> crossPos { getObjIndex(p.Y + 1, p.X), getObjIndex(p.Y, p.X + 1), getObjIndex(p.Y - 1, p.X), getObjIndex(p.Y, p.X - 1) };
        std::array<Block *, 4> cross;
        for (size_t i = 0; i < 4; i++)
            cross[i] = (crossPos[i] < _map.size()) ? _map[crossPos[i]] : nullptr;
        m->IA(p, cross, players);
    }
}

bool Map::isOnWall(Player *p)
{
    auto pos = p->getMapPos();

    if (getObjIndex(pos.Y, pos.X) < _map.size())
        return _map[getObjIndex(pos.Y, pos.X)]->getBlockType() == 'x';
    return false;
}

void Map::disableWallPass(Player *p)
{
    for (auto *b : _map)
        if (b->getBlockType() == 'x')
            p->createCollision(b, _smgr);
}

void Map::applyWallPass(Player *p)
{
    for (auto *b : _map)
        if (b->getBlockType() == 'x') {
            p->supLinkCollision(b);
            b->deleteLink(p);
        }
}

core::vector3df Map::getPosCorner(int num)
{
    switch (num) {
        case 0:     return core::vector3df(2, 0.2, 2);
        case 1:     return core::vector3df((_size.X - 2) * 2, 0.2, (_size.Y - 2) * 2);
        case 2:     return core::vector3df(2, 0.2, (_size.Y - 2) * 2);
        case 3:     return core::vector3df((_size.X - 2) * 2, 0.2, 2);
    }
    throw std::runtime_error{ "Invalide corner\n" };
}

void Map::save(saveBomberman *file)
{
    file->nbBlobk = _map.size();
    file->mapSize = _size;
    for (std::size_t i = 0; i < _map.size() && i < 2000; i++)
        file->block[i] = _map[i]->getBlockType();
    file->nbMob = 0;
    for (std::size_t i = 0; i < _mobs.size() && i < 2000; i++) {
        file->mob[i].pos = _mobs[i]->getMap2D();
        file->nbMob++;
    }
}

void Map::load(saveBomberman *file)
{
    for (std::size_t i = 0; i < _map.size() && i < file->nbBlobk && i < 2000; i++)
        _map[i]->update(file->block[i]);
    for (std::size_t i = 0; i < file->nbMob && i < 2000; i++)
        _mobs.push_back(new Mob{ _smgr, (int)file->mob[i].pos.Y, (int)file->mob[i].pos.X });
}

irr::u32 Map::getNbMob()
{
    u32 mobs = 0;

    for (auto& m : _mobs)
        if (m->isAlive())
            mobs++;
    return mobs;
}