//
// Created by marcd on 21-1-2019.
//

#include "GameMode.hpp"

namespace tf {
GameMode::GameMode(tf::TopforceWindow &window, const std::string &mapName, sf::IpAddress & serverIp):
    window(window),
    level(mapName, window),
    client(serverIp),
    ownPlayer(window, sf::IpAddress::getLocalAddress().toInteger(), view, level.getHitboxes(), enemies, packet)
{
    view.setSize(1920.f, 1080.f);
}

GameMode::~GameMode() {

}

bool GameMode::playerExists(const tf::PlayerPacket & packet) {
    for (const auto& enemy : enemies) {
        if (enemy.playerID == packet.PlayerId) {
            return true;
        }
    }
    return false;
}

void GameMode::setEnemyParams(tf::PlayerPacket & packet) {
    for (auto& enemy : enemies) {
        if (enemy.playerID == packet.PlayerId) {
            enemy.setPosition(packet.position);
            enemy.setRotation(packet.rotation);
            enemy.firePos = packet.firePos;
            return;
        }
    }
}
void GameMode::sendDamage() {
    sf::Uint32 enemyID = ownPlayer.getEnemyID();
    if(enemyID > 0){
        damagePacket.playerId = enemyID;
        client.send(damagePacket);
    }
}
}