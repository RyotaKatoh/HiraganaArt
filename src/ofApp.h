#pragma once

#include "ofMain.h"

#include "ofxTrueTypeFontUC.h"
#include "HiraganaUtil.h"
#include "CharImage.h"

#include "GAMain.h"

/*  DRAW_MODE  */
// 1: create HIRAGANA ART
// 2: draw created HIRAGANA ART
const static int DRAW_MODE = 2;

class ofApp : public ofBaseApp{

public:
    void setup();
    void update();
    void draw();
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    ofImage targetImage, charImage;
    int     charImageNumber;
    
    GAMain  myGA;
    
    bool startDrawing;
};
