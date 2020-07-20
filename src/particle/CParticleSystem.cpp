/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** CParticleSystem
*/
#include "particle/CParticleSystem.hpp"

#include "particle/CBillboardParticleDrawer.hpp"
#include "particle/COrientedParticleDrawer.hpp"
#include "particle/CTrailParticleDrawer.hpp"

CParticleSystem::CParticleSystem(ISceneNode* parent, irr::scene::ISceneManager* mgr, irr::s32 id,
    const irr::core::vector3df& position,
    const irr::core::vector3df& rotation,
    const irr::core::vector3df& scale)
    : irr::scene::ISceneNode(parent, mgr, id, position, rotation, scale)
{
    //ctor
    LastTime = 0;
    diff = 0.f;
    Paused = false;
    UseOverrideMaterial = false;
    localParticles = false;
}

CParticleSystem::~CParticleSystem()
{
    //dtor
    for (irr::u32 i = 0; i < Drawer.size(); i++) {
        Drawer[i]->drop();
    }
    Drawer.clear();
}

void CParticleSystem::update(irr::u32 timeMs, irr::f32 diff)
{
    for (irr::u32 i = 0; i < Drawer.size(); i++) {
        Drawer[i]->doParticles(localParticles, SceneManager->getActiveCamera(), AbsoluteTransformation, timeMs, Paused ? 0.f : diff);
        if (i == 0) {
            Box.reset(Drawer[i]->getBBox());
        } else
            Box.addInternalBox(Drawer[i]->getBBox());
    }
}

void CParticleSystem::addDrawer(CParticleDrawer* drawer)
{
    if (drawer) {
        drawer->grab();
        Drawer.push_back(drawer);
    }
}

CParticleDrawer* CParticleSystem::getDrawer(const irr::u32& id)
{
    if (id < Drawer.size())
        return Drawer[id];
    return 0;
}

void CParticleSystem::setOverrideMaterial(const bool& use)
{
    UseOverrideMaterial = use;
}

void CParticleSystem::setOverrideMaterial(const irr::video::SMaterial& material)
{
    OverrideMaterial = material;
    UseOverrideMaterial = true;
}

irr::video::SMaterial& CParticleSystem::getOverrideMaterial(void)
{
    return OverrideMaterial;
}

CParticleDrawer* CParticleSystem::addTrailParticleDrawer(const bool& bindSpeedSize, const bool& useRotationAsVector, const E_TRAILPARTICLE_DRAW_OPTION& drawOption)
{
    CParticleDrawer* drawer = new CTrailParticleDrawer(bindSpeedSize, useRotationAsVector, drawOption);
    addDrawer(drawer);
    drawer->drop();
    return drawer;
}

CParticleDrawer* CParticleSystem::addParticleDrawer(void)
{
    CParticleDrawer* drawer = new CBillboardParticleDrawer();
    addDrawer(drawer);
    drawer->drop();
    return drawer;
}

CParticleDrawer* CParticleSystem::addOrientedParticleDrawer(void)
{
    CParticleDrawer* drawer = new COrientedParticleDrawer();
    addDrawer(drawer);
    drawer->drop();
    return drawer;
}

void CParticleSystem::setLocalParticles(bool local)
{
    localParticles = local;
}

bool CParticleSystem::isLocalParticles(void)
{
    return localParticles;
}

void CParticleSystem::OnRegisterSceneNode(void)
{
    if (isVisible()) {
        SceneManager->registerNodeForRendering(this);
    }
    ISceneNode::OnRegisterSceneNode();
}

void CParticleSystem::OnAnimate(irr::u32 timeMs)
{
    if (LastTime == 0) {
        LastTime = timeMs;
        return;
    }
    diff = timeMs - LastTime;
    diff /= 1000.f;
    ISceneNode::OnAnimate(timeMs);
    LastTime = timeMs;
}

void CParticleSystem::render(void)
{
    update(LastTime, diff);

    if (UseOverrideMaterial)
        SceneManager->getVideoDriver()->setMaterial(OverrideMaterial);

    irr::core::matrix4 trans = irr::core::IdentityMatrix;
    if (localParticles) {
        trans.setTranslation(AbsoluteTransformation.getTranslation());
    }

    SceneManager->getVideoDriver()->setTransform(irr::video::ETS_WORLD, trans);

    for (irr::u32 i = 0; i < Drawer.size(); ++i) {
        Drawer[i]->drawParticles(trans, SceneManager->getVideoDriver(), UseOverrideMaterial);
    }
}

const irr::core::aabbox3d<irr::f32>& CParticleSystem::getBoundingBox() const
{
    return Box;
}

irr::video::SMaterial& CParticleSystem::getMaterial(irr::u32 num)
{
    if (UseOverrideMaterial)
        return OverrideMaterial;

    if (num < Drawer.size())
        return Drawer[num]->getMaterial();
    return irr::video::IdentityMaterial;
}

irr::u32 CParticleSystem::getMaterialCount() const
{
    if (UseOverrideMaterial)
        return 1;

    return Drawer.size();
}