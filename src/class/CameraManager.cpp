/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** CameraManager
*/

#include "class/CameraManager.hpp"
#include <iostream>

using namespace irr;

CameraManager::CameraManager(scene::ICameraSceneNode *camera)
{
    _hasFinish = true;
    _isPerspective = true;
    setCamera(camera);
    _camStatus = cameraStatus::IDLE;
}

void CameraManager::setCamera(irr::scene::ICameraSceneNode *camera)
{
    _camera = camera;
    if (camera)
        _projectionMatrix = camera->getProjectionMatrix();
}

void CameraManager::toggleProjection()
{
    if (_isPerspective)
        setOrthogonal();
    else
        setPerspective();
}

void CameraManager::setOrthogonal()
{
     _camera->getProjectionMatrix();
    core::matrix4 proj{};
    _camera->setProjectionMatrix(proj.buildProjectionMatrixOrthoLH(57, 29, 0, 1000), true);
    _isPerspective = false;
}

void CameraManager::setPerspective()
{
    _camera->setProjectionMatrix(_projectionMatrix);
    _isPerspective = true;
}

void CameraManager::stop()
{
    _camera->removeAnimators();
    _camera->setPosition(_finalPos);
    _camera->setTarget(_finalTarget);
    _hasFinish = true;
}

void CameraManager::animation1(scene::IMeshSceneNode* focusPrewiew)
{
    //Port 51.6732 4.47557 -14.2238 
    //Fenetre -11.5219 6.80482 -15.8139
    //Mur1 9.3689 7.65905 -40.7057 
    //Dos 46.4644 5.29014 -3.76626
    core::array<core::vector3df> positions {};
    positions.push_back(core::vector3df(52, 8, -15));
    positions.push_back(core::vector3df(40, 8, -15));
    positions.push_back(core::vector3df(5, 8, -15));
    positions.push_back(core::vector3df(-10, 8, -15));
    positions.push_back(core::vector3df(34.7f, 9, 10));
    _finalPos = positions.getLast();
    core::array<core::vector3df> targets {};
    targets.push_back(core::vector3df(-11, 5, -15));
    targets.push_back(core::vector3df(-11, 8, -15));
    targets.push_back(core::vector3df(100, 8, -50));
    targets.push_back(core::vector3df(46, 15, 10));
    targets.push_back(core::vector3df(34.7f, 9, 27));
    _finalTarget = targets.getLast();
    core::array<u32> keys {};
    keys.push_back(0);
    keys.push_back(800);
    keys.push_back(2800);
    keys.push_back(4500);
    keys.push_back(6500);
    _hasFinish = false;
    scene::ISceneNodeAnimator *anim;
    anim = new CSceneNodeAnimatorCameraMove(positions, targets, keys, 500, &_hasFinish, focusPrewiew);
    _camera->addAnimator(anim);
    anim->drop();
    _camStatus = cameraStatus::INTRO;
}

void CameraManager::animation2(scene::IMeshSceneNode* focusPrewiew)
{
    core::array<core::vector3df> positions {};
    positions.push_back(_camera->getPosition());
    positions.push_back(core::vector3df(40, 11, 5));
    _finalPos = positions.getLast();
    core::array<core::vector3df> targets {};
    targets.push_back(_camera->getTarget());
    targets.push_back(core::vector3df(50, 3, 5));
    _finalTarget = targets.getLast();
    core::array<u32> keys {};
    keys.push_back(0);
    keys.push_back(1500);
    _hasFinish = false;
    scene::ISceneNodeAnimator *anim;
    anim = new CSceneNodeAnimatorCameraMove(positions, targets, keys, 0, &_hasFinish, focusPrewiew);
    _camera->addAnimator(anim);
    anim->drop();
    _camStatus = cameraStatus::PLAYER_CHOOSE;
}

void CameraManager::animation3(scene::IMeshSceneNode* focusPrewiew)
{
    core::array<core::vector3df> positions {};
    positions.push_back(_camera->getPosition());
    positions.push_back(core::vector3df(43, 11, -6));
    _finalPos = positions.getLast();
    core::array<core::vector3df> targets {};
    targets.push_back(_camera->getTarget());
    targets.push_back(core::vector3df(50, 3, 5));
    _finalTarget = targets.getLast();
    core::array<u32> keys {};
    keys.push_back(0);
    keys.push_back(1000);
    _hasFinish = false;
    scene::ISceneNodeAnimator *anim;
    anim = new CSceneNodeAnimatorCameraMove(positions, targets, keys, 0, &_hasFinish, focusPrewiew);
    _camera->addAnimator(anim);
    anim->drop();
    _camStatus = cameraStatus::MAP_CHOOSE;
}

void CameraManager::animation4(f32 factor, scene::IMeshSceneNode* focusPrewiew)
{
    core::array<core::vector3df> positions {};
    positions.push_back(_camera->getPosition());
    positions.push_back(core::vector3df(18, 22, 2));
    _finalPos = positions.getLast();
    core::array<core::vector3df> targets {};
    targets.push_back(_camera->getTarget() * factor);
    targets.push_back(core::vector3df(18,0,11) * factor);
    _finalTarget = targets.getLast();
    _camera->setTarget(_camera->getTarget() * factor);
    core::array<u32> keys {};
    keys.push_back(0);
    keys.push_back(1500);
    _hasFinish = false;
    scene::ISceneNodeAnimator *anim;
    anim = new CSceneNodeAnimatorCameraMove(positions, targets, keys, 0, &_hasFinish, focusPrewiew);
    _camera->addAnimator(anim);
    anim->drop();
    _camStatus = cameraStatus::GAME;
}

void CameraManager::animation5(scene::IMeshSceneNode* focusPrewiew)
{
    core::array<core::vector3df> positions {};
    positions.push_back(_camera->getPosition());
    positions.push_back(core::vector3df(40, 19, 18));
    _finalPos = positions.getLast();
    core::array<core::vector3df> targets {};
    targets.push_back(_camera->getTarget());
    targets.push_back(core::vector3df(50, 19, 18));
    _finalTarget = targets.getLast();
    core::array<u32> keys {};
    keys.push_back(0);
    keys.push_back(1000);
    _hasFinish = false;
    scene::ISceneNodeAnimator *anim;
    anim = new CSceneNodeAnimatorCameraMove(positions, targets, keys, 0, &_hasFinish, focusPrewiew);
    _camera->addAnimator(anim);
    anim->drop();
    _camStatus = cameraStatus::CREDITS;
}

void CameraManager::animation6(scene::IMeshSceneNode* focusPrewiew)
{
    core::array<core::vector3df> positions {};
    positions.push_back(_camera->getPosition());
    positions.push_back(core::vector3df(34.7f, 9, 10));
    _finalPos = positions.getLast();
    core::array<core::vector3df> targets {};
    targets.push_back(_camera->getTarget());
    targets.push_back(core::vector3df(34.7f, 9, 27));
    _finalTarget = targets.getLast();
    core::array<u32> keys {};
    keys.push_back(0);
    keys.push_back(1000);
    _hasFinish = false;
    scene::ISceneNodeAnimator *anim;
    anim = new CSceneNodeAnimatorCameraMove(positions, targets, keys, 0, &_hasFinish, focusPrewiew);
    _camera->addAnimator(anim);
    anim->drop();
    _camStatus = cameraStatus::INTRO;
}

void CameraManager::shake()
{
    if (!_hasFinish && _camStatus == cameraStatus::SHAKE)
        stop();
    core::array<core::vector3df> positions {};
    core::array<core::vector3df> targets {};
    core::array<u32> keys {};
    core::vector3df cameraPos = _camera->getPosition();
    for (int i = 0; i < 20; i++) {
        float x = ((std::rand()/(double)RAND_MAX ) * 0.6f) - 0.3f;
        float y = ((std::rand()/(double)RAND_MAX ) * 0.6f) - 0.3f;
        float z = ((std::rand()/(double)RAND_MAX ) * 0.6f) - 0.3f;
        positions.push_back(core::vector3df(x, y, z) + cameraPos);
        targets.push_back(_camera->getTarget());
        keys.push_back(i*15);
    }
    positions.push_back(_camera->getPosition());
    _finalPos = positions.getLast();
    targets.push_back(_camera->getTarget());
    _finalTarget = targets.getLast();
    keys.push_back(300);

    _hasFinish = false;
    scene::ISceneNodeAnimator *anim;
    anim = new CSceneNodeAnimatorCameraMove(positions, targets, keys, 0, &_hasFinish);
    _camera->addAnimator(anim);
    anim->drop();
    _camStatus = cameraStatus::SHAKE;
}
