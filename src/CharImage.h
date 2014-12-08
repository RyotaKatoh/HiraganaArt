//
//  CharImage.h
//  HiraganaArt
//
//  Created by 加藤亮太 on 2014/12/06.
//
//

#ifndef __HiraganaArt__CharImage__
#define __HiraganaArt__CharImage__

#include "ofMain.h"
#include "ofxTrueTypeFontUC.h"
#include "HiraganaUtil.h"

const static int NUM_CHARACTER = 1500;
const static int WIDTH         = 512;
const static int HEIGHT        = 768;

class CharImage{

public:

    void        setup(ofxTrueTypeFontUC &font, HiraganaUtil &h);
    
    void        setCharacter(int index, string c);
    string      getCharacter(int index);

    void        setFbo();
    ofImage     getCharImage();
    
    void        setFitness(float f);
    float       getFitness();
    
//    CharImage &operator=(const CharImage &left);
    
    ofxTrueTypeFontUC *fontUC;
    string      charSet[NUM_CHARACTER];
    ofPoint     location[NUM_CHARACTER];
    ofColor     charColor[NUM_CHARACTER];
    float       fontScale[NUM_CHARACTER];
    
    ofFbo       charImageFbo;
    ofImage     image;
    
    float       fitness;
    
private:
    
    
};

#endif /* defined(__HiraganaArt__CharImage__) */
