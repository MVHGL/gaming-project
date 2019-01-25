#include "Server.hpp"


Server::Server(unsigned short serverPort, int minuteToPlay, int secondToPlay):
minuteToPlay(minuteToPlay),
secondToPlay(secondToPlay)
{
    if (secondToPlay > 60)
        secondToPlay = 59;

    socket.bind(serverPort);
    socket.setBlocking(0); // just drop datagrams instead of trying to catch all of them
    NETWORK_INFO("port binded");

}


sf::Socket::Status Server::serverReceive() {

    if (socket.receive(playerPacket, lastIp, lastPort) != sf::Socket::Done) {
#if DEBUG
        //NETWORK_INFO("received nothing");
#endif // DEBUG
        return sf::Socket::NotReady;
    }
#if DEBUG
   // NETWORK_INFO("Received data");
#endif // DEBUG
    clientIps.insert(lastIp);
    return sf::Socket::Done; 
}

sf::Socket::Status Server::playerSend() {
#if DEBUG
    //NETWORK_INFO("Server send function");
#endif // DEBUG
    std::for_each(clientIps.begin(), clientIps.end(), [&](sf::IpAddress client){
        if (client != lastIp) {
            if (socket.send(playerPacket, client, lastPort) != sf::Socket::Done) {
                //NETWORK_ERROR("Sending failed");
                return sf::Socket::Error;
            }
        }
    });
    return sf::Socket::Done;
}

sf::Socket::Status Server::timeSend(){
#if DEBUG
    //NETWORK_INFO("Server send function");
#endif // DEBUG
    std::for_each(clientIps.begin(), clientIps.end(), [&](sf::IpAddress client){
       if(socket.send(timePacket, client, lastPort) != sf::Socket::Done){
            //NETWORK_ERROR("Sending failed");
            return sf::Socket::Error;
       }

    });
}

void Server::run() {
    NETWORK_INFO("Server running");

    while (true) {
        
        if (timerClock.getElapsedTime().asSeconds() > 1){ // every second we send a time packet
#if DEBUG
            NETWORK_INFO("Time packet: M: {} S: {}", minuteToPlay, secondToPlay);
#endif // DEBUG

            timePacket << "time" << minuteToPlay << secondToPlay; // constructing time packet
            timeSend();

            --secondToPlay;
            if (secondToPlay <= 0 && minuteToPlay > 0){
                --minuteToPlay;
                secondToPlay = 59;
            }
            else if (secondToPlay <= 0 && minuteToPlay <= 0){
                exit(1);
            }

            timerClock.restart(); // restart the clock
        }

        serverReceive();
        playerSend();


    }
}

