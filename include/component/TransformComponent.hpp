/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** TransformComponent
*/

#ifndef TRANSFORMCOMPONENT_HPP_
#define TRANSFORMCOMPONENT_HPP_

#include "interface/IEntityComponent.hpp"
#include "component/MotionComponent.hpp"
#include <irrlicht/irrlicht.h>

class TransformComponent : public virtual IEntityComponent
{
protected:
    irr::core::vector3df _pos;
    irr::core::vector3df _rot;
    irr::core::vector3df _scale;
    bool _updated;
public:
    TransformComponent();
    virtual ~TransformComponent() { };
    bool needUpdate();
    bool isUpdated() const { return _updated; };
    const irr::core::vector3df &getPos() const { return _pos; };
    const irr::core::vector3df &getRot() const { return _rot; };
    const irr::core::vector3df &getScale() const { return _scale; };
    void setPosition(irr::core::vector3df pos) { _pos = pos; };
    virtual void update(MotionComponent *m, const irr::f32 deltaFrameRate);
};

#endif /* !TRANSFORMCOMPONENT_HPP_ */
