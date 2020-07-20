/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** GraphicsComponent
*/

#ifndef GRAPHICSCOMPONENT_HPP_
#define GRAPHICSCOMPONENT_HPP_

#include "interface/IEntityComponent.hpp"
#include "component/TransformComponent.hpp"
#include <irrlicht/irrlicht.h>
#include <vector>

class GraphicsComponent : public virtual IEntityComponent
{
public:
    struct animation {
        irr::s32 start;
        irr::s32 end;
        irr::s32 speed;
        animation(irr::s32 start, irr::s32 end, irr::s32 speed) : start{ start }, end{ end }, speed{ speed } {}
    };

    GraphicsComponent(irr::scene::ISceneManager *smgr);
    virtual ~GraphicsComponent() { };
    bool setAnimation(std::size_t meshNum, std::size_t animNum);
    virtual void update(TransformComponent *t);
    irr::scene::IMeshSceneNode *getMesh(std::size_t meshNum);
    void deleteMesh(std::size_t meshNum) { _meshs.erase(_meshs.begin() + meshNum ); };
protected:
    irr::scene::ISceneManager *_smgr;
    bool _firstInit;
    irr::core::vector3df _lastCords;
    std::vector<std::pair<void *, std::vector<animation>>> _meshs;
    void addMesh(const irr::io::path &filename, bool animated = false, std::vector<animation> frame = {}, int id = 0);
    bool setMaterialTexture(size_t meshNum, irr::u32 textureLayer, irr::video::ITexture* texture);
};

#endif /* !GRAPHICSCOMPONENT_HPP_ */
