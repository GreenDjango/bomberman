/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Item
*/

#ifndef ITEM_HPP_
#define ITEM_HPP_

#include "interface/IEntityComponent.hpp"
#include "component/GraphicsComponent.hpp"
#include "component/TransformComponent.hpp"
#include "component/InteractionComponent.hpp"
#include <irrlicht/irrlicht.h>

class Item : public virtual IEntityComponent
, public GraphicsComponent
, public TransformComponent
, public InteractionComponent
{
public:
    enum ttype {
        FIRE_UP,
        BOMB_UP,
        SPEED_UP,
        WALL_PASS,
        EXTRA_LIFE
    };
    Item(irr::scene::ISceneManager *smgr, ttype type, int posMapX, int posMapY, irr::video::IVideoDriver *driver);
    void processInteraction(enum interaction, IEntityComponent *e);
    irr::core::vector2di getMapPos();
    ttype getItemType() { return _type; };
    ~Item() { };
    void drop();
private:
    ttype _type;
};

#endif /* !ITEM_HPP_ */
