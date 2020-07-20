/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Bomb
*/

#ifndef BOMB_HPP_
#define BOMB_HPP_

#include "class/ICollision.hpp"
#include "interface/IEntityComponent.hpp"
#include "component/GraphicsComponent.hpp"
#include "component/TransformComponent.hpp"
#include "component/ActionEventComponent.hpp"
#include "component/TimeEventComponent.hpp"
#include "entity/Player.hpp"
#include <irrlicht/irrlicht.h>

class Bomb : public virtual IEntityComponent
, public GraphicsComponent
, public TransformComponent
, public ActionEventComponent
, public TimeEventComponent
, public ICollision
{
private:
    Player *_poseur;
    irr::core::vector2di _pos;
    std::vector<Player *> _remainCollisionPlayer;
    bool outBomb(Player *p);
    int _range;
public:
    enum timeEvent {
        Explose
    };
    enum actionEvent {
        Explose_Map,
        Interaction,
        RemainInteraction
    };

    Bomb(Player *poseur, irr::scene::ISceneManager* smgr);
    ~Bomb() { };
    void explose(irr::scene::ISceneManager* smgr, std::array<int, 4> cross);
    irr::core::vector2di getMapPos() { return _pos; };
    // Component
    void proccessTimer(irr::u32 action);
    void processAction(void *g);
};

#endif /* !BOMB_HPP_ */
