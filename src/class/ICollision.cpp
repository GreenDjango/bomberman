/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** ICollision
*/

#include "class/ICollision.hpp"
#include <iostream>

using namespace irr;
using namespace core;
using namespace std;

ICollision::ICollision(vector3df idbx)
    : _idbx{ idbx }, _node{ nullptr }, enable{ true }
{ }

bool ICollision::createCollision(ICollision *col, irr::scene::ISceneManager* smgr)
{
    if (!col->_node || !_node) {
        std::cerr << "Bad collision settings\n";
        return false;
    }
    if (!enable)
        return false;
    for (auto &p : _host)
        if (p.first == col)
            return false;
    scene::ITriangleSelector* selector = smgr->createTriangleSelectorFromBoundingBox(
        col->_node
    );
    col->_node->setTriangleSelector(selector);
    scene::ISceneNodeAnimator* anim = smgr->createCollisionResponseAnimator(
        selector, _node, _idbx, core::vector3df(0,0,0), core::vector3df(0,0,0)
    );
    _node->addAnimator(anim);
    selector->drop();
    auto elem = pair<ICollision *, scene::ISceneNodeAnimator *>(col, anim);
    _host.push_back(elem);
    col->_links.push_back((ICollision *)this);
    return true;
}

void ICollision::deleteLink(ICollision *col)
{
    for (std::size_t i = 0; i < _links.size(); i++)
        if (_links[i] == col) {
            _links.erase(_links.begin() + i);
            return;
        }
}

void ICollision::removeAnimatorCollision(irr::scene::ISceneNodeAnimator *animator)
{
    _node->removeAnimator(animator);
    animator->drop();
}

bool ICollision::supLinkCollision(ICollision *col)
{
    if (!enable)
        return false;
    for (std::size_t i = 0; i < _host.size(); i++)
        if (_host[i].first == col) {
            removeAnimatorCollision(_host[i].second);
            _host.erase(_host.begin() + i);
            return true;
        } 
    return false;
}

bool ICollision::reset()
{
    if (enable)
        return false;
    enable = true;
    return true;
}

void ICollision::drop()
{
    if (!enable)
        return;
    enable = false;
    for (std::size_t i = 0; i < _host.size(); i++) {
        removeAnimatorCollision(_host[i].second);
        _host[i].first->deleteLink((ICollision *)this);
    }
    _host = { };
    for (std::size_t i = 0; i < _links.size(); i++) {
        _links[i]->supLinkCollision((ICollision *)this);
    }
    _links = { };
}