
#include "NetworkGameManager.h"
#include <iostream>

NetworkGameClient::NetworkGameClient()
{
	slen_update = sizeof(si_other_update);
	slen_broadcast = sizeof(si_other_broadcast);
}

NetworkGameClient::~NetworkGameClient(){}


void NetworkGameClient::initUpdateSocket(char *server){

	//create socket
	s_update = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if(s_update==SOCKET_ERROR)
	{
		printf("failed to create socket...");
		exit(-2); 
	}

	//address structure
	memset((char*) &si_other_update, 0, sizeof(si_other_update));

	si_other_update.sin_family = AF_INET;
	si_other_update.sin_port = htons(PORT);
	si_other_update.sin_addr.S_un.S_addr = inet_addr(server);

	//set up non-blocking mode
	u_long iMode = 1;
	ioctlsocket(s_update, FIONBIO, &iMode);
}

void NetworkGameClient::initBroadcastSocket(){

	//create socket
	s_broadcast = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if(s_broadcast==SOCKET_ERROR)
	{
		printf("failed to create socket...");
		exit(-4); 
	}

	////////////////////////////////////////////////////////////////
	//set up the broadcast option 
	bool bOpt = true;
	int err = setsockopt(s_broadcast, SOL_SOCKET, SO_BROADCAST, (char*)&bOpt, sizeof(bOpt));
	if(err == SOCKET_ERROR)
	{
		printf("failed to set broadcast option...");
		exit(-5); 
	}
	///////////////////////////////////////////////////////////////

	//address structure
	memset((char*) &si_other_broadcast, 0, sizeof(si_other_broadcast));

	si_other_broadcast.sin_family = AF_INET;
	si_other_broadcast.sin_port = htons(PORT);
	si_other_broadcast.sin_addr.S_un.S_addr = htonl(INADDR_BROADCAST);

	//set up non-blocking mode
	u_long iMode = 1;
	ioctlsocket(s_broadcast, FIONBIO, &iMode);
}

void NetworkGameClient::sendMessage(const char *message, bool broadcast)
{
	if(broadcast){
		if(sendto(s_broadcast, message, strlen(message), 0, (struct sockaddr *) &si_other_broadcast, slen_broadcast) == SOCKET_ERROR)
		{
			int nError = WSAGetLastError();
			printf("Failed to send");
			exit(-6);
		}
	}
	else{
		if(sendto(s_update, message, strlen(message), 0, (struct sockaddr *) &si_other_update, slen_update) == SOCKET_ERROR)
		{
			int nError = WSAGetLastError();
			printf("Failed to send");
			exit(-7);
		}
	}
}

void NetworkGameClient::cleanUp()
{
	closesocket(s_update);
	closesocket(s_broadcast);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

NetworkGameServer::NetworkGameServer()
{
	slen = sizeof(si_other);
}
NetworkGameServer::~NetworkGameServer(){}

void NetworkGameServer::serverInit()
{
	//create socket
	s = socket(AF_INET, SOCK_DGRAM, 0);
	if(s==INVALID_SOCKET)
	{
		printf("failed to create socket...");
		exit(-9); 
	}

	//address structure
	memset((char*) &si_other, 0, sizeof(si_other));

	server.sin_family = AF_INET;
	server.sin_port = htons(PORT);
	server.sin_addr.s_addr = INADDR_ANY;


	if(bind(s, (struct sockaddr *)&server, sizeof(server)) == SOCKET_ERROR)
	{
		printf("Bind failed...");
		exit(-10);
	}
	//set up non-blocking mode
	u_long iMode = 1;
	ioctlsocket(s, FIONBIO, &iMode);
}

std::vector<float> NetworkGameServer::recieveMessage()
{
	memset(data, '\0', BUFLEN);
	recv_len = recvfrom(s, data, BUFLEN, 0,(struct sockaddr *) &si_other, &slen);

	int nError = WSAGetLastError();
	if(nError != WSAEWOULDBLOCK && nError!=0)
	{
		printf("Recieve failed");
		exit(-11);
	}

	std::vector<float> output; 
	if(nError != WSAEWOULDBLOCK && data[0] != 0)
	{
		int start = 0;	//start of the float
		
		//process message to get required data 
		for(int i = 0; i < BUFLEN; i++)
		{
			//no more data to process
			if(data[i] == 0)
			{
				break;
			}

			if(data[i] == '@')	//each float is seperated by the @ symbol
			{
				char num[100];
				for(int k = 0; k < i; k++)
				{
					num[k] = data[start + k];
				}

				start = i + 1;	//get start of next float 
				output.push_back(atof(num));
			}
		}
	}
	return output; 
}

char* NetworkGameServer::recieveBroadcast(){

	memset(data, '\0', BUFLEN);

	recv_len = recvfrom(s, data, BUFLEN, 0,(struct sockaddr *) &si_other, &slen);

	int nError = WSAGetLastError();
	if(nError != WSAEWOULDBLOCK && nError!=0)
	{
		printf("Recieve failed");
		exit(-12);
	}

	if(nError != WSAEWOULDBLOCK && data[0] != 0)
	{
		return data; 
	}

	return NULL;
}

void NetworkGameServer::cleanUp()
{
	closesocket(s);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
NetworkGameManager::NetworkGameManager(){
	lobbySize = 1;
	findLobbyCounter = 0;
}

void NetworkGameManager::init(){

	//Initialize winsocket
	printf("\nInitializing winsocket...");
	if(WSAStartup(MAKEWORD(2,2),&wsa)!=0)
	{
		printf("Failed to initialize...");
		exit(-1);
	}
	printf("Initialized...\n");

	//
	server.serverInit();

	///////////////////////////////////////////////////////////////
	//Get local host IP adress 

	char ac[80];
	//get host's name
    if (gethostname(ac, sizeof(ac)) == SOCKET_ERROR) {
        printf("Failed to get host's name...");
		exit(-13);
    }
	//get host
    struct hostent *phe = gethostbyname(ac);
    if (phe == 0) {
        printf("Failed to get host...");
		exit(-14);
    }

	//get host's address
	struct in_addr addr;
    for (int i = 0; phe->h_addr_list[i] != 0; ++i) {
        memcpy(&addr, phe->h_addr_list[i], sizeof(struct in_addr));
    }

	client.localAddr = inet_ntoa(addr);
	//////////////////////////////////////////////////////////////
}

bool NetworkGameManager::lobbyListen()
{

	char *remoteAddr = server.recieveBroadcast();	//listen for every frame

	if(remoteAddr != NULL){
		client.initUpdateSocket(remoteAddr);	//if get remote addr 

		client.sendMessage(client.localAddr, false);

		lobbySize++;

		return true;
	}

	return false;
}

bool NetworkGameManager::joinMatchInit()
{
	client.initBroadcastSocket();

	client.sendMessage(client.localAddr, true);

	//search for lobby
	char *remoteAddr = NULL;
	while(findLobbyCounter < 100000){
		remoteAddr = server.recieveBroadcast();
		
		if(remoteAddr != NULL){
			//if we recieved our own broadcast, discard it and keep listening
			if(std::strcmp(remoteAddr,client.localAddr) != 0){
				break;
			}
		}
		findLobbyCounter++; 
	}

	findLobbyCounter = 0;

	if(remoteAddr != NULL)
	{
		client.initUpdateSocket(remoteAddr);
		lobbySize++;
		return true;
	}

	return false;
}

void NetworkGameManager::cleanUp()
{
	server.cleanUp();
	//client.cleanUp();
	WSACleanup();
}