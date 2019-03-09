#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Server
#include <boost/test/unit_test.hpp>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <errno.h>
#include <ctype.h>



int createSocket();
int createSockaddr(struct sockaddr_in*,struct hostent*, int);
int bindSocketToPort(int, struct sockaddr_in*);
int establishConnection(int, struct sockaddr_in*);


const char* namehost = "localhost";
struct hostent *hostname = gethostbyname(namehost);
    //hostname = gethostbyname(namehost);
struct sockaddr_in serverAddress;
struct sockaddr_in clientAddress;
socklen_t clientSocketLength = sizeof(clientAddress);
int sockfd;
int portNumber = 5555;
int socketFileDescriptor = createSocket();



int createSocket()
{
    return socket(AF_INET, SOCK_STREAM, 0);
}

int createSockaddr(struct sockaddr_in* serverAddress, struct hostent* hostname, int portNumber)
{
    bcopy((char*)hostname->h_addr, (char*)&serverAddress->sin_addr.s_addr, hostname->h_length);
    serverAddress->sin_family = AF_INET;
    serverAddress->sin_port = htons(portNumber);
    return portNumber;
}

int bindSocketToPort(struct sockaddr_in* addr, int sockfd)
{
    int _bind = bind(sockfd, (struct sockaddr*) addr, sizeof(addr));
    return _bind;
}

int establishConnection(int socketFileDescriptor, struct sockaddr_in* serverAddress)
{
    int _connect = connect(socketFileDescriptor, (struct sockaddr*) serverAddress, sizeof(sockaddr_in));
    return _connect;
}




//TESTY

BOOST_AUTO_TEST_CASE( testcreateSocket )

{

    BOOST_CHECK( createSocket() != 1 );

}




BOOST_AUTO_TEST_CASE( testcreateSockaddr )

{

    BOOST_CHECK( createSockaddr(&serverAddress,hostname, 5555)  != 1 );

}



BOOST_AUTO_TEST_CASE( testestablishConnection )

{

    BOOST_CHECK( establishConnection(socketFileDescriptor, &serverAddress) != 1 );

}



BOOST_AUTO_TEST_CASE( testbindSocketToPort )

{

    BOOST_CHECK( bindSocketToPort(&serverAddress, socketFileDescriptor) != 1 );

}


