/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Mob
*/

#include "entity/Mob.hpp"
#include "Game.hpp"

using namespace irr;

Mob::Mob(irr::scene::ISceneManager *smgr, int y, int x)
    : IEntityComponent{ EType::MOB, this }, GraphicsComponent{ smgr }, ICollision{ core::vector3df(0,0,0) }
    , _targetPos{ 0, 0 }, _fromBlock{ 0 }, _target{ false }
{
    video::IVideoDriver *driver = smgr->getVideoDriver();
    GraphicsComponent::addMesh("assets/enemy1/enemy1.x", true, { animation(1, 71, 25) }, 42);
    int mob = std::rand() % 5;
    if (mob == 1) {
        GraphicsComponent::setMaterialTexture(0, 0, driver->getTexture("assets/enemy1/chorobonbody00_alb1.png"));
    } else if (mob == 2) {
        GraphicsComponent::setMaterialTexture(0, 0, driver->getTexture("assets/enemy1/chorobonbody00_alb2.png"));
    } else if (mob == 3) {
        GraphicsComponent::setMaterialTexture(0, 0, driver->getTexture("assets/enemy1/chorobonbody00_alb3.png"));
    } else if (mob == 4) {
        GraphicsComponent::setMaterialTexture(0, 0, driver->getTexture("assets/enemy1/chorobonbody00_alb4.png"));
    }
    GraphicsComponent::setAnimation(0, 0);
    TransformComponent::_rot = core::vector3df(-90,180,0);
    TransformComponent::_pos = core::vector3df(x * 2, 0.4, y * 2);
    InteractionComponent::_range = core::vector3df(0,0,0);
    ICollision::setNode(GraphicsComponent::getMesh(0));
}

void Mob::update(TransformComponent *t)
{
    if (!isAlive())
        return;
    scene::ISceneNode *node = (scene::ISceneNode *)_meshs[0].first;
    node->setScale(t->getScale());
    node->setRotation(t->getRot());
    core::vector3df vec{ t->getPos() };
    if (_rot.Y == 90)
        vec.X += 1.0f;
    else if (_rot.Y == -90)
        vec.X -= 1.0f;
    else if (_rot.Y == 180)
        vec.Z -= 1.0f;
    else
        vec.Z += 1.0f;

    node->setPosition(vec);
    _lastCords = t->getPos();
}

bool Mob::receiveExplosion(irr::u32 y, irr::u32 x)
{
    if (y == (u32)(floor(_pos.Z / 2 + 0.5))
    && x == (u32)(floor(_pos.X / 2 + 0.5)) && _alive) {
        GraphicsComponent::getMesh(0)->remove();
        _alive = false;
        deadAnimation();
        return true;
    }
    return false;
}

void Mob::processAction(void *)
{
    while (ActionEventComponent::_actionsId.size() > 0) {
        auto a = _actionsId.back();

        if (a == action::DEAD) {
            GraphicsComponent::getMesh(0)->remove();
            _alive = false;
            deadAnimation();
        }

        _actionsId.pop_back();
    }
}

void Mob::processInteraction(enum interaction i, IEntityComponent *e)
{
    if (i == interaction::Range && e->getType() == IEntity::EType::PLAYER && _alive)
        ActionEventComponent::addAction(DEAD);
}

irr::core::vector2d<irr::u32> Mob::getMap2D()
{
    auto pos = TransformComponent::_pos;

    return {
        (u32)(floor(pos.X / 2 + 0.5)),
        (u32)(floor(pos.Z / 2 + 0.5))
    };
}

void Mob::IA(core::vector2d<u32> pos, std::array<Block *, 4> &cross, std::vector<Player *> &players)
{
    if (_target && moveTarget(_targetPos.Y, _targetPos.X) == false)
        return;
    else if (_target)
        _target = false;
    bool changeDirection = false;
    bool playerDetected = false;

    // magnetic player
    for (auto *p : players)
        if (p->isAlive()) {
            auto mPos = p->getMapPos();
            if ((u32)mPos.X == pos.X && (u32)mPos.Y == pos.Y + 1 && (playerDetected = true))
                _fromBlock = 0;
            else if ((u32)mPos.X == pos.X + 1 && (u32)mPos.Y == pos.Y && (playerDetected = true))
                _fromBlock = 1;
            else if ((u32)mPos.X == pos.X && (u32)mPos.Y == pos.Y - 1 && (playerDetected = true))
                _fromBlock = 2;
            else if ((u32)mPos.X == pos.X - 1 && (u32)mPos.Y == pos.Y && (playerDetected = true))
                _fromBlock = 3;
            break;
        }

    // Keep Direction
    if (!changeDirection || playerDetected == true) {
        if (_fromBlock == 0 && cross[0] && cross[0]->getBlockType() == '.' && (_target = true))
            _targetPos = core::vector2d<u32>(pos.X, pos.Y + 1);
         else if (_fromBlock == 1 && cross[1] && cross[1]->getBlockType() == '.' && (_target = true))
            _targetPos = core::vector2d<u32>(pos.X + 1, pos.Y);
        else if (_fromBlock == 2 && cross[2] && cross[2]->getBlockType() == '.' && (_target = true))
            _targetPos = core::vector2d<u32>(pos.X, pos.Y - 1);
        else if (_fromBlock == 3 && cross[3] && cross[3]->getBlockType() == '.' && (_target = true))
            _targetPos = core::vector2d<u32>(pos.X - 1, pos.Y);
        if (_target)
            return;
    }
    
    // Direction Random
    int rand = std::rand() % 4; // new direction
    if (cross[0] && cross[0]->getBlockType() == '.' && (rand == 0) && (_target = true) && (_fromBlock = 0) < 4)
        _targetPos = core::vector2d<u32>(pos.X, pos.Y + 1);
    else if (cross[1] && cross[1]->getBlockType() == '.' && (rand == 1) && (_target = true) && (_fromBlock = 1))
        _targetPos = core::vector2d<u32>(pos.X + 1, pos.Y);
    else if (cross[2] && cross[2]->getBlockType() == '.' && (rand == 2) && (_target = true) && (_fromBlock = 2))
        _targetPos = core::vector2d<u32>(pos.X, pos.Y - 1);
    else if (cross[3] && cross[3]->getBlockType() == '.' && (rand == 3) && (_target = true) && (_fromBlock = 3))
        _targetPos = core::vector2d<u32>(pos.X - 1, pos.Y);
}

bool Mob::moveTarget(irr::u32 y, irr::u32 x)
{
    static const float marge = 0.15;
    static const float speed = 2.5;
    core::vector3df wanted = core::vector3df(x * 2, _pos.Y, y * 2);
    if (wanted.X - marge < _pos.X && _pos.X < wanted.X + marge
    && wanted.Z - marge < _pos.Z && _pos.Z < wanted.Z + marge) {
        TransformComponent::_pos = wanted;
        MotionComponent::_mov_speed = core::vector3df(0,0,0);
        return true;
    }
    float dx = (wanted.X - _pos.X > 0) ? speed : (wanted.X - _pos.X < 0) ? -speed : 0;
    float dy = (wanted.Z - _pos.Z > 0) ? speed : (wanted.Z - _pos.Z < 0) ? -speed : 0;

    if (dy != 0)
        TransformComponent::_rot.Y = (dy > 0) ? 180 : 0;
    else if (dx != 0)
        TransformComponent::_rot.Y = (dx > 0) ? -90 : 90;

    core::vector3df direction{ dx, 0, dy };
    MotionComponent::_mov_speed = direction;
    return false;
}

#include "particle/CParticleSystem.hpp"
void Mob::deadAnimation()
{
    CParticleSystem* system = new CParticleSystem(_smgr->getRootSceneNode(), _smgr);
    system->setPosition(core::vector3df(_pos.X, 1.0f, _pos.Z));
    system->setRotation(core::vector3df(0, 0, 0));
    system->setScale(irr::core::vector3df(1, 1, 1));
    system->updateAbsolutePosition();

    CParticleDrawer* drawer;
    CParticleAffector* affector;

    ///Flash Emitter
    drawer = system->addParticleDrawer();
    drawer->addUVCoords(SParticleUV(irr::core::vector2df(0.5, 0),
        irr::core::vector2df(0.75, 0), irr::core::vector2df(0.5, 0.25),
        irr::core::vector2df(0.75f, 0.25f)));
    drawer->addUVCoords(SParticleUV(irr::core::vector2df(0.5 + 0.25f, 0),
        irr::core::vector2df(0.75 + 0.25f, 0), irr::core::vector2df(0.5 + 0.25f, 0.25),
        irr::core::vector2df(0.75f + 0.25f, 0.25f)));
     drawer->addStandardEmitter(irr::core::vector3df(0, 0, 0), irr::core::vector3df(0, 0, 0),
        irr::core::vector3df(0, 0, 0), irr::core::vector3di(0), 20, 50, 5, 200, 300,
        irr::core::vector2df(1, 1), irr::core::vector2df(1, 1), irr::core::vector2df(3),
        irr::video::SColor(255, 255, 255, 100), irr::video::SColor(255, 255, 255, 100));
    affector = new ColorAffector(irr::video::SColor(0, 255, 255, 100));
    drawer->addAffector(affector);
    affector->drop();

    ///Smoke
    drawer = system->addParticleDrawer();
    drawer->addUVCoords(SParticleUV(irr::core::vector2df(0.5f, 0.75f), irr::core::vector2df(0.75f, 0.75f), irr::core::vector2df(0.5f, 1.f), irr::core::vector2df(0.75f, 1.f)));
    drawer->addStandardEmitter(irr::core::vector3df(0, 0, 0), irr::core::vector3df(1, 0, 0),
        irr::core::vector3df(2, 0, 0), irr::core::vector3di(0, 180, 0), 0, 200, 70, 500, 700,
        irr::core::vector2df(1, 1), irr::core::vector2df(2, 2), irr::core::vector2df(2),
        irr::video::SColor(190, 0, 0, 0), irr::video::SColor(230, 0, 0, 0));
    affector = new GravityAffector(irr::core::vector3df(0.f, 10.0f, 0.f));
    drawer->addAffector(affector);
    affector->drop();

    irr::video::SMaterial overrideMaterial;
    overrideMaterial.MaterialType = irr::video::EMT_ONETEXTURE_BLEND;
    overrideMaterial.setTexture(0, _smgr->getVideoDriver()->getTexture("assets/particle/explose.png"));
    overrideMaterial.setFlag(irr::video::EMF_LIGHTING, false);
    overrideMaterial.setFlag(irr::video::EMF_ZWRITE_ENABLE, false);
    overrideMaterial.setFlag(irr::video::EMF_BACK_FACE_CULLING, false);
    overrideMaterial.MaterialTypeParam = irr::video::pack_textureBlendFunc(irr::video::EBF_SRC_ALPHA,
        irr::video::EBF_ONE_MINUS_SRC_ALPHA, irr::video::EMFN_MODULATE_1X,
        irr::video::EAS_VERTEX_COLOR | irr::video::EAS_TEXTURE);
    system->setOverrideMaterial(overrideMaterial);
    irr::scene::ISceneNodeAnimator* anim = _smgr->createDeleteAnimator(3000);
    system->addAnimator(anim);
    anim->drop();
    system->drop();
}