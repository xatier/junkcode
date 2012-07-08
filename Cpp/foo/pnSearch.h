#ifndef MY_PNS
#define MY_PNS

#include <vector>
#include "board.h"

// the infinity value of pn-search
#define PNS_INFINITY 1000000

struct pnsNode {
    Board brd;
    int turn;
    int pn;
    int dn;
    vector< pair<int,int> > childrenList;
    vector<pnsNode*> children;

    pnsNode(Board b, int t){
        brd = b;
        turn = t;
        pn = 1;
        dn = 1; 
    }

    pnsNode(pnsNode parent, const pair<int,int> coord){
        brd = parent.brd;
        turn = opposite(parent.turn);
        brd.set(coord.first, coord.second, turn);
        pn = 1;
        dn = 1; 
    }
} ;

void findChildrenList(pnsNode *n)
{
    for(int i=0; i< n->brd.size(); i++)
        for(int j=0; j< n->brd.size(); j++)
            if(n->brd.get(i, j)==EMPTY) n->childrenList.push_back(make_pair(i,j));
}

// for temp-terminal node (whose childrenList[] is empty) 
// return value is the most-proving-node 
// ( return NULL if not in current tree )
pnsNode* proofNumberSearchTerminal(pnsNode *node)
{
    // run evaluation function
    if(threatSpaceSearchEntry(node->brd, node->turn) == WIN){
        // find WIN => this node is a real-terminal node
        if(node->turn == BLACK){ 
            node->pn = 0;
            node->dn = PNS_INFINITY;
        }else{
            node->pn = PNS_INFINITY;
            node->dn = 0;
        }
        return NULL;
    }else{
        // expand this node's children
        findChildrenList(node);
        if(node->turn == BLACK){ 
            /****** max node ******/
            // pn = min( all child.pn )
            node->pn = 1;
            // dn = sum( all child.dn )
            node->dn = node->childrenList.size();
            // if dn == 1, 
            // then node->dn is not changed
            // then node is still the most-proving-node
            if( node->dn==1 ) return node;
        }else{
            /****** min node ******/
            // pn = sum( all child.pn )
            node->pn = node->childrenList.size();
            // dn = min( all child.dn )
            node->dn = 1;
            // if pn == 1, 
            // then node->pn is not changed
            // then node is still the most-proving-node
            if( node->pn==1 ) return node;
        }
        // the pn or dn has changed, node is no longer the most-proving-node
        return NULL;
    }
}

// return value is the most-proving-node 
// ( return NULL if not in current tree )
pnsNode* proofNumberSearch(pnsNode *node)
{
    pnsNode *successor = NULL;
    if(node->turn==BLACK){
        // in max node, the child who has min pn is the successor
        for(int i=0; i<node->children.size(); i++)
            if(node->children[i]->pn == node->pn){
                successor = node->children[i];
                break;
            }
    }else if(node->turn==WHITE){
        // in min node, the child who has min dn is the successor
        for(int i=0; i<node->children.size(); i++)
            if(node->children[i]->dn == node->dn){
                successor = node->children[i];
                break;
            }
    }else err(EXIT, "pnsNode turn wrong value: should be BLACK or WHITE \n");

    // most-proving-node
    pnsNode *mpn;
    // pn & dn before doing search
    int pnBefore, dnBefore;
    // search ( terminal nodes OR internal nodes )
    if(successor==NULL){
        /****** successor is a terminal node (pn==1, dn==1) ******/
        // malloc just when the node is the best proving node and is to be searched (now)
        successor = new pnsNode(*node, *(node->childrenList[node->children.size()]) );
        node.children.push_back( successor );
        //     search (find winVAlue OR expand children list)
        pnBefore = successor->pn;
        dnBefore = successor->dn;
        mpn = proofNumberSearchTerminal( successor, opposite(node->turn) );
    }else{
        // successor is an internal node
        pnBefore = successor->pn;
        dnBefore = successor->dn;
        mpn = proofNumberSearch(successor, opposite(node->turn));
    }

    // (mpn != NULL) means mpn is node.children & node.pn/dn need not changed
    if(mpn != NULL) return mpn;

    // flag if pn & dn is different
    int flag=0;
    // update pn & dn
    if( pnBefore != successor->pn ){
        flag = 1;
        if(turn == BLACK){ 
            // max node, pn = min( all child.pn )
            if( node->childrenList.size() > node->children.size()){
                // there exists terminal node (unmalloc node)
                // terminal node's pn is always 1
                node->pn = 1;
            }else {
                // find the min pn of all children
                for( int i=0, node->pn = successor->pn;
                        i < node.children.size();
                        i++)
                    if(node->children[i]->pn < node->pn)
                        node->pn = node->children[i]->pn;
            }
        }else{
            // min node, pn = sum( all child.pn )
            node->pn = -pnBefore + successor->pn;
        }
    }
    if( dnBefore != successor->dn ){
        flag = 1;
        if(turn == BLACK){ 
            // max node, dn = sum( all child.dn )
            node->dn = -dnBefore + successor->dn;
        }else{
            // min node, dn = min( all child.dn )
            if( node->childrenList.size() > node->children.size()){
                // there exists terminal node (unmalloc node)
                // terminal node's dn is always 1
                node->dn = 1;
            }else {
                // find the min dn of all children
                for( int i=0, node->dn = successor->dn;
                        i < node.children.size();
                        i++)
                    if(node->children[i]->dn < node->dn)
                        node->dn = node->children[i]->dn;
            }
        }
    }
    // successor's pn&dn is not changed => mpn is still successor
    if( flag == 0 ) return successor;
    // mpn is changed, not in current tree
    else return NULL;
}


#endif
