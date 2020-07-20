/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** COrientedParticleDrawer
*/
#ifndef CORIENTEDPARTICLEDRAWER_H
#define CORIENTEDPARTICLEDRAWER_H

#include "CParticleDrawer.hpp"

class COrientedParticleDrawer : public CParticleDrawer
{
    public:
        COrientedParticleDrawer();
        virtual ~COrientedParticleDrawer();

        E_PARTICLE_DRAWER_TYPE getType() const
        {
            return E_PARTICLE_DRAWER_TYPE::EPDT_ORIENTED;
        }

        void createParticle(const irr::u32& id, const Particle* particle, const irr::core::vector3df& view, const irr::core::matrix4& transform);
    protected:
    private:
};

#endif // CORIENTEDPARTICLEDRAWER_H
