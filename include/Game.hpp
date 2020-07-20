/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** game
*/

#ifndef GAME_HPP_
#define GAME_HPP_

#include "GameStats.hpp"
#include "interface/IEntityComponent.hpp"
#include "entity/Bomb.hpp"
#include "class/SoundManager.hpp"
#include "class/CameraManager.hpp"
#include "scene/SceneIntro.hpp"
#include "scene/SceneMenu.hpp"
#include "scene/SceneChoosePlayer.hpp"
#include "scene/SceneGameMob.hpp"
#include "scene/SceneGameVs.hpp"
#include "entity/Player.hpp"
#include "entity/Room.hpp"
#include "class/Map.hpp"
#include <irrlicht/irrlicht.h>
#include <vector>

class Game : public irr::IEventReceiver
{
private:
    GameStats _stats;
    irr::IrrlichtDevice *_device;
    irr::video::IVideoDriver* _driver;
    irr::scene::ISceneManager* _smgr;
    irr::gui::IGUIEnvironment* _guienv;
    irr::scene::ICameraSceneNode *_camera;
    CameraManager _cameraM;
    SoundManager _soundM;
    std::vector<Bomb *> _bombs;
    std::vector<Player *> _players;
    std::vector<IEntityComponent *> _entites;
    Map *_map;
    IScene::SceneID _scene;
    std::map<IScene::SceneID, IScene *> _scenes;
    Room *_room;
    bool _started;
    bool OnEvent(const irr::SEvent& event);
    bool _keyIsDown[irr::KEY_KEY_CODES_COUNT];
    void setScene(IScene::SceneID newScene);
public:
    Game(char const *argv[]);
    ~Game() { };
    void run();
    void loadObjects();
    void ecsCore(const irr::f32 delta);
    bool isPaused(irr::u32 &then);
    /* Getter */
    const irr::IrrlichtDevice *getter_device() const { return _device; };
    const irr::video::IVideoDriver *getter_driver() const { return _driver; };
    const irr::scene::ISceneManager *getter_sceneManage() const { return _smgr; };
    //tmp
    std::vector<IEntityComponent *> &getEntites() { return _entites; };
    std::vector<Bomb *> &getBombs() { return _bombs; };
    irr::u32 getDeviceTime() const { return _device->getTimer()->getTime(); };
    std::vector<Player *> &getPlayers() { return _players; }
    CameraManager &getCameraManager() { return _cameraM; };
    irr::scene::ICameraSceneNode *getCamera() { return _camera; };
    SoundManager &getSounManager() { return _soundM; };
    Map *getMap() { return _map; };
    void fpsIndicatorRefresh() const;
    bool limitFPS(irr::u32 now, const float wanted);
    void start(int mobSpwanPercent, irr::io::path save = "");
    void end(bool save = true);
};

#endif /* !GAME_HPP_ */