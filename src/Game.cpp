/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** game
*/

#include "Game.hpp"
#include "entity/Player.hpp"
#include "entity/Room.hpp"
#include "class/Map.hpp"
#include "entity/Item.hpp"
#include <iostream>
#include <algorithm>
#include <array>
#include <exception>
#include "Pack.hpp"
#include "ECS.hpp"

using namespace irr;

Game::Game(char const *argv[]) {
    bool isWindowsDriver = false;
    for (int i = 0; argv[i] != NULL; i++)
    {
        if (!strcmp("-direct3D9", argv[i]))
            isWindowsDriver = true;
        else if (!strcmp("-openGL", argv[i]))
            isWindowsDriver = false;
        else if (!strcmp("-silent", argv[i])) {
            _soundM.toggleMuteSound();
            _soundM.toggleMuteTheme();
        }
    }
    if (isWindowsDriver)
        _device = createDeviceEx(Pack::windows10_deviceParameters());
    else
        _device = createDeviceEx(Pack::default_deviceParameters());
    if (!_device)
        throw std::runtime_error("[Game] - Can't allow memory for device.");
    _device->setEventReceiver(this);
    _driver = _device->getVideoDriver();
    _smgr = _device->getSceneManager();
    _guienv = _device->getGUIEnvironment();
    if (!_driver || !_smgr)
        throw std::runtime_error("[Game] - Bad driver/scene manager.");
    for (size_t i = 0; i < KEY_KEY_CODES_COUNT; i++)
        _keyIsDown[i] = false;
    _scene = IScene::IDLE;
    _started = false;
    memset(&_stats, 0, sizeof(_stats));
    _stats.savePath = nullptr;
    _smgr->addEmptySceneNode(nullptr, 21);
    _smgr->addEmptySceneNode(nullptr, 42);
}

void Game::loadObjects()
{
    _camera = _smgr->addCameraSceneNode(_smgr->getSceneNodeFromId(21),
        core::vector3df(52, 8, -15),
        core::vector3df(-11, 5, -15));
    _camera->bindTargetAndRotation(true);
    _cameraM.setCamera(_camera);
    _device->getFileSystem()->addFileArchive("assets/room.zip");
    _device->getFileSystem()->addFileArchive("assets/players.zip");

    _scenes[IScene::INTRO] = new SceneIntro();
    _scenes[IScene::INTRO]->init(_device, &_stats, &_cameraM, &_soundM);
    _scenes[IScene::MENU] = new SceneMenu();
    _scenes[IScene::MENU]->init(_device, &_stats, &_cameraM, &_soundM);
    _scenes[IScene::PLAYER_CHOOSE] = new SceneChoosePlayer();
    _scenes[IScene::PLAYER_CHOOSE]->init(_device, &_stats, &_cameraM, &_soundM);
    _scenes[IScene::GAME_MOB] = new SceneGameMob();
    _scenes[IScene::GAME_MOB]->init(_device, &_stats, &_cameraM, &_soundM);
    _scenes[IScene::GAME_VS] = new SceneGameVs();
    _scenes[IScene::GAME_VS]->init(_device, &_stats, &_cameraM, &_soundM);
    _entites.push_back(new Room{ _smgr });
}

// Mob spawn || map fichier, etage
void Game::start(int mobSpwan, irr::io::path save)
{
    _smgr->getSceneNodeFromId(42)->setScale(core::vector3df(1, 1, 1));
    // SAVE
    irr::io::IReadFile *file;
    if (!save.empty()) {
        file = _device->getFileSystem()->createAndOpenFile(save);
        if (!file)
            throw std::invalid_argument("bad file");
        saveBomberman *game = new saveBomberman();
        if (file->read(game, sizeof(saveBomberman)) != sizeof(saveBomberman))
            throw std::invalid_argument("bad file");
        if (game->magicNum != 42)
            throw std::invalid_argument("bad file");
        _stats.remainingTime = game->remain_time;
        for (u32 i = 0; i < game->nbPlayers; i++) {
            io::path path{"player"};
            path += io::path{game->player[i].model};
            path += "/player";
            path += io::path{game->player[i].model};
            path += "_all.x";
            _stats.players[i].modelNum = game->player[i].model;
            Player *p = new Player{path, _smgr, game->player[i].model};
            p->setMoveKey(Pack::default_playerKeys(i));
            p->applySave(game->player[i]);
            _players.push_back(p);
            _entites.push_back(p);
        }
        //stats
        for (std::size_t i = 0; i < _players.size(); i++) {
            _stats.players[i].life = _players[i]->getLife();
            _stats.players[i].capacityBomb = _players[i]->getBombCapacity();
            _stats.players[i].rangeBomb = _players[i]->getBombRange();
            _stats.players[i].wallPassTimer = _players[i]->getTimeRemain(Player::timeEvent::END_WALL_PASS);
            _stats.players[i].speedTimer = _players[i]->getTimeRemain(Player::timeEvent::END_SPEED);
        }
        _stats.isVersus = game->isVersus;
        irr::u32 ssize = (game->mapSize.X - 1) / 4;
        _stats.size = ssize;
        _stats.nbPlayer = game->nbPlayers;
        _smgr->getSceneNodeFromId(21)->setScale(core::vector3df(ssize * 0.22f));
        _map = new Map{ game->mapSize, _smgr, _driver };
        _map->load(game);
        _map->appendEntities(_entites);
        _map->setInteraction(_players, _smgr);
        _stats.nbMob = _map->getNbMob();
        _stats.isFinish = false;

        delete game;
        file->drop();
        return;
    }
    // no save (map 4/3 format)
    _smgr->getSceneNodeFromId(21)->setScale(core::vector3df(_stats.size * 0.22f));
    u32 width = (_stats.size * 4) + 1;
    u32 height = (_stats.size * 3) % 2 == 0 ? (_stats.size * 3) - 1 : (_stats.size * 3);
    _map = new Map{ {width, height}, _smgr, _driver };
    for (std::size_t i = 0; i < _stats.nbPlayer && i < 4; i++) {
        io::path path{"player"};
        path += io::path{_stats.players[i].modelNum};
        path += "/player";
        path += io::path{_stats.players[i].modelNum};
        path += "_all.x";
        Player *p = new Player{path, _smgr, _stats.players[i].modelNum};
        p->setSpawn(_map->getPosCorner(i));
        p->setMoveKey(Pack::default_playerKeys(i));
        _players.push_back(p);
        _entites.push_back(p);
    }
    _map->generateMob(_smgr, mobSpwan);
    _map->appendEntities(_entites);
    _map->setInteraction(_players, _smgr);
    _stats.nbMob = _map->getNbMob();
    _stats.remainingTime = 90000 + ((_stats.size - 3) * 30000);
    _stats.isFinish = false;
}

#include <iostream>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <ctime>
#include "save.hpp"

void Game::end(bool save)
{
    _smgr->getSceneNodeFromId(21)->setScale(core::vector3df(1));
    if (save && _started == true) {
        auto t = std::time(nullptr);
        auto tm = *std::localtime(&t);
        std::ostringstream oss;
        oss << std::put_time(&tm, "save/save-%Y-%m-%d_%H.%M.%S.bomber");
        irr::io::IWriteFile *file = _device->getFileSystem()->createAndWriteFile(oss.str().c_str(), false);
        if (file) {
            saveBomberman *bomberman = new saveBomberman();
            memset((void *)bomberman, 0, sizeof(saveBomberman));
            bomberman->magicNum = 42;
            bomberman->isVersus = _stats.isVersus;
            bomberman->remain_time = _stats.remainingTime;
            // Players
            bomberman->nbPlayers = _players.size();
            for (std::size_t i = 0; i < _players.size() && i < 4; i++ )
                bomberman->player[i] = _players[i]->getSave();
            // Map
            _map->save(bomberman);

            file->write(bomberman, sizeof(saveBomberman));
            file->drop();
            delete bomberman;
        }
    }
    if (_started == true) {
        // [free]
        for (auto it = _entites.begin(); it != _entites.end(); ) {
            if ((*it)->getType() == IEntity::EType::PLAYER) {
                Player *p = (Player *)((*it)->getObj());
                p->drop();
            }
            else if ((*it)->getType() == IEntity::EType::BOMB) {
                Bomb *p = (Bomb *)((*it)->getObj());
                p->drop();
            }
            delete (*it);
            it = _entites.erase(it);
        }
        delete _map;
        _started = false;
    }
}

void Game::ecsCore(const f32 delta)
{

    for (auto it = _entites.begin(); it != _entites.end(); ) {
        if (!(*it)->IEntity::isAlive()) {
            if ((*it)->IEntity::needFree())
                delete (*it);
            it = _entites.erase(it);
        }
        else
            it++;
    }
    for (std::size_t i = 0; i < _entites.size(); i++) {
        ECS::actionSystem(_entites[i], this);
        ECS::interactionSystem(_entites[i], _entites);
        ECS::eventSystem(_entites[i], delta);
        ECS::renderSystem(_entites[i], delta);
    }
}

void Game::run()
{
    _scene = IScene::INTRO;
    _scenes[_scene]->start(_device->getTimer()->getTime());
    ecsCore(0);
    u32 then = _device->getTimer()->getTime();
    while (_device->run())
    {
        if (isPaused(then))
            continue;
        const u32 now = _device->getTimer()->getTime();
        const f32 frameDeltaTime = (f32)(now - then) / 1000.f;
        if (!limitFPS((f32)(now - then), 60.0))
            continue;
        then = now;
        if (_scene != IScene::IDLE && _scenes[_scene]->OnTimer(now, _scene))
            _scenes[_scene]->start(_device->getTimer()->getTime());
        if (_scene == IScene::GAME_MOB || _scene == IScene::GAME_VS) {
            _map->mobIA(_players);
            ecsCore(frameDeltaTime);
            _stats.nbMob = _map->getNbMob();
            _stats.remainingTime -= _stats.remainingTime <= frameDeltaTime * 1000 ? _stats.remainingTime : frameDeltaTime * 1000;
            for (std::size_t i = 0; i < _players.size(); i++) {
                _stats.players[i].life = _players[i]->getLife();
                _stats.players[i].capacityBomb = _players[i]->getBombCapacity();
                _stats.players[i].rangeBomb = _players[i]->getBombRange();
                _stats.players[i].wallPassTimer = _players[i]->getTimeRemain(Player::timeEvent::END_WALL_PASS);
                _stats.players[i].speedTimer = _players[i]->getTimeRemain(Player::timeEvent::END_SPEED);
                _stats.players[i].maxBomb = _players[i]->getMaxBombCapacity();
            }
        }
        _driver->beginScene(true, true, video::SColor(0,57,149,195));
        _smgr->drawAll();
        if (_scene != IScene::IDLE)
            _scenes[_scene]->draw();
        _driver->endScene();
        fpsIndicatorRefresh();
    }
    end(!_stats.isFinish);
    for (auto el : _scenes)
        delete el.second;
    _device->drop();
}

bool Game::OnEvent(const irr::SEvent& event)
{
    if (_scene != IScene::IDLE && _scenes[_scene]->OnEvent(event, _scene)) {
        if (_started) {
            end(false);
            _camera->setPosition(core::vector3df(34.7f, 9, 10));
            _camera->setTarget(core::vector3df(34.7f, 9, 27));
        } else if (_scene == IScene::GAME_MOB || _scene == IScene::GAME_VS) {
            _started = true;
            if (_scene == IScene::GAME_MOB)
                start(10);
            else
                start(0);
        } else if (_stats.savePath != nullptr) {
            start(0, _stats.savePath);
            _scenes[_scene]->clean();
            if (_stats.isVersus)
                _scene = IScene::GAME_VS;
            else 
                _scene = IScene::GAME_MOB;
            _started = true;
            _stats.savePath = nullptr;
        }
        _scenes[_scene]->start(_device->getTimer()->getTime());
    }
    if (_scene != IScene::GAME_MOB && _scene != IScene::GAME_VS)
        return false;
    if (event.EventType == EET_KEY_INPUT_EVENT) {
        bool change_state = _keyIsDown[event.KeyInput.Key] != event.KeyInput.PressedDown;
        _keyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;
        if (change_state)
            for (auto *e : _entites) {
                auto i = (InputEventComponent *)e->getComponent(IEntityComponent::Component::InputEvent);
                if (i)
                    i->keyReceived(event.KeyInput.Key, _keyIsDown[event.KeyInput.Key], _keyIsDown);
            }
    }
    return false;
}

bool Game::isPaused(u32 &then)
{
    static bool pause = false;

    if (!_device->isWindowActive() && !_device->getTimer()->isStopped()) {
        if (!pause) {
            pause = true;
            _device->getTimer()->stop();
            _driver->beginScene(true, true, video::SColor(0,57,149,195));
            _smgr->drawAll();
            _driver->draw2DRectangle(video::SColor(125, 0, 0, 0), core::rect<s32>(0,0,1920,1080));
            gui::IGUIFont *font = _guienv->getFont("assets/font/handel_gothic_56_b.xml");
            font->draw(L"PAUSE", core::recti(0,0,1920,1080), video::SColor(220,255,255,255), true, true);
            _driver->endScene();
        }
        _device->yield();
        then = _device->getTimer()->getTime();
        return true;
    }
    if (pause) {
        pause = false;
        _device->getTimer()->start();
    }
    return false;
}

bool Game::limitFPS(u32 now, const float wanted)
{
    static u32 current = 0;
    current += now;
    if (now > (1000.0 / wanted)) {
        current = 0;
        return true;
    }
    _device->sleep(1);
    return false;
}

void Game::fpsIndicatorRefresh() const
{
    static int lastFPS = -1;
    int fps = _driver->getFPS();

    if (lastFPS != fps)
    {
        core::stringw tmp(L"Bomberman [");
        tmp += _driver->getName();
        tmp += L"] fps: ";
        tmp += fps;
        _device->setWindowCaption(tmp.c_str());
        lastFPS = fps;
    }
}

void Game::setScene(IScene::SceneID newScene)
{
    _scene = newScene;
}