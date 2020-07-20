/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** CollisionComponent
*/

#include "component/CollisionComponent.hpp"

using namespace irr;

CollisionComponent::CollisionComponent(core::vector3df idbx)
    : IEntityComponent{ IEntity::EType::UNKNOWN, nullptr }
    , alive{ false }, _idbx{ idbx }
{
    IEntityComponent::addComponent(Component::Collision, this);
}