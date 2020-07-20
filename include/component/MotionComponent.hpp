/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** MotionComponent
*/

#ifndef MOTIONCOMPONENT_HPP_
#define MOTIONCOMPONENT_HPP_

#include "interface/IEntityComponent.hpp"
#include <irrlicht/irrlicht.h>

class MotionComponent : public virtual IEntityComponent
{
protected:
    // movement
    irr::core::vector3df _mov_speed;
    irr::core::vector3df _mov_max_speed;
    irr::core::vector3df _mov_acceleration;
    irr::core::vector3df _prev_speed;
public:
    MotionComponent();
    virtual ~MotionComponent() { };
    virtual void update(const irr::f32 deltaFrameRate);
    // getter
    const irr::core::vector3df &getMovSpeed() const { return _mov_speed; };
};


#endif /* !MOTIONCOMPONENT_HPP_ */
