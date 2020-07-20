/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** SceneMenu
*/

#include "scene/SceneMenu.hpp"
#include "utils/ImageCreator.hpp"
#include <iostream>

using namespace irr;

static void setButton(gui::IGUIButton *button)
{
    button->setScaleImage(true);
    button->setUseAlphaChannel(true);
    button->setDrawBorder(false);
}

void SceneMenu::toggleCredits(bool isCredits)
{
    _gui[GUI::PLAY]->setVisible(!isCredits);
    _gui[GUI::LOAD]->setVisible(!isCredits);
    _gui[GUI::EXIT]->setVisible(!isCredits);
    _gui[GUI::CREDITS]->setVisible(!isCredits);
    _gui[GUI::BACK]->setVisible(isCredits);
}

void SceneMenu::init(IrrlichtDevice *device, GameStats *gameS, CameraManager *cameraM, SoundManager *soundM)
{
    _device = device;
    _guienv = device->getGUIEnvironment();
    _driver = device->getVideoDriver();
    _gameS = gameS;
    _cameraM = cameraM;
    _soundM = soundM;
    _cd = _device->getFileSystem()->getWorkingDirectory();
    _isCredits = false;

    _fonts[GUI::PLAY] = _guienv->getFont("assets/font/handel_gothic_56_b.xml");
    _fonts[GUI::PLAY]->setKerningWidth(3);
    _fonts[GUI::EXIT] = _guienv->getFont("assets/font/handel_gothic_36_b.xml");
    _fonts[GUI::EXIT]->setKerningWidth(3);
    gui::IGUIButton *button;
    // SOUND icon
    button = _guienv->addButton(core::recti({1650, 880}, core::dimension2di{100, 100}));
    button->setImage(_driver->getTexture("./assets/gui/icons/effect.png"));
    button->setPressedImage(_driver->getTexture("./assets/gui/icons/effect_mute.png"));
    button->setIsPushButton(true);
    setButton(button);
    button->setID(GUI::SOUND);
    _gui[GUI::SOUND] = button;
    // MUSIC icon
    button = _guienv->addButton(core::recti({1780, 880}, core::dimension2di{100, 100}));
    button->setImage(_driver->getTexture("./assets/gui/icons/music.png"));
    button->setPressedImage(_driver->getTexture("./assets/gui/icons/music_mute.png"));
    button->setIsPushButton(true);
    setButton(button);
    button->setID(GUI::MUSIC);
    _gui[GUI::MUSIC] = button;
    // PLAY button
    button = ImageCreator::newButton(_guienv, _driver->getTexture("./assets/gui/TextBTN.png"), {644, 350, 1270, 570}, ImageCreator::TOP_LEFT, 0.7f);
    button->setPressedImage(_driver->getTexture("./assets/gui/TextBTN_Pressed.png"));
    button->setID(GUI::PLAY);
    _gui[GUI::PLAY] = button;
    // LOAD button
    button = ImageCreator::newButton(_guienv, _driver->getTexture("./assets/gui/TextBTN.png"), {644, 350, 1270, 570}, ImageCreator::TOP_RIGHT, 0.7f);
    button->setPressedImage(_driver->getTexture("./assets/gui/TextBTN_Pressed.png"));
    button->setID(GUI::LOAD);
    _gui[GUI::LOAD] = button;
    // EXIT button
    button = ImageCreator::newButton(_guienv, _driver->getTexture("./assets/gui/TextBTN.png"), {644, 350, 1270, 570}, ImageCreator::BOTTOM_CENTER, 0.6f);
    button->setPressedImage(_driver->getTexture("./assets/gui/TextBTN_Pressed.png"));
    button->setID(GUI::EXIT);
    _gui[GUI::EXIT] = button;
    // CREDITS button
    button = ImageCreator::newButton(_guienv, _driver->getTexture("./assets/gui/TextBTN.png"), {644, 600, 1270, 0}, ImageCreator::TOP_CENTER, 0.6f);
    button->setPressedImage(_driver->getTexture("./assets/gui/TextBTN_Pressed.png"));
    button->setID(GUI::CREDITS);
    _gui[GUI::CREDITS] = button;
    // BACK button
    button = ImageCreator::newButton(_guienv, _driver->getTexture("./assets/gui/TextBTN.png"), {644, 800, 1270, 0}, ImageCreator::TOP_CENTER, 0.6f);
    button->setPressedImage(_driver->getTexture("./assets/gui/TextBTN_Pressed.png"));
    button->setID(GUI::BACK);
    _gui[GUI::BACK] = button;

    gui::IGUISkin* newskin = _guienv->createSkin(gui::EGST_BURNING_SKIN);
	_guienv->setSkin(newskin);
	newskin->drop();
    _gui[GUI::FILE] = _guienv->addFileOpenDialog(L"Select a save in SAVE folder");

    for (auto el : _gui)
        el.second->setVisible(false);
}

void SceneMenu::start(u32 startTime)
{
    _startTime = startTime;
    for (auto el : _gui)
        el.second->setVisible(true);
    _gui[GUI::FILE]->setVisible(false);
    _gui[GUI::BACK]->setVisible(false);
    ((gui::IGUIButton *)_gui[GUI::SOUND])->setPressed(_soundM->isMuteSound());
    ((gui::IGUIButton *)_gui[GUI::MUSIC])->setPressed(_soundM->isMuteTheme());
}

void SceneMenu::draw()
{
    _gui[GUI::SOUND]->draw();
    _gui[GUI::MUSIC]->draw();
    _gui[GUI::PLAY]->draw();
    _gui[GUI::LOAD]->draw();
    _gui[GUI::EXIT]->draw();
    _gui[GUI::CREDITS]->draw();
    _gui[GUI::BACK]->draw();
    if (!_isCredits) {
        _fonts[GUI::PLAY]->draw(L"Play", _gui[GUI::PLAY]->getAbsoluteClippingRect() + core::vector2di(_fonts[GUI::PLAY]->getKerningWidth(), 0), video::SColor(200,255,255,255), true, true);
        _fonts[GUI::EXIT]->draw(L"Continue", _gui[GUI::LOAD]->getAbsoluteClippingRect() + core::vector2di(_fonts[GUI::EXIT]->getKerningWidth(), 0), video::SColor(200,255,255,255), true, true);
        _fonts[GUI::EXIT]->draw(L"Quit", _gui[GUI::EXIT]->getAbsoluteClippingRect() + core::vector2di(_fonts[GUI::EXIT]->getKerningWidth(), 0), video::SColor(200,255,255,255), true, true);
        _fonts[GUI::EXIT]->draw(L"Credits", _gui[GUI::CREDITS]->getAbsoluteClippingRect() + core::vector2di(_fonts[GUI::EXIT]->getKerningWidth(), 0), video::SColor(200,255,255,255), true, true);
    } else {
        _fonts[GUI::EXIT]->draw(L"Back", _gui[GUI::BACK]->getAbsoluteClippingRect() + core::vector2di(_fonts[GUI::EXIT]->getKerningWidth(), 0), video::SColor(200,255,255,255), true, true);
    }
    _gui[GUI::FILE]->draw();
}

void SceneMenu::clean()
{
    for (auto el : _gui)
        el.second->setVisible(false);
}

bool SceneMenu::OnTimer(u32, SceneID&)
{
    if (_isCredits && _cameraM->cameraStat() == CameraManager::INTRO && _cameraM->hasFinish()) {
        _isCredits = false;
        _isCredits = false;
        toggleCredits(false);
    }
    return false;
}

bool SceneMenu::OnEvent(const SEvent& event, SceneID& sceneID)
{
    if (event.EventType == irr::EEVENT_TYPE::EET_KEY_INPUT_EVENT && event.KeyInput.Key == irr::KEY_RETURN) {
        sceneID = SceneID::PLAYER_CHOOSE;
        clean();
        return true;
    }
    if (event.EventType == EEVENT_TYPE::EET_GUI_EVENT
        && event.GUIEvent.EventType == gui::EGUI_EVENT_TYPE::EGET_BUTTON_CLICKED
        && event.GUIEvent.Caller) {
        _soundM->click();
         if (event.GUIEvent.Caller->getID() == GUI::SOUND)
            _soundM->toggleMuteSound();
        if (event.GUIEvent.Caller->getID() == GUI::MUSIC)
            _soundM->toggleMuteTheme();
        if (event.GUIEvent.Caller->getID() == GUI::PLAY) {
            sceneID = SceneID::PLAYER_CHOOSE;
            clean();
            return true;
        }
        if (event.GUIEvent.Caller->getID() == GUI::LOAD) {
            _gui[GUI::FILE]->setVisible(true);
        }
        if (event.GUIEvent.Caller->getID() == GUI::EXIT) {
            _device->closeDevice();
        }
        if (event.GUIEvent.Caller->getID() == GUI::CREDITS) {
            _isCredits = true;
            toggleCredits(true);
            _cameraM->animation5();
        }
        if (event.GUIEvent.Caller->getID() == GUI::BACK && _cameraM->hasFinish()) {
            _cameraM->animation6();
        }
    }
    if (event.EventType == EEVENT_TYPE::EET_GUI_EVENT
        && (event.GUIEvent.EventType == gui::EGUI_EVENT_TYPE::EGET_FILE_SELECTED ||
        event.GUIEvent.EventType == gui::EGUI_EVENT_TYPE::EGET_FILE_CHOOSE_DIALOG_CANCELLED)) {
        _soundM->click();
        if (event.GUIEvent.EventType == gui::EGUI_EVENT_TYPE::EGET_FILE_SELECTED) {
            _guienv->removeFocus(event.GUIEvent.Caller);
            _gameS->savePath = ((gui::IGUIFileOpenDialog *)_gui[GUI::FILE])->getFileName();
            _device->getFileSystem()->changeWorkingDirectoryTo(_cd);
            return true;
        }
        _gui[GUI::FILE] = _guienv->addFileOpenDialog(L"Select a save in SAVE folder");
        _gui[GUI::FILE]->setVisible(false);
    }
    return false;
}