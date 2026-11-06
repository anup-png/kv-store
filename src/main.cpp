#include <iostream>
#include <string>
#include <winsock2.h>
#include <ws2tcpip.h>

const int PORT = 6379;

int main() {
    // 1. Initialize Winsock
    WSADATA wsaData;
    int wsaInit = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (wsaInit != 0) {
        std::cerr << "WSAStartup failed with error: " << wsaInit << "\n";
        return 1;
    }

    // 2. Create a TCP socket
    SOCKET serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (serverSocket == INVALID_SOCKET) {
        std::cerr << "Socket creation failed with error: " << WSAGetLastError() << "\n";
        WSACleanup();
        return 1;
    }

    // 3. Bind socket to IP and Port (0.0.0.0:6379)
    sockaddr_in serverAddr{};
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(PORT);

    if (bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        std::cerr << "Bind failed with error: " << WSAGetLastError() << "\n";
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }

    // 4. Start listening for incoming client connections
    if (listen(serverSocket, SOMAXCONN) == SOCKET_ERROR) {
        std::cerr << "Listen failed with error: " << WSAGetLastError() << "\n";
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }

    std::cout << "kv-store TCP server started successfully!\n";
    std::cout << "Listening for clients on port " << PORT << "...\n";

    // 5. Accept an incoming client connection (Blocking call)
    sockaddr_in clientAddr{};
    int clientAddrSize = sizeof(clientAddr);
    SOCKET clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddr, &clientAddrSize);
    
    if (clientSocket == INVALID_SOCKET) {
        std::cerr << "Accept failed with error: " << WSAGetLastError() << "\n";
    } else {
        std::cout << "Client connected successfully!\n";

        // Send a standard Redis response back (+PONG\r\n)
        std::string response = "+PONG\r\n";
        send(clientSocket, response.c_str(), response.length(), 0);

        closesocket(clientSocket);
        std::cout << "Client disconnected and connection socket closed.\n";
    }

    // Clean up server socket
    closesocket(serverSocket);
    WSACleanup();

    return 0;
}