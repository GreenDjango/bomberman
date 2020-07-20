/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** MotionComponent
*/

#include "component/MotionComponent.hpp"

MotionComponent::MotionComponent()
    : IEntityComponent{ IEntity::EType::UNKNOWN, nullptr }
    , _mov_speed{ 0,0,0 }, _mov_max_speed{ 100, 100, 100 }, _mov_acceleration{ 0,0,0 }
{
    IEntityComponent::addComponent(Motion, this);
}

void MotionComponent::update(const irr::f32 delta)
{
    if (_mov_acceleration.X != 0 || _mov_acceleration.Y != 0 || _mov_acceleration.Z != 0) {
        _mov_speed.X += (delta * _mov_acceleration.X);
        _mov_speed.Y += (delta * _mov_acceleration.Y);
        _mov_speed.Z += (delta * _mov_acceleration.Z);
        if (_mov_speed.X > _mov_max_speed.X)
            _mov_speed.X = _mov_max_speed.X;
        if (_mov_speed.Y > _mov_max_speed.Y)
            _mov_speed.Y = _mov_max_speed.Y;
        if (_mov_speed.Z > _mov_max_speed.Z)
            _mov_speed.Z = _mov_max_speed.Z;
    }
}