/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** SoundManager
*/

#ifndef SOUNDMANAGER_HPP_
#define SOUNDMANAGER_HPP_

#include <SFML/Audio.hpp>
#include <iostream>
#include <map>

class SoundManager
{
public:
    enum Theme {
        MENU,
        GAME
    };
    SoundManager();
    ~SoundManager();
    bool isMuteTheme() {return _muteTheme;};
    bool isMuteSound() {return _muteSound;};
    void toggleMuteTheme();
    void toggleMuteSound();
    void playTheme(Theme theme);
    void stopTheme();
    void click();
    void win();
    void death();
    void explose();
    void audienceCheer();
    void audienceClap();
    void audienceDisappoint();
    void audienceStir();
    void takeObj();
    void takeLife();
private:
    bool _muteTheme;
    bool _muteSound;
    Theme _actualTheme;
    std::map<Theme, sf::Music *> _themes;
    sf::Sound _click;
    sf::Sound _explosion;
    sf::Sound _debris;
    sf::Sound _audience_cheer;
    sf::Sound _audience_clap;
    sf::Sound _audience_disappoint;
    sf::Sound _audience_stir;
    sf::Sound _takeObj;
    sf::Sound _takeLife;
    sf::Sound _death;
    sf::Sound _fall;
    sf::Sound _win;
    sf::SoundBuffer _clickSB;
    sf::SoundBuffer _explosionSB;
    sf::SoundBuffer _debrisSB;
    sf::SoundBuffer _audience_cheerSB;
    sf::SoundBuffer _audience_clapSB;
    sf::SoundBuffer _audience_disappointSB;
    sf::SoundBuffer _audience_stirSB;
    sf::SoundBuffer _takeObjSB;
    sf::SoundBuffer _takeLifeSB;
    sf::SoundBuffer _deathSB;
    sf::SoundBuffer _fallSB;
    sf::SoundBuffer _winSB;
};

#endif /* !SOUNDMANAGER_HPP_ */
