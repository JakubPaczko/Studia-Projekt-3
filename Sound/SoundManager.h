#ifndef ROGALIK_SOUNDMANAGER_H
#define ROGALIK_SOUNDMANAGER_H

#include <iostream>
#include <SFML/Audio.hpp>

class SoundManager {
    sf::SoundBuffer attackBuffer;
    sf::Sound attackSound;
    sf::SoundBuffer killBuffer;
    sf::Sound killSound;
    sf::SoundBuffer castBuffer;
    sf::Sound castSound;
    sf::SoundBuffer nextLevelBuffer;
    sf::Sound nextLvlSound;
    sf::SoundBuffer enemyHitBuffer;
    sf::Sound enemyHitSound;
    sf::SoundBuffer hitBuffer;
    sf::Sound hitSound;
    sf::SoundBuffer projectileBuffer;
    sf::Sound projectileSound;

    void loadSounds();

public:
    SoundManager();

    void playAttackSound();
    void playKillSound();
    void playCastSound();
    void playNextLvlSound();
    void playHitSound();
    void playEnemyHitSound();
    void playProjectileSound();

};


#endif //ROGALIK_SOUNDMANAGER_H
