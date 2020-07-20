/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** SceneGameMob
*/

#include "scene/SceneGameMob.hpp"
#include "utils/ImageCreator.hpp"
#include "Pack.hpp"
#include <iostream>

using namespace irr;

static void setButton(gui::IGUIButton *button)
{
    button->setScaleImage(true);
    button->setUseAlphaChannel(true);
    button->setDrawBorder(false);
}

static core::stringw msToString(u32 time)
{
    core::stringw rTime{time / 60000};
    rTime += L":";
    u32 second = (time % 60000) / 1000;
    if (second < 10)
        rTime += L"0";
    rTime += second;
    return rTime;
}

void SceneGameMob::init(IrrlichtDevice *device, GameStats *gameS, CameraManager *cameraM, SoundManager *soundM)
{
    _device = device;
    _guienv = device->getGUIEnvironment();
    _driver = device->getVideoDriver();
    _gameS = gameS;
    _cameraM = cameraM;
    _soundM = soundM;
    _showHelp = false;
    _isEnd = false;
    _isWin = false;

    _fonts[GUI::END_PNL] = _guienv->getFont("assets/font/handel_gothic_56_b.xml");
    _fonts[GUI::HELP_PNL] = _guienv->getFont("assets/font/handel_gothic_36_b.xml");
    _fonts[GUI::PLAYER1] = _guienv->getFont("assets/font/handel_gothic_28.xml");
    _fonts[GUI::STATS] = _guienv->getFont("assets/font/handel_gothic_28_b.xml");
    gui::IGUIButton *button;
    gui::IGUIImage *image;
    // PERSPEC button
    button = _guienv->addButton(core::recti({1520, 880}, core::dimension2d<s32>{100, 100}));
    button->setImage(_driver->getTexture("./assets/gui/icons/projec_perspe.png"));
    button->setPressedImage(_driver->getTexture("./assets/gui/icons/projec_ortho.png"));
    button->setIsPushButton(true);
    setButton(button);
    button->setID(GUI::PERSPEC);
    _gui[GUI::PERSPEC] = button;
    // SOUND button
    button = _guienv->addButton(core::recti({1650, 880}, core::dimension2d<s32>{100, 100}));
    button->setImage(_driver->getTexture("./assets/gui/icons/effect.png"));
    button->setPressedImage(_driver->getTexture("./assets/gui/icons/effect_mute.png"));
    button->setIsPushButton(true);
    setButton(button);
    button->setID(GUI::SOUND);
    _gui[GUI::SOUND] = button;
    // MUSIC button
    button = _guienv->addButton(core::recti({1780, 880}, core::dimension2d<s32>{100, 100}));
    button->setImage(_driver->getTexture("./assets/gui/icons/music.png"));
    button->setPressedImage(_driver->getTexture("./assets/gui/icons/music_mute.png"));
    button->setIsPushButton(true);
    setButton(button);
    button->setID(GUI::MUSIC);
    _gui[GUI::MUSIC] = button;
    // SAVE button
    button = ImageCreator::newButton( _guienv, _driver->getTexture("./assets/gui/buttonLong_brown.png"), {1620, 50, 1920, 180}, ImageCreator::TOP_CENTER, 1.2f);
    button->setPressedImage(_driver->getTexture("./assets/gui/buttonLong_brown_pressed.png"));
    button->setID(GUI::SAVE);
    _gui[GUI::SAVE] = button;
    // HELP_BTN button
    button = ImageCreator::newButton( _guienv, _driver->getTexture("./assets/gui/buttonLong_brown.png"), {1620, 50, 1920, 180}, ImageCreator::BOTTOM_CENTER, 1.2f);
    button->setPressedImage(_driver->getTexture("./assets/gui/buttonLong_brown_pressed.png"));
    button->setID(GUI::HELP_BTN);
    _gui[GUI::HELP_BTN] = button;
    // HELP_PNL button
    button = ImageCreator::newButton( _guienv, _driver->getTexture("./assets/gui/panel_brown.png"), {0, 0, 1920, 950}, ImageCreator::CENTER_CENTER);
    button->setID(GUI::HELP_PNL);
    _gui[GUI::HELP_PNL] = button;
    // END_PNL button
    button = ImageCreator::newButton( _guienv, _driver->getTexture("./assets/gui/panel_brown.png"), {0, 0, 1920, 950}, ImageCreator::CENTER_CENTER);
    button->setID(GUI::END_PNL);
    _gui[GUI::END_PNL] = button;
    // PLAYER_OVERLAY
    image = _guienv->addImage(core::recti({30, 702}, core::dimension2d<s32>{320, 248}));
    _gui[GUI::PLAYER1] = image;
    // PLAYER_OVERLAY2
    image = _guienv->addImage(core::recti({30, 50}, core::dimension2d<s32>{320, 248}));
    _gui[GUI::PLAYER2] = image;
    // TIME
    image = ImageCreator::newImage(_guienv, _driver->getTexture("./assets/gui/remaining_time.png"), {0, 25, 1920, 0}, ImageCreator::TOP_CENTER);
    _gui[GUI::TIME] = image;
    for (auto el : _gui)
        el.second->setVisible(false);
}

void SceneGameMob::start(u32 startTime)
{
    _startTime = startTime;
    f32 factor = _device->getSceneManager()->getSceneNodeFromId(21)->getScale().X;
    _cameraM->animation4(factor);
    _soundM->playTheme(SoundManager::GAME);
    for (auto el : _gui)
        el.second->setVisible(true);
    _gui[GUI::HELP_PNL]->setVisible(false);
    _gui[GUI::END_PNL]->setVisible(false);
    io::path player1 = "./assets/gui/players/player";
    player1 += io::path{_gameS->players[0].modelNum};
    player1 += "_bonus.png";
    ((gui::IGUIImage *)_gui[GUI::PLAYER1])->setImage(_driver->getTexture(player1));
    if (_gameS->nbPlayer >= 2) {
        io::path player2 = "./assets/gui/players/player";
        player2 += io::path{_gameS->players[1].modelNum};
        player2 += "_bonus.png";
        ((gui::IGUIImage *)_gui[GUI::PLAYER2])->setImage(_driver->getTexture(player2));
    } else
        _gui[GUI::PLAYER2]->setVisible(false);
    ((gui::IGUIButton *)_gui[GUI::SOUND])->setPressed(_soundM->isMuteSound());
    ((gui::IGUIButton *)_gui[GUI::MUSIC])->setPressed(_soundM->isMuteTheme());
}

void SceneGameMob::draw()
{
    _gui[GUI::PERSPEC]->draw();
    _gui[GUI::SOUND]->draw();
    _gui[GUI::MUSIC]->draw();
    _gui[GUI::SAVE]->draw();
    _gui[GUI::HELP_BTN]->draw();
    _gui[GUI::PLAYER1]->draw();
    _gui[GUI::PLAYER2]->draw();
    _gui[GUI::TIME]->draw();
    _fonts[GUI::PLAYER1]->draw(L"Player 1", core::recti(188,910,0,0), video::SColor(255,255,255,255));
    _fonts[GUI::STATS]->draw(core::stringw(_gameS->players[0].life), core::recti(250,700,0,0), video::SColor(240,255,255,255));
    _fonts[GUI::STATS]->draw(core::stringw(_gameS->players[0].rangeBomb), core::recti(250,740,0,0), video::SColor(240,255,255,255));
    _fonts[GUI::STATS]->draw(core::stringw(_gameS->players[0].capacityBomb) + L"/" + core::stringw(_gameS->players[0].maxBomb), core::recti(250,780,0,0), video::SColor(240,255,255,255));
    _fonts[GUI::STATS]->draw(core::stringw((int)_gameS->players[0].speedTimer) + L"s", core::recti(250,820,0,0), video::SColor(240,255,255,255));
    _fonts[GUI::STATS]->draw(core::stringw((int)_gameS->players[0].wallPassTimer) + L"s", core::recti(250,860,0,0), video::SColor(240,255,255,255));
    if (_gameS->nbPlayer >= 2) {
        _fonts[GUI::PLAYER1]->draw(L"Player 2", core::recti(188,258,0,0), video::SColor(255,255,255,255));
        _fonts[GUI::STATS]->draw(core::stringw(_gameS->players[1].life), core::recti(250,45,0,0), video::SColor(240,255,255,255));
        _fonts[GUI::STATS]->draw(core::stringw(_gameS->players[1].rangeBomb), core::recti(250,85,0,0), video::SColor(240,255,255,255));
        _fonts[GUI::STATS]->draw(core::stringw(_gameS->players[1].capacityBomb) + L"/" + core::stringw(_gameS->players[1].maxBomb), core::recti(250,125,0,0), video::SColor(240,255,255,255));
        _fonts[GUI::STATS]->draw(core::stringw((int)_gameS->players[1].speedTimer) + L"s", core::recti(250,165,0,0), video::SColor(240,255,255,255));
        _fonts[GUI::STATS]->draw(core::stringw((int)_gameS->players[1].wallPassTimer) + L"s", core::recti(250,205,0,0), video::SColor(240,255,255,255));
    }
    _fonts[GUI::PLAYER1]->draw(L"Save & Exit", _gui[GUI::SAVE]->getAbsoluteClippingRect(), video::SColor(240,255,255,255), true, true);
    _fonts[GUI::PLAYER1]->draw(L"Help (?)", _gui[GUI::HELP_BTN]->getAbsoluteClippingRect(), video::SColor(240,255,255,255), true, true);
    _fonts[GUI::STATS]->draw(msToString(_gameS->remainingTime), _gui[GUI::TIME]->getAbsoluteClippingRect(), video::SColor(240,255,255,255), true, true); 
    if (_isEnd) {
        _driver->draw2DRectangle(video::SColor(130, 0, 0, 0), core::rect<s32>(0,0,1920,1080));
        _gui[GUI::END_PNL]->draw();
        _fonts[GUI::HELP_PNL]->draw(L"Finish\n", _gui[GUI::END_PNL]->getAbsoluteClippingRect() + core::vector2di(0, 50), video::SColor(240,255,255,255), true);
        if (_isWin)
            _fonts[GUI::END_PNL]->draw(L"You win !", _gui[GUI::END_PNL]->getAbsoluteClippingRect(), video::SColor(240,255,255,255), true, true);
        else
            _fonts[GUI::END_PNL]->draw(L"You loose...", _gui[GUI::END_PNL]->getAbsoluteClippingRect(), video::SColor(240,255,255,255), true, true);
    }
    if (_showHelp) {
        _driver->draw2DRectangle(video::SColor(130, 0, 0, 0), core::rect<s32>(0,0,1920,1080));
        _gui[GUI::HELP_PNL]->draw();
        _fonts[GUI::HELP_PNL]->draw(L"Help\n", _gui[GUI::HELP_PNL]->getAbsoluteClippingRect() + core::vector2di(0, 50), video::SColor(240,255,255,255), true);
        _fonts[GUI::PLAYER1]->draw(staticText::helpMob, _gui[GUI::HELP_PNL]->getAbsoluteClippingRect(), video::SColor(240,255,255,255), true, true);
    }
    if (_showHelp && !_device->getTimer()->isStopped())
        _device->getTimer()->stop();
}

void SceneGameMob::clean()
{
    for (auto el : _gui)
        el.second->setVisible(false);
}

bool SceneGameMob::OnTimer(u32, SceneID&)
{
    if (_isEnd)
        return false;
    if (_gameS->nbMob <= 0) {
        _soundM->playTheme(SoundManager::Theme::MENU);
        _soundM->audienceCheer();
        _soundM->audienceClap();
        _soundM->win();
        _isEnd = true;
        _gameS->isFinish = true;
        _isWin = true;
        _gui[GUI::END_PNL]->setVisible(true);
    } else if (_gameS->players[0].life < 0 || (_gameS->nbPlayer >= 2 && _gameS->players[1].life < 0)) {
        _soundM->playTheme(SoundManager::Theme::MENU);
        _soundM->audienceDisappoint();
        _soundM->audienceClap();
        _isEnd = true;
        _gameS->isFinish = true;
        _isWin = false;
        _gui[GUI::END_PNL]->setVisible(true);
    } else if (_gameS->remainingTime == 0) {
        _soundM->playTheme(SoundManager::Theme::MENU);
        _soundM->audienceDisappoint();
        _soundM->audienceClap();
        _isEnd = true;
        _gameS->isFinish = true;
        _isWin = false;
        _gui[GUI::END_PNL]->setVisible(true);
    }
    return false;
}

bool SceneGameMob::OnEvent(const SEvent& event, SceneID&)
{
    if (event.EventType == EEVENT_TYPE::EET_GUI_EVENT
        && event.GUIEvent.EventType == gui::EGUI_EVENT_TYPE::EGET_BUTTON_CLICKED
        && event.GUIEvent.Caller) {
        _soundM->click();
        if (event.GUIEvent.Caller->getID() == GUI::PERSPEC)
            _cameraM->toggleProjection();
        if (event.GUIEvent.Caller->getID() == GUI::SOUND)
            _soundM->toggleMuteSound();
        if (event.GUIEvent.Caller->getID() == GUI::MUSIC)
            _soundM->toggleMuteTheme();
        if (event.GUIEvent.Caller->getID() == GUI::SAVE)
            _device->closeDevice();
        if (event.GUIEvent.Caller->getID() == GUI::HELP_BTN) {
            _showHelp = true;
            _gui[GUI::HELP_PNL]->setVisible(true);
        }
        if (event.GUIEvent.Caller->getID() == GUI::HELP_PNL) {
            _showHelp = false;
            _gui[GUI::HELP_PNL]->setVisible(false);
            _device->getTimer()->start();
        }
        if (event.GUIEvent.Caller->getID() == GUI::END_PNL) {
            _device->closeDevice();
            /*TODO
            sceneID = SceneID::MENU;
            clean();
            return true;*/
        }
        _guienv->removeFocus(event.GUIEvent.Caller);
    }
    return false;
}