/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** InputEventComponent
*/

#ifndef INPUTEVENTCOMPONENT_HPP_
#define INPUTEVENTCOMPONENT_HPP_

#include "interface/IEntityComponent.hpp"
#include <irrlicht/irrlicht.h>

class InputEventComponent : public virtual IEntityComponent
{
public:
    InputEventComponent();
    virtual ~InputEventComponent() { };
    virtual void keyReceived(irr::EKEY_CODE key, bool pressed, bool keyIsDown[irr::KEY_KEY_CODES_COUNT]) = 0;
};

#endif /* !INPUTEVENTCOMPONENT_HPP_ */
