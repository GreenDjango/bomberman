/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** CSceneNodeAnimatorCameraMove
*/

#include "class/CSceneNodeAnimatorCameraMove.hpp"

using namespace irr;

CSceneNodeAnimatorCameraMove::CSceneNodeAnimatorCameraMove(core::array<core::vector3df>& position,
    core::array<core::vector3df>& target, core::array<u32>& key, u32 startTime, bool *finishTrigger,
    scene::IMeshSceneNode *focusPrewiew)
    : _pos(position)
    , _target(target)
    , _key(key)
    , StartTime(startTime)
    , _firstLoop(true)
    , HasFinished(false)
{
    _index = 0;
    _finishTrigger = finishTrigger;
    _focusPrewiew = focusPrewiew;
}

void CSceneNodeAnimatorCameraMove::animateNode(scene::ISceneNode* node, u32 timeMs)
{
    if (_firstLoop) {
        _firstLoop = false;
        _startAnimTime = timeMs;
    }
    if (HasFinished || timeMs - _startAnimTime <= StartTime)
        return;
    timeMs -= _startAnimTime;
    timeMs -= StartTime;
    const u32 kSize = _key.size();
    scene::ICameraSceneNode* camera = static_cast<scene::ICameraSceneNode*>(node);
    if (kSize <= 1 || _key[kSize - 1] < timeMs) {
        camera->setPosition(_pos[kSize - 1]);
        camera->setTarget(_target[kSize - 1]);
        HasFinished = true;
        if (_finishTrigger)
            *_finishTrigger = true;
        camera->removeAnimator(this);
        return;
    }
    while (kSize > _index + 1 && _key[_index] <= timeMs)
    {
        if (kSize > _index + 2) {
            _pos[_index + 1].interpolate(_pos[_index + 1], _pos[_index], 0.5f);
            _target[_index + 1].interpolate(_target[_index + 1], _target[_index], 0.5f);
        }
        _locPos = _pos[_index + 1] - _pos[_index];
        _locTarget = _target[_index + 1] - _target[_index];
        _timeInterval = (_key[_index + 1] - _key[_index]);
        _index++;
    }
    f32 timeFactor = ((_key[_index] - timeMs) / (f32)_timeInterval);
    core::vector3df relPos = _pos[_index] - (_locPos * timeFactor);
    core::vector3df relTarget = _target[_index] - (_locTarget * timeFactor);
    camera->setPosition(relPos);
    camera->setTarget(relTarget);
    if (_focusPrewiew)
        _focusPrewiew->setPosition(relTarget);
}

scene::ISceneNodeAnimator* CSceneNodeAnimatorCameraMove::createClone(scene::ISceneNode* node, scene::ISceneManager* newManager)
{
    node = (scene::ISceneNode*)node;
    newManager = (scene::ISceneManager*)newManager;
    return nullptr;
}

