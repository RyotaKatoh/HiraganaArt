//
//  CharImage.cpp
//  HiraganaArt
//
//  Created by 加藤亮太 on 2014/12/06.
//
//

#include "CharImage.h"

void CharImage::setup(ofxTrueTypeFontUC &font, HiraganaUtil &h){

    fontUC = &font;
    
    for(int i=0;i<NUM_CHARACTER;i++){
    
        charSet[i] = h.getRandomKana();
        location[i].set(ofRandom(-fontUC->getFontSize(), WIDTH+fontUC->getFontSize()), ofRandom(HEIGHT) );
        charColor[i].set(ofRandom(255), ofRandom(255), ofRandom(255));
        fontScale[i] = ofRandom(1.0);
        
    }
    
    charImageFbo.allocate(WIDTH, HEIGHT);
    
    fitness = 0.0;
    
}

void CharImage::setCharacter(int index, string c){

    charSet[index] = c;
    
}

string CharImage::getCharacter(int index){
    
    return charSet[index];
    
}

void CharImage::setFbo(){
    

    charImageFbo.begin();
    
    ofClear(0);
    ofBackground(0);
    for(int i=0;i<NUM_CHARACTER;i++){
    
        ofPushMatrix();
        
        ofTranslate(location[i].x, location[i].y);
        
        ofPushStyle();
        
        ofSetColor(charColor[i]);
        
        ofScale(fontScale[i], fontScale[i]);
        fontUC->drawString(charSet[i], 0, 0);
        
        ofPopStyle();
        
        ofPopMatrix();
    }
    
    charImageFbo.end();
    
}

ofImage CharImage::getCharImage(){

    ofPixels pixel;
    charImageFbo.readToPixels(pixel);
    image.setFromPixels(pixel);
    
    return image;
    
    
}

void CharImage::setFitness(float f){

    fitness = f;
    
    
}

float CharImage::getFitness(){

    return fitness;
    
    
}

#pragma mark - operator

//CharImage &CharImage::operator=(const CharImage &left){
//
//    for(int i=0;i<NUM_CHARACTER;i++){
//    
//        charSet[i]  =    left.charSet[i];
//        location[i] =    left.location[i];
//        charColor[i]=   left.charColor[i];
//        fontScale[i]=   left.fontScale[i];
//        
//        fitness     =   left.fitness;
//    }
//    
//    return *this;
//    
//    
//}