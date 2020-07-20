/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Room
*/

#include "entity/Room.hpp"

using namespace irr;
using namespace core;

Room::Room(irr::scene::ISceneManager* smgr)
    : IEntityComponent(IEntity::EType::ROOM, this), GraphicsComponent(smgr), TransformComponent()
{
    GraphicsComponent::addMesh("room.obj", false, {}, 21);
    TransformComponent::_pos = vector3df(33, -12, -8.5f);
    TransformComponent::_scale = vector3df(2.0f, 2.0f, 2.0f);
    TransformComponent::_rot = vector3df(0, 180, 0);
}