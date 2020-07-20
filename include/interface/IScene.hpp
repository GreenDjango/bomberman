/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** IScene
*/

#ifndef ISCENE_HPP_
#define ISCENE_HPP_

#include <irrlicht/irrlicht.h>
#include "class/CameraManager.hpp"
#include "class/SoundManager.hpp"
#include "GameStats.hpp"

class IScene
{
public:
    enum SceneID {
        IDLE,
        INTRO,
        MENU,
        PLAYER_CHOOSE,
        GAME_MOB,
        GAME_VS
    };
    virtual ~IScene() {};

    virtual void init(irr::IrrlichtDevice *device,
        GameStats *gameS, CameraManager *cameraM, SoundManager *soundM) = 0;
    virtual void start(irr::u32 startTime) = 0;
    virtual void draw() = 0;
    virtual void clean() = 0;
    virtual bool OnTimer(irr::u32 startTime, SceneID &) = 0;
    virtual bool OnEvent(const irr::SEvent &, SceneID &) = 0;
protected:
    irr::u32 _startTime;
    irr::IrrlichtDevice *_device; 
    irr::gui::IGUIEnvironment *_guienv;
    irr::video::IVideoDriver *_driver;
    GameStats *_gameS;
    CameraManager *_cameraM;
    SoundManager *_soundM;
};

#endif /* !ISCENE_HPP_ */
