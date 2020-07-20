/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** SceneMenu
*/

#ifndef SCENEMENU_HPP_
#define SCENEMENU_HPP_

#include "interface/IScene.hpp"
#include <map>

class SceneMenu : public IScene
{
public:
    SceneMenu() {};
    void init(irr::IrrlichtDevice *device,
        GameStats *gameS, CameraManager *cameraM, SoundManager *soundM);
    void start(irr::u32 startTime);
    void draw();
    void clean();
    bool OnTimer(irr::u32 startTime, SceneID&);
    bool OnEvent(const irr::SEvent &, SceneID&);
private:
    enum GUI {
        SOUND = 50,
        MUSIC,
        PLAY,
        LOAD,
        EXIT,
        CREDITS,
        BACK,
        FILE
    };
    void toggleCredits(bool);
    irr::io::path _cd;
    bool _isCredits;
    std::map<GUI, irr::gui::IGUIElement *> _gui;
    std::map<GUI, irr::gui::IGUIFont *> _fonts;
};

#endif /* !SCENEMENU_HPP_ */
