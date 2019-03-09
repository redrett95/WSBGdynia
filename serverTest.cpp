//includes here
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#define BUFFER_SIZE 256
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Server
#include <boost/test/unit_test.hpp>

void error(const char *msg)
{
    perror(msg);
    exit(1);
}

int createSocket();
int createSockaddr(struct sockaddr_in*, int);
int bindSocketToPort(int, struct sockaddr_in*);

int createConnection(int, struct sockaddr_in*, socklen_t);
int listenForClient(int);
int acceptConnection(int ,struct sockaddr_in* , socklen_t );


ssize_t recieveTextMessage(int, char*);
ssize_t recieveFile(int);

FILE* createFile(const char*);
int getWordCount(int, int*);


void sendMessage();
void waitForReply();
void closeConnection();



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

int listenForClient(int sockfd)
{
    return listen(sockfd, 5);
}

int acceptConnection(int sockfd,struct sockaddr_in* clientAddress, socklen_t cSLength)
{
    return accept(sockfd, (struct sockaddr*) clientAddress, &cSLength);//
}

int getWordCount(int newSocketFileDescriptor,int* wordCount)
{
    return read(newSocketFileDescriptor, wordCount, sizeof(*wordCount));
}

FILE* createFile(const char* fileName)
{
    char path[BUFFER_SIZE];
    bzero(path,BUFFER_SIZE);
    strcat(path, "/root/");
    strcat(path, fileName);
    return fopen(path,"a");
}

int createSockaddr(struct sockaddr_in* addr, int portNumber)
{
    addr->sin_addr.s_addr = INADDR_ANY;
    addr->sin_family = AF_INET;
    addr->sin_port = htons(portNumber);
    return portNumber;
}

int bindSocketToPort(struct sockaddr_in* addr, int sockfd)
{
    int _bind = bind(sockfd, (struct sockaddr*) addr, sizeof(addr));
    return _bind;
}

int createConnection(int sockfd,struct sockaddr_in* clientAddress, socklen_t clientSocketLength)
{
    printf("listetnig fro client..\n");
    if (listenForClient(sockfd) == 0)
    {
        return acceptConnection(sockfd,clientAddress,clientSocketLength);
    }return -2;
}


int bindSocketToPort(int socketFileDescriptor ,struct sockaddr_in* serverAddress)
{
    return bind(socketFileDescriptor, (struct sockaddr*) serverAddress, sizeof(*serverAddress));
}

ssize_t recieveTextMessage(int newSocketFileDescriptor,char* messageBuffer)
{
    return read(newSocketFileDescriptor, messageBuffer, sizeof(*messageBuffer) * BUFFER_SIZE);
}

ssize_t recieveFile(int newSocketFileDescriptor)
{
    char filebuff[BUFFER_SIZE];
    int wordCount;
    FILE* fileHanlder = createFile("test");
    ssize_t bytes_read = getWordCount(newSocketFileDescriptor,&wordCount);
    for (int wordRead=0; wordRead < wordCount; wordRead++)
    {
        recieveTextMessage(newSocketFileDescriptor, filebuff);
        if(filebuff == NULL) printf("is null\n");
        fprintf(fileHanlder," %s", filebuff);
    }

    bzero(filebuff,BUFFER_SIZE);

    fclose(fileHanlder);
    return bytes_read;
}




//TESTY
BOOST_AUTO_TEST_CASE( testcreateSocket )
{
    BOOST_CHECK( createSocket() != 1 );
}

/*
BOOST_AUTO_TEST_CASE( testcreateSockaddr )
{
    BOOST_CHECK( createSockaddr(serverAddress, portNumber)  != 1 );
}
*/
BOOST_AUTO_TEST_CASE( testlistenForClient )
{
    BOOST_CHECK( listenForClient(sockfd) != 1 );
}
/*
BOOST_AUTO_TEST_CASE( testacceptConnection )
{
    BOOST_CHECK( acceptConnection(sockfd,clientAddress,clientSocketLength) != 1 );
}
*/
BOOST_AUTO_TEST_CASE( testbindSocketToPort )
{
    BOOST_CHECK( bindSocketToPort(socketFileDescriptor, &serverAddress) != 1 );
}
/*
BOOST_AUTO_TEST_CASE( testcreateConnection )
{
    BOOST_CHECK( createConnection(socketFileDescriptor,&clientAddress,clientSocketLength) != 1 );
}
*/
BOOST_AUTO_TEST_CASE( testbindSocketToPort1 )
{
    BOOST_CHECK( bindSocketToPort(socketFileDescriptor, &serverAddress) != 1 );
}

