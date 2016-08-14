#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <cstring>

using namespace std;
const float P = 0.5;
const int MAXLEVEL = 6;
const int MAXDOCS=21;

int genRandomLevel();

class SLNode
{	
	
	public:int docid;
	int slevel;
	SLNode **Skips;
	SLNode()
	{
	}
	SLNode(int level,int docid) 
    	{
        Skips = new SLNode*[level + 1];
        for(int i=0;i<level+1;i++)
        Skips[i]=NULL;
        
        this->docid = docid;
        this->slevel=level;
    	}
   ~SLNode() 
    {
  //  cout<<"in destructor of Snode"<<endl;
        delete [] Skips;
    //  cout<<"Skips deleted"<<endl;
       
    }
};
struct Skiplist
{
public:    SLNode *head;
    int level;

    Skiplist() {
        head = new SLNode(MAXLEVEL,-1);
        level = 0;
    }
    ~Skiplist() {
   // cout<<"in destructor of Skiplists"<<endl;
        delete head;
            //cout<<"head deleted"<<endl;
       
    }
    
    void printSL() ;
    void addToSL(int docid);
    
};
void calIntersect(Skiplist **Slists,int numQWords,int numDocs,int* output);
int findMaxId(SLNode **tslnodes,int numQWords);
