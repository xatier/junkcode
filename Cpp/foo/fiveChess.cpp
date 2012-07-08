#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include "ioe.h"
#include "board.h"
#include "threat.h"
#include "tsSearch.h"
#include "pnSearch.h"

using namespace std;

int main()
{
    /****** to decide the chess board ******/
    Board brd = Board();
    int cnt=0;
    while(1){
        // read in a char
        char tmp = mygetchar();
        // brd.setMap()
        int rv = brd.set( cnt/brd.size(), cnt%brd.size(), tmp-'0' );
        // rv=return value, error judgement
        if(rv== -1)
            err(EXIT,"character should be %d or %d or %d",EMPTY,BLACK,WHITE);
        if(rv!=tmp-'0')
            err(!EXIT,"map[%d][%d] wasn't changed.", cnt/brd.size(), cnt%brd.size());

        cnt++;
        if(cnt >= brd.size()*brd.size()) break;
    }

    /****** to decide who's next ******/
    int turn;
    scanf("%d",&turn);
    if(turn!=BLACK && turn!=WHITE)
        err(EXIT,"turn should be %d or %d",BLACK,WHITE);

    /****** test ******/
    brd.printBoard();
    printf("[[ turn: %d - %s ]]\n\n", turn, (turn==WHITE) ? "WHITE" : "BLACK" );
    
    /****** run pn-search ******/
    pnsNode *root = pnsNode(brd, turn);
    proofNumberSearchTerminal(root);
    // most-proving-node
    pnsNode *mpn = root;
    // (pn==0 || dn==0) means the result has been found
    while( root->pn!=0 && root->dn!=0 ){
        mpn = proofNumberSearch(mpn);
        if( mpn==NULL ) mpn = root;
    }
    // print result
    printf("===== %s =====\n", (pn==0)? "WIN" : "LOSE");

    /****** run ts-search ******/
    //int winValue = threatSpaceSearchEntry(brd, turn);
    //if(winValue==WIN) printf("====== WIN =======\n");
    //else printf("====== LOSE ======\n");

    return 0;
}
