/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** SceneIntro
*/

#ifndef SCENEINTRO_HPP_
#define SCENEINTRO_HPP_

#include "interface/IScene.hpp"
#include <map>

class SceneIntro : public IScene
{
public:
    SceneIntro() {};
    void init(irr::IrrlichtDevice *device,
        GameStats *gameS, CameraManager *cameraM, SoundManager *soundM);
    void start(irr::u32 startTime);
    void draw();
    void clean();
    bool OnTimer(irr::u32 startTime, SceneID&);
    bool OnEvent(const irr::SEvent &, SceneID &);
private:
    enum GUI {
        SKIP = 0
    };
    std::map<GUI, irr::gui::IGUIElement *> _gui;
    std::map<GUI, irr::gui::IGUIFont *> _fonts;
};

#endif /* !SCENEINTRO_HPP_ */
