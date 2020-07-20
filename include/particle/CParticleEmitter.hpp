/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** CParticleEmitter
*/
#ifndef CPARTICLEEMITTER_H
#define CPARTICLEEMITTER_H

#include "Particle.hpp"
#include <irrlicht/irrlicht.h>

class CEmitterRegion : public irr::IReferenceCounted
{
public:
    CEmitterRegion() {}
    virtual ~CEmitterRegion() {}

    ///Get a Spawn point from the spawn region
    virtual irr::core::vector3df getPoint(const irr::core::matrix4& transform) = 0;
    ///Call this function to check if there is direction vector avaiable for the last spawnpoint
    virtual bool isForceField(void) const
    {
        return false;
    }
    ///Only returns usefull stuff after calling getPoint and isForceField() returns true
    virtual irr::core::vector3df getVector(void)
    {
        return irr::core::vector3df();
    }
};

class CPointRegion : public CEmitterRegion
{
public:
    ///Get a Spawn point from the spawn region
    virtual irr::core::vector3df getPoint(const irr::core::matrix4& transform)
    {
        return transform.getTranslation();
    }
};

class CLineRegion : public CEmitterRegion
{
public:
    CLineRegion(const irr::core::vector3df& s, const irr::core::vector3df& e)
    {
        Start = s;
        End = e;
    }
    CLineRegion(const irr::f32& x, const irr::f32& y, const irr::f32& z,
        const irr::f32& a, const irr::f32& b, const irr::f32& c)
    {
        Start = irr::core::vector3df(x,y,z);
        End = irr::core::vector3df(a,b,c);
    }
    virtual irr::core::vector3df getPoint(const irr::core::matrix4& transform)
    {
        irr::f32 r0 = ((irr::f32)(rand()%100))/100.f;
        irr::core::vector3df vec = End-Start;
        irr::core::vector3df point = Start+vec*0.5f;
        transform.rotateVect(vec);
        point += vec*(r0-0.5f);
        printf("add: %f - %f, %f, %f\n", r0, point.X, point.Y, point.Z);
        return transform.getTranslation()+point;
    }
    irr::core::vector3df Start;
    irr::core::vector3df End;
};

class CCrossRegion : public CEmitterRegion
{
public:
    CCrossRegion(const irr::core::vector3df& s1, const irr::core::vector3df& e1,
        const irr::core::vector3df& s2, const irr::core::vector3df& e2)
    {
        Start1 = s1;
        End1 = e1;
        Start2 = s2;
        End2 = e2;
    }
    virtual irr::core::vector3df getPoint(const irr::core::matrix4& transform)
    {
        int axe = rand()%2;
        irr::core::vector3df start = axe == 0 ? Start1 : Start2;
        irr::core::vector3df end = axe == 0 ? End1 : End2;
        irr::f32 r0 = ((irr::f32)(rand()%100))/100.f;
        irr::core::vector3df vec = end-start;
        irr::core::vector3df point = start+vec*0.5f;
        transform.rotateVect(vec);
        point += vec*(r0-0.5f);
        return transform.getTranslation()+point;
    }
    irr::core::vector3df Start1;
    irr::core::vector3df End1;
    irr::core::vector3df Start2;
    irr::core::vector3df End2;
};

class CParticleEmitter : public irr::IReferenceCounted {
public:
    CParticleEmitter(const irr::core::vector3df& rotation = irr::core::vector3df(0, 0, 0),
        const irr::core::vector3df& rotationspeed = irr::core::vector3df(0, 0, 0),
        const irr::core::vector3df& speed = irr::core::vector3df(0, 1, 0),
        const irr::core::vector3di& maxAngle = irr::core::vector3di(45, 0, 45),
        const irr::u32& minPpS = 50, const irr::u32& maxPpS = 100, const irr::u32& maxEmitt = 100,
        const irr::u32& minlifetime = 100, const irr::u32& maxlifetime = 1000,
        const irr::core::vector2df& minsize = irr::core::vector2df(1, 1),
        const irr::core::vector2df& maxsize = irr::core::vector2df(1, 1),
        const irr::core::vector2df& sizespeed = irr::core::vector2df(0, 0),
        const irr::video::SColor& minColor = irr::video::SColor(255, 255, 255, 255),
        const irr::video::SColor& maxColor = irr::video::SColor(255, 255, 255, 255));
    CParticleEmitter(void);
    virtual ~CParticleEmitter(void);

    virtual void emitt(const irr::core::matrix4& transform, irr::core::list<Particle*>& particles, irr::core::list<Particle*>& particlepool, irr::u32 timeMs, irr::f32 diff, const irr::core::array<SParticleUV>& coords);

    bool emittAll(void) const
    {
        if (MinParticlesPerSecond == 0 && ParticlesEmitted < MaxParticleEmitt)
            return true;
        return false;
    }

    void setRegion(CEmitterRegion* region)
    {
        if (region)
            region->grab();
        if (Region)
            Region->drop();
        Region = region;
    }

    CEmitterRegion* getRegion(void)
    {
        return Region;
    }

    const irr::u32& getMaxParticleEmitt(void) const
    {
        return MaxParticleEmitt;
    }

    const irr::u32& getParticleEmitted(void) const
    {
        return ParticlesEmitted;
    }

    const irr::u32& getMaxParticlesPerSecond(void) const
    {
        return MaxParticlesPerSecond;
    }

    const irr::u32& getMinParticlesPerSecond(void) const
    {
        return MinParticlesPerSecond;
    }

    const irr::u32& getMaxLifeTime(void) const
    {
        return MaxLifeTime;
    }

    const irr::u32& getMinLifeTime(void) const
    {
        return MinLifeTime;
    }

    void setColor(const irr::video::SColor& min, const irr::video::SColor& max)
    {
        MinColor = min;
        MaxColor = max;
    }

    const irr::video::SColor& getMinColor(void) const
    {
        return MinColor;
    }

    const irr::video::SColor& getMaxColor(void) const
    {
        return MaxColor;
    }

    void setMaxAngleDegrees(const irr::core::vector3di& angle)
    {
        MaxAngleDegrees = angle;
    }

    const irr::core::vector3di& getMaxAngleDegrees(void) const
    {
        return MaxAngleDegrees;
    }

    void setSpeed(const irr::core::vector3df& speed)
    {
        Speed = speed;
    }

    const irr::core::vector3df& getSpeed(void) const
    {
        return Speed;
    }

    void setRotation(const irr::core::vector3df& rot)
    {
        Rotation = rot;
    }

    const irr::core::vector3df& getRotation(void) const
    {
        return Rotation;
    }

    void setRotationSpeed(const irr::core::vector3df& rotspeed)
    {
        RotationSpeed = rotspeed;
    }

    const irr::core::vector3df& getRotationSpeed(void) const
    {
        return RotationSpeed;
    }

    void setSize(const irr::core::vector2df& min, const irr::core::vector2df& max)
    {
        MinSize = min;
        MaxSize = max;
    }

    const irr::core::vector2df& getMinSize(void) const
    {
        return MinSize;
    }

    const irr::core::vector2df& getMaxSize(void) const
    {
        return MaxSize;
    }

    void setSizeSpeed(const irr::core::vector2df& speed)
    {
        SizeSpeed = speed;
    }

    const irr::core::vector2df& getSizeSpeed(void) const
    {
        return SizeSpeed;
    }

protected:
    CEmitterRegion* Region;

    irr::f32 Time;

    irr::core::vector3di MaxAngleDegrees;

    irr::u32 MaxParticleEmitt;
    irr::u32 ParticlesEmitted;

    irr::u32 MinParticlesPerSecond;
    irr::u32 MaxParticlesPerSecond;

    irr::core::vector3df Speed;

    irr::core::vector3df Rotation;
    irr::core::vector3df RotationSpeed;

    irr::core::vector2df MinSize;
    irr::core::vector2df MaxSize;
    irr::core::vector2df SizeSpeed;

    irr::video::SColor MinColor;
    irr::video::SColor MaxColor;

    irr::u32 MinLifeTime;
    irr::u32 MaxLifeTime;

    Particle* create(irr::core::list<Particle*>& particlepool, const irr::core::vector3df& pos, const irr::core::vector3df& speed, const irr::core::vector3df& rot, const irr::core::vector3df& rotSpeed, const irr::core::vector2df& size, const irr::core::vector2df& sizespeed, const irr::video::SColor& color, const irr::u32& start, const irr::u32& end);
    irr::core::vector3df rotateVec(const irr::core::vector3df& vec);
    bool doEmitt(irr::f32 diff);
    virtual void emittParticleStandard(const irr::core::vector3df& pos, const irr::core::matrix4& transform, irr::core::list<Particle*>& particles, irr::core::list<Particle*>& particlepool, irr::u32 timeMs, const irr::core::array<SParticleUV>& coords);
};

#endif