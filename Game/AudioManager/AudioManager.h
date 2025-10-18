//
// Created by Adis Veletanlic on 11/8/23.
//

#ifndef CHESSGAME_AUDIOMANAGER_H
#define CHESSGAME_AUDIOMANAGER_H
#pragma once
#include <SFML/Audio.hpp>

class AudioManager {
public:
    AudioManager();

    void PlayMoveSound();

    void PlayCastleSound();

    void PlayCheckmateSound();

    void PlayCheckSound();

    void PlayPromotionSound();

    void PlayCaptureSound();

private:
    sf::SoundBuffer captureBuffer{};
    sf::SoundBuffer castleBuffer{};
    sf::SoundBuffer checkmateBuffer{};
    sf::SoundBuffer moveBuffer{};
    sf::SoundBuffer checkBuffer{};
    sf::SoundBuffer promotionBuffer{};

    sf::Sound moveSound{moveBuffer};
    sf::Sound captureSound{captureBuffer};
    sf::Sound castleSound{castleBuffer};
    sf::Sound checkmateSound{checkmateBuffer};
    sf::Sound checkSound{checkBuffer};
    sf::Sound promotionSound{promotionBuffer};
};


#endif //CHESSGAME_AUDIOMANAGER_H
