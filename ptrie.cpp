#include<iostream>
#include<vector>
#include<cstring>
#include<sstream>
#include "ptrie.h"
int  PTrienode::findCharsMatched(char *inputword)
{	
	int maxMatchLength,numCharsMatched=0;
	maxMatchLength=getContentLength(nodecontent)<=getContentLength(inputword)?getContentLength(nodecontent):getContentLength(inputword);
	for(int i=0;i<maxMatchLength;i++)
	{	if(nodecontent[i]!=inputword[i])
	 	return numCharsMatched;
	 	numCharsMatched=numCharsMatched+1;
	 }
	 return numCharsMatched;
}
void  PTrienode::appendChild(PTrienode* newnode)
{
	children.push_back(newnode);
}


void PTrie::addWord(char* word,PTrienode *startnode,int docid)
{
	
	
	char *remainingchars=NULL;
	int i=0,j=0;
	PTrienode *currentnode;
	currentnode=startnode;
	PTrienode* currentchild=NULL;
	if(currentnode->getContentLength(word)==0)
	{	
		
	
		 currentnode->setWordFlag();
		if(currentnode->SL==NULL)
		currentnode->SL=new Skiplist();
		currentnode->SL->addToSL(docid);
		return;
	}
	
	int numChilds=(int)currentnode->children.size();
	
		int numCharsMatched=-1;
	if(numChilds==0)
	{
			PTrienode* childnode= new PTrienode(word,true);
		 	childnode->SL->addToSL(docid);
		 	currentnode->appendChild(childnode);
		 
		 	return ;
	
	
	}

	if(numChilds>0)
	{
	
		for(int k=0;k<numChilds;k++)
		{	currentchild=currentnode->children.at(k);
			numCharsMatched=currentchild->findCharsMatched(word);
			if(numCharsMatched>0)
			break;
		}
		int maxMatchLength;
		maxMatchLength=getContentLength(word)<=getContentLength(currentchild->nodecontent)?getContentLength(word):getContentLength(currentchild->nodecontent);

		if(numCharsMatched==0)
		{
			PTrienode* childnode= new PTrienode(word,true);
		 	childnode->SL->addToSL(docid);
		 	currentnode->appendChild(childnode);
		 	
		 	return ;
		}
		if(numCharsMatched<maxMatchLength)
		{	
		
				j=numCharsMatched;
				i=0;
				char * rword;
				rword=new char[(getContentLength(currentchild->nodecontent)-numCharsMatched)+1];
				while(currentchild->nodecontent[j]!='\0')
				{	rword[i]=currentchild->nodecontent[j];
					i++;
					j++;
				}
				rword[i]='\0';
				currentchild->wordflag=false;
				PTrienode* rchildnode= new PTrienode(rword,true);
				rchildnode->SL=currentchild->SL;
		
				currentchild->SL=NULL;
				
				int childcount=(int)currentchild->children.size();
				
				if(childcount>0)
				{
				
				rchildnode->children=currentchild->children;
				 currentchild->children.clear();

				}
				
				
				currentchild->appendChild(rchildnode);
				
		 		delete currentchild->nodecontent;
		 		currentchild->nodecontent=NULL;
		 		currentchild->nodecontent=new char[numCharsMatched+1];
				
				for( i=0;i< numCharsMatched;i++)
				currentchild->nodecontent[i]=word[i];
				currentchild->nodecontent[i]='\0';
				j=numCharsMatched;
				i=0;
				char *tempword;
				tempword=new char[getContentLength(word)-numCharsMatched+1];
				while(word[j]!='\0')
				{	
					
					tempword[i]=word[j];
					i++;
					j++;
					
					
				}
				tempword[i]='\0';

				PTrienode* wchildnode= new PTrienode(tempword,true);
				wchildnode->SL->addToSL(docid);
				currentchild->appendChild(wchildnode);
				return;
				
			}
			if(numCharsMatched==maxMatchLength)
				{
					if(maxMatchLength==getContentLength(word))
					{	if(getContentLength(word)==getContentLength(currentchild->nodecontent))
						{	currentchild->setWordFlag();
						
							if(currentchild->SL==NULL)
							{	
								currentchild->SL=new Skiplist();
							}
							
							currentchild->SL->addToSL(docid);
							return;
						
						
						}
						char *tempword;
						tempword=new char[getContentLength(currentchild->nodecontent)-numCharsMatched+1];
						j=numCharsMatched;i=0;
						while(currentchild->nodecontent[j]!='\0')
						{	
				
							tempword[i]=currentchild->nodecontent[j];
							i++;
							j++;
				
				
						}
						tempword[i]='\0';
						PTrienode* rchildnode= new PTrienode(tempword,true);
						rchildnode->SL=currentchild->SL;
				
						currentchild->SL=NULL;
						currentchild->SL=new Skiplist();
						currentchild->SL->addToSL(docid);
						int childcount=(int)currentchild->children.size();
						if(*tempword!='\0')				
						{	if(childcount>0)
							{
	
							rchildnode->children=currentchild->children;
	
						 	currentchild->children.clear();
	

							}
							currentchild->appendChild(rchildnode);
							delete currentchild->nodecontent;
							currentchild->nodecontent=NULL;
							currentchild->nodecontent=new char[numCharsMatched+1];
							i=0;
							while(word[i]!='\0')
							{currentchild->nodecontent[i]=word[i];
							i++;
							}
							currentchild->nodecontent[i]='\0';
							
						}
						return;
					}
					else
					{	
						int templ;
						templ=getContentLength(word);
						remainingchars=new char[templ-numCharsMatched+1];
						j=numCharsMatched;i=0;
						while(word[j]!='\0')
						{remainingchars[i]=word[j];
						j++;i++;
						}
						remainingchars[i]='\0';
						if(*remainingchars=='\0') return;
						
						addWord(remainingchars,currentchild,docid);	
					
					
					
					}
				
				}
				
				
		
		}
	
	
	}
Skiplist* PTrie::findWord(PTrienode* startnode,char* word)
{	

	if((*word=='\0')&&(startnode->getWordFlag())){ return startnode->SL;}
	if((*word=='\0')&&(!startnode->getWordFlag())) 
		return NULL;
	
	PTrienode *current,*temp;
	current=startnode;
	
	char *remainingchars;
	int  i,j,k,numChilds=(int)(current->children.size());
	
	int numCharsMatched=-1;
	for(i=0;i<numChilds;i++)
	{
		numCharsMatched=current->children.at(i)->findCharsMatched(word);
	
		if(numCharsMatched>0)
		break;
	}
	if(i==numChilds) 
	{
		return NULL;
	}
	j=numCharsMatched;
	remainingchars=new char[getContentLength(word)-numCharsMatched+1];
	j=numCharsMatched;k=0;
	while(word[j]!='\0')
	{remainingchars[k]=word[j];

	j++;k++;
	}
	remainingchars[k]='\0';
	findWord(current->children.at(i),remainingchars);


}
void PTrie::displayTrie(PTrienode* startnode)
{	
	PTrienode *current,*parent,*child;
	current=startnode;
	int numchilds=0;

	numchilds=(int)current->children.size();
	int i;
	for(i=0;i<numchilds;i++)
	displayTrie(current->children.at(i));
	


}

