/*
** EPITECH PROJECT, 2020
** OOP_indie_studio_2019
** File description:
** SoundManager
*/

#include "class/SoundManager.hpp"

SoundManager::SoundManager()
{
    _muteTheme = false;
    _muteSound = false;
    _actualTheme = Theme::MENU;
    _themes.emplace(Theme::MENU, new sf::Music());
    _themes[Theme::MENU]->openFromFile("assets/sound/11_zip.ogg");
    _themes.emplace(Theme::GAME, new sf::Music());
    _themes[Theme::GAME]->openFromFile("assets/sound/03_redial.ogg");
    _clickSB.loadFromFile("assets/sound/Click.ogg");
    _explosionSB.loadFromFile("assets/sound/grenade.ogg");
    _debrisSB.loadFromFile("assets/sound/Debris4.ogg");
    _audience_cheerSB.loadFromFile("assets/sound/se_audience_cheer_s.wav");
    _audience_clapSB.loadFromFile("assets/sound/se_audience_clap_m.wav");
    _audience_disappointSB.loadFromFile("assets/sound/se_audience_disappoint.wav");
    _audience_stirSB.loadFromFile("assets/sound/se_audience_stir_m.wav");
    _takeObjSB.loadFromFile("assets/sound/Bubble3.ogg");
    _takeLifeSB.loadFromFile("assets/sound/se_common_lifeup.wav");
    _deathSB.loadFromFile("assets/sound/se_common_finishhit.wav");
    _fallSB.loadFromFile("assets/sound/se_common_stage_fall.wav");
    _winSB.loadFromFile("assets/sound/01_complete.ogg");
    _click.setBuffer(_clickSB);
    _explosion.setBuffer(_explosionSB);
    _debris.setBuffer(_debrisSB);
    _audience_cheer.setBuffer(_audience_cheerSB);
    _audience_clap.setBuffer(_audience_clapSB);
    _audience_disappoint.setBuffer(_audience_disappointSB);
    _audience_stir.setBuffer(_audience_stirSB);
    _takeObj.setBuffer(_takeObjSB);
    _takeLife.setBuffer(_takeLifeSB);
    _death.setBuffer(_deathSB);
    _fall.setBuffer(_fallSB);
    _win.setBuffer(_winSB);
    _themes[Theme::MENU]->setLoop(true);
    _themes[Theme::GAME]->setLoop(true);
    _themes[Theme::MENU]->setVolume(40);
    _themes[Theme::GAME]->setVolume(40);
    _debris.setVolume(80);
    _audience_cheer.setVolume(50);
    _audience_clap.setVolume(50);
    _audience_disappoint.setVolume(50);
    _audience_stir.setVolume(50);
    _takeLife.setVolume(50);
    _death.setVolume(40);
    _explosion.setVolume(50);
}

SoundManager::~SoundManager()
{
    for (auto el : _themes) {
        el.second->stop();
        delete el.second;
    }
};

void SoundManager::toggleMuteTheme()
{
    _muteTheme = !_muteTheme;
    if (_muteTheme) {
        stopTheme();
    } else {
        playTheme(_actualTheme);
    }
}

void SoundManager::toggleMuteSound()
{
    _muteSound = !_muteSound;
}

void SoundManager::playTheme(Theme theme)
{
    Theme last = _actualTheme;
    _actualTheme = theme;
    if (last != _actualTheme && _themes[last]->getStatus() == sf::Music::Playing)
        _themes[last]->stop();
    if (_themes[_actualTheme]->getStatus() == sf::Music::Playing || _muteTheme)
        return;
    _themes[_actualTheme]->play();
}

void SoundManager::stopTheme()
{
    _themes[_actualTheme]->stop();
}

void SoundManager::click()
{
    if (_muteSound)
        return;
    _click.play();
}

void SoundManager::explose()
{
    if (_muteSound)
        return;
    _debris.setPitch((std::rand()/(double)RAND_MAX ) * (1.6f-0.6f) + 0.6f);
    _debris.play();
    _explosion.setPitch((std::rand()/(double)RAND_MAX ) * (1.6f-0.6f) + 0.6f);
    _explosion.play();
}

void SoundManager::audienceCheer()
{
    if (_muteSound)
        return;
    _audience_cheer.play();
}

void SoundManager::audienceClap()
{
    if (_muteSound)
        return;
    _audience_clap.play();
}

void SoundManager::audienceDisappoint()
{
    if (_muteSound)
        return;
    _audience_disappoint.play();
}

void SoundManager::audienceStir()
{
    if (_muteSound)
        return;
    _audience_stir.play();
}

void SoundManager::takeObj()
{
    if (_muteSound)
        return;
    _takeObj.play();
}

void SoundManager::takeLife()
{
    if (_muteSound)
        return;
    _takeLife.play();
}

void SoundManager::death()
{
    if (_muteSound)
        return;
    _death.play();
    _fall.play();
}

void SoundManager::win()
{
    if (_muteSound)
        return;
    _win.play();
}