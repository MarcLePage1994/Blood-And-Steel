#ifndef __NETWORKMANAGER_H__
#define __NETWORKMANAGER_H__

//a peer to peer framework
//a peer process is both a client and server

#include <WinSock2.h>
#pragma comment (lib, "ws2_32.lib") // winsock libarary

#include <vector>

#define BUFLEN 512 //Max length of buffer
#define PORT 8888 //port 

//A client is a process that runs on a network host that asks for a service
//In this case, the client will send information to another peer's server
class NetworkGameClient
{
public:
	NetworkGameClient();
	~NetworkGameClient();

	void initUpdateSocket(char *server);
	void initBroadcastSocket();
	void sendMessage(const char *message, bool broadcast);	//if broadcast is true, message will be sent to every remote host on network
	void cleanUp();

	char *localAddr;	//IP address of local host

private:
	//for update socket
	SOCKET s_update; 
	struct sockaddr_in si_other_update;
	int slen_update;
	
	//for broadcast socket
	SOCKET s_broadcast; 
	struct sockaddr_in si_other_broadcast;
	int slen_broadcast;
};

//A server is a process that runs on a network host that waits to provide a service
//In this case, the server will revcieve information from another peer's server
class NetworkGameServer
{
public:
	NetworkGameServer();
	~NetworkGameServer();

	void serverInit();
	std::vector<float> recieveMessage(); 
	char* recieveBroadcast(); 
	void cleanUp();

private:
	struct sockaddr_in server, si_other;
	int slen;
	int recv_len;
	char data[BUFLEN];
	SOCKET s;
};

//Manages the peer's host client and server processes 
//Makes is easier for programmer to enact client and server functionality 
class NetworkGameManager 
{
public:
	NetworkGameManager();

	void init();
	bool lobbyListen();	//listens for players who want to join lobby, true when player is found, false when not
	bool joinMatchInit();	//return true if able to join lobby and false if not. 
	void cleanUp();

	NetworkGameClient client;
	NetworkGameServer server;

	int lobbySize;

private:
	WSADATA wsa;
	int findLobbyCounter;
};

#endif // __NETWORKMANAGER_H__