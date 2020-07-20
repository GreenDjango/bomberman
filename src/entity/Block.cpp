/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Block
*/

#include "entity/Block.hpp"

using namespace irr;

Block::Block(char type, core::vector2d<u32> pos, irr::scene::ISceneManager *smgr, int corner, int border)
    : IEntityComponent{ EType::BLOCK, this }, GraphicsComponent{ smgr }, ICollision{ core::vector3df(0,0,0) }
    , _type{ type }, _pos{ pos }, _corner{ corner }, _border{ border }
{
    if (type == '|') {
        if (border >= 0) {
            GraphicsComponent::addMesh("assets/map/wall.obj", false, {}, 42);
            TransformComponent::_rot = core::vector3df(0, (float)border, 0);
        }
        else {
            GraphicsComponent::addMesh("assets/map/wall_angle.obj", false, {}, 42);
            TransformComponent::_rot = core::vector3df(0, (float)corner, 0);
        }
    }
    else if (type == 'o') {
        GraphicsComponent::addMesh("assets/map/pillar.obj", false, {}, 42);
        TransformComponent::_scale = core::vector3df(0.90, 0.90, 0.90);
    }
    else if (type == 'x') {
        GraphicsComponent::addMesh("assets/map/brick.obj", false, {}, 42);
        TransformComponent::_scale = core::vector3df(0.90, 0.90, 0.90);
    }
    else
        GraphicsComponent::addMesh("assets/map/plane.obj", false, {}, 42);
    auto posB = core::vector3df((float)pos.X * 2, 0, (float)pos.Y * 2);
    TransformComponent::_pos = core::vector3df(posB);
    ICollision::setNode(GraphicsComponent::getMesh(0));
    if (type != '.' && type != '|') {
        GraphicsComponent::addMesh("assets/map/plane.obj", false, {}, 42);
        GraphicsComponent::getMesh(1)->setPosition(posB);
    }
}

#include <iostream>
void Block::update(char type)
{
    if (_type == 'x' && type == '.') {
        _type = '.';
        GraphicsComponent::getMesh(0)->remove();
        GraphicsComponent::getMesh(1)->remove();
        deleteMesh(1);
        deleteMesh(0);
        TransformComponent::_scale = core::vector3df(1,1,1);
        GraphicsComponent::addMesh("assets/map/plane.obj", false, {}, 42);
    }
    if (_type == '.' && type == 'x') {
        _type = 'x';
        GraphicsComponent::getMesh(0)->remove();
        deleteMesh(0);
        GraphicsComponent::addMesh("assets/map/brick.obj", false, {}, 42);
        TransformComponent::_scale = core::vector3df(0.90, 0.90, 0.90);
        ICollision::setNode(GraphicsComponent::getMesh(0));
        GraphicsComponent::addMesh("assets/map/plane.obj", false, {}, 42);
        GraphicsComponent::getMesh(1)->setPosition(TransformComponent::_pos);
    }
}

void Block::explose()
{
    if (_type == 'x' && IEntity::_alive) {
        ICollision::drop();
        _node->removeAll();
        _node->remove();
    }
    _type = '.';
}