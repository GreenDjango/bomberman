/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** IEntityComponent
*/

#ifndef IENTITYCOMPONENT_HPP_
#define IENTITYCOMPONENT_HPP_

#include "interface/IEntity.hpp"
#include <map>

class IEntityComponent : public IEntity
{
public:
    enum Component {
        Graphics,
        Transform,
        Motion,
        InputEvent,
        Collision,
        ActionEvent,
        TimeEvent,
        Interaction,
    };
protected:
    std::map<Component, void*> _components;
    void addComponent(Component name, void *tthis);
public:
    IEntityComponent(IEntity::EType type, void *objAddr);
    void *getComponent(Component name) const;
    virtual ~IEntityComponent() { };
};

#endif /* !IENTITYCOMPONENT_HPP_ */
