/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** TimeEventComponent
*/

#include "component/TimeEventComponent.hpp"
using namespace irr;

TimeEventComponent::TimeEventComponent()
    : IEntityComponent{ IEntity::EType::UNKNOWN, nullptr }
{
    IEntityComponent::addComponent(TimeEvent, this);
}

void TimeEventComponent::addTimer(irr::f32 sec, irr::u32 action)
{
    auto elem = std::pair<f32, u32>(sec, action);

    _timers.push_back(elem);
}

void TimeEventComponent::updateTimer(irr::f32 sec, irr::u32 action)
{
    bool add = true;
    for (auto &t : _timers) {
        if (t.second == action) {
            t.first = sec;
            add = false;
        }
    }
    if (add) {
        auto elem = std::pair<f32, u32>(sec, action);
        _timers.push_back(elem);
    }
}

void TimeEventComponent::update(const f32 deltaFrameRate)
{
    for (auto it = _timers.begin(); it != _timers.end(); ) {
        if (it->first < deltaFrameRate) {
            proccessTimer(it->second);
            it = _timers.erase(it);
        }
        else {
            it->first -= deltaFrameRate;
            it++;
        }
    }
}