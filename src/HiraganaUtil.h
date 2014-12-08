//
//  Hiragana.h
//  HiraganaArt
//
//  Created by 加藤亮太 on 2014/12/07.
//
//

#ifndef HiraganaArt_Hiragana_h
#define HiraganaArt_Hiragana_h

class HiraganaUtil{

public:
    
    HiraganaUtil(){
    
        kana = "あいうえおかきくけこさしすせそたちつてとなにぬねのはひふへほまみむめもやゆよらりるれろわをん";
        
        int charSize;
        
        
        for(int i=0;i<kana.size();i += charSize){
            
            HiraganaIdx.push_back(i);
            unsigned char h = kana[i];
            if(h < 0x80)
                charSize = 1;
            else if(h < 0xE0)
                charSize = 2;
            else if(h < 0xF0)
                charSize = 3;
            else
                charSize = 4;
            
        }
        
        
    }

    int getNumHiragana(){
    
        return kana.size();
        
    }
    
    string getKana(int idx){
    
        int charSize;
        unsigned char h = kana[idx];
        if(h < 0x80)
            charSize = 1;
        else if(h < 0xE0)
            charSize = 2;
        else if(h < 0xF0)
            charSize = 3;
        else
            charSize = 4;
        
        return kana.substr(idx, charSize);
        
    }
    
    string getRandomKana(){
    
        int idx = HiraganaIdx[ofRandom(HiraganaIdx.size())];
        unsigned char h = kana[idx];
        
        int charSize;
        if(h < 0x80)
            charSize = 1;
        else if(h < 0xE0)
            charSize = 2;
        else if(h < 0xF0)
            charSize = 3;
        else
            charSize = 4;
        
        return kana.substr(idx, charSize);
        
    }
    
    
    
    vector<int> HiraganaIdx;
    
    
private:
    string kana;
    
};

#endif
