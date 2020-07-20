/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** CBillboardParticleDrawer
*/
#ifndef CBILLBOARDPARTICLEDRAWER_H
#define CBILLBOARDPARTICLEDRAWER_H

#include "CParticleDrawer.hpp"


class CBillboardParticleDrawer : public CParticleDrawer
{
    public:
        CBillboardParticleDrawer();
        virtual ~CBillboardParticleDrawer();

        E_PARTICLE_DRAWER_TYPE getType() const
        {
            return EPDT_BILLBOARD;
        }

        void createParticle(const irr::u32& id, const Particle* particle, const irr::core::vector3df& view, const irr::core::matrix4& transform);
    protected:
    private:
};

#endif // CBILLBOARDPARTICLEDRAWER_H
