/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Room
*/

#ifndef ROOM_HPP_
#define ROOM_HPP_

#include "interface/IEntityComponent.hpp"
#include "component/GraphicsComponent.hpp"
#include "component/TransformComponent.hpp"
#include <irrlicht/irrlicht.h>

class Room : public virtual IEntityComponent, public GraphicsComponent, public TransformComponent
{
public:
    Room(irr::scene::ISceneManager* smgr);
    ~Room() { };
};

#endif /* !ROOM_HPP_ */
