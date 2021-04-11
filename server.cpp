/*
Name: Tailer Justin Delarosa Nguyen
Class: COSC 3360 Mon-Wed 4-5:30
Description:
Server side of TCP connection
which creates multiple sockets to
connect to client side and send back data.
the program terminates when "terminate" is 
called.


*/


#include <iostream>
#include <fstream>
#include<string>
#include<vector>
#include<iomanip>
#include<stdio.h>
#include<errno.h>
#include<signal.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<sys/wait.h>
#include<netinet/in.h>
#include<netdb.h>
#include<cstring>
#include<arpa/inet.h>
#include<netdb.h>
using namespace std;



string zodiacToReturn(vector<string> vec, int sign){
    //cout<<"I WAS CALLED!"<<endl;
    //cout<<"sign is: "<<sign<<endl;
    if(sign==0){
        //cout<<"ARIES IS CALLED"<<endl;
        return vec.at(0);

    }
    else if(sign==1){
        return vec.at(1);
    }
    else if(sign==2){
        return vec.at(2);
    }
    else if(sign==3){
        return vec.at(3);
    }
    else if(sign==4){
        return vec.at(4);
    }
    else if(sign==5){
        return vec.at(5);
    }
    else if(sign==6){
        return vec.at(6);
    }
    else if(sign==7){
        return vec.at(7);
    }
    else if(sign==8){
        return vec.at(8);
    }
    else if(sign==9){
        return vec.at(9);
    }
    else if(sign==10){
        return vec.at(10);
    }
    else if(sign==11){
        return vec.at(11);
    }
    else{
        return "That is not a valid zodiac";
    }
    
}

int main(){
     ifstream ifs("predictions20.txt");
    
    vector<string> arr;
    while(!ifs.eof()){
        string temp;
        getline(ifs,temp);
        if(temp!=""){
            arr.push_back(temp);
        }
    }
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

    //initialize winsock
    //create a socket
    //bind socket to  port
    //tell winsock socket is to listen
    //wait for a connection
    //close listening
    //while loop, accept & echo from client
    //shutdown socket
    

    //AF_INET IS JUST IP
    int listening = socket(AF_INET, SOCK_STREAM,0);
    if(listening==-1){
        cerr<<"can't create a socket";
        return -1;
    }

    sockaddr_in hint;
    hint.sin_family=AF_INET;
    hint.sin_port=htons(SPN);

    //inet_pton is pointer to fstream #
    inet_pton(AF_INET,"0.0.0.0", &hint.sin_addr);

    if(bind(listening, (sockaddr*)&hint,sizeof(hint))==-1){
        cerr<<"Can't bind to IP/PORT"<<endl;
        return -2;
    }
    if(listen(listening,SOMAXCONN)==-1){
        cerr<<"Can't listen"<<endl;
        return -3;
    }
    sockaddr_in client;
    socklen_t clientSize = sizeof(client);
    char host[NI_MAXHOST]; //name of host
    char svc[NI_MAXSERV]; //server name
    
    int sockfd, newsockfd, portno, clilen, n;
    /*
    int clientSocket=accept(listening,(sockaddr*) &client, &clientSize);
    if(clientSocket==-1){//if error
        cerr<<"problem w/ client connecting"<<endl;
        return -4;
    }
    memset(host,0,NI_MAXHOST);
    memset(svc,0,NI_MAXSERV);
    int result=getnameinfo((sockaddr*)&client,sizeof(client),host,NI_MAXHOST,svc,NI_MAXSERV,0);
    if(result){
        //cout<<host<< " connected on " << svc<<endl;
    }else{
        inet_ntop(AF_INET, &client.sin_addr, host, NI_MAXHOST);
        cout<<host<<" connected on "<<ntohs(client.sin_port)<<endl;
    }
    */
    
    int clientSocket;
    char buf[4096];
    bool isExit = false;
    while(!isExit){
        
        clientSocket=accept(listening,(sockaddr*) &client, &clientSize);
        if(clientSocket==-1){//if error
            cerr<<"problem w/ client connecting"<<endl;
            return -4;
        }
        
        memset(host,0,NI_MAXHOST);
        memset(svc,0,NI_MAXSERV);
        int result=getnameinfo((sockaddr*)&client,sizeof(client),host,NI_MAXHOST,svc,NI_MAXSERV,0);
        if(result){
            //cout<<host<< " connected on " << svc<<endl;
        }else{
            inet_ntop(AF_INET, &client.sin_addr, host, NI_MAXHOST);
            //cout<<host<<" connected on "<<ntohs(client.sin_port)<<endl;
        }
        
        


        //clear buffer
        memset(buf,0,4096);
        //wait for msg
        
        int bytesRecv = recv(clientSocket,buf,4096,0);
        //cout<<string(buf,0,bytesRecv)<<endl;

        if(bytesRecv==-1){
            cerr<<"there was a connection issue"<<endl;
            break;
        }
        string convertStr = string(buf,0,bytesRecv);
        
        if(convertStr=="TERMINATE" || convertStr == "Terminate" || convertStr=="terminate"){
            isExit=true;
            
            break;
        }
        
       if(convertStr!=""){
           cout<<"Daily horoscope for "<<convertStr<<":"<<endl;
       }
       
        string msg; 
        //string str = string(&buf[0], &buf[11]);
        //cout<<"STR:" <<str<<endl;
        if(convertStr=="Aries" || convertStr=="aries"){
            cout<<""<<zodiacToReturn(arr, 0)<<endl;
            msg = zodiacToReturn(arr, 0);
        }else if(convertStr==""){
            
        }
        else if(convertStr=="Taurus" || convertStr=="taurus"){
            cout<<""<<zodiacToReturn(arr,1)<<endl;
            msg = zodiacToReturn(arr, 1);
        }
        else if(convertStr=="Gemini" || convertStr=="gemini"){
            cout<<""<<zodiacToReturn(arr,2)<<endl;
            msg = zodiacToReturn(arr, 2);
        }
        else if(convertStr=="Cancer"|| convertStr=="cancer"){
            cout<<""<<zodiacToReturn(arr,3)<<endl;
            msg = zodiacToReturn(arr, 3);
        }
        else if(convertStr=="Leo"|| convertStr=="leo"){
            cout<<""<<zodiacToReturn(arr,4)<<endl;
            msg = zodiacToReturn(arr, 4);
        }
        else if(convertStr=="Virgo"|| convertStr=="virgo"){
            cout<<""<<zodiacToReturn(arr,5)<<endl;
            msg = zodiacToReturn(arr, 5);
        }
        else if(convertStr=="Libra"|| convertStr=="libra"){
            cout<<""<<zodiacToReturn(arr,6)<<endl;
            msg = zodiacToReturn(arr, 6);
        }
        else if(convertStr=="Scorpio"|| convertStr=="scorpio"){
            cout<<""<<zodiacToReturn(arr,7)<<endl;
            msg = zodiacToReturn(arr, 7);
        }
        else if(convertStr=="Sagittarius"|| convertStr=="sagittarius"){
            cout<<""<<zodiacToReturn(arr,8)<<endl;
            msg = zodiacToReturn(arr, 8);
        }
        else if(convertStr=="Capricorn"|| convertStr=="capricorn"){
            cout<<""<<zodiacToReturn(arr,9)<<endl;
            msg = zodiacToReturn(arr, 9);
        }
        else if(convertStr=="Aquarius"|| convertStr=="aquarius"){
            cout<<""<<zodiacToReturn(arr,10)<<endl;
            msg = zodiacToReturn(arr, 10);
        }
        else if(convertStr=="Pisces"|| convertStr=="pisces"){
            cout<<""<<zodiacToReturn(arr,11)<<endl;
            msg = zodiacToReturn(arr, 11);
        }
        else{
            cout<<""<<zodiacToReturn(arr,12)<<endl;
            msg=zodiacToReturn(arr,12);
        }
       
        //cout<<"received: "<< zodiacToReturn(arr,0)<<endl;
        
        const char* c = msg.c_str();

        
        int sendRes = send(clientSocket, msg.c_str(), msg.size()+1,0);
        if(sendRes==-1){
            cout<<"could not send to server\r\n";
            continue;
        }
        //cout<<"sending back to client"<<endl;
        //send(clientSocket,c,strlen(c),0); 
        //write(clientSocket, c, strlen(c));
        //send(clientSocket,buf,bytesRecv+1,0);
    
        //display msg
        //resend message
        close(clientSocket);
    }
    
    //cout<<"SHALOM:"<<zodiacToReturn(arr,"Aquarius");
   
   
    cout<<"Connection terminated... goodbye"<<endl;
    //close(clientSocket);
    close(listening);
    
    
    return 0;
}