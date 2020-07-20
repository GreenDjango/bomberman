/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Item
*/

#include "entity/Item.hpp"

using namespace irr;

Item::Item(scene::ISceneManager *smgr, ttype type, int posY, int posX, video::IVideoDriver *driver)
    : IEntityComponent{ IEntity::EType::ITEM, this }
    , GraphicsComponent{ smgr }
    , _type{ type }
{
    GraphicsComponent::addMesh("assets/items/items.x", true, {}, 42);
    int item = std::rand() % 5;
    if (item == 4 && std::rand() % 3 != 0)
        item = 2;        
    if (item == 1 && (_type = BOMB_UP)) {
        GraphicsComponent::setMaterialTexture(0, 0, driver->getTexture("assets/items/map_item_bombup.png"));
    } else if (item == 2 && (_type = SPEED_UP)) {
        GraphicsComponent::setMaterialTexture(0, 0, driver->getTexture("assets/items/map_item_speedup.png"));
    } else if (item == 3 && (_type = WALL_PASS)) {
        GraphicsComponent::setMaterialTexture(0, 0, driver->getTexture("assets/items/map_item_wallpass.png"));
    } else if (item == 4 && (_type = EXTRA_LIFE)) {
        GraphicsComponent::setMaterialTexture(0, 0, driver->getTexture("assets/items/map_item_extralife.png"));
    }
    TransformComponent::_rot = core::vector3df(0,180,0);
    TransformComponent::_pos = core::vector3df(posX * 2, 0.1f, posY * 2);
    TransformComponent::_scale = core::vector3df(1.3f);
    InteractionComponent::_range = core::vector3df(0,0,0);
}

void Item::drop()
{
    _alive = false;
    _needFree = true;
    GraphicsComponent::getMesh(0)->remove();
}

void Item::processInteraction(enum interaction, IEntityComponent *)
{ }

irr::core::vector2di Item::getMapPos()
{
    auto pos = TransformComponent::_pos;
    return {
        (s32)(floor(pos.X / 2 + 0.5)),
        (s32)(floor(pos.Z / 2 + 0.5))
    };
}