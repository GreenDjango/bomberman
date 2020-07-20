/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Player
*/

#include "entity/Item.hpp"
#include "entity/Player.hpp"
#include "entity/Bomb.hpp"
#include "Game.hpp"

using namespace irr;
using namespace core;

Player::Player(const io::path& filename, scene::ISceneManager* smgr, int model)
    : IEntityComponent(IEntity::EType::PLAYER, this), GraphicsComponent(smgr), ICollision(vector3df(0.65, 0.01, 0.65))
    , _stop{ false }, _shield{ false }, _wallPass{ false }, speed{ 5 }, _life{ 3 }
{
    GraphicsComponent::addMesh(filename, true, { animation(0, 199, 25), animation(300, 353, 80), animation(200, 300, 25) }, 42);
    GraphicsComponent::setAnimation(0, anim::IDLE);
    TransformComponent::_rot = vector3df(-90.0,0,0);
    TransformComponent::_pos = vector3df(2.0,0.2,2.0);
    InteractionComponent::_range = vector3df(1,1,1);

    _node = (scene::IAnimatedMeshSceneNode *)GraphicsComponent::_meshs[0].first;
    _alive = true;
    _bomb_capacity = 1;
    _max_bomb_capacity = 1;
    _bomb_range = 2;
    _bomb_strength = 1;
    _model = model;
    setNode(_node);
}

void Player::keyReceived(EKEY_CODE key, bool pressed, bool keyIsDown[KEY_KEY_CODES_COUNT])
{
    if (_stop)
        return;
    bool walk = true;
    if (keyIsDown[_keys[keyAction::FORWARD]]) {
        MotionComponent::_mov_speed = vector3df(0,0,speed);
        TransformComponent::_rot.Y = 180;
    }
    else if (keyIsDown[_keys[keyAction::BACK]]) {
        MotionComponent::_mov_speed = vector3df(0,0,-speed);
        TransformComponent::_rot.Y = 0;
    }
    else if (keyIsDown[_keys[keyAction::LEFT]]) {
        MotionComponent::_mov_speed = vector3df(-speed,0,0);
        TransformComponent::_rot.Y = 90;
    }
    else if (keyIsDown[_keys[keyAction::RIGHT]]) {
        MotionComponent::_mov_speed = vector3df(speed,0,0);
        TransformComponent::_rot.Y = -90;
    }
    else {
        walk = false;
        GraphicsComponent::setAnimation(0, anim::IDLE);
        MotionComponent::_mov_speed = vector3df(0,0,0);
    }
    if (walk) {
        GraphicsComponent::setAnimation(0, anim::WALK);
        TransformComponent::_updated = true;
    }
    if (key == _keys[keyAction::BOMB] && !pressed && _bomb_capacity > 0 && !_shield && !_wallPass)
        ActionEventComponent::addAction(action::PLACE_BOMB);
}

irr::f32 Player::getTimeRemain(u32 action)
{
    irr::f32 res = 0.0;
    for (auto &p : TimeEventComponent::_timers) {
        if (p.second == action)
            res = p.first;
    }
    return res;
}

void Player::proccessTimer(u32 action)
{
    switch (action)
    {
    case timeEvent::T_DEAD:
        _life--;
        if (_life < 0)
            IEntity::_alive = false;
        else {
            _stop = false;
            MotionComponent::_mov_acceleration = vector3df(0,0,0);
            MotionComponent::_mov_speed = vector3df(0,0,0);
            speed = 5.0;
            setPosition(_spawn);
            GraphicsComponent::setAnimation(0, IDLE);
            ActionEventComponent::addAction(action::RE_APPLY_COLLISION);
        }
    break;
    case timeEvent::START_SHIELD:
        _stop = false;
        _mov_speed = core::vector3df(0,0,0);
        _mov_acceleration = core::vector3df(0,0,0);
        GraphicsComponent::setAnimation(0, anim::IDLE);
        break;   
    case timeEvent::END_SHIELD:
        if (!_wallPass)
            GraphicsComponent::getMesh(0)->setMaterialType(video::EMT_SOLID);
        _shield = false;
        break;
    case timeEvent::END_SPEED:
        speed = 5.0;
    break;
    case timeEvent::END_WALL_PASS:
        ActionEventComponent::addAction(DISABLE_WALL_PASS);
    break;
    };
}

void Player::processAction(void *g)
{
    Game *game = (Game *)g;
    while (ActionEventComponent::_actionsId.size() > 0) {
        auto a = _actionsId.back();

        if (a == action::PLACE_BOMB) {
            bool caseAlreadyUsed = false;
            vector2di dest = getMapPos();
            for (auto &b : game->getBombs())
                if (b->getMapPos().X == dest.X && b->getMapPos().Y == dest.Y) {
                    caseAlreadyUsed = true;
                    break;
                }
            if (!caseAlreadyUsed) {
                Bomb *bomb = new Bomb{this, _smgr };
                game->getBombs().push_back(bomb);
                game->getEntites().push_back(bomb);
            }
        }
        else if (a == action::PLAY_ITEM_SOUNG)
            game->getSounManager().takeObj();
        else if (a == action::PLAY_ITEM_LIFE_SOUNG)
            game->getSounManager().takeLife();
        else if (a == action::PLAY_DEATH_BY_MOB_SOUNG)
            game->getSounManager().audienceDisappoint();
        else if (a == action::PLAY_DEATH_BY_BOMB_SOUNG) {
            game->getSounManager().death();
            game->getSounManager().audienceStir();
        } else if (a == action::DISABLE_WALL_PASS) {
            if (!game->getMap()->isOnWall(this)) {
                GraphicsComponent::getMesh(0)->setMaterialType(video::EMT_SOLID);
                _wallPass = false;
                game->getMap()->disableWallPass(this);
            }
            else
                TimeEventComponent::updateTimer(0, timeEvent::END_WALL_PASS);
        }
        else if (a == action::WALL_PASS) {
            game->getMap()->applyWallPass(this);
        }
        else if (a == action::RE_APPLY_COLLISION) {
            game->getMap()->reSetInteraction(this);
        }

        _actionsId.pop_back();
    }
}

irr::core::vector2di Player::getMapPos()
{
    auto pos = TransformComponent::_pos;
    return {
        (s32)(floor(pos.X / 2 + 0.5)),
        (s32)(floor(pos.Z / 2 + 0.5))
    };
}

void Player::processInteraction(enum interaction i, IEntityComponent *e)
{
    switch (i)
    {
    case interaction::Range:
        if (e->getType() == IEntity::EType::ITEM) {
            auto t = ((Item *)e->getObj())->getItemType();
            if (t == Item::ttype::EXTRA_LIFE)
                ActionEventComponent::addAction(PLAY_ITEM_LIFE_SOUNG);
            else
                ActionEventComponent::addAction(PLAY_ITEM_SOUNG);
            if (t == Item::ttype::BOMB_UP) {
                _bomb_capacity += 1;
                _max_bomb_capacity += 1;
            }
            else if (t == Item::ttype::FIRE_UP)
                _bomb_range += 1;
            else if (t == Item::ttype::SPEED_UP) {
                TimeEventComponent::updateTimer(10.0, END_SPEED);
                speed = 7.0;
                auto vec = core::vector3df((_mov_speed.X != 0) ? ((_mov_speed.X > 0) ? speed : -speed) : 0.0
                , 0.0
                , (_mov_speed.Z != 0) ? ((_mov_speed.Z > 0) ? speed : -speed) : 0.0);
                MotionComponent::_mov_speed = vec;
            }
            else if (t == Item::ttype::WALL_PASS) {
                ActionEventComponent::addAction(action::WALL_PASS);
                GraphicsComponent::getMesh(0)->setMaterialType(video::EMT_TRANSPARENT_ADD_COLOR);
                TimeEventComponent::updateTimer(3.0, timeEvent::END_WALL_PASS);
                _wallPass = true;
            }
            if (e->isAlive()) {
                auto *g = (GraphicsComponent *)e->getComponent(Component::Graphics);
                if (g)
                    g->getMesh(0)->remove();
                e->setAlive(false);
            }
        }
        else if (e->getType() == IEntity::EType::MOB && !_shield) {
            ActionEventComponent::addAction(PLAY_DEATH_BY_MOB_SOUNG);
            _life--;
            if (_life < 0) {
                GraphicsComponent::setAnimation(0,anim::DEAD);
                _alive = false;
            }
            else {
                GraphicsComponent::setAnimation(0, anim::DEAD);
                _stop = true;
                _shield = true;
                GraphicsComponent::getMesh(0)->setMaterialType(video::EMT_TRANSPARENT_ADD_COLOR);
                TimeEventComponent::addTimer(0.4, timeEvent::START_SHIELD);
                MotionComponent::_mov_speed = core::vector3df(-_mov_speed.X,0,-_mov_speed.Z);
                MotionComponent::_mov_acceleration = core::vector3df(_mov_speed.X/10,0,-_mov_speed.Z/10);
                TimeEventComponent::addTimer(3.0, timeEvent::END_SHIELD);
            }
        }
        break;
    }
}

void Player::receiveExplosion(int y, int x, int direction)
{
    if (y == (int)(floor(_node->getPosition().Z / 2 + 0.5))
    && x == (int)(floor(_node->getPosition().X / 2 + 0.5))
    && !_shield) {
        static const float vH = 40;
        static const float vL = 60;
        ActionEventComponent::addAction(PLAY_DEATH_BY_BOMB_SOUNG);
        _stop = true;
        ICollision::drop();
        GraphicsComponent::setAnimation(0, anim::DEAD);
        MotionComponent::_mov_acceleration = vector3df(0, -50, 0);
        TimeEventComponent::addTimer(2.0, timeEvent::T_DEAD);
        switch (direction)
        {
        case 0: MotionComponent::_mov_speed = vector3df(-vL,vH,0);  break;
        case 1: MotionComponent::_mov_speed = vector3df(vL,vH,0);   break;
        case 2: MotionComponent::_mov_speed = vector3df(0,vH,-vL);  break;
        case 3: MotionComponent::_mov_speed = vector3df(0,vH,vL);   break;
        }
    }
}

savePlayer Player::getSave()
{
    savePlayer save;
    //memset(&save, 0, sizeof(savePlayer));
    save.alive = _alive,
    save.posY = getMapPos().Y,
    save.posX = getMapPos().X,
    save.bombCapacity = _max_bomb_capacity;
    save.bombRange = _bomb_range;
    save.life = _life;
    save.spawn = _spawn;
    save.model = _model;
    return save;
}

void Player::applySave(savePlayer save)
{
    _alive = save.alive;
    TransformComponent::_pos = core::vector3df(save.posX * 2, 0.2, save.posY * 2);
    _bomb_capacity = save.bombCapacity;
    _bomb_range = save.bombRange;
    _life = save.life;
    _spawn = save.spawn;
    _model = save.model;
}