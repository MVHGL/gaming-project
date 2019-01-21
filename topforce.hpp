//
// Topforce main headers file
//

#ifndef TOPFORCE_HEADERS_HPP
#define TOPFORCE_HEADERS_HPP

// Standard library includes
#include <iostream>
#include <algorithm>
#include <functional>
#include <cstdint>
#include <memory>

#include <string>
#include <sstream>
#include <vector>

// SFML includes
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
//#include <SFML/Time.hpp>

// Logger include
#include "Log.hpp"

// Global enum classes
namespace tf {
    enum class GameModes {
        None,
        Team_Deathmatch,
        Search_and_Destroy,
        Free_For_All
    };

    struct playerPacket {
        std::string header;
        sf::Vector2f position;
        float rotation;
        bool walking;
        bool firing;
    };

    struct timePacket {
        std::string header;
        int minutes;
        int seconds;
    };

}

#endif //TOPFORCE_HEADERS_HPP
