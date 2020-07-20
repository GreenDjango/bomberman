/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** CTrailParticleDrawer
*/
#include "particle/CTrailParticleDrawer.hpp"

CTrailParticleDrawer::CTrailParticleDrawer(const bool& bindSpeedSize, const bool& useRotationAsVector, const E_TRAILPARTICLE_DRAW_OPTION& drawOption)
{
    //ctor
    DrawOption = drawOption;
    UseRotationAsVector = useRotationAsVector;
    BindSpeedSize = bindSpeedSize;
}

CTrailParticleDrawer::~CTrailParticleDrawer()
{
    //dtor
}

void CTrailParticleDrawer::createParticle(const irr::u32& id, const Particle* particle, const irr::core::vector3df& view, const irr::core::matrix4&)
{
    irr::core::vector3df forward;
    if (particle->Speed == irr::core::vector3df() || UseRotationAsVector)
        forward = particle->Rotation;
    else
        forward = particle->Speed;
    forward.normalize();

    irr::core::vector3df left = view.crossProduct(forward);
    left.normalize();

    if (DrawOption == E_TRAILPARTICLE_DRAW_OPTION::ETDO_CENTER)
        forward = forward*particle->Size.Y*0.5f;
    else
        forward = forward*particle->Size.Y;

    if (BindSpeedSize)
        forward *= particle->Speed.getLengthSQ()/particle->StartSpeed.getLengthSQ();

    left = left*particle->Size.X*0.5f;

    if (DrawOption == E_TRAILPARTICLE_DRAW_OPTION::ETDO_START)
    {
        Buffer->Vertices[id*4].Pos       = particle->Position+forward+left;
        Buffer->Vertices[id*4].Color     = particle->Color;
        Buffer->Vertices[id*4].Normal    = -view;
        Buffer->Vertices[id*4].TCoords   = particle->UVs.UV0;

        Buffer->Vertices[id*4+1].Pos       = particle->Position+forward-left;
        Buffer->Vertices[id*4+1].Color     = particle->Color;
        Buffer->Vertices[id*4+1].Normal    = -view;
        Buffer->Vertices[id*4+1].TCoords   = particle->UVs.UV1;

        Buffer->Vertices[id*4+2].Pos       = particle->Position+left;
        Buffer->Vertices[id*4+2].Color     = particle->Color;
        Buffer->Vertices[id*4+2].Normal    = -view;
        Buffer->Vertices[id*4+2].TCoords   = particle->UVs.UV2;

        Buffer->Vertices[id*4+3].Pos       = particle->Position-left;
        Buffer->Vertices[id*4+3].Color     = particle->Color;
        Buffer->Vertices[id*4+3].Normal    = -view;
        Buffer->Vertices[id*4+3].TCoords   = particle->UVs.UV3;
    }
    else if (DrawOption == E_TRAILPARTICLE_DRAW_OPTION::ETDO_END)
    {
        Buffer->Vertices[id*4].Pos       = particle->Position+left;
        Buffer->Vertices[id*4].Color     = particle->Color;
        Buffer->Vertices[id*4].Normal    = -view;
        Buffer->Vertices[id*4].TCoords   = particle->UVs.UV0;

        Buffer->Vertices[id*4+1].Pos       = particle->Position-left;
        Buffer->Vertices[id*4+1].Color     = particle->Color;
        Buffer->Vertices[id*4+1].Normal    = -view;
        Buffer->Vertices[id*4+1].TCoords   = particle->UVs.UV1;

        Buffer->Vertices[id*4+2].Pos       = particle->Position-forward+left;
        Buffer->Vertices[id*4+2].Color     = particle->Color;
        Buffer->Vertices[id*4+2].Normal    = -view;
        Buffer->Vertices[id*4+2].TCoords   = particle->UVs.UV2;

        Buffer->Vertices[id*4+3].Pos       = particle->Position-forward-left;
        Buffer->Vertices[id*4+3].Color     = particle->Color;
        Buffer->Vertices[id*4+3].Normal    = -view;
        Buffer->Vertices[id*4+3].TCoords   = particle->UVs.UV3;
    }
    else
    {
        Buffer->Vertices[id*4].Pos       = particle->Position+forward+left;
        Buffer->Vertices[id*4].Color     = particle->Color;
        Buffer->Vertices[id*4].Normal    = -view;
        Buffer->Vertices[id*4].TCoords   = particle->UVs.UV0;

        Buffer->Vertices[id*4+1].Pos       = particle->Position+forward-left;
        Buffer->Vertices[id*4+1].Color     = particle->Color;
        Buffer->Vertices[id*4+1].Normal    = -view;
        Buffer->Vertices[id*4+1].TCoords   = particle->UVs.UV1;

        Buffer->Vertices[id*4+2].Pos       = particle->Position-forward+left;
        Buffer->Vertices[id*4+2].Color     = particle->Color;
        Buffer->Vertices[id*4+2].Normal    = -view;
        Buffer->Vertices[id*4+2].TCoords   = particle->UVs.UV2;

        Buffer->Vertices[id*4+3].Pos       = particle->Position-forward-left;
        Buffer->Vertices[id*4+3].Color     = particle->Color;
        Buffer->Vertices[id*4+3].Normal    = -view;
        Buffer->Vertices[id*4+3].TCoords   = particle->UVs.UV3;
    }
}