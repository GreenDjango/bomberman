/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Player
*/

#ifndef PLAYER_HPP_
#define PLAYER_HPP_

#include "save.hpp"
#include "class/ICollision.hpp"
#include "interface/IEntityComponent.hpp"
#include "component/GraphicsComponent.hpp"
#include "component/TransformComponent.hpp"
#include "component/MotionComponent.hpp"
#include "component/InputEventComponent.hpp"
#include "component/ActionEventComponent.hpp"
#include "component/TimeEventComponent.hpp"
#include "component/InteractionComponent.hpp"
#include <irrlicht/irrlicht.h>
#include <array>

class Player : public virtual IEntityComponent
, public GraphicsComponent
, public TransformComponent
, public MotionComponent
, public InputEventComponent
, public ActionEventComponent
, public TimeEventComponent
, public InteractionComponent
, public ICollision
{
public:
    enum keyAction {
        FORWARD = 0,
        BACK = 1,
        LEFT = 2,
        RIGHT = 3,
        BOMB = 4
    };
    enum anim {
        IDLE = 0,
        WALK = 1,
        DEAD = 2
    };
    enum action {
        PLACE_BOMB = 0,
        PLAY_ITEM_SOUNG,
        PLAY_ITEM_LIFE_SOUNG,
        PLAY_DEATH_BY_MOB_SOUNG,
        PLAY_DEATH_BY_BOMB_SOUNG,
        DISABLE_WALL_PASS,
        WALL_PASS,
        RE_APPLY_COLLISION
    };
    enum timeEvent {
        T_DEAD = 0,
        END_SHIELD = 1,
        START_SHIELD = 2,
        END_SPEED,
        END_WALL_PASS
    };

    Player(const irr::io::path& filename, irr::scene::ISceneManager* smgr, int model);
    ~Player() {};
    //  [Getter & Setter]
    void setMoveKey(std::array<irr::EKEY_CODE, 5> keys) { _keys = keys; };
    void add_bomb_capacity(int nb) { _bomb_capacity += nb; };
    irr::core::vector2di getMapPos();
    int getBombRange() const { return _bomb_range; };
    int getBombeStrenght() const { return _bomb_strength; };
    int getBombCapacity() const { return _bomb_capacity; };
    int getLife() const { return _life; };
    int getMaxBombCapacity() const { return _max_bomb_capacity; };
    irr::f32 getTimeRemain(irr::u32 action);
    void receiveExplosion(int y, int x, int direction);
    //  [Component]
    void keyReceived(irr::EKEY_CODE key, bool pressed, bool keyIsDown[irr::KEY_KEY_CODES_COUNT]);
    void processAction(void *game);
    void proccessTimer(irr::u32 timeEvent);
    void processInteraction(enum interaction, IEntityComponent *e);
    savePlayer getSave();
    void applySave(savePlayer save);
    void setSpawn(irr::core::vector3df s) { _spawn = s; setPosition(s); };
private:
    std::array<irr::EKEY_CODE, 5> _keys;
    bool _stop;
    bool _shield;
    bool _wallPass;
    float speed;
    int _life;
    irr::core::vector3df _spawn;
    // stats
    int _max_bomb_capacity;
    int _bomb_capacity;
    int _bomb_range;
    int _bomb_strength;
    int _model;
};

#endif /* !PLAYER_HPP_ */
