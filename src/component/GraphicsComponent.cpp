/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** GraphicsComponent
*/

#include "component/GraphicsComponent.hpp"
#include <stdexcept>

using namespace irr;

GraphicsComponent::GraphicsComponent(scene::ISceneManager *smgr)
    : IEntityComponent{ IEntity::EType::UNKNOWN, nullptr }
    , _smgr{ smgr }, _firstInit{ true }
{
    IEntityComponent::addComponent(Graphics, this);
}

void GraphicsComponent::addMesh(const io::path &filename, bool animated, std::vector<animation> frames, int id)
{
    scene::IAnimatedMesh *mesh{ _smgr->getMesh(filename) };
    scene::ISceneNode *parent = (id != 0) ? _smgr->getSceneNodeFromId(id) : nullptr;
    if (!mesh)
        throw std::runtime_error("[Graphics-C] - Can't load assets.");
    scene::ISceneNode *node;
    if (animated)
        node = _smgr->addAnimatedMeshSceneNode(mesh, parent);
    else
        node = _smgr->addMeshSceneNode(mesh, parent);
    if (!node)
            throw std::runtime_error("[Graphics-C] - Can't allow memory for mesh.");
    auto elem = std::pair<scene::ISceneNode *, std::vector<animation>>(node, frames);
    _meshs.push_back(elem);
    // default settings
    node->setMaterialFlag(video::EMF_LIGHTING, false);
}

scene::IMeshSceneNode *GraphicsComponent::getMesh(size_t meshNum)
{
    if (_meshs.size() <= meshNum)
        return nullptr;
    return (scene::IMeshSceneNode *)_meshs[meshNum].first;
}

bool GraphicsComponent::setMaterialTexture(size_t meshNum, u32 textureLayer, video::ITexture* texture)
{
    if (_meshs.size() <= meshNum)
        return false;
    ((scene::IMeshSceneNode *)_meshs[meshNum].first)->setMaterialTexture(textureLayer, texture);
    return true;
}

bool GraphicsComponent::setAnimation(size_t meshNum, size_t animNum)
{
    if (_meshs.size() <= meshNum
    || _meshs[meshNum].second.size() == 0 || _meshs[meshNum].second.size() <= animNum)
        return false;
    scene::IAnimatedMeshSceneNode *node = (scene::IAnimatedMeshSceneNode *)_meshs[meshNum].first;
    if (node->getStartFrame() != _meshs[meshNum].second[animNum].start
    || node->getEndFrame() != _meshs[meshNum].second[animNum].end) {
        node->setFrameLoop(_meshs[meshNum].second[animNum].start, _meshs[meshNum].second[animNum].end);
        node->setAnimationSpeed(_meshs[meshNum].second[animNum].speed);
        return true;
    }
    return false;
}

void GraphicsComponent::update(TransformComponent *t)
{
    scene::ISceneNode *node = (scene::ISceneNode *)_meshs[0].first;
    if (_firstInit)
        _firstInit = false;
    else {
        static const float marge = 0.1;
        if (node->getPosition().X < _lastCords.X - marge || _lastCords.X + marge < node->getPosition().X
        || node->getPosition().Y < _lastCords.Y - marge || _lastCords.Y + marge < node->getPosition().Y
        || node->getPosition().Z < _lastCords.Z - marge || _lastCords.Z + marge < node->getPosition().Z)
            t->setPosition(node->getPosition());
    }
    node->setScale(t->getScale());
    node->setRotation(t->getRot());
    node->setPosition(t->getPos());
    _lastCords = t->getPos();
}