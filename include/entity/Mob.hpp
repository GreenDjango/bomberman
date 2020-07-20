/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Mob
*/

#ifndef MOB_HPP_
#define MOB_HPP_

#include <irrlicht/irrlicht.h>
#include "entity/Block.hpp"
#include "entity/Player.hpp"
#include "class/ICollision.hpp"
#include "interface/IEntityComponent.hpp"
#include "component/GraphicsComponent.hpp"
#include "component/TransformComponent.hpp"
#include "component/MotionComponent.hpp"
#include "component/InteractionComponent.hpp"
#include "component/ActionEventComponent.hpp"

class Mob : public virtual IEntityComponent
, public GraphicsComponent
, public TransformComponent
, public MotionComponent
, public InteractionComponent
, public ActionEventComponent
, public ICollision
{
private:
    irr::core::vector2d<irr::u32> _targetPos;
    size_t _fromBlock;
    bool _target;
public:
    Mob(irr::scene::ISceneManager *smgr, int y, int x);
    bool receiveExplosion(irr::u32 y, irr::u32 x);
    virtual void update(TransformComponent *t);
    void processInteraction(enum interaction, IEntityComponent *e);
    virtual ~Mob() { };
    virtual void processAction(void *game);
    irr::core::vector2d<irr::u32> getMap2D();
    void IA(irr::core::vector2d<irr::u32> pos, std::array<Block *, 4> &cross, std::vector<Player *> &p);
    bool moveTarget(irr::u32 y, irr::u32 x);
    void deadAnimation();

    enum action {
        DEAD
    };
};

#endif /* !MOB_HPP_ */
