/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** ICollision
*/

#ifndef ICOLLISION_HPP_
#define ICOLLISION_HPP_

#include <irrlicht/irrlicht.h>
#include <map>
#include <vector>

class ICollision
{
protected:
    irr::core::vector3df _idbx;
    irr::scene::ISceneNode *_node;
    std::vector<std::pair<ICollision *, irr::scene::ISceneNodeAnimator *>> _host;
    std::vector<ICollision *> _links;
private:
    bool enable;
public:
    virtual bool createCollision(ICollision *col, irr::scene::ISceneManager* smgr);
    virtual bool supLinkCollision(ICollision *col);
    virtual void drop();
    virtual void setNode(irr::scene::ISceneNode *node) { _node = node; };
    virtual void deleteLink(ICollision *col);
    virtual void removeAnimatorCollision(irr::scene::ISceneNodeAnimator *);
    bool reset();
    ICollision(irr::core::vector3df idbx);
    ~ICollision() { };
};

#endif /* !ICOLLISION_HPP_ */
