/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** SceneChoosePlayer
*/

#ifndef SCENECHOOSEPLAYER_HPP_
#define SCENECHOOSEPLAYER_HPP_

#include "interface/IScene.hpp"
#include <map>

class SceneChoosePlayer : public IScene
{
public:
    SceneChoosePlayer() {};
    void init(irr::IrrlichtDevice *device,
        GameStats *gameS, CameraManager *cameraM, SoundManager *soundM);
    void start(irr::u32 startTime);
    void draw();
    void clean();
    bool OnTimer(irr::u32 startTime, SceneID&);
    bool OnEvent(const irr::SEvent &, SceneID&);
private:
    enum GUI {
        SOUND = 100,
        MUSIC,
        TITLE,
        ADD_PLAYER,
        RM_PLAYER,
        BG_NAV,
        BG_NAV2,
        BG_NAV3,
        NEXT,
        NEXT2,
        NEXT3,
        PREVIOUS,
        PREVIOUS2,
        PREVIOUS3,
        NAME,
        MAP_PILLAR,
        MAP_GROUND,
        GAME_MOB,
        GAME_VS,
        PLAY
    };
    void startMap();
    void updateMapDimension();
    irr::u32 _showStatus;
    irr::u32 _playerNb;
    irr::u32 _mapSize;
    irr::core::vector2di _mapDim;
    bool _isVersus;
    irr::u32 _player1;
    irr::u32 _player2;
    std::map<irr::u32, irr::scene::IAnimatedMeshSceneNode *> _playerModels;
    std::map<GUI, irr::gui::IGUIElement *> _guiPlayer;
    std::map<GUI, irr::gui::IGUIElement *> _guiMap;
    std::map<GUI, irr::gui::IGUIFont *> _fonts;
};

#endif /* !SCENECHOOSEPLAYER_HPP_ */
