/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Bomb
*/

#include "entity/Bomb.hpp"
#include "Game.hpp"
#include <algorithm>

using namespace irr;
using namespace core;

Bomb::Bomb(Player *p, scene::ISceneManager* smgr)
    : IEntityComponent(IEntity::EType::BOMB, this), GraphicsComponent(smgr), ICollision(vector3df(0,0,0))
    , _poseur{ p }, _pos{ p->getMapPos() }, _range{ p->getBombRange() }
{
    TimeEventComponent::addTimer(3.0, timeEvent::Explose);
    GraphicsComponent::addMesh("assets/bomb1/bomb1.x", true, {}, 42);
    TransformComponent::_scale = vector3df(1.2, 1.2, 1.2);
    TransformComponent::_pos = vector3df(_pos.X * 2, 0.01, _pos.Y * 2);
    ICollision::setNode(GraphicsComponent::getMesh(0));
    ActionEventComponent::addAction(Interaction);
    _poseur->add_bomb_capacity(-1);
}

void Bomb::proccessTimer(u32 action)
{
    switch (action)
    {
    case timeEvent::Explose:   ActionEventComponent::addAction(Explose_Map) ;   break;
    };
}

void Bomb::processAction(void *g)
{
    Game *game = (Game *)g;
    while (ActionEventComponent::_actionsId.size() > 0) {
        auto a = _actionsId.back();

        switch (a) {
            case actionEvent::Explose_Map:
                game->getSounManager().explose();
                game->getCameraManager().shake();
                explose(_smgr, game->getMap()->applyExplosion( { (u32)_pos.X, (u32)_pos.Y }, _range, 1, game->getPlayers(), game->getEntites(), game->getBombs() ));
                _alive = false;
                ICollision::drop();
                GraphicsComponent::getMesh(0)->remove();
                _poseur->add_bomb_capacity(1);
                // remove
                _needFree = true;
                game->getBombs().erase(std::remove(game->getBombs().begin(), game->getBombs().end(), this), game->getBombs().end());
                //
                break;
            case actionEvent::Interaction:
                for (auto *p : game->getPlayers()) {
                    if (p->getMapPos().X != _pos.X || p->getMapPos().Y != _pos.Y)
                        ((ICollision *)p)->createCollision((ICollision *)this, _smgr);
                    else
                        _remainCollisionPlayer.push_back(p);
                }
                break;
            case actionEvent::RemainInteraction:
                for (auto it = _remainCollisionPlayer.begin(); it != _remainCollisionPlayer.end(); ) {
                    if (outBomb(*it)) {
                        ((ICollision *)(*it))->createCollision((ICollision *)this, _smgr);
                        it = _remainCollisionPlayer.erase(it);
                    }
                    else
                        ++it;
                }
                break;
        }

        _actionsId.pop_back();
    }
    if (_remainCollisionPlayer.size() > 0)
        ActionEventComponent::addAction(actionEvent::RemainInteraction);
}

bool Bomb::outBomb(Player *p)
{
    float p_y = p->getPos().Z / 2;
    float p_x = p->getPos().X / 2;
    float marge = 0.7;

    if (((float)_pos.Y) - marge < p_y && p_y < ((float)_pos.Y) + marge
    && ((float)_pos.X) - marge < p_x && p_x < ((float)_pos.X) + marge)
        return false;
    return true;
}

#include "particle/CParticleSystem.hpp"
void Bomb::explose(scene::ISceneManager* smgr, std::array<int, 4> cross)
{
    CParticleSystem* system = new CParticleSystem(smgr->getSceneNodeFromId(42), smgr);
    system->setPosition(core::vector3df(_pos.X * 2, 1.0f, _pos.Y * 2));
    system->setRotation(core::vector3df(0, 0, 0));
    system->setScale(irr::core::vector3df(1, 1, 1));
    system->updateAbsolutePosition();

    CParticleDrawer* drawer;
    CParticleEmitter* emitter;
    CParticleAffector* affector;

    ///Spark Trails
    drawer = system->addTrailParticleDrawer();
    SParticleUV uv(irr::core::vector2df(0.75f, 0.75f), irr::core::vector2df(1.0f, 0.75f),
        irr::core::vector2df(0.75f, 1.0f), irr::core::vector2df(1.0f, 1.0f));
    uv.turnRight();
    drawer->addUVCoords(uv);
    emitter = drawer->addStandardEmitter(irr::core::vector3df(0, 0, 0), irr::core::vector3df(0, 0, 0),
        irr::core::vector3df(0, 15, 0), irr::core::vector3di(180, 0, 180), 0, 500, 30, 500, 1200,
        irr::core::vector2df(1.0), irr::core::vector2df(1.5), irr::core::vector2df(0, 0),
        irr::video::SColor(255, 255, 255, 0), irr::video::SColor(255, 255, 255, 0));
    affector = new ColorAffector(irr::video::SColor(0, 100, 50, 0));
    drawer->addAffector(affector);
    affector->drop();

    ///Smoke Trails
    drawer = system->addTrailParticleDrawer();
    uv = SParticleUV(irr::core::vector2df(0.0f, 0.5f), irr::core::vector2df(0.5f, 0.5f),
        irr::core::vector2df(0.0f, 0.5f + 0.125f), irr::core::vector2df(0.5f, 0.5f + 0.125f));
    uv.turnRight();
    drawer->addUVCoords(uv);
    uv = SParticleUV(irr::core::vector2df(0.0f, 0.5f + 0.125f), irr::core::vector2df(0.5f, 0.5f + 0.125f),
        irr::core::vector2df(0.0f, 0.5f + 0.125f + 0.125f), irr::core::vector2df(0.5f, 0.5f + 0.125f + 0.125f));
    uv.turnRight();
    drawer->addUVCoords(uv);
    uv = SParticleUV(irr::core::vector2df(0.0f, 0.5f + 0.125f + 0.125f), irr::core::vector2df(0.5f, 0.5f + 0.125f + 0.125f),
        irr::core::vector2df(0.0f, 0.5f + 0.125f + 0.125f + 0.125f), irr::core::vector2df(0.5f, 0.5f + 0.125f + 0.125f + 0.125f));
    uv.turnRight();
    drawer->addUVCoords(uv);
    emitter = drawer->addStandardEmitter(irr::core::vector3df(0, 0, 0), irr::core::vector3df(0, 0, 0),
        irr::core::vector3df(0, 10, 0), irr::core::vector3di(180, 0, 180), 0, 500, 10, 400, 600,
        irr::core::vector2df(0.25, 1.0), irr::core::vector2df(0.25, 1.0), irr::core::vector2df(2.f),
        irr::video::SColor(255, 255, 128, 50), irr::video::SColor(255, 255, 128, 50));
    affector = new ColorAffectorQ(irr::video::SColor(128, 128, 128, 50), irr::video::SColor(0, 0, 0, 0));
    drawer->addAffector(affector);
    affector->drop();

    ///Debris
    drawer = system->addParticleDrawer();
    drawer->addUVCoords(SParticleUV(irr::core::vector2df(0.5f, 0.5f), irr::core::vector2df(0.5f + 0.0833f, 0.5f), irr::core::vector2df(0.5f, 0.5f + 0.0833f), irr::core::vector2df(0.5f + 0.0833f, 0.5f + 0.0833f)));
    drawer->addUVCoords(SParticleUV(irr::core::vector2df(0.5f + 0.0833f, 0.5f), irr::core::vector2df(0.5f + 0.0833f + 0.0833f, 0.5f), irr::core::vector2df(0.5f + 0.0833f, 0.5f + 0.0833f), irr::core::vector2df(0.5f + 0.0833f + 0.0833f, 0.5f + 0.0833f)));
    drawer->addUVCoords(SParticleUV(irr::core::vector2df(0.5f + 0.0833f + 0.0833f, 0.5f), irr::core::vector2df(0.5f + 0.0833f + 0.0833f + 0.0833f, 0.5f), irr::core::vector2df(0.5f + 0.0833f + 0.0833f, 0.5f + 0.0833f), irr::core::vector2df(0.5f + 0.0833f + 0.0833f + 0.0833f, 0.5f + 0.0833f)));
    drawer->addUVCoords(SParticleUV(irr::core::vector2df(0.5f, 0.5f + 0.0833f), irr::core::vector2df(0.5f + 0.0833f, 0.5f + 0.0833f), irr::core::vector2df(0.5f, 0.5f + 0.0833f + 0.0833f), irr::core::vector2df(0.5f + 0.0833f, 0.5f + 0.0833f + 0.0833f)));
    drawer->addUVCoords(SParticleUV(irr::core::vector2df(0.5f, 0.5f + 0.0833f + 0.0833f), irr::core::vector2df(0.5f + 0.0833f, 0.5f + 0.0833f + 0.0833f), irr::core::vector2df(0.5f, 0.5f + 0.0833f + 0.0833f + 0.0833f), irr::core::vector2df(0.5f + 0.0833f, 0.5f + 0.0833f + 0.0833f + 0.0833f)));
    emitter = drawer->addStandardEmitter(irr::core::vector3df(0, 0, 0), irr::core::vector3df(1, 0, 0), irr::core::vector3df(0, 15, 0), irr::core::vector3di(45, 0, 45), 0, 400, 10, 2000, 3000, irr::core::vector2df(0.2, 0.2), irr::core::vector2df(0.5, 0.5), irr::core::vector2df(0, 0), irr::video::SColor(255, 255, 100, 0), irr::video::SColor(255, 255, 100, 0));
    affector = new ColorAffectorQ(irr::video::SColor(255, 50, 50, 50), irr::video::SColor(255, 50, 50, 50));
    drawer->addAffector(affector);
    affector->drop();
    affector = new GravityAffector(irr::core::vector3df(0.f, -30.0f, 0.f));
    drawer->addAffector(affector);
    affector->drop();
    affector = new PlaneCollisionAffector(irr::core::plane3df(0, 0, 0, 0, 1, 0));
    drawer->addAffector(affector);
    affector->drop();

    ///Shock wave
    drawer = system->addOrientedParticleDrawer();
    drawer->getMaterial().BackfaceCulling = false;
    drawer->addUVCoords(SParticleUV(irr::core::vector2df(0.75f, 0.5f), irr::core::vector2df(1.0f, 0.5f),
        irr::core::vector2df(0.75f, 0.75f), irr::core::vector2df(1.0f, 0.75f)));
    emitter = drawer->addStandardEmitter(irr::core::vector3df(0, 0, 0), irr::core::vector3df(0, 0, 0),
        irr::core::vector3df(0, 0, 0), irr::core::vector3di(0), 20, 50, 1, 500, 500, irr::core::vector2df(2.5, 2.5),
        irr::core::vector2df(2.5, 2.5), irr::core::vector2df(15), irr::video::SColor(255, 200, 100, 0),
        irr::video::SColor(255, 200, 128, 0));
    affector = new ColorAffector(irr::video::SColor(0, 100, 10, 0));
    drawer->addAffector(affector);
    affector->drop();

    ///Fire/Smoke
    drawer = system->addParticleDrawer();
    drawer->addUVCoords(SParticleUV(irr::core::vector2df(0.0f, 0.0f), irr::core::vector2df(0.25f, 0.0f), irr::core::vector2df(0.0f, 0.25f), irr::core::vector2df(0.25f, 0.25f)));
    drawer->addUVCoords(SParticleUV(irr::core::vector2df(0.25f, 0.25f), irr::core::vector2df(0.5f, 0.25f), irr::core::vector2df(0.25f, 0.5f), irr::core::vector2df(0.5f, 0.5f)));
    drawer->addUVCoords(SParticleUV(irr::core::vector2df(0.25f, 0.0f), irr::core::vector2df(0.5f, 0.0f), irr::core::vector2df(0.25f, 0.25f), irr::core::vector2df(0.5f, 0.25f)));
    drawer->addUVCoords(SParticleUV(irr::core::vector2df(0.0f, 0.25f), irr::core::vector2df(0.25f, 0.25f), irr::core::vector2df(0.0f, 0.5f), irr::core::vector2df(0.25f, 0.5f)));
    emitter = drawer->addStandardEmitter(irr::core::vector3df(0, 0, 0), irr::core::vector3df(1, 0, 0),
        irr::core::vector3df(2, 0, 0), irr::core::vector3di(0, 180, 0), 0, 200, 70, 500, 700,
        irr::core::vector2df(1, 1), irr::core::vector2df(2, 2), irr::core::vector2df(2),
        irr::video::SColor(200, 200, 180, 0), irr::video::SColor(200, 200, 180, 0));
    if (cross[0] != 0 || cross[1] != 0 || cross[2] != 0 || cross[3] != 0) {
        CEmitterRegion* emitterRegion = new CCrossRegion(irr::core::vector3df((-(cross[0])*2) - 0.5, 0, 0),
            irr::core::vector3df((cross[1]*2) + 0.5, 0, 0), irr::core::vector3df(0, 0, -(cross[2])*2) - 0.5,
            irr::core::vector3df(0, 0, (cross[3]*2) + 0.5));
        emitter->setRegion(emitterRegion);
        emitterRegion->drop();
    }
    affector = new ColorAffectorQ(irr::video::SColor(200, 100, 0, 0), irr::video::SColor(0, 0, 0, 0));
    drawer->addAffector(affector);
    affector->drop();
    affector = new GravityAffector(irr::core::vector3df(0.f, 10.0f, 0.f));
    drawer->addAffector(affector);
    affector->drop();

    ///Spark Emitter
    drawer = system->addParticleDrawer();
    drawer->addUVCoords(SParticleUV(irr::core::vector2df(0.5f, 0.75f), irr::core::vector2df(0.75f, 0.75f), irr::core::vector2df(0.5f, 1.0f), irr::core::vector2df(0.75f, 1.0f)));
    emitter = drawer->addStandardEmitter(irr::core::vector3df(0, 0, 0), irr::core::vector3df(0, 0, 0), irr::core::vector3df(0, 6, 0), irr::core::vector3di(90, 0, 90), 20, 50, 10, 1000, 1200, irr::core::vector2df(1.5, 1.5), irr::core::vector2df(2.0, 2.0), irr::core::vector2df(1, 1), irr::video::SColor(255, 255, 128, 0), irr::video::SColor(255, 255, 128, 0));
    affector = new GravityAffector(irr::core::vector3df(0.f, 0.8f, 0.f));
    drawer->addAffector(affector);
    affector->drop();
    affector = new ColorAffector(irr::video::SColor(0, 255, 128, 0));
    drawer->addAffector(affector);
    affector->drop();

    ///Flash Emitter
    drawer = system->addParticleDrawer();
    drawer->addUVCoords(SParticleUV(irr::core::vector2df(0.5, 0), irr::core::vector2df(0.75, 0), irr::core::vector2df(0.5, 0.25), irr::core::vector2df(0.75f, 0.25f)));
    drawer->addUVCoords(SParticleUV(irr::core::vector2df(0.5 + 0.25f, 0), irr::core::vector2df(0.75 + 0.25f, 0), irr::core::vector2df(0.5 + 0.25f, 0.25), irr::core::vector2df(0.75f + 0.25f, 0.25f)));
    emitter = drawer->addStandardEmitter(irr::core::vector3df(0, 0, 0), irr::core::vector3df(0, 0, 0), irr::core::vector3df(0, 0, 0), irr::core::vector3di(0), 20, 50, 5, 200, 300, irr::core::vector2df(1, 1), irr::core::vector2df(1, 1), irr::core::vector2df(3), irr::video::SColor(255, 255, 255, 100), irr::video::SColor(255, 255, 255, 100));
    affector = new ColorAffector(irr::video::SColor(0, 255, 255, 100));
    drawer->addAffector(affector);
    affector->drop();

    irr::video::SMaterial overrideMaterial;
    overrideMaterial.MaterialType = irr::video::EMT_ONETEXTURE_BLEND;
    overrideMaterial.setTexture(0, smgr->getVideoDriver()->getTexture("assets/particle/explose.png"));
    overrideMaterial.setFlag(irr::video::EMF_LIGHTING, false);
    overrideMaterial.setFlag(irr::video::EMF_ZWRITE_ENABLE, false);
    overrideMaterial.setFlag(irr::video::EMF_BACK_FACE_CULLING, false);
    overrideMaterial.MaterialTypeParam = irr::video::pack_textureBlendFunc(irr::video::EBF_SRC_ALPHA,
        irr::video::EBF_ONE_MINUS_SRC_ALPHA, irr::video::EMFN_MODULATE_1X,
        irr::video::EAS_VERTEX_COLOR | irr::video::EAS_TEXTURE);
    system->setOverrideMaterial(overrideMaterial);
    irr::scene::ISceneNodeAnimator* anim = smgr->createDeleteAnimator(3000);
    system->addAnimator(anim);
    anim->drop();
    system->drop();
}