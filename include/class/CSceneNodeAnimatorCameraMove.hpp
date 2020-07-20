/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** Bombe
*/

#ifndef CSCENENODEANIMATORCAMERAMOVE_HPP_
#define CSCENENODEANIMATORCAMERAMOVE_HPP_

#include <irrlicht/irrlicht.h>
#include <vector>

class CSceneNodeAnimatorCameraMove : public irr::scene::ISceneNodeAnimator {
public:
    CSceneNodeAnimatorCameraMove(irr::core::array<irr::core::vector3df>& position,
        irr::core::array<irr::core::vector3df>& target, irr::core::array<irr::u32>& key,
        irr::u32 startTime, bool *finishTrigger = nullptr, irr::scene::IMeshSceneNode *focusPrewiew = nullptr);

    virtual void animateNode(irr::scene::ISceneNode* node, irr::u32 timeMs);
    virtual ISceneNodeAnimator* createClone(irr::scene::ISceneNode* node, irr::scene::ISceneManager* newManager = 0);
    virtual bool hasFinished(void) const { return HasFinished; }

private:
    irr::u32 _index;
    irr::u32 _timeInterval;
    irr::core::vector3df _locPos;
    irr::core::vector3df _locTarget;
    irr::core::array<irr::core::vector3df> _pos;
    irr::core::array<irr::core::vector3df> _target;
    irr::core::array<irr::u32> _key;
    irr::u32 StartTime;
    irr::u32 _startAnimTime;
    irr::scene::IMeshSceneNode *_focusPrewiew;
    bool _firstLoop;
    bool HasFinished;
    bool *_finishTrigger;
};

#endif /* !CSCENENODEANIMATORCAMERAMOVE_HPP_ */
