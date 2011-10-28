#include "ofxFTP.h"

//
// server
//

void ofxFTPServer::start(int port, string publish_dir, string username, string password)
{
	server.SetDataPortRange(10000, 12000);
	server.SetCheckPassDelay(500);
	server.EnableFXP(true);
	
	publish_dir = ofToDataPath(publish_dir, true);
	
	CFtpServer::CUserEntry *user = server.AddUser(username.c_str(), password.c_str(), publish_dir.c_str());
	user->SetMaxNumberOfClient(0);
	user->SetPrivileges(CFtpServer::READFILE | CFtpServer::WRITEFILE |
						CFtpServer::LIST | CFtpServer::DELETEFILE | CFtpServer::CREATEDIR |
						CFtpServer::DELETEDIR);
	
	if (server.StartListening(INADDR_ANY, port))
	{
		if (!server.StartAccepting())
			ofLogError("ofxFTPServer", "server couldn't start");
	}
	else
		ofLogError("ofxFTPServer", "port is already used");
}


//
// client
//

void ofxFTPClient::connect(string host, int port, string username, string password)
{
	ftp = ofPtr<Poco::Net::FTPClientSession>(new Poco::Net::FTPClientSession(host, port));
	ftp->login(username, password);
}

void ofxFTPClient::disconnect()
{
	ftp->abort();
	ftp->close();
}

void ofxFTPClient::send(string local, string remote, bool is_binary)
{
	ostream& ftpOStream = ftp->beginUpload(remote.c_str());
	
	Poco::Net::FTPClientSession::FileType type = Poco::Net::FTPClientSession::TYPE_TEXT;
	if (is_binary) type = Poco::Net::FTPClientSession::TYPE_BINARY;
	
	ftp->setFileType(type);
	
	ifstream localIFStream(local.c_str(), ifstream::in | ifstream::binary);
	Poco::StreamCopier::copyStream(localIFStream, ftpOStream);
	
	ftp->endUpload();
}

void ofxFTPClient::get(string remote, string local, bool is_binary)
{
	istream& ftpOStream = ftp->beginDownload(remote.c_str());
	
	Poco::Net::FTPClientSession::FileType type = Poco::Net::FTPClientSession::TYPE_TEXT;
	if (is_binary) type = Poco::Net::FTPClientSession::TYPE_BINARY;
	
	ftp->setFileType(type);
	
	ofstream localIFStream(local.c_str(), ifstream::in | ifstream::binary);
	Poco::StreamCopier::copyStream(ftpOStream, localIFStream);
	
	ftp->endDownload();
	
}

vector<string> ofxFTPClient::list(string path)
{
	string res;
	istream &ist = ftp->beginList(path, true);
	Poco::StreamCopier::copyToString(ist, res);
	ftp->endList();
	
	return ofSplitString(res, "\n", true, true);
}
