//
//  GAMain.h
//  HiraganaArt
//
//  Created by 加藤亮太 on 2014/12/06.
//
//

#ifndef __HiraganaArt__GAMain__
#define __HiraganaArt__GAMain__

#include "ofMain.h"
#include "ofxTrueTypeFontUC.h"
#include "CharImage.h"
#include "HiraganaUtil.h"

const static int    MAX_GENERAtION = 50000;
const static int    DISPLAY_TIME   = 100;
const static int    NUM_POPULATION = 10;
const static int    NUM_CHILD = 10;
const static float  CROSSOVER_RATE = 0.3;
const static float  MUTATION_RATE  = 0.01;


class GAMain{

public:
    
    void setup();
    
    void crossover(CharImage &target, CharImage &input1, CharImage &input2);
    void mutate(CharImage &input);
    void calcFitness(CharImage &input);
    void GALifeCycle();
    
    void saveBestPopulation();
    
    ofImage getBestCharImage();
    
    int  generation;
    ofImage   targetImage;
    
private:
    
    float calcDiff2Image(ofImage &input1, ofImage &input2);
    
    void  sortPopulation(CharImage *input, int left, int right);
    
    ofxTrueTypeFontUC JapaneseFont;
    HiraganaUtil   kana;
    

    
    CharImage population[NUM_POPULATION];
    CharImage children[NUM_CHILD];
    
    
    
};

#endif /* defined(__HiraganaArt__GAMain__) */
