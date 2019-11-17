//
// Created by marcd on 25-1-2019.
//

#include "Character.hpp"

namespace tf {

Character::Character(tf::TopforceWindow &window, const sf::Uint32 &playerID):
    tf::MoveableScreenObject(window),
    playerID(playerID)
{
    mySprite.setTexture(imageManager.getTexture(tf::Animation::EnemyStationary));
    sf::FloatRect bounds = mySprite.getGlobalBounds();
    mySprite.setOrigin(bounds.width / 2, bounds.height / 2);
    hitbox.setSize({55.0f, 55.0f});
    hitbox.setFillColor(sf::Color(0,0,0,0));
#if DEBUG
    hitbox.setFillColor(sf::Color(255,0,0,100));
#endif
}

void Character::setTexture (const Animation anim){
    if(anim == Animation::EnemyWalking && mySprite.getTexture() != &imageManager.getTexture(Animation::EnemyWalking)){
        mySprite.setTexture(imageManager.getTexture(Animation::EnemyWalking), true);
    }
    if(anim == Animation::EnemyStationary && mySprite.getTexture() != &imageManager.getTexture(Animation::EnemyStationary)){
        mySprite.setTexture(imageManager.getTexture(Animation::EnemyStationary), true);
    }
}

void Character::update() {
}

void Character::draw() const {
    window.draw(mySprite);
#if DEBUG
    window.draw(hitbox);
#endif
}

sf::FloatRect Character::getBounds() {
    return hitbox.getGlobalBounds();
}

sf::Vector2f Character::getPosition() {
    return mySprite.getPosition();
}

sf::Vector2f Character::getWeaponPosition() {
    float rotation = mySprite.getRotation();
    sf::Vector2f weaponLocation = mySprite.getPosition();
    weaponLocation.x += cos((rotation + 212) * (PI / 180)) *- 20;
    weaponLocation.y += sin((rotation + 212) * (PI / 180)) *- 20;
    return weaponLocation;
}

void Character::setPosition(const sf::Vector2f &position) {
    mySprite.setPosition(position);
    hitbox.setPosition(mySprite.getPosition().x -25, mySprite.getPosition().y - 25);
}

float Character::getRotation() {
    return mySprite.getRotation();
}

void Character::setRotation(const float rotation) {
    mySprite.setRotation(rotation);
}


void Character::setShootLine(const sf::Vector2f & ownPos, const sf::Vector2f & firePos) {
    shootLine[0] = sf::Vertex(ownPos);
    shootLine[1] = sf::Vertex(firePos);
    shootLine->color = sf::Color::Yellow;
}

void Character::drawShootLine () const {
    window.draw(shootLine, 2, sf::Lines);
}

}
