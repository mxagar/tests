#include <iostream>
#include <string>

#include "asl/defs.h" // infinity(), nan(), sqr(), rad2deg(), deg2rad(), random(), max(), min(), clamp()
// defs includes
// - asl/time.h: sleep(), now()
// - asl/atomic.h: AtomicCount
#include "asl/Array.h" // Array
#include "asl/Map.h" // Map, Dic
#include "asl/String.h" // String
#include "asl/Var.h" // Var
#include "asl/JSON.h" // Json
#include "asl/Xml.h" // XML
#include "asl/testing.h" // Testing
#include "asl/Log.h" // Logging
#include "asl/Directory.h" // File System; It indludes File.h
#include "asl/CmdArgs.h" // Command Line Argument Paring
#include "asl/Socket.h" // Sockets

using namespace asl;

int main(int argc, char** argv) {

    /*
        See:
        https://aslze.github.io/asl-doc/index.html

        Covered here: Socket Communication

    */

    bool udp = false;
    bool tcp = !udp;

    // 1. UDP Socket: Simple Basic Type Receiver
    if (udp) {
        String hostUDP = "localhost"; // network name or IP
        int portUDP = 53427; // random big value
        PacketSocket socketUDP;
        socketUDP.bind(hostUDP, portUDP); // bind() to a local port, connect() to a remote server
        int *data = new int; // packet
        std::cout << "Waiting for UDP packets..." << std::endl;
        while (socketUDP.waitInput(5.0)) {
            // Receive packet
            socketUDP.readFrom(InetAddress(hostUDP, portUDP), (void*)data, sizeof(data));
            std::cout << "data = " << *data << std::endl;
        }
        std::cout << "Finished!" << std::endl;
    }

    // 2. TCP Socket: JSON string receiver
    if (tcp) {
        String hostTCP = "localhost"; // network name or IP
        int portTCP = 53529; // random big value
        Socket socketTCP;
        socketTCP.bind(hostTCP, portTCP); // bind() to a local port, connect() to a remote server
        std::cout << "Waiting for TCP packets..." << std::endl;
        while (socketTCP.waitData(5.0)) {
            // Receive packet
            //String packet_string = socketTCP.readLine();
            int n = socketTCP.available();
            char* data;
            int ret	= socketTCP.read((void*)data, n);
            String packet_string = (char*)data;
            std::cout << "<- " << std::string(packet_string) << std::endl;
            // Decode packet and display
            Var packet = Json::decode(packet_string);
            if (packet.ok()) {
                printf("%s\n", *packet.toString());
            }
        }
        std::cout << "Finished!" << std::endl;
    }

}