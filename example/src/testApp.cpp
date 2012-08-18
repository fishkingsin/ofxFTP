#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){

    client.setup("<yourhost>","<username>","<passwork>");
    client.setVerbose(true);
}       

//--------------------------------------------------------------
void testApp::update(){

}

//--------------------------------------------------------------
void testApp::draw(){

}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

    if(key=='1')
    {
    if(client.send("<filename>","<localpath>","<remotepath>")>0)
    {
        printf("Send file to server success\n\n");
    }
    }
    if(key=='2')
    {
    if(client.get("<filename>","<localpath>","<remotepath>")>0)
    {
        printf("get file to server success\n\n");
    }
    }
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 
    for(int i = 0 ; i < dragInfo.files.size() ; i++)
    {
        ofFile file(dragInfo.files[i]);
        string path = file.path().substr(0,file.path().length()-file.getFileName().length());
        client.send(file.getFileName(),path,"/");
    }
}