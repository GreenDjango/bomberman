/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** IEntityComponent
*/

#include "interface/IEntityComponent.hpp"

IEntityComponent::IEntityComponent(IEntity::EType type, void *objAddr)
    : IEntity{ type, objAddr }
{
}

void *IEntityComponent::getComponent(Component name) const
{
    auto search = _components.find(name);
    return (search != _components.end() ? search->second : nullptr);
}

void IEntityComponent::addComponent(Component name, void *tthis)
{
    _components[name] = tthis;
}