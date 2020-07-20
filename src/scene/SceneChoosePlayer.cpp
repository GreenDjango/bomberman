/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** SceneChoosePlayer
*/

#include "scene/SceneChoosePlayer.hpp"
#include "utils/ImageCreator.hpp"
#include <iostream>

using namespace irr;

void SceneChoosePlayer::init(IrrlichtDevice *device, GameStats *gameS, CameraManager *cameraM, SoundManager *soundM)
{
    _device = device;
    _guienv = device->getGUIEnvironment();
    _driver = device->getVideoDriver();
    _gameS = gameS;
    _cameraM = cameraM;
    _soundM = soundM;
    _showStatus = 0;
    _isVersus = false;
    _playerNb = 1;
    _mapSize = 3;
    updateMapDimension();
    _player1 = 1;
    _player2 = 1;

    for (int i = 1; i < 7; i++)
    {
        io::path path{"player"};
        path += io::path{i};
        path += "/player";
        path += io::path{i};
        path += "_all.x";
        scene::IAnimatedMesh *mesh{ _device->getSceneManager()->getMesh(path) };
        if (!mesh)
            throw std::runtime_error("[Graphics-C] - Can't load assets.");
        scene::IAnimatedMeshSceneNode *node = _device->getSceneManager()->addAnimatedMeshSceneNode(mesh);
        if (!node)
                throw std::runtime_error("[Graphics-C] - Can't allow memory for mesh.");
        node->setMaterialFlag(video::EMF_LIGHTING, false);
        node->setPosition(core::vector3df(46, 3, 4));
        node->setRotation(core::vector3df(-90, 90, 0));
        node->setAnimationSpeed(25);
        node->setFrameLoop(0, 199);
        node->setVisible(false);
        _playerModels.emplace(i, node);
    }

    _fonts[GUI::TITLE] = _guienv->getFont("assets/font/handel_gothic_56_b.xml");
    _fonts[GUI::TITLE]->setKerningWidth(3);
    _fonts[GUI::GAME_MOB] = _guienv->getFont("assets/font/handel_gothic_36_b.xml");
    _fonts[GUI::NAME] = _guienv->getFont("assets/font/handel_gothic_28.xml");
    _fonts[GUI::NAME]->setKerningWidth(2);
    gui::IGUIButton *button;
    gui::IGUIImage *image;

    // CHOOSE PLAYER ---
    // SOUND icon
    button = ImageCreator::newButton(_guienv, _driver->getTexture("./assets/gui/icons/effect.png"), {1650, 880, 1920, 1080});
    button->setPressedImage(_driver->getTexture("./assets/gui/icons/effect_mute.png"));
    button->setIsPushButton(true);
    button->setID(GUI::SOUND);
    _guiPlayer[GUI::SOUND] = button;
    _guiMap[GUI::SOUND] = button;
    // MUSIC icon
    button = ImageCreator::newButton(_guienv, _driver->getTexture("./assets/gui/icons/music.png"), {1780, 880, 1920, 1080});
    button->setPressedImage(_driver->getTexture("./assets/gui/icons/music_mute.png"));
    button->setIsPushButton(true);
    button->setID(GUI::MUSIC);
    _guiPlayer[GUI::MUSIC] = button;
    _guiMap[GUI::MUSIC] = button;
    // BG_NAV button
    image = ImageCreator::newImage(_guienv, _driver->getTexture("./assets/gui/tmp.png"), {695, 375}, {2.35f, 2.2f});
    _guiPlayer[GUI::BG_NAV] = image;
    core::recti clipping = image->getAbsoluteClippingRect();
    clipping.UpperLeftCorner.X += 8;
    clipping.LowerRightCorner.X -= 8;
    clipping.UpperLeftCorner.Y += 5;
    // PREVIOUS button
    button = ImageCreator::newButton(_guienv, _driver->getTexture("./assets/gui/arrow_left.png"), clipping, ImageCreator::TOP_LEFT, 1.5f);
    button->setPressedImage(_driver->getTexture("./assets/gui/arrow_left_press.png"));
    button->setID(GUI::PREVIOUS);
    _guiPlayer[GUI::PREVIOUS] = button;
    // NEXT button
    button = ImageCreator::newButton(_guienv, _driver->getTexture("./assets/gui/arrow_right.png"), clipping, ImageCreator::TOP_RIGHT, 1.5f);
    button->setPressedImage(_driver->getTexture("./assets/gui/arrow_right_press.png"));
    button->setID(GUI::NEXT);
    _guiPlayer[GUI::NEXT] = button;
    // BG_NAV2 button
    image = ImageCreator::newImage(_guienv, _driver->getTexture("./assets/gui/tmp.png"), {695+250, 375}, {2.4f, 2.2f});
    _guiPlayer[GUI::BG_NAV2] = image;
    core::recti clipping2 = image->getAbsoluteClippingRect();
    clipping2.UpperLeftCorner.X += 8;
    clipping2.LowerRightCorner.X -= 8;
    clipping2.UpperLeftCorner.Y += 5;
    // PREVIOUS2 button
    button = ImageCreator::newButton(_guienv, _driver->getTexture("./assets/gui/arrow_left.png"), clipping2, ImageCreator::TOP_LEFT, 1.5f);
    button->setPressedImage(_driver->getTexture("./assets/gui/arrow_left_press.png"));
    button->setID(GUI::PREVIOUS2);
    _guiPlayer[GUI::PREVIOUS2] = button;
    // NEXT2 button
    button = ImageCreator::newButton(_guienv, _driver->getTexture("./assets/gui/arrow_right.png"), clipping2, ImageCreator::TOP_RIGHT, 1.5f);
    button->setPressedImage(_driver->getTexture("./assets/gui/arrow_right_press.png"));
    button->setID(GUI::NEXT2);
    _guiPlayer[GUI::NEXT2] = button;
    // ADD_PLAYER
    button = ImageCreator::newButton(_guienv, _driver->getTexture("./assets/gui/buttonLong_brown.png"), {925, 445, 1180, 705}, ImageCreator::CENTER_CENTER, 1.4f);
    button->setPressedImage(_driver->getTexture("./assets/gui/buttonLong_brown_pressed.png"));
    button->setID(GUI::ADD_PLAYER);
    _guiPlayer[GUI::ADD_PLAYER] = button;
    // RM_PLAYER
    clipping2.UpperLeftCorner.Y -= 50;
    button = ImageCreator::newButton(_guienv, _driver->getTexture("./assets/gui/buttonRound_cross.png"), clipping2, ImageCreator::TOP_CENTER, 1.2f);
    button->setPressedImage(_driver->getTexture("./assets/gui/buttonRound_cross_press.png"));
    button->setID(GUI::RM_PLAYER);
    _guiPlayer[GUI::RM_PLAYER] = button;
    // GAME_MOB
    button = ImageCreator::newButton(_guienv, _driver->getTexture("./assets/gui/TextBTN.png"), {1250, 350, 1920, 650}, ImageCreator::TOP_CENTER, 0.8f);
    button->setPressedImage(_driver->getTexture("./assets/gui/TextBTN_Pressed.png"));
    button->setID(GUI::GAME_MOB);
    _guiPlayer[GUI::GAME_MOB] = button;
    // GAME_VS
    button = ImageCreator::newButton(_guienv, _driver->getTexture("./assets/gui/TextBTN.png"), {1250, 350, 1920, 650}, ImageCreator::BOTTOM_CENTER, 0.8f);
    button->setPressedImage(_driver->getTexture("./assets/gui/TextBTN_Pressed.png"));
    button->setID(GUI::GAME_VS);
    _guiPlayer[GUI::GAME_VS] = button;

    // CHOOSE MAP ---
    // MAP_GROUND button
    image = ImageCreator::newImage(_guienv, _driver->getTexture("./assets/gui/map_ground.jpg"), {850, 375});
    image->setColor(video::SColor(200, 255, 255, 255));
    _guiMap[GUI::MAP_GROUND] = image;
    // MAP_GROUND button
    image = ImageCreator::newImage(_guienv, _driver->getTexture("./assets/gui/map_pillar.jpg"), {800, 375});
    image->setColor(video::SColor(230, 255, 255, 255));
    _guiMap[GUI::MAP_PILLAR] = image;
    // BG_NAV button
    image = ImageCreator::newImage(_guienv, _driver->getTexture("./assets/gui/tmp.png"), {800, 220}, {2.8f, 2.3f});
    _guiMap[GUI::BG_NAV3] = image;
    clipping = image->getAbsoluteClippingRect();
    clipping.UpperLeftCorner.X += 8;
    clipping.LowerRightCorner.X -= 8;
    clipping.UpperLeftCorner.Y += 5;
    // PREVIOUS button
    button = ImageCreator::newButton(_guienv, _driver->getTexture("./assets/gui/arrow_left.png"), clipping, ImageCreator::TOP_LEFT, 1.5f);
    button->setPressedImage(_driver->getTexture("./assets/gui/arrow_left_press.png"));
    button->setID(GUI::PREVIOUS3);
    _guiMap[GUI::PREVIOUS3] = button;
    // NEXT button
    button = ImageCreator::newButton(_guienv, _driver->getTexture("./assets/gui/arrow_right.png"), clipping, ImageCreator::TOP_RIGHT, 1.5f);
    button->setPressedImage(_driver->getTexture("./assets/gui/arrow_right_press.png"));
    button->setID(GUI::NEXT3);
    _guiMap[GUI::NEXT3] = button;
    // PLAY button
    button = ImageCreator::newButton(_guienv, _driver->getTexture("./assets/gui/TextBTN.png"), {1250, 550, 1920, 1080}, ImageCreator::TOP_CENTER, 0.8f);
    button->setPressedImage(_driver->getTexture("./assets/gui/TextBTN_Pressed.png"));
    button->setID(GUI::PLAY);
    _guiMap[GUI::PLAY] = button;

    for (auto el : _guiPlayer)
        el.second->setVisible(false);
    for (auto el : _guiMap)
        el.second->setVisible(false);
}

void SceneChoosePlayer::start(u32 startTime)
{
    _startTime = startTime;
    _showStatus = 0;
    _isVersus = false;
    _playerNb = 1;
    _mapSize = 3;
    updateMapDimension();
    _player1 = 1;
    _player2 = 1;
    _cameraM->animation2();
    _guiPlayer[GUI::SOUND]->setVisible(true);
    _guiPlayer[GUI::MUSIC]->setVisible(true);
    ((gui::IGUIButton *)_guiPlayer[GUI::SOUND])->setPressed(_soundM->isMuteSound());
    ((gui::IGUIButton *)_guiPlayer[GUI::MUSIC])->setPressed(_soundM->isMuteTheme());
}

void SceneChoosePlayer::startMap()
{
    _showStatus = 0;
    _cameraM->animation3();
    for (auto el : _guiPlayer)
        el.second->setVisible(false);
    _guiMap[GUI::SOUND]->setVisible(true);
    _guiMap[GUI::MUSIC]->setVisible(true);
}

void SceneChoosePlayer::updateMapDimension() {
    _mapDim.X = (_mapSize * 4) + 1;
    _mapDim.Y = (_mapSize * 3) % 2 == 0 ? (_mapSize * 3) - 1 : (_mapSize * 3);
}

void SceneChoosePlayer::draw()
{
    if (_playerNb >= 1) {
        _playerModels[_player1]->setPosition(core::vector3df(46, 3, 6.6f));
        _playerModels[_player1]->setVisible(true);
        _playerModels[_player1]->OnRegisterSceneNode();
        _playerModels[_player1]->OnAnimate(_device->getTimer()->getTime());
        _playerModels[_player1]->render();
        _playerModels[_player1]->setVisible(false);
    }
    if (_playerNb >= 2) {
        _playerModels[_player2]->setPosition(core::vector3df(46, 3, 4));
        _playerModels[_player2]->setVisible(true);
        _playerModels[_player2]->OnRegisterSceneNode();
        _playerModels[_player2]->OnAnimate(_device->getTimer()->getTime());
        _playerModels[_player2]->render();
        _playerModels[_player2]->setVisible(false);
    }
    if (_showStatus == 1) {
        _guiPlayer[GUI::BG_NAV]->draw();
        _guiPlayer[GUI::PREVIOUS]->draw();
        _guiPlayer[GUI::NEXT]->draw();
        if (_playerNb <= 1)
            _guiPlayer[GUI::ADD_PLAYER]->draw();
        else
            _guiPlayer[GUI::RM_PLAYER]->draw();
        if (_playerNb >= 2) {
            _guiPlayer[GUI::BG_NAV2]->draw();
            _guiPlayer[GUI::PREVIOUS2]->draw();
            _guiPlayer[GUI::NEXT2]->draw();
        }
        _guiPlayer[GUI::GAME_MOB]->draw();
        _guiPlayer[GUI::GAME_VS]->draw();
        _fonts[GUI::TITLE]->draw(L"Choose your player", core::recti(0,0,1920,300) + core::vector2di(_fonts[GUI::TITLE]->getKerningWidth(), 0), video::SColor(230,255,255,255), true, true);
        _fonts[GUI::NAME]->draw(L"Player 1", _guiPlayer[GUI::BG_NAV]->getAbsoluteClippingRect() + core::vector2di(_fonts[GUI::NAME]->getKerningWidth(), 2), video::SColor(230,255,255,255), true, true);
        _fonts[GUI::GAME_MOB]->draw(L"Game Versus", _guiPlayer[GUI::GAME_VS]->getAbsoluteClippingRect(), video::SColor(230,255,255,255), true, true);
        _fonts[GUI::GAME_MOB]->draw(L"Game IA", _guiPlayer[GUI::GAME_MOB]->getAbsoluteClippingRect(), video::SColor(230,255,255,255), true, true);
        if (_playerNb >= 2)
            _fonts[GUI::NAME]->draw(L"Player 2", _guiPlayer[GUI::BG_NAV2]->getAbsoluteClippingRect() + core::vector2di(_fonts[GUI::NAME]->getKerningWidth(), 2), video::SColor(230,255,255,255), true, true);
        else
            _fonts[GUI::NAME]->draw(L"Add player", _guiPlayer[GUI::ADD_PLAYER]->getAbsoluteClippingRect(), video::SColor(240,255,255,255), true, true);
    }
    if (_showStatus == 2) {
        s32 ratio = 700/_mapDim.X;
        s32 offsetX = (1920/2) - (_mapDim.X*ratio) / 2;
        s32 offsetY = 400;
        for (s32 y = _mapDim.Y; y > 0; y--)
        {
            bool isPillar = true;
            for (s32 i = _mapDim.X; i > 0; i--)
            {
                if ((isPillar && y % 2 != 0) || y == _mapDim.Y || y == 1 || i == _mapDim.X || i == 1) {
                    _guiMap[GUI::MAP_PILLAR]->setRelativePosition({ratio*(i-1)+offsetX, ratio*(y-1)+offsetY, ratio*i+offsetX, ratio*y+offsetY});
                    _guiMap[GUI::MAP_PILLAR]->draw();
                } else {
                    _guiMap[GUI::MAP_GROUND]->setRelativePosition({ratio*(i-1)+offsetX, ratio*(y-1)+offsetY, ratio*i+offsetX, ratio*y+offsetY});
                    _guiMap[GUI::MAP_GROUND]->draw();
                }
                isPillar = !isPillar;
            }
        }
        _guiMap[GUI::BG_NAV3]->draw();
        _guiMap[GUI::PREVIOUS3]->draw();
        _guiMap[GUI::NEXT3]->draw();
        _guiMap[GUI::PLAY]->draw();
        io::path mapSize{_mapDim.X};
        mapSize += " x ";
        mapSize += io::path{_mapDim.Y};
        _fonts[GUI::NAME]->draw(mapSize, _guiMap[GUI::BG_NAV3]->getAbsoluteClippingRect() + core::vector2di(_fonts[GUI::NAME]->getKerningWidth(), 2), video::SColor(230,255,255,255), true, true);
        _fonts[GUI::TITLE]->draw(L"Choose your map", core::recti(0,0,1920,300) + core::vector2di(_fonts[GUI::TITLE]->getKerningWidth(), 0), video::SColor(230,255,255,255), true, true);
        _fonts[GUI::GAME_MOB]->draw(L"Play !", _guiMap[GUI::PLAY]->getAbsoluteClippingRect(), video::SColor(230,255,255,255), true, true);
    }
    _guiPlayer[GUI::SOUND]->draw();
    _guiPlayer[GUI::MUSIC]->draw();
}

void SceneChoosePlayer::clean()
{
    for (auto el : _guiPlayer)
        el.second->setVisible(false);
    for (auto el : _guiMap)
        el.second->setVisible(false);
}

bool SceneChoosePlayer::OnTimer(u32, SceneID&)
{
    if (!_showStatus && _cameraM->hasFinish() &&
        _cameraM->cameraStat() == CameraManager::PLAYER_CHOOSE) {
        _showStatus = 1;
        for (auto el : _guiPlayer)
            el.second->setVisible(true);
    }
    if (!_showStatus && _cameraM->hasFinish() &&
        _cameraM->cameraStat() == CameraManager::MAP_CHOOSE) {
        _showStatus = 2;
        for (auto el : _guiMap)
            el.second->setVisible(true);
    }
    return false;
}


bool SceneChoosePlayer::OnEvent(const SEvent& event, SceneID& sceneID)
{
    if (event.EventType == EEVENT_TYPE::EET_GUI_EVENT
        && event.GUIEvent.EventType == gui::EGUI_EVENT_TYPE::EGET_BUTTON_CLICKED
        && event.GUIEvent.Caller) {
        _soundM->click();
        if (event.GUIEvent.Caller->getID() == GUI::PLAY) {
            _guienv->removeFocus(event.GUIEvent.Caller);
            _gameS->nbPlayer = _playerNb;
            _gameS->size = _mapSize;
            _gameS->players[0].modelNum = _player1;
            _gameS->players[0].life = 3;
            _gameS->players[1].modelNum = _player2;
            _gameS->players[1].life = 3;
            if (_isVersus) {
                _gameS->isVersus = true;
                sceneID = SceneID::GAME_VS;
            } else {
                _gameS->isVersus = false;
                sceneID = SceneID::GAME_MOB;
            }
            clean();
            return true;
        }
        if (event.GUIEvent.Caller->getID() == GUI::SOUND)
            _soundM->toggleMuteSound();
        if (event.GUIEvent.Caller->getID() == GUI::MUSIC)
            _soundM->toggleMuteTheme();
        if (event.GUIEvent.Caller->getID() == GUI::GAME_MOB) {
            _isVersus = false;
            startMap();
        }
        if (event.GUIEvent.Caller->getID() == GUI::GAME_VS && _playerNb >= 2) {
            _isVersus = true;
            startMap();
        }
        if (event.GUIEvent.Caller->getID() == GUI::PREVIOUS)
            _player1 = _player1 - 1 <= 0 ? _playerModels.size() : _player1 - 1;
        if (event.GUIEvent.Caller->getID() == GUI::NEXT)
            _player1 = _player1 + 1 > _playerModels.size() ? 1 : _player1 + 1;
        if (event.GUIEvent.Caller->getID() == GUI::PREVIOUS3) {
            _mapSize -= _mapSize <= 3 ? 0 : 1;
            updateMapDimension();
        }
        if (event.GUIEvent.Caller->getID() == GUI::NEXT3) {
            _mapSize += _mapSize >= 11 ? 0 : 1;
            updateMapDimension();
        }
        if (event.GUIEvent.Caller->getID() == GUI::ADD_PLAYER && _playerNb <= 1)
            _playerNb++;
        if (event.GUIEvent.Caller->getID() == GUI::ADD_PLAYER && _playerNb <= 1)
            _playerNb++;
        if (_playerNb <= 1)
            return false;
        if (event.GUIEvent.Caller->getID() == GUI::RM_PLAYER)
            _playerNb--;
        if (event.GUIEvent.Caller->getID() == GUI::PREVIOUS2)
            _player2 = _player2 - 1 <= 0 ? _playerModels.size() : _player2 - 1;
        if (event.GUIEvent.Caller->getID() == GUI::NEXT2)
            _player2 = _player2 + 1 > _playerModels.size() ? 1 : _player2 + 1;
    }
    return false;
}