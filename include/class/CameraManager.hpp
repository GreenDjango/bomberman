/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** CameraManager
*/

#ifndef CAMERAMANAGER_HPP_
#define CAMERAMANAGER_HPP_

#include "class/CSceneNodeAnimatorCameraMove.hpp"

class CameraManager
{
public:
    enum cameraStatus {
        IDLE,
        INTRO,
        CREDITS,
        PLAYER_CHOOSE,
        MAP_CHOOSE,
        GAME,
        SHAKE
    };
    CameraManager(irr::scene::ICameraSceneNode *camera = nullptr);
    ~CameraManager() {};
    void setCamera(irr::scene::ICameraSceneNode *camera);
    bool hasFinish() {return _hasFinish;};
    cameraStatus cameraStat() {return _camStatus;};
    void toggleProjection();
    void setOrthogonal();
    void setPerspective();
    void stop();
    void animation1(irr::scene::IMeshSceneNode* focusPrewiew = nullptr);
    void animation2(irr::scene::IMeshSceneNode* focusPrewiew = nullptr);
    void animation3(irr::scene::IMeshSceneNode* focusPrewiew = nullptr);
    void animation4(irr::f32 factor, irr::scene::IMeshSceneNode* focusPrewiew = nullptr);
    void animation5(irr::scene::IMeshSceneNode* focusPrewiew = nullptr);
    void animation6(irr::scene::IMeshSceneNode* focusPrewiew = nullptr);
    void shake();
private:
    irr::f32 _factor;
    irr::core::vector3df _finalPos;
    irr::core::vector3df _finalTarget;
    bool _isPerspective;
    irr::core::matrix4 _projectionMatrix;
    bool _hasFinish;
    irr::scene::ICameraSceneNode *_camera;
    cameraStatus _camStatus;
};

#endif /* !CAMERAMANAGER_HPP_ */
