/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** ActionEventComponent
*/

#include "component/ActionEventComponent.hpp"

ActionEventComponent::ActionEventComponent()
    : IEntityComponent{ IEntity::EType::UNKNOWN, nullptr }
{
    IEntityComponent::addComponent(Component::ActionEvent, this);
}