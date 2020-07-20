/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** CParticleSystem
*/
#ifndef CPARTICLESYSTEM_H
#define CPARTICLESYSTEM_H

#include "CParticleDrawer.hpp"
#include <irrlicht/irrlicht.h>

class CParticleSystem : public irr::scene::ISceneNode {
public:
    CParticleSystem(ISceneNode* parent, irr::scene::ISceneManager* mgr, irr::s32 id = -1,
        const irr::core::vector3df& position = irr::core::vector3df(0, 0, 0),
        const irr::core::vector3df& rotation = irr::core::vector3df(0, 0, 0),
        const irr::core::vector3df& scale = irr::core::vector3df(1.0f, 1.0f, 1.0f));
    virtual ~CParticleSystem();

    void addDrawer(CParticleDrawer* drawer);
    CParticleDrawer* getDrawer(const irr::u32& id);
    void setOverrideMaterial(const bool& use);
    void setOverrideMaterial(const irr::video::SMaterial& material);
    irr::video::SMaterial& getOverrideMaterial(void);

    CParticleDrawer* addTrailParticleDrawer(const bool& bindSpeedSize = false, const bool& useRotationAsVector = false, const E_TRAILPARTICLE_DRAW_OPTION& drawOption = E_TRAILPARTICLE_DRAW_OPTION::ETDO_CENTER);
    CParticleDrawer* addParticleDrawer(void);
    CParticleDrawer* addOrientedParticleDrawer(void);

    void setLocalParticles(bool local);
    bool isLocalParticles(void);

    bool Paused;

    //ISceneNode
    void OnRegisterSceneNode(void);
    void OnAnimate(irr::u32 timeMs);
    void render(void);
    const irr::core::aabbox3d<irr::f32>& getBoundingBox() const;
    irr::video::SMaterial& getMaterial(irr::u32 num);
    irr::u32 getMaterialCount() const;

protected:
    void update(irr::u32 timeMs, irr::f32 diff);

    irr::core::array<CParticleDrawer*> Drawer;
    irr::video::SMaterial OverrideMaterial;
    bool UseOverrideMaterial;

    bool localParticles;

    irr::core::aabbox3d<irr::f32> Box;

    irr::u32 LastTime;
    irr::f32 diff;

private:
};

class ColorAffector : public CParticleAffector {
public:
    ColorAffector(const irr::video::SColor& targetColor)
    {
        Target = targetColor;
    }
    void affect(Particle* particle, irr::u32, irr::f32)
    {
        irr::f32 lifeTime = particle->LifeTime; //particle->DestroyTimeMs-particle->CreateTimeMs;
        irr::f32 livedTime = particle->TimeLived; //timeMs-particle->CreateTimeMs;

        particle->Color = Target.getInterpolated(particle->StartColor, livedTime / lifeTime);
    }
    irr::video::SColor Target;
};

class ColorAffectorQ : public CParticleAffector {
public:
    ColorAffectorQ(const irr::video::SColor& targetColor0, const irr::video::SColor& targetColor1)
    {
        Target0 = targetColor0;
        Target1 = targetColor1;
    }
    void affect(Particle* particle, irr::u32, irr::f32)
    {
        irr::f32 lifeTime = particle->LifeTime; //particle->DestroyTimeMs-particle->CreateTimeMs;
        irr::f32 livedTime = particle->TimeLived; //timeMs-particle->CreateTimeMs;

        particle->Color = particle->StartColor.getInterpolated_quadratic(Target0, Target1, livedTime / lifeTime);
    }
    irr::video::SColor Target0;
    irr::video::SColor Target1;
};

class GravityAffector : public CParticleAffector {
public:
    GravityAffector(const irr::core::vector3df& gravity)
    {
        Gravity = gravity;
    }
    void affect(Particle* particle, irr::u32, irr::f32 diff)
    {
        particle->Speed += Gravity * diff;
    }
    irr::core::vector3df Gravity;
};

class PlaneCollisionAffector : public CParticleAffector {
public:
    PlaneCollisionAffector(const irr::core::plane3df& plane)
    {
        Plane = plane;
    }
    void affect(Particle* particle, irr::u32, irr::f32 diff)
    {
        irr::core::vector3df collision;
        if (Plane.getIntersectionWithLimitedLine(particle->Position, particle->Position + particle->Speed * diff, collision)) {
            irr::core::vector3df r = particle->Speed - (2 * particle->Speed.dotProduct(Plane.Normal)) * Plane.Normal;
            particle->Speed = r * 0.5f;
        }
    }
    irr::core::plane3df Plane;
};

#endif // CPARTICLESYSTEM_H
