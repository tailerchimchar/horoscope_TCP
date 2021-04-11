/*
Name: Tailer Justin Delarosa Nguyen
Class: COSC 3360 Mon-Wed 4-5:30
Description:
Client side of TCP connection
which establishes a connection 
with the server side and terminates
every single instance.


*/


#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include<iostream>
#include<string>
#include<string.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<limits.h>

void error(char *msg)
{
    perror(msg);
    exit(0);
}

using namespace std;

int main()
{


    //prompt user for server host name and host port num
    // create a socket
    int sock = socket(AF_INET,SOCK_STREAM, 0);
    if(sock==-1){
        return 1;
    }

    char localhost[HOST_NAME_MAX];
    gethostname(localhost, HOST_NAME_MAX+1);
    //cout<<string(localhost,0,HOST_NAME_MAX);

    string hostname;
    cout<<"Enter the host name:";
    cin>>hostname;
    if(hostname!=string(localhost) && (hostname!="localhost")){
        return -1;
    }

    //hostent* hp = gethostbyname(localhost);
    //cout<<"LOCALHOST IS: "<<localhost<<endl;
    int SPN=0;
    while(SPN<1024){
        cout<<"Enter the server port number: ";
        cin>> SPN;
        if(SPN<1024){
            cout<<"num must be >=1024. Try again.";
            cin>>SPN;
        }
        cout<<endl;
    }
    


    int port = 54000;
    string ipaddress="127.0.0.1";

    sockaddr_in hint;
    hint.sin_family=AF_INET;
    hint.sin_port=htons(SPN);
    inet_pton(AF_INET, ipaddress.c_str(), &hint.sin_addr);
    
    int connectRes = connect(sock, (sockaddr*)&hint, sizeof(hint));
    if(connectRes==-1){
        return 1;
    }

    char buf[4096];
    int i = 0;
    string userInput;
    bool isExit = false;
    cout<<"ENTER A ZODIAC SIGN:";
        
        
    cin >> userInput;
    if(userInput=="TERMINATE" || userInput=="Terminate" 
    || userInput=="terminate"){
        isExit == true;
        
    }
    //cout<<"SENDING NOW:"<<endl;
    int sendRes = send(sock, userInput.c_str(), userInput.size()+1,0);
    if(sendRes==-1){
        cout<<"could not send to server\r\n";
        
    }
    memset(buf, 0, 4096);
    int bytesReceived = recv(sock, buf, 4096, 0);
    if(bytesReceived==-1){
        cout<<"there was an error from server \r\n";
    }else{
        cout<<"" <<string(buf,bytesReceived)<<"\r\n";
    }
    

    

    if(isExit){
        cout<<"ISEXIT IS TRUE!"<<endl;
        close(sock);
    }
    


    // connect to server
    // prompt user for zodiac
    // send sign to server
    // receive & print out reply from server
    // terminate


}