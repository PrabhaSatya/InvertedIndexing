
#include"skiplist.hpp"
bool *reachedEnd;
int genRandomLevel()
{   
    int v=1;
    double randnum;
    randnum=(double)rand()/(double)RAND_MAX;
    while(randnum<P && v< MAXLEVEL)
    {	v=v+1;
    	randnum=(double)rand()/(double)RAND_MAX;
    }
    return v;
} 


void Skiplist::addToSL(int inputdocid) 
{
    	SLNode *x = head;	
    	SLNode *update[MAXLEVEL + 1];
    	for(int i=0;i<MAXLEVEL+1;i++)
    	    update[i]=NULL;
    	for (int i = level; i >= 0; i--) 
    	{
		while (x->Skips[i] != NULL && x->Skips[i]->docid < inputdocid)
        		x = x->Skips[i];
       		update[i] = x; 
        }
   	 x = x->Skips[0];
    	if(x == NULL || x->docid != inputdocid)
     	{        
        	int grlevel = genRandomLevel();
	    	if (grlevel > level)
         	{	for (int i = level + 1; i <= grlevel; i++)
	 	       update[i] = head;
	 		 level = grlevel;
	 	}
        	x = new SLNode(grlevel, inputdocid);
		for (int i = 0; i <= grlevel; i++) 
		{	x->Skips[i] = update[i]->Skips[i];
	 		 update[i]->Skips[i] = x;
		}	
    	}
}
void Skiplist::printSL() 
{
     SLNode *x = head->Skips[0];
    cout << "startlist"<<endl;
    while (x != NULL)
     {
        cout << x->docid;
        x = x->Skips[0];
        if (x != NULL)
            cout << endl;
    }    
    cout << "endlist"<<endl;
}
int findMaxId(SLNode **tslnodes,int numQWords)
{
	int max;
	int k=0;
	for(int i=0;i<numQWords;i++)
	while(reachedEnd[k])
	{	
		k++;
	}
	max=tslnodes[k]->Skips[0]->docid;
	for(int i=k+1;i<numQWords;i++)
		if((!reachedEnd[i])&&tslnodes[i]->Skips[0]!=NULL)
			{
				if(max<tslnodes[i]->Skips[0]->docid)
					max=tslnodes[i]->Skips[0]->docid;
			}
	return max;
}
void calIntersect(Skiplist **Slists,int numQWords,int numDocs,int *output)
{
	
	int id,level,maxSkip,maxDocId,outputcount=0;
	for(int i=0;i<numDocs;i++)
	output[i]=-1;
	int properQWords=0;
	for(int i=0;i<numQWords;i++)
	if(Slists[i]!=NULL)
	properQWords++;
	if(properQWords==0) 
	{	
		return;
	}
	reachedEnd=new bool[properQWords];
	for(int i=0;i<properQWords;i++)
	reachedEnd[i]=false;
	bool checknull=false,checknotequal=false;
	SLNode *x;
	SLNode ** tslnodes;
	tslnodes=new SLNode*[properQWords];
	for(int i=0;i<properQWords;i++)
	tslnodes[i]=new SLNode();
	int k=0;
	for(int i=0;i<numQWords;i++)
	if(Slists[i]!=NULL)
	{	tslnodes[k]=Slists[i]->head;
		k++;
	}
	k=0;
	maxDocId=findMaxId(tslnodes,properQWords);
	while(checknull==false)
	{		checknull=true;
			for(int i=0;i<properQWords;i++)
			{	
			if((tslnodes[i]->docid)!=maxDocId)
				{	
					checknotequal=true;
					break;
			
				}
			}	
			if(checknotequal==false)
			output[outputcount++]=maxDocId;
			checknotequal=false;
			maxDocId=findMaxId(tslnodes,properQWords);
			for(int i=0;i<properQWords;i++)
			{	
		l1:		level=tslnodes[i]->slevel;
				while(tslnodes[i]->Skips[level]==NULL)
					level--;
				k=level;
				if(k==-1)
					reachedEnd[i]=true;
				while(k>=0)
				{	
					if((k==0) && (tslnodes[i]->Skips[k]==NULL) )
					{	
						reachedEnd[i]=true;
						tslnodes[i]=NULL;
						 break;
						
					}
					while(maxDocId<(tslnodes[i]->Skips[k]->docid)&&(maxDocId>(tslnodes[i]->docid))&&k>=0) 
					{	
							k=k-1;
							if(k==-1) break;
					}
					if(k==-1)
					{	tslnodes[i]=tslnodes[i]->Skips[0];
						if(tslnodes[i]->Skips[0]==NULL)reachedEnd[i]=true;
						 break;
					}
					while((maxDocId>=tslnodes[i]->Skips[k]->docid))
					{	
						if(tslnodes[i]->Skips[k]!=NULL)
						tslnodes[i]=tslnodes[i]->Skips[k];
						goto l1;
						
					}
					if(maxDocId<tslnodes[i]->Skips[k]->docid)
						k=k-1;
					while(tslnodes[i]->Skips[k]==NULL)
						k=k-1;
						
				}
			
			}
			for(int i=0;i<properQWords;i++)
			{	
				if(reachedEnd[i]==false) 
				{	checknull=false;
					break;
				}
				if(i==properQWords-1)
				{
					for(int i=0;i<properQWords;i++)
					{	
						if((tslnodes[i]->docid)!=maxDocId)
						{	
						checknotequal=true;
						break;
				
						}
					}	
					if(checknotequal==false)
						output[outputcount++]=maxDocId;
			
				}
			}
	
	}
}

