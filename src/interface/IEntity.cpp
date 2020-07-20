/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** IEntity
*/

#include "interface/IEntity.hpp"

IEntity::IEntity(EType type, void *objAddr)
     : _type{ type }, _alive{ true }, _needFree{ false }, _objAddr{ objAddr }
{ }