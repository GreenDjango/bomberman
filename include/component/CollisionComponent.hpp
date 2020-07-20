/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** CollisionComponent
*/

#ifndef COLLISIONCOMPONENT_HPP_
#define COLLISIONCOMPONENT_HPP_

#include "interface/IEntityComponent.hpp"
#include <irrlicht/irrlicht.h>
#include <vector>

class CollisionComponent : public virtual IEntityComponent
{
private:
    bool alive; 
    irr::core::vector3df _idbx;
    irr::scene::ISceneNode *_node;
    std::vector<std::pair<CollisionComponent *, irr::scene::ISceneNodeAnimator *>> _host;
    std::vector<CollisionComponent *> _links;
    void removeAnimatorCollision(irr::scene::ISceneNodeAnimator *);
    void deleteLink(CollisionComponent *col);
public:
    CollisionComponent(irr::core::vector3df idbx);
    virtual ~CollisionComponent() { };
    //
    void setNode(irr::scene::ISceneNode *node) { _node = node; };
    bool createCollision(CollisionComponent *col, irr::scene::ISceneManager* smgr);
    bool supLinkCollision(CollisionComponent *col);
    void drop();
};

#endif /* !COLLISIONCOMPONENT_HPP_ */
