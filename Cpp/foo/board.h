#ifndef MY_BOARD
#define MY_BOARD

#include <vector>

#define SIZE_DEFAULT 15

#define EMPTY 0
#define BLACK 1
#define WHITE 2
#define BOUND 3

#define WIN 1
#define NOWIN 0

using namespace std;

inline int opposite(int turn)
{
    if(turn==WHITE)return BLACK;
    else if(turn==BLACK)return WHITE;
    else err(EXIT,"wrong use of opposite");
}

class Board {
    public:
        Board(){
            boardSize = SIZE_DEFAULT;
            twoDimArr = vector< vector<unsigned char> >(boardSize,vector<unsigned char>(boardSize,EMPTY));
        }
        Board(int size){
            boardSize=size;
            twoDimArr = vector< vector<unsigned char> >(boardSize,vector<unsigned char>(boardSize,EMPTY));
        }
        Board(vector< vector<unsigned char> > arr){
            boardSize=arr.size();
            twoDimArr=arr;
        }

        int size(){ 
            return boardSize;
        }

        unsigned char get(int i,int j){
            if(i<0||i>=boardSize||j<0||j>=boardSize) return BOUND;
            else return twoDimArr[i][j];
        }

        unsigned char set(int i,int j,unsigned char value){
            if(value!=EMPTY && value!=BLACK && value!=WHITE) return -1;
            else if(i<0||i>=boardSize||j<0||j>=boardSize) return BOUND;
            else{
                twoDimArr[i][j]=value;
                return twoDimArr[i][j];
            }
        }

        void printBoard(){
            int i,j;
            for(printf("  "), j=0; j<boardSize; j++)
                printf("%X ",j);
            printf("\n");
            for(i=0; i<boardSize; i++){
                printf("%X ",i);
                for(j=0; j<boardSize; j++)
                    if( get(i,j)==EMPTY ) printf("  ");
                    else printf( "%d ", get(i,j) );
                printf("\n");
            }
        }

    private:

        int boardSize;
        vector< vector<unsigned char> > twoDimArr;
};

#endif
