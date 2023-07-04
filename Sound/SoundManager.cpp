#include "SoundManager.h"

SoundManager::SoundManager() {
    loadSounds();
}

void SoundManager::loadSounds() {

    if(!castBuffer.loadFromFile("../Sound/spell.wav")){
        std::cout << "failed to load a sound" << "\n";
    }
    if(!attackBuffer.loadFromFile("../Sound/attack.wav")){
        std::cout << "failed to load a sound" << "\n";
    }
    if(!hitBuffer.loadFromFile("../Sound/Damage.wav")){
        std::cout << "failed to load a sound" << "\n";
    }
    if(!killBuffer.loadFromFile("../Sound/dead.wav")){
        std::cout << "failed to load a sound" << "\n";
    }
    if(!nextLevelBuffer.loadFromFile("../Sound/next_level.wav")){
        std::cout << "failed to load a sound" << "\n";
    }
    if(!projectileBuffer.loadFromFile("../Sound/Projectile.wav")){
        std::cout << "failed to load a sound" << "\n";
    }
    if(!enemyHitBuffer.loadFromFile("../Sound/enemyHit.wav")){
        std::cout << "failed to load a sound" << "\n";
    }

}

void SoundManager::playAttackSound() {
    attackSound.setBuffer(attackBuffer);
    attackSound.play();
}

void SoundManager::playKillSound() {
    killSound.setBuffer(killBuffer);
    killSound.play();
}

void SoundManager::playCastSound() {
    castSound.setBuffer(castBuffer);
    castSound.play();
}

void SoundManager::playNextLvlSound() {
    nextLvlSound.setBuffer(nextLevelBuffer);
    nextLvlSound.play();
}

void SoundManager::playHitSound() {
    hitSound.setBuffer(hitBuffer);
    hitSound.play();
}

void SoundManager::playProjectileSound() {
    projectileSound.setBuffer(projectileBuffer);
    projectileSound.play();
}

void SoundManager::playEnemyHitSound() {
    enemyHitSound.setBuffer(enemyHitBuffer);
    enemyHitSound.play();
}

