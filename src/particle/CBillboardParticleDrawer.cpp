/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** CBillboardParticleDrawer
*/
#include "particle/CBillboardParticleDrawer.hpp"

CBillboardParticleDrawer::CBillboardParticleDrawer()
{
    //ctor
}

CBillboardParticleDrawer::~CBillboardParticleDrawer()
{
    //dtor
}

void CBillboardParticleDrawer::createParticle(const irr::u32& id, const Particle* particle, const irr::core::vector3df& view, const irr::core::matrix4& transform)
{
    irr::f32 f = 0;
    if (particle->Rotation.X != 0)
    {
        f = 0.5f * particle->Size.X;
        irr::core::vector3df left ( transform[0] * f, transform[4] * f, transform[8] * f);

        f = -0.5f * particle->Size.Y;
        irr::core::vector3df forward ( transform[1] * f, transform[5] * f, transform[9] * f);

        irr::core::matrix4 mat;
        irr::core::quaternion quad;
        quad.fromAngleAxis(particle->Rotation.X, view);
        mat = quad.getMatrix();

        mat.rotateVect(forward);
        mat.rotateVect(left);

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
    else
    {
        f = 0.5f * particle->Size.X;
        const irr::core::vector3df left ( transform[0] * f, transform[4] * f, transform[8] * f);

        f = -0.5f * particle->Size.Y;
        const irr::core::vector3df forward ( transform[1] * f, transform[5] * f, transform[9] * f);

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