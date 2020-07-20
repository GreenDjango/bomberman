/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** InputEventComponent
*/

#include "component/InputEventComponent.hpp"

InputEventComponent::InputEventComponent()
    : IEntityComponent{ IEntity::EType::UNKNOWN, nullptr }
{
    IEntityComponent::addComponent(InputEvent, this);
}