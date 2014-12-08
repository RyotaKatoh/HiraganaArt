#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofBackground(0);

    if(DRAW_MODE == 1){
     
        myGA.setup();
    
    }
    else if(DRAW_MODE == 2){
     
        targetImage.loadImage("../../../../../common/image/Vermeer.jpg");
        
        charImageNumber = 0;
        charImage.loadImage("charImages/" + ofToString(charImageNumber) + ".png");
        
        startDrawing = false;
    }
  
}

//--------------------------------------------------------------
void ofApp::update(){

    if(DRAW_MODE == 1){
        
        myGA.GALifeCycle();
    
    }
    else if(DRAW_MODE == 2){
        
        if(ofGetFrameNum() % 3 == 0 && charImageNumber < 3700 && startDrawing){
            charImageNumber ++;
            
            ofFile file;
            file.open("charImages/" + ofToString(charImageNumber) + ".png");
            while(!file.exists()){
                
                charImageNumber++;
                file.open("charImages/" + ofToString(charImageNumber) + ".png");
                
            }
            charImage.loadImage(file);
            
        }
    }
    
}

//--------------------------------------------------------------
void ofApp::draw(){

    if(DRAW_MODE == 1){
        
        myGA.targetImage.draw(0, 0);
    
        ofImage bestCharImage = myGA.getBestCharImage();
        bestCharImage.draw(WIDTH, 0);
    
    }
    else if(DRAW_MODE == 2){
        
        targetImage.draw(0, 0);
        charImage.draw(WIDTH, 0);
        
    }

//    ofDrawBitmapString("fps: " + ofToString(ofGetFrameRate()) + "\nimageNumber: " + ofToString(charImageNumber), 10, 10);

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    startDrawing = !startDrawing;
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
