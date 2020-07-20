/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** ECSCore
*/

#ifndef ECSCORE_HPP_
#define ECSCORE_HPP_

#include "interface/IEntityComponent.hpp"
#include <irrlicht/irrlicht.h>
#include <vector>

class ECS
{
public:
    static void interactionSystem(IEntityComponent *entity, std::vector<IEntityComponent *> &entities); 
    static void eventSystem(IEntityComponent *entity, const irr::f32 frameDeltaTime);
    static void renderSystem(IEntityComponent *entity, const irr::f32 frameDeltaTime);
    static void actionSystem(IEntityComponent *entity, void *game);
};

#endif /* !ECSCORE_HPP_ */
