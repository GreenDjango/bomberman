/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** InteractionComponent
*/

#include "component/InteractionComponent.hpp"

InteractionComponent::InteractionComponent()
    : IEntityComponent{ IEntity::EType::UNKNOWN, nullptr }
    , _range{ -1, -1, -1 }
{
    IEntityComponent::addComponent(Component::Interaction, this);
}
