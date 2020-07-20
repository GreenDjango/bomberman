/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** ActionEventComponent
*/

#ifndef ACTIONEVENTCOMPONENT_HPP_
#define ACTIONEVENTCOMPONENT_HPP_

#include "interface/IEntityComponent.hpp"
#include <irrlicht/irrlicht.h>
#include <vector>

class ActionEventComponent : public virtual IEntityComponent
{
protected:
    std::vector<irr::u32> _actionsId;
public:
    ActionEventComponent();
    virtual ~ActionEventComponent() { };
    void addAction(irr::u32 action) { _actionsId.push_back(action); };
    std::size_t getNbAction() const { return _actionsId.size(); };
    virtual void processAction(void *game) = 0;
};

#endif /* !ACTIONEVENTCOMPONENT_HPP_ */
