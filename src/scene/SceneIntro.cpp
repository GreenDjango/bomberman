/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** SceneIntro
*/

#include "scene/SceneIntro.hpp"
#include <iostream>

using namespace irr;

void SceneIntro::init(IrrlichtDevice *device, GameStats *gameS, CameraManager *cameraM, SoundManager *soundM)
{
    _device = device;
    _guienv = device->getGUIEnvironment();
    _driver = device->getVideoDriver();
    _gameS = gameS;
    _cameraM = cameraM;
    _soundM = soundM;
    
    _fonts[GUI::SKIP] = _guienv->getFont("assets/font/handel_gothic_28_b.xml");
    gui::IGUIImage *image;
    image = _guienv->addImage(core::recti({640, 650}, core::dimension2d<s32>{640, 360}));
    image->setImage(_driver->getTexture("./assets/gui/title.png"));
    image->setScaleImage(true);
    _gui[GUI::SKIP] = image;
}

void SceneIntro::start(u32 startTime)
{
    _startTime = startTime;
    _cameraM->animation1();
    _soundM->playTheme(SoundManager::MENU);
}

void SceneIntro::draw()
{
    _gui[GUI::SKIP]->draw();
    _fonts[GUI::SKIP]->draw(L"Press `SPACE' for skip", core::recti(0,950,1920,1080), video::SColor(250,255,255,255), true);
}

void SceneIntro::clean()
{
    for (auto el : _gui)
        el.second->setVisible(false);
}

bool SceneIntro::OnTimer(u32, SceneID& sceneID)
{
    if (_cameraM->hasFinish() && _cameraM->cameraStat() == CameraManager::INTRO) {
        sceneID = SceneID::MENU;
        clean();
        return true;
    }
    return false;
}

bool SceneIntro::OnEvent(const SEvent& event, SceneID& sceneID)
{
    if (event.EventType == irr::EEVENT_TYPE::EET_KEY_INPUT_EVENT && event.KeyInput.Key == irr::KEY_SPACE) {
        _cameraM->stop();
        sceneID = SceneID::MENU;
        clean();
        return true;
    }
    return false;
}