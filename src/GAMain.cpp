//
//  GAMain.cpp
//  HiraganaArt
//
//  Created by 加藤亮太 on 2014/12/06.
//
//

#include "GAMain.h"

void GAMain::setup(){

    generation = 0;
    targetImage.loadImage("../../../../../common/image/Vermeer.jpg");
    
    
    // if target image does not have alpha channel, add alpha channel by usinf FBO.
    if(targetImage.getPixelsRef().getNumChannels() != 4){
    
        // draw target image to FBO.
        ofFbo tmpFbo;
        tmpFbo.allocate(targetImage.width, targetImage.height);
        tmpFbo.begin();
        
        targetImage.draw(0, 0);
        
        tmpFbo.end();
        
        
        // load target image from FBO.
        ofPixels pixels;
        tmpFbo.readToPixels(pixels);
        
        targetImage.clear();
        
        targetImage.setFromPixels(pixels);
        
        
    }
    
    JapaneseFont.loadFont("../../../../../common/font/ヒラギノ角ゴ Pro W3.otf", 100);
    
    for(int i=0;i<NUM_POPULATION;i++){
    
        population[i].setup(JapaneseFont, kana);
        population[i].setFbo();
        
        ofImage popImage = population[i].getCharImage();
        population[i].setFitness(calcDiff2Image(popImage, targetImage));
        
        
    }
    
    sortPopulation(population, 0, NUM_POPULATION-1);
    
    ofImage savedImage = population[0].getCharImage();
    savedImage.saveImage("charImages/" + ofToString(generation) + ".png");
    


    
    /*  test */

    
    
    
}

void GAMain::GALifeCycle(){

    if(generation < MAX_GENERAtION){
    
        for(int i=0;i<DISPLAY_TIME;i++){
   
            CharImage parent1, parent2;
            
            parent1 = population[0];
            int parent2Idx  = (int)ofRandom(1, NUM_POPULATION);
            parent2 = population[parent2Idx];
            
            for(int j=0;j<NUM_CHILD;j++){
                
                crossover(children[j], parent1, parent2);
                
                mutate(children[j]);
                
                calcFitness(children[j]);
                
            }
            sortPopulation(children, 0, NUM_CHILD-1);
            
            if(children[0].fitness > parent1.fitness){
                population[0] = children[0];
            
                ofImage savedImage = population[0].getCharImage();
                savedImage.saveImage("charImages/" + ofToString(generation) + ".png");
                

            }
            else if(children[0].fitness > parent2.fitness)
                population[parent2Idx] = children[0];
            
            if(children[1].fitness > population[parent2Idx].fitness)
                population[parent2Idx] = children[1];
            
            sortPopulation(population, 0, NUM_POPULATION-1);
            
            generation ++;
            if(generation > MAX_GENERAtION)
                break;
            
            cout<<"generation: "<<generation;
            cout<<"   fitness: "<<population[0].fitness<<endl;
        }
        
        ofImage savedImage = population[0].getCharImage();
        savedImage.saveImage("charImages/" + ofToString(generation) + ".png");
        

    
    }
    
    
}

void GAMain::crossover(CharImage &target, CharImage &input1, CharImage &input2){

    target = input1;
    
    
    for(int i=0;i<NUM_CHARACTER;i++){
    
        if(ofRandom(1.0) < CROSSOVER_RATE){
        
            target.charSet[i]   = input2.charSet[i];
            target.location[i]  = input2.location[i];
            target.charColor[i] = input2.charColor[i];
            target.fontScale[i] = input2.fontScale[i];
        }
        
    }
    
    target.setFbo();
    
}

void GAMain::mutate(CharImage &input){

    
    for(int i=0;i<NUM_CHARACTER;i++){
    
        if(ofRandom(1.0) < MUTATION_RATE){
            
            input.charSet[i]   = kana.getRandomKana();
            input.location[i]  = ofPoint(ofRandom(WIDTH), ofRandom(HEIGHT));
            input.charColor[i] = ofColor(ofRandom(255), ofRandom(255), ofRandom(255));
            input.fontScale[i] = ofRandom(1.0);
            
        }
        
        
    }
    
    input.setFbo();
    
}


void GAMain::calcFitness(CharImage &input){

    ofImage inputImage = input.getCharImage();
    float f = calcDiff2Image(inputImage, targetImage);
    
    input.fitness = f;

}

ofImage GAMain::getBestCharImage(){

    ofImage retVal = population[0].getCharImage();
    
    return retVal;
    
}

// TODO: save best poplation
void GAMain::saveBestPopulation(){

    FILE *fp;
    string dataPath = ofToDataPath("bestPop.txt");
    
    fp = fopen(dataPath.c_str(), "wt");
    
}

void GAMain::sortPopulation(CharImage *input, int left, int right){

    int i, j;
    float pivot;
    i = left;
    j = right;
    
    pivot = input[(left+right)/2].getFitness();
    while(1){
    
        while(input[i].fitness > pivot)
            i++;
        while(pivot > input[j].fitness)
            j--;
        
        if(i>=j)
            break;
        
        CharImage tmp;
        tmp = input[i];
        input[i] = input[j];
        input[j] = tmp;
        
        i++;
        j--;
        
    }
    
    if(left < i-1)
        sortPopulation(input, left, i-1);
    if(j+1 < right)
        sortPopulation(input, j+1, right);
    
}


float GAMain::calcDiff2Image(ofImage &input1, ofImage &input2){

    if(input1.getPixelsRef().getNumChannels() != input2.getPixelsRef().getNumChannels() ){
    
        cout<<" input the same channel images. "<<endl;
        
        return 0.0;
        
    }
    
    float diff = 0.;
    
    unsigned char *pixels1 = input1.getPixels();
    unsigned char *pixels2 = input2.getPixels();
    
    int width   = input1.getWidth();
    int height  = input1.getHeight();
    int channels= input1.getPixelsRef().getNumChannels();
    int sumDiff = 0;
    
    for(int y=0;y<height;y++){
    
        for(int x=0;x<width;x++){
        
            for(int c=0;c<channels;c++){
            
                
                if(c != 3) // ignore alpha channel.
                    sumDiff += abs( (int)pixels1[(y*width + x)*channels + c ] - (int)pixels2[(y*width + x)*channels + c] );
                
            }
        }
        
    }
    
    int maxDiff = width*height*channels*255;
    
    diff = (maxDiff - sumDiff) / (float)maxDiff * 100;
    
    return diff;
    
}