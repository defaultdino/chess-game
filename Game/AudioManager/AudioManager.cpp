//
// Created by Adis Veletanlic on 11/8/23.
//

#include "AudioManager.h"

AudioManager::AudioManager() {
    auto loadedMoveBuffer = moveBuffer.loadFromFile("Assets/Audio/move-self.mp3");
    auto loadedCaptureBuffer = captureBuffer.loadFromFile("Assets/Audio/capture.mp3");
    auto loadedCastleBuffer = castleBuffer.loadFromFile("Assets/Audio/castle.mp3");
    auto loadedCheckmateBuffer = checkmateBuffer.loadFromFile("Assets/Audio/game-end.mp3");
    auto loadedCheckBuffer = checkBuffer.loadFromFile("Assets/Audio/move-check.mp3");
    auto loadedPromotionBuffer = promotionBuffer.loadFromFile("Assets/Audio/promote.mp3");

    moveSound.setBuffer(moveBuffer);
    captureSound.setBuffer(captureBuffer);
    castleSound.setBuffer(castleBuffer);
    checkmateSound.setBuffer(checkmateBuffer);
    checkSound.setBuffer(checkBuffer);
    promotionSound.setBuffer(promotionBuffer);
}

void AudioManager::PlayMoveSound() {
    moveSound.play();
}

void AudioManager::PlayCaptureSound() {
    captureSound.play();
}

void AudioManager::PlayCastleSound() {
    castleSound.play();
}

void AudioManager::PlayCheckmateSound() {
    checkmateSound.play();
}

void AudioManager::PlayCheckSound() {
    checkSound.play();
}

void AudioManager::PlayPromotionSound() {
    promotionSound.play();
}
