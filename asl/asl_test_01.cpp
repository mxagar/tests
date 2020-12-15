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

    // 1. UDP Socket: Simple Basic Type Sender
    if (udp) {
        String hostUDP = "localhost"; // network name or IP
        int portUDP = 53427; // random big value
        PacketSocket socketUDP;
        socketUDP.connect(hostUDP, portUDP); // bind() to a local port, connect() to a remote server
        int *data = new int; // packet
        unsigned long int maxPacketNumber = 1000;
        std::cout << "Sending UDP packets..." << std::endl;
        for (unsigned int i = 0; i < maxPacketNumber; ++i) {
            // Update packet and send
            *data = i;
            socketUDP.sendTo(InetAddress(hostUDP, portUDP), (void*)data, sizeof(data));
        }
    }

    if (tcp) {
        // 2. JSON Object: Measurement
        Var measurement = Var("name", "measurement")
                        ("id", 73)
                        ("reference", 42)
                        ("time", Date::now())
                        ("successful", true)
                        ("values", Var::array({1.1f, 2.2f, 3.3f, 4.4f, 5.5f, 6.6f}));

        String measurement_json = Json::encode(measurement); // Encode Var as JSON string; equivalent to JavaScript stringify()
        bool ret_json = Json::write("measurement.json", measurement); // Writes a var to a file in JSON format
        Var measurement_read = Json::read("measurement.json"); // Read file data.json which is in JSON format, ans save it as Var
        if (measurement_read.ok())
            printf("%s\n", *measurement_read.toString()); // Print read JSON file

        // 3. TCP Socket: JSON string sender
        String hostTCP = "localhost"; // network name or IP
        int portTCP = 53529; // random big value
        Socket socketTCP;
        socketTCP.connect(hostTCP, portTCP); // bind() to a local port, connect() to a remote server
        unsigned long int maxPacketNumber = 1000;
        std::cout << "Sending TCP packets..." << std::endl;
        for (unsigned int i = 0; i < maxPacketNumber; ++i) {
            // Update packet
            measurement["id"] = i;
            measurement["time"] = Date::now();
            measurement["values"] =  Var::array({float(i), float(i*2), float(i*3), float(i*4), float(i*5), float(i*6)});
            // Prepare packet and send
            String packet = Json::encode(measurement);
            const char* packet_str = std::string(packet).c_str();
            std::cout << "-> [" << packet.length() << "]: " << std::string(packet) << std::endl;
            socketTCP.write((void*)(packet_str), packet.length());
        }
    }
   

}