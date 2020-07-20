/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** InteractionComponent
*/

#ifndef INTERACTIONCOMPONENT_HPP_
#define INTERACTIONCOMPONENT_HPP_

#include "interface/IEntityComponent.hpp"
#include <irrlicht/irrlicht.h>

class InteractionComponent : public virtual IEntityComponent
{
protected:
    // range > 0    -> can take obj + takable
    // range == 0   -> takable
    // range < 0    -> nothing
    irr::core::vector3df _range;
public:
    enum interaction
    {
        Range
    };

    InteractionComponent();
    const irr::core::vector3df &getRange() const { return _range; };
    virtual void processInteraction(enum interaction, IEntityComponent *e) = 0;
    virtual ~InteractionComponent() { };
};

#endif /* !INTERACTIONCOMPONENT_HPP_ */
