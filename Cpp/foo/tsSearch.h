#ifndef MY_TSS
#define MY_TSS

#include <algorithm>
#include <vector>
#include "ioe.h"
#include "board.h"
#include "threat.h"


void printLine(vector <unsigned char> queue)
{
    printf("[[");

    for(vector<unsigned char>::iterator it = queue.begin();
            it != queue.end();
            it++)
        switch(*it){
            case EMPTY: printf("_"); break;
            case WHITE: printf("O"); break;
            case BLACK: printf("X"); break;
            case BOUND: printf("#"); break;
        }

    printf("]]\n");
}

// Finds a threat who
//   has (x,y), which is an empty square, to be a gain square, and
//   has some point (restX,restY) to be its rest square (done by using [restMask]).
// And to save time, it should only search for the specified direction
//   (the direction - (x,y) to (restX,restY)) (done by using [dx],[dy])
Threat* findThreat(Board brd,int turn,int x,int y,int dx,int dy,unsigned short int restMask)
{
    if( brd.get(x,y) != EMPTY ) return NULL;

#ifdef RECTHREAT
    // to record the stones in the whole straight line
    vector <unsigned char> line;
#endif

    // gets the value of the line, and store them into 16 bits
    // transform board value into a 2-byte short int
    unsigned short int decodeBytes;
    int cnt, tmpx, tmpy;
    for(cnt=9, tmpx=x-4*dx, tmpy=y-4*dy;   cnt>0;   cnt--, tmpx+=dx, tmpy+=dy){
        if(tmpx == x && tmpy == y){
#ifdef RECTHREAT
            // imagine brd[x][y] (original empty) is being put on a 'turn' stone
            line.push_back(turn);
#endif
            continue;
        }
        unsigned char square = brd.get(tmpx,tmpy);
        unsigned char decodeBits;
#ifdef RECTHREAT
        line.push_back(square);
#endif
        if( square==BOUND || square==opposite(turn) )
            decodeBits = 0b01;
        else if ( square==EMPTY )
            decodeBits = 0b10;
        else if ( square==turn )
            decodeBits = 0b11;
        else err (EXIT, "board value error: at (%d,%d)", tmpx, tmpy);
        // add decodeBits(2-bit) into the tail of decodeBytes(total 2-byte)
        decodeBytes <<= 2;
        decodeBytes += decodeBits ;
    }

    Threat *ans = NULL;
    for(int i=0; i<BasicThreatListLen; i++)
        if(     ( (decodeBytes & restMask) != 0 ) &&
                ( (decodeBytes & BasicThreatList[i].mask) == BasicThreatList[i].seqb )    ){
            ans = new Threat(x,y,dx,dy,BasicThreatList[i]);
#ifdef RECTHREAT
            printLine(line);
#endif
            break;
        }
#ifdef RECTHREAT
    line.clear();
#endif
    return ans;
}

int directions[4][2] = {{1,1},{1,0},{1,-1},{0,1}} ;
Threat* findThreat(Board brd,int turn,int x,int y)
{
    Threat *ans = NULL;
    for(int dir=0; dir<4 ; dir++){
        Threat *t = findThreat(brd,turn,x,y,directions[dir][0],directions[dir][1],0b11111111);
        if(t == NULL)
            continue;
        else if(ans == NULL || t->type > ans->type){
            delete ans;
            ans = t;
        }else delete t;
    }
    return ans;
}

// int x, y : last threat's gain square -> need to be one of the current threat's rest squares
int threatSpaceSearch(Board brd, int turn, int x, int y, int depth)
{
    /*************************************************************************
     * the threat list
     *************************************************************************/
    vector< Threat* > threatList = vector< Threat* >();

    /*************************************************************************
     * find all the possible threats that contains (x,y) as its rest square
     *************************************************************************/
    // four directions: 0(horizontal),45,90(vertical),135 degrees
    for(int dir=0; dir<4; dir++){
        int dx=directions[dir][0], dy=directions[dir][1];
        // if (tmpx,tmpy) is EMPTY then it is the candidate gain square of the current threat
        // ( EMPTY is examined in findThreat() not here )
        int cnt, tmpx, tmpy;
        // the mask comes from
        //   the relative place of 
        //     the specified rest square and the candidate gain square
        // which is used to examine
        //   whether the candidate threat type contains the specified rest square
        unsigned short int restSquareMask = 0b0000000000000011;
        for(cnt=9, tmpx=x-4*dx, tmpy=y-4*dy;   cnt>0;   cnt--, tmpx+=dx, tmpy+=dy){
            if(tmpx == x && tmpy == y) continue;
            Threat *t = findThreat(brd, turn, tmpx, tmpy, dx, dy, restSquareMask);
            if(t==NULL) continue; // (tmpx,tmpy) is not empty | no threat with (gain) & (rest) is found
            else if(t->type==Five || t->type==StrF){
                for(int i=0;i<depth;i++)printf(" ");
                t->printThreat();
                for(int i=0; i<threatList.size(); i++) free(threatList[i]);
                return WIN;
            }else threatList.push_back(t);
            restSquareMask <<=2;
        }
    }

    /*************************************************************************
     * search all the threats down
     *************************************************************************/
    int winValue;
    for(int no=0; no<threatList.size(); no++){
        Threat *t = threatList[no];
        /*******************************   test   ******************************/
        for(int i=0;i<depth;i++)printf(" ");
        t->printThreat();
        /********   start to search down all possible threat sequence   ********/
        // preset
        brd.set(t->getGainX(), t->getGainY(), turn);
        for(int i=0;i<t->costNum;i++) brd.set(t->getCostX(i), t->getCostY(i), opposite(turn));
        // search
        winValue = threatSpaceSearch(brd, turn, t->getGainX(), t->getGainY(), depth+1);
        // reset
        brd.set(t->getGainX(), t->getGainY(), EMPTY);
        for(int i=0;i<t->costNum;i++) brd.set(t->getCostX(i), t->getCostY(i), EMPTY);
    }

    for(int i=0; i<threatList.size(); i++) free(threatList[i]);
    if( winValue == WIN ) return WIN;
    else return NOWIN;
}

int threatSpaceSearchEntry(Board brd, int turn)
{
    int winValue = NOWIN;
    for(int i=0; i < brd.size(); i++)
        for(int j=0; j < brd.size(); j++){
            Threat *t = findThreat(brd, turn, i, j);

            if(t==NULL)
                continue;
            else if(t->type==Five || t->type==StrF){
                // if the threat is already a winning threat, then don't search down
                t->printThreat();
                winValue = WIN;
            }else{
                t->printThreat();
                // start to search down all possible threat sequence
                // preset
                brd.set(t->getGainX(), t->getGainY(), turn);
                for(int i=0;i<t->costNum;i++) brd.set(t->getCostX(i), t->getCostY(i), opposite(turn));
                // search
                winValue = threatSpaceSearch(brd, turn, t->getGainX(), t->getGainY(), 1); //depth==1
                // reset
                brd.set(t->getGainX(), t->getGainY(), EMPTY);
                for(int i=0;i<t->costNum;i++) brd.set(t->getCostX(i), t->getCostY(i), EMPTY);
            }

            delete t;
            //if( winValue == WIN ) return winValue;
        }
    return winValue;
}

#endif
