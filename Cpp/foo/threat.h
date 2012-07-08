#ifndef MY_THREAT
#define MY_THREAT

#include <vector>
#include <cstdarg>
#include "board.h"

// *****************************************************
// threat type
#define Five 59

#define StrF 49     // straight four (empty at two sides)
#define Four 42     // with one side enemy and another empty (1 cost square)
#define BrkF 41     // broken four (1 cost square)

#define StrT 32     // stright three (2 kinds- 2 or 3 cost squares)
#define BrkT 31     // broken three (3 cost squares)
// *****************************************************

char* getTypeName(int no){
    switch(no){
        case Five: return (char*)"Five";
        case StrF: return (char*)"StrF";
        case Four: return (char*)"Four";
        case BrkF: return (char*)"BrkF";
        case StrT: return (char*)"StrT";
        case BrkT: return (char*)"BrkT";
        default: return NULL;
    }
}

class BasicThreat {
    public:
        BasicThreat(unsigned short int m, unsigned short int s, int t, int cn, ...){
            mask=m;
            seqb=s;
            type=t;
            costNum=cn;

            va_list argList;
            va_start(argList, cn);
            for(int i=0; i<costNum; i++) cost[i]=va_arg(argList,int);
            va_end(argList);
        }

        int type;
        unsigned short int mask;
        unsigned short int seqb;  // binary sequence

        int costNum;
        int cost[3];
};

class Threat {
    public:
        // gain square (x,y)
        // direction (dx,dy)
        // BasicThreatList[no]
        Threat(int x,int y,int dx,int dy,BasicThreat basicThreat){
            gain = x & 0b00001111 ;
            gain <<= 4 ;
            gain += y & 0b00001111 ;
            
            costNum = basicThreat.costNum;
            for(int i=0; i<costNum; i++){
                int costX = x + basicThreat.cost[i]*dx ;
                int costY = y + basicThreat.cost[i]*dy ;
                cost[i] = costX & 0b00001111 ;
                cost[i] <<= 4 ;
                cost[i] += costY & 0b00001111 ;
            }

            type = basicThreat.type;
        }

        int type;
        int costNum;
        int getGainX(){ return int((gain & 0b11110000)>>4); }
        int getGainY(){ return int(gain & 0b00001111); }
        int getCostX(int no){ return int((cost[no] & 0b11110000)>>4); }
        int getCostY(int no){ return int(cost[no] & 0b00001111); }

        void printThreat(){
            printf("%s\t",getTypeName(type) );
            printf("%02X\t",gain);
            for(int i=0; i<costNum; i++) printf("%02X,",cost[i]);
            if(type==Five || type==StrF) printf("\t<= WIN");
            printf("\n");
        }
    private:
        unsigned char gain;
        unsigned char cost[3];
};

// x: don't care
// M: the gain square, always in the middle
// I: the stone that is the the same color with M
// U: the enemy
#define BasicThreatListLen 44
BasicThreat BasicThreatList[BasicThreatListLen] = {
    // Five: <ooooo>
    BasicThreat( // x x x x I I I I    x x x x M I I I I (x
            0b0000000011111111,
            0b0000000011111111,
            Five,0),
    BasicThreat( // x x x I I I I x    x x x I M I I I x:q
            0b0000001111111100,
            0b0000001111111100,
            Five,0),
    BasicThreat( // x x I I I I x x    x x I I M I I x x
            0b0000111111110000,
            0b0000111111110000,
            Five,0),
    BasicThreat( // x I I I I x x x    x I I I M I x x x
            0b0011111111000000,
            0b0011111111000000,
            Five,0),
    BasicThreat( // I I I I x x x x    I I I I M x x x x
            0b1111111100000000,
            0b1111111100000000,
            Five,0),

    // Straight Four: <_oooo_>
    BasicThreat( // x x x _ I I I _    x x x _ M I I I _
            0b0000001111111111,
            0b0000001011111110,
            StrF,0),
    BasicThreat( // x x _ I I I _ x    x x _ I M I I _ x
            0b0000111111111100,
            0b0000101111111000,
            StrF,0),
    BasicThreat( // x _ I I I _ x x    x _ I I M I _ x x
            0b0011111111110000,
            0b0010111111100000,
            StrF,0),
    BasicThreat( // _ I I I _ x x x    _ I I I M _ x x x
            0b1111111111000000,
            0b1011111110000000,
            StrF,0),

    // Four: <_oooox>
    BasicThreat( // x x x _ I I I U    x x x _ M I I I U
            0b0000001111111111,
            0b0000001011111101,
            Four,1,-1),
    BasicThreat( // x x _ I I I U x    x x _ I M I I U x
            0b0000111111111100,
            0b0000101111110100,
            Four,1,-2),
    BasicThreat( // x _ I I I U x x    x _ I I M I U x x
            0b0011111111110000,
            0b0010111111010000,
            Four,1,-3),
    BasicThreat( // _ I I I U x x x    _ I I I M U x x x
            0b1111111111000000,
            0b1011111101000000,
            Four,1,-4),
    // Four: or <xoooo_>
    BasicThreat( // x x x U I I I _    x x x U M I I I _
            0b0000001111111111,
            0b0000000111111110,
            Four,1,4),
    BasicThreat( // x x U I I I _ x    x x U I M I I _ x
            0b0000111111111100,
            0b0000011111111000,
            Four,1,3),
    BasicThreat( // x U I I I _ x x    x U I I M I _ x x
            0b0011111111110000,
            0b0001111111100000,
            Four,1,2),
    BasicThreat( // U I I I _ x x x    U I I I M _ x x x
            0b1111111111000000,
            0b0111111110000000,
            Four,1,1),

    // Broken Four: <ooo_o>
    BasicThreat( // x x x x I I _ I    x x x x M I I _ I
            0b0000000011111111,
            0b0000000011111011,
            BrkF,1,3),
    BasicThreat( // x x x I I _ I x    x x x I M I _ I x
            0b0000001111111100,
            0b0000001111101100,
            BrkF,1,2),
    BasicThreat( // x x I I _ I x x    x x I I M _ I x x
            0b0000111111110000,
            0b0000111110110000,
            BrkF,1,1),
    BasicThreat( // I I I _ x x x x    I I I _ M x x x x
            0b1111111100000000,
            0b1111111000000000,
            BrkF,1,-1),
    // Broken Four: <oo_oo>
    BasicThreat( // x x x x I _ I I    x x x x M I _ I I
            0b0000000011111111,
            0b0000000011101111,
            BrkF,1,2),
    BasicThreat( // x x x I _ I I x    x x x I M _ I I x
            0b0000001111111100,
            0b0000001110111100,
            BrkF,1,1),
    BasicThreat( // x I I _ I x x x    x I I _ M I x x x
            0b0011111111000000,
            0b0011111011000000,
            BrkF,1,-1),
    BasicThreat( // I I _ I x x x x    I I _ I M x x x x
            0b1111111100000000,
            0b1111101100000000,
            BrkF,1,-2),
    // Broken Four: <o_ooo>
    BasicThreat( // x x x x _ I I I    x x x x M _ I I I
            0b0000000011111111,
            0b0000000010111111,
            BrkF,1,1),
    BasicThreat( // x x I _ I I x x    x x I _ M I I x x
            0b0000111111110000,
            0b0000111011110000,
            BrkF,1,-1),
    BasicThreat( // x I _ I I x x x    x I _ I M I x x x
            0b0011111111000000,
            0b0011101111000000,
            BrkF,1,-2),
    BasicThreat( // I _ I I x x x x    I _ I I M x x x x
            0b1111111100000000,
            0b1110111100000000,
            BrkF,1,-3),

    // Straight Three: <__ooo__>
    BasicThreat( // x x _ _ I I _ _    x x _ _ M I I _ _
            0b0000111111111111,
            0b0000101011111010,
            StrT,2,-1,3),
    BasicThreat( // x _ _ I I _ _ x    x _ _ I M I _ _ x
            0b0011111111111100,
            0b0010101111101000,
            StrT,2,-2,2),
    BasicThreat( // _ _ I I _ _ x x    _ _ I I M _ _ x x
            0b1111111111110000,
            0b1010111110100000,
            StrT,2,-3,1),
    // Straight Three: <__ooo_x>
    BasicThreat( // x x _ _ I I _ U    x x _ _ M I I _ U
            0b0000111111111111,
            0b0000101011111001,
            StrT,3,-1,3,-2),
    BasicThreat( // x _ _ I I _ U x    x _ _ I M I _ U x
            0b0011111111111100,
            0b0010101111100100,
            StrT,3,-2,2,-3),
    BasicThreat( // _ _ I I _ U x x    _ _ I I M _ U x x
            0b1111111111110000,
            0b1010111110010000,
            StrT,3,-3,1,-4),
    // Straight Three: <x_ooo__>
    BasicThreat( // x x U _ I I _ _    x x U _ M I I _ _
            0b0000111111111111,
            0b0000011011111010,
            StrT,3,3,-1,4),
    BasicThreat( // x U _ I I _ _ x    x U _ I M I _ _ x
            0b0011111111111100,
            0b0001101111101000,
            StrT,3,2,-2,3),
    BasicThreat( // U _ I I _ _ x x    U _ I I M _ _ x x
            0b1111111111110000,
            0b0110111110100000,
            StrT,3,1,-3,2),

    // Broken Three: <_oo_o_>
    BasicThreat( // x x x _ I _ I _    x x x _ M I _ I _
            0b0000001111111111,
            0b0000001011101110,
            BrkT,3,2,4,-1),
    BasicThreat( // x x _ I _ I _ x    x x _ I M _ I _ x
            0b0000111111111100,
            0b0000101110111000,
            BrkT,3,1,3,-2),
    BasicThreat( // _ I I _ _ x x x    _ I I _ M _ x x x
            0b1111111111000000,
            0b1011111010000000,
            BrkT,3,-1,1,-4),
    // Broken Three: <_o_oo_>
    BasicThreat( // x x x _ _ I I _    x x x _ M _ I I _
            0b0000001111111111,
            0b0000001010111110,
            BrkT,3,1,4,-1),
    BasicThreat( // x _ I _ I _ x x    x _ I _ M I _ x x
            0b0011111111110000,
            0b0010111011100000,
            BrkT,3,-1,2,-3),
    BasicThreat( // _ I _ I _ x x x    _ I _ I M _ x x x
            0b1111111111000000,
            0b1011101110000000,
            BrkT,3,-2,1,-4),
};
#endif
