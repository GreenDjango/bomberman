/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** TimeEventComponent
*/

#ifndef TIMEEVENTCOMPONENT_HPP_
#define TIMEEVENTCOMPONENT_HPP_

#include "interface/IEntityComponent.hpp"
#include <irrlicht/irrlicht.h>
#include <vector>

class TimeEventComponent : public virtual IEntityComponent
{
protected:
    std::vector<std::pair<irr::f32, irr::u32>> _timers;
public:
    TimeEventComponent();
    void addTimer(irr::f32 sec, irr::u32 action);
    void update(const irr::f32 deltaFrameRate);
    virtual void updateTimer(irr::f32 sec, irr::u32 action);
    virtual void proccessTimer(irr::u32) = 0;
    virtual ~TimeEventComponent() { };
};

#endif /* !TIMEEVENTCOMPONENT_HPP_ */
