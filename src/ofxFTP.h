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
	
	void connect(string host, int port, string username = "anonymous", string password = "");
	void disconnect();
	void send(string local, string remote, bool is_binary = false);
	void get(string remote, string local, bool is_binary = false);
	vector<string> list(string path);
	
private:
	
	ofPtr<Poco::Net::FTPClientSession> ftp;
	
};