#pragma once

#include "ofMain.h"

#include "CFtpServer.h"
#include "Poco/Net/FTPClientSession.h"
#include "Poco/StreamCopier.h"

class ofxFTPServer
{
public:
	
	void start(int port, string publish_dir = "", string username = "anonymous", string password = "");
	
private:
	CFtpServer server;
};


class ofxFTPClient
{
public:
	ofxFTPClient();
	void setup(string _host, string username = "anonymous", string password = "", int _port = 21);
	int send(string fileName, string localFolder, string remoteFolder);
	int get(string fileName, string localFolder, string remoteFolder);
	vector<string> list(string path);
	void setVerbose(bool verbose);
private:
	//------------------------------------------------------------
    void startFtpSesssion(){
        endFtpSession();
        
        ftpClient = new Poco::Net::FTPClientSession(host, port);
        
    }
    
    //------------------------------------------------------------
    void endFtpSession(){
        if( ftpClient != NULL ){
            ftpClient->close();
            delete ftpClient;
            ftpClient = NULL;
        }
    }

	bool bVerbose;
    
    Poco::Net::FTPClientSession* ftpClient;
    string user, host, pass;
    int port;
    bool bSetup;
	
};