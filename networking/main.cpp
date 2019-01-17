// This is the server main file, it will
// be a dedicated server and must be
// compiled as a seperate executable!
#include "topForceServer.hpp"

int main(){
    tf::log::init();
    TF_INFO("Starting Topforce server!");

    //bool server_is_running = true;
    uint16_t server_port = 31337;
    tf::topforce_server current_server(server_port); // run server on port 31337

    while(1){
        current_server.listen();
        sf::sleep(sf::milliseconds(200));
        std::cout << "received: " << current_server.get_data() << "\nsize: " << current_server.get_data_size() << '\n';
        if( strncmp(current_server.get_data(), "HELLO", 80)){
            current_server.send("Hello there!");
        }
        else if(strncmp(current_server.get_data(), "STOP", 80)){
            current_server.send("Goodbye!");
            break;
        }
    }

    TF_INFO("Topforce server shutting down!...");
    return 0;
}
