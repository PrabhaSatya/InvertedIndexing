#include<cstring>
#include"skiplist.hpp"
using namespace std;
class PTrienode
{
public:
	char* nodecontent;
	bool wordflag;
	vector<PTrienode*> children;
	Skiplist *SL;
 PTrienode()
 {
 	
 	SL = new Skiplist();
 	nodecontent=NULL;
 	wordflag=false;
 	
 }
 PTrienode(char* c,bool wrdflag)
 {	
 	nodecontent =new char[getContentLength(c)+1];
 	int i=0;
 	while(c[i]!='\0')
 	{	nodecontent[i]=c[i];
 		i++;
 	}
 	nodecontent[i]='\0';
 	wordflag=wrdflag;
	SL=new Skiplist();
 }
	void setWordFlag()
	{
		this->wordflag=true;
	
	}
	bool getWordFlag()
	{
	return wordflag;}
	char* getNodeContent()
	{
		if(nodecontent==NULL)
		return (char*)"null";
		else return this->nodecontent;
	}
	void setNodeContent(char* c)
	{	int i=0;
 	while(c[i]!='\0')
 	{	nodecontent[i]=c[i];
 		i++;
 	}
 	nodecontent[i]='\0';
		
	}
	int  findCharsMatched(char* inputword);
	void appendChild(PTrienode* newnode);
	int getContentLength(char *str)
	{	
	
		int i=0;
		while(str[i]!='\0')
		i++;
	
		return i;
	
	}
	
};
class PTrie
{
	public:
	PTrienode* root;
	void addWord(char* word,PTrienode *startnode,int docid);
	Skiplist* findWord(PTrienode* startnode,char* word);
	void deleteWord(char* word);
	void displayTrie(PTrienode* startnode);
	PTrie()
	{
		root = new PTrienode();
	}
	int getContentLength(char *str)
	{
		int i=0;
		while(str[i]!='\0')
		i++;
	
		return i;
	
	}
	
};
