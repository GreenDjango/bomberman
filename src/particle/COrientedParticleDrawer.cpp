/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** COrientedParticleDrawer
*/
#include "particle/COrientedParticleDrawer.hpp"

COrientedParticleDrawer::COrientedParticleDrawer()
{
    //ctor
}

COrientedParticleDrawer::~COrientedParticleDrawer()
{
    //dtor
}

void COrientedParticleDrawer::createParticle(const irr::u32& id, const Particle* particle, const irr::core::vector3df& view, const irr::core::matrix4&)
{
    irr::core::vector3df forward(0,-1,0);
    if (particle->Rotation.getLengthSQ() > 0)
    {
        irr::core::matrix4 mat;
        mat.setRotationDegrees(particle->Rotation);
        mat.rotateVect(forward);
    }

    irr::core::vector3df left = view.crossProduct(forward);
    left.normalize();

    forward = left.crossProduct(forward);
    forward.normalize();

    forward = forward*particle->Size.Y*0.5f;
    left = left*particle->Size.X*0.5f;

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