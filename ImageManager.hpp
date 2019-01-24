//
// Created by Nathan Hoekstra on 2019-01-23.
//

#ifndef TOPFORCE_IMAGEMANAGER_HPP
#define TOPFORCE_IMAGEMANAGER_HPP

#include <string>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/Texture.hpp>


namespace tf{
enum class Animation {
    Idle,
    Running
};

class ImageManager {
private:
    ImageManager();
    const std::string PATH =  "assets/images/";
    sf::Texture texture[3];
    sf::Image icon;
public:
    static ImageManager & getInstance();
    const sf::Texture& getMenuBackground();
    const sf::Texture& getSoldierStationary();
    const sf::Texture& getSoldierWalking();
    const sf::Uint8* getWindowIcon();
};
}


#endif //TOPFORCE_IMAGEMANAGER_HPP