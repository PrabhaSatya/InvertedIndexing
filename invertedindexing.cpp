#include<iostream>
#include<fstream>
#include<cstring>
#include<algorithm>
#include<vector>
#include<sstream>
#include <string>
#include <stdlib.h>
#include "ptrie.h"


int numQWords=0;

using namespace std;
PTrie *PT =new PTrie();
class focusWords{
public:

	string toUpper(string name){
		int length=name.size();
		string temp;
		int k=0;
		temp=name;
		for(int i=0;i<length;i++)
			{	if(isalpha(int(name[i])))
				{	temp[k]=toupper(name[i]);
					k++;
				}
			}
		return temp;
	}
	
	string toLower(string name){
		int length=name.size();
		string temp;
		int k=0;
		temp=name;
		for(int i=0;i<length;i++)
			{	if(isalpha(int(name[i])))
				{	temp[k]=tolower(name[i]);
					k++;
				}
			}
		return temp;
	}
	
	
	string findFocusWords(string word){
		string Word (toUpper(word));
		
		ifstream readFrom;
		readFrom.open("StopWords");
		string s;
		int flag = 0;
        string focus_word = "null";
        while (getline(readFrom,s)) {
            if (Word==s) {
                flag = 1;
            }
        }
        if (flag != 1) {
            focus_word = word;
        }
        return focus_word; 
	}
	
	
	void readFromFile(int docid,const char* filename){		
		int j=0,size=0;
		string line;
		string word;
		ifstream readFrom;
		readFrom.open(filename);
	
		while(getline(readFrom,line)){
			int i=0;
			size = line.length();
			
			while (i != size){  
				if(!((line[i]>=65 && line[i]<=90) || (line[i]>=97 && line[i]<=122) || line[i]==32)){
					line[i]=' ';
				}
				i++;
			}
			stringstream stream(line);
			while (getline(stream, word, ' ')) {
				string result = findFocusWords(word);
				string loweredword;
				if(result!="null")
				{
				
					
					loweredword=toLower(result);
					char* Trieword=new char[loweredword.size() + 1];
					
					copy(loweredword.begin(), loweredword.end(), Trieword);
					Trieword[loweredword.size()] = '\0';
					PT->addWord(Trieword,PT->root,docid);
					delete[] Trieword;
				}
			}
		}
		readFrom.close();
	}
};
void flush(istream & is)
{
is.clear();
is.ignore(80,'\n');
}
int main(){
	


	focusWords *preprocess = new focusWords;
	string inputQuery;
	int exit=0; 
	char** QArray;
	int i=0,k=0,m=0,length;
	Skiplist  **Slists;
	int count=0;
	int numDocs=0;
	
	string temppath;
	cout<<"enter the path of the folder to be indexed"<<endl;
	cin>>temppath;
	char* path;
	path=new char[temppath.size()+1];
	copy(temppath.begin(), temppath.end(), path);
	path[temppath.size()] = '\0';
	char cmd[100];
	sprintf(cmd,"/bin/sh ./shellscript.sh  %s",path);
	system(cmd);
	ifstream fileptr("./filenames.txt");
	string filename;
	while(getline(fileptr,filename))
	numDocs++;
	string filenames[numDocs];
	fileptr.close();
	fileptr.open("./filenames.txt");
	int p=0;
	while(getline(fileptr,filename))
	{	filenames[p]=filename;
		p++;
	}
	if(p==0) {cout<<"Invalid Input"<<endl;
			return 0;
		}
	string finalpath;
	cout<<"**********************************************Indexing in Process**************************************************"<<endl;
	clock_t startTime = clock();
	for(int i=0;i<numDocs;i++)
	{	finalpath=temppath+"/"+filenames[i];
		preprocess->readFromFile(i,finalpath.c_str());
		cout<<"indexing done to"<<i<<endl;
	}
	cout << double( clock() - startTime ) / (double)CLOCKS_PER_SEC<< " seconds." << endl;
	flush(cin);
	
	while(exit==0)
	{
		
		cout<<"enter input query";
		
		getline(cin,inputQuery);
		
		length=inputQuery.size();
		
		while(m!=length)
		{if(!(65<=inputQuery[m]&&inputQuery[m]<=90)&&!(97<=inputQuery[m]&&inputQuery[m]<=122)&&inputQuery[m]!=32)
			inputQuery[m]=' ';
		
		m++;
		
		}
		m=0;
		
		
	 
		istringstream  iss(inputQuery);

	    do
	    {
		string sub;
		iss >> sub;
		if(iss)
		{	string result = preprocess->findFocusWords(sub);
			if(result.compare("null") != 0)
				numQWords++;
				
		}
	    } while (iss);
	   
	    QArray=new char*[numQWords];
	    istringstream   jss(inputQuery);
	    do
	    {
		string sub;
		jss >> sub;
		if(jss)
		{	
			string result = preprocess->findFocusWords(sub);
			if(result.compare("null") != 0)
			{	string loweredword;
				loweredword=preprocess->toLower(result);
				QArray[i]=new char[loweredword.size()+1];
				copy(loweredword.begin(), loweredword.end(), QArray[i]);
				QArray[i][loweredword.size()]='\0';
				i++;
			}
		}
	    } while (jss);
	   Slists=new Skiplist*[numQWords];
	   for(int l=0;l<numQWords;l++)
	   Slists[l]=new Skiplist();
	   for(int l=0;l<numQWords;l++)
	   Slists[l]=PT->findWord(PT->root,QArray[l]);
	   int output[numDocs];
	   calIntersect(Slists,numQWords,numDocs,output);
	   int check=0,results=0;
		
	   for(int v=0;v<numDocs;v++)
	   	if(output[v]!=-1)
	   	{	check=1;
	   		results++;
	   	}
	   if(check==1)
	   {	cout<<"Query found in the following documents:"<<endl;
	   	cout<<"******************************************************************************************"<<endl;
	   	cout<<"Total Number of Documents:"<<results<<endl;
	   	for(int v=0;v<numDocs;v++)
		if(output[v]!=-1)
		 	cout<<filenames[output[v]]<<endl;
	       cout<<"******************************************************************************************"<<endl;
	   }
	   else
	   {  cout<<"******************************************************************************************"<<endl;
	     cout<<"Query not found in any of the documents"<<endl;
	     cout<<"******************************************************************************************"<<endl;
	    }
           cout<<"Do you want to continue querying,if so  enter 0 else enter 1"<<endl;
        
	   cin>>exit;
	   flush(cin);
	   numQWords=0;
	   count=0;
	   iss.clear();
	   jss.clear();
	   i=0;
	   
	}
	return 0;
}
