/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** TransformComponent
*/

#include "component/TransformComponent.hpp"

using namespace irr::core;

TransformComponent::TransformComponent()
    : IEntityComponent{ IEntity::EType::UNKNOWN, nullptr }
    , _pos{ vector3df(0,0,0) }, _rot{ vector3df(0,0,0) }, _scale{ vector3df(1,1,1) }, _updated{ true }
{
    IEntityComponent::addComponent(Transform, this);
}

bool TransformComponent::needUpdate()
{
    if (_updated && !(_updated = false))
        return true;
    return false;
}

void TransformComponent::update(MotionComponent *m, const irr::f32 deltaFrameRate)
{
    auto &speed = m->getMovSpeed();

    _pos.X += speed.X * deltaFrameRate;
    _pos.Y += speed.Y * deltaFrameRate;
    _pos.Z += speed.Z * deltaFrameRate;
    _updated = true;
}