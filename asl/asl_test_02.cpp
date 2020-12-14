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

    String path = "/index.html", host = "somehost.com";
    Socket socket;
    socket.connect(host, 80);
    socket << String(0, "GET %s HTTP/1.0\r\nHost: %s\r\n\r\n", *path, *host);
    String response;
    char buffer[1001];
    while(true)
    {
        if(!socket.waitInput())
            continue;
        if(socket.disconnected())
            break;
        int n = socket.read(buffer, min(socket.available(), 1000));
        if(n <= 0)
            break;
        response += String(buffer, n);
    }

}