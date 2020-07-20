/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** CParticleDrawer
*/
#ifndef CPARTICLEDRAWER_H
#define CPARTICLEDRAWER_H

#include "CParticleEmitter.hpp"
#include "Particle.hpp"
#include <irrlicht/irrlicht.h>

enum E_TRAILPARTICLE_DRAW_OPTION {
    ETDO_CENTER = 0,
    ETDO_START,
    ETDO_END,
    ETDO_COUNT
};

enum E_PARTICLE_DRAWER_TYPE {
    EPDT_BILLBOARD = 0,
    EPDT_ORIENTED,
    EPDT_TRAIL,
    EPDT_COUNT
};

class CParticleAffector : public irr::IReferenceCounted {
public:
    CParticleAffector(void) {}
    virtual ~CParticleAffector(void) {}

    virtual void affect(Particle* particle, irr::u32 timeMs, irr::f32 diff) = 0;
};

class CParticleDrawer : public irr::IReferenceCounted {
public:
    CParticleDrawer(void);
    virtual ~CParticleDrawer(void);

    CParticleEmitter* addStandardEmitter(const irr::core::vector3df& rotation,
        const irr::core::vector3df& rotationspeed, const irr::core::vector3df& speed,
        const irr::core::vector3di& maxAngle, const irr::u32& minPpS, const irr::u32& maxPpS,
        const irr::u32& maxEmitt, const irr::u32& minlifetime, const irr::u32& maxlifetime,
        const irr::core::vector2df& minsize, const irr::core::vector2df& maxsize,
        const irr::core::vector2df& sizespeed, const irr::video::SColor& minColor,
        const irr::video::SColor& maxColor);

    irr::video::SMaterial& getMaterial(void);

    void addUVCoords(const SParticleUV& coord);

    virtual void doParticles(bool localParticles, const irr::scene::ICameraSceneNode* camera, const irr::core::matrix4& transform, irr::u32 timeMs, irr::f32 diff);

    virtual void createParticle(const irr::u32& id, const Particle* particle, const irr::core::vector3df& view, const irr::core::matrix4& transform) = 0;

    virtual void drawParticles(const irr::core::matrix4& transform, irr::video::IVideoDriver* driver, bool useOneMaterial);

    void setEmitter(CParticleEmitter* emitter);

    CParticleEmitter* getEmitter(void);

    void addAffector(CParticleAffector* affector);

    static irr::core::list<irr::scene::SMeshBuffer*>* BufferPool;
    //static irr::core::list<Particle*> ParticlePool;

    const irr::core::aabbox3df& getBBox(void) const;

    virtual E_PARTICLE_DRAWER_TYPE getType() const = 0;

protected:
    irr::scene::SMeshBuffer* Buffer;
    irr::video::SMaterial Material;
    CParticleEmitter* Emitter;

    irr::core::list<Particle*> Particles;
    irr::core::list<Particle*> ParticlePool;

    irr::core::list<CParticleAffector*> Affectors;
    irr::core::array<SParticleUV> UVCoords;

    virtual void rellocateBuffer(irr::u32 particleCount = 0);
    irr::u32 ParticleCount;

    irr::core::aabbox3df Box;
};

#endif // CPARTICLEDRAWER_H
