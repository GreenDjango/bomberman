/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** CTrailParticleDrawer
*/
#ifndef CTRAILPARTICLEDRAWER_H
#define CTRAILPARTICLEDRAWER_H

#include "CParticleDrawer.hpp"
class CTrailParticleDrawer : public CParticleDrawer
{
    public:
        CTrailParticleDrawer(const bool& bindSpeedSize = false, const bool& useRotationAsVector = false, const E_TRAILPARTICLE_DRAW_OPTION& drawOption = E_TRAILPARTICLE_DRAW_OPTION::ETDO_CENTER);
        virtual ~CTrailParticleDrawer();

        E_PARTICLE_DRAWER_TYPE getType() const
        {
            return E_PARTICLE_DRAWER_TYPE::EPDT_TRAIL;
        }

        void createParticle(const irr::u32& id, const Particle* particle, const irr::core::vector3df& view, const irr::core::matrix4& transform);
    protected:
        E_TRAILPARTICLE_DRAW_OPTION DrawOption;
        bool UseRotationAsVector;
        bool BindSpeedSize;
    private:
};

#endif // CTRAILPARTICLEDRAWER_H
