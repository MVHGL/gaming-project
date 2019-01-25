//
// Created by Nathan Hoekstra on 2019-01-21.
//

#include "FreeForAll.hpp"

namespace tf{ namespace gamemode{
FreeForAll::FreeForAll(tf::TopforceWindow & window, const std::string & mapName, sf::IpAddress & serverIp):
    GameMode(window, mapName),
    client(53000, serverIp, 53000),
    sendThread(&FreeForAll::send, this)
{
    ownPlayer.setHitboxes(level.getHitboxes());
    view.setSize(1920.f, 1080.f);
    sendThread.detach();
}
FreeForAll::~FreeForAll() {}

bool FreeForAll::playerExists() {
    for (const auto& enemy : enemies) {
        if (enemy.playerID == serverPacket.PlayerId) {
            return true;
        }
    }
    return false;
}

void FreeForAll::setEnemyParams() {
    for (auto& enemy : enemies) {
        if (enemy.playerID == serverPacket.PlayerId) {
            enemy.setPosition(serverPacket.position);
            enemy.setRotation(serverPacket.rotation);
            return;
        }
    }
}

void FreeForAll::run() {
    packet.PlayerId = ownPlayer.playerID;
    packet.playerName = sf::IpAddress::getLocalAddress().toString();

    // ---- Free-For-All gameloop ----
    while (window.isOpen()) {
        // Recieve Server packets
        serverPacket = client.getLastPacket();

        if (!playerExists()) {
            enemies.push_back(Character(window, view, serverPacket.PlayerId));
        }
        // set position, rotation, shooting ... etc
        setEnemyParams();

        window.clear(sf::Color::Black);
        window.setView(view);

        //Cursor position calculation
        window.setSpritePosition();

        // Draw objects
        level.draw();
        ownPlayer.update();
        ownPlayer.draw();
        for (const auto& enemy : enemies) {
            enemy.draw();
        }

        ownPlayer.setTime(client.getTime());
        window.draw(window.getCursorSprite());
        window.display();

        // Handle pollEvents
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
    }
}

void FreeForAll::send(){
    while(true) {
        packet.rotation = ownPlayer.getRotation();
        packet.position = ownPlayer.getPosition();
        client.send(packet);
        sf::sleep(sf::milliseconds(5));
    }
}
}}