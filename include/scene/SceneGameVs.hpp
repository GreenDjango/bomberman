/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** SceneGameVs
*/

#ifndef SCENEGAMEVS_HPP_
#define SCENEGAMEVS_HPP_

#include "interface/IScene.hpp"
#include <map>

class SceneGameVs : public IScene
{
public:
    SceneGameVs() {};
    void init(irr::IrrlichtDevice *device,
        GameStats *gameS, CameraManager *cameraM, SoundManager *soundM);
    void start(irr::u32 startTime);
    void draw();
    void clean();
    bool OnTimer(irr::u32 startTime, SceneID&);
    bool OnEvent(const irr::SEvent &, SceneID&);
private:
    enum GUI {
        SOUND = 150,
        MUSIC,
        PERSPEC,
        HELP_BTN,
        HELP_PNL,
        SAVE,
        PLAYER1,
        PLAYER2,
        END_PNL,
        STATS,
        TIME
    };
    bool _showHelp;
    bool _isEnd;
    irr::u32 _winnerId;
    std::map<GUI, irr::gui::IGUIElement *> _gui;
    std::map<GUI, irr::gui::IGUIFont *> _fonts;
};

#endif /* !SCENEGAMEVS_HPP_ */
