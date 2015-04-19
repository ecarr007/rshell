#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <vector>
#include <string.h>
#include <cstring>
#include <sys/param.h>

using namespace std;
void printcmd()
{
		char *usrnm;
		if((usrnm = getlogin()) == NULL)
        {
        	perror("getlogin");
        	_exit(1);
        }
        
        char hstnm[BUFSIZ];
        int hGet = gethostname(hstnm, BUFSIZ);
        if(hGet == -1)
        {
        	perror("gethostname");
        	_exit(1);
        }
        cout << usrnm << "@" << hstnm << ":~$ ";
}

std::string lookForComm(string s)
{
   std::string comm = "#";
   std::string token;
   int pos = 0;
   if((pos = s.find(comm)) != std::string::npos)
   {
        token = s.substr(0, pos);
        s.erase(pos, s.length());
        return token;
   }
   else
   {
   	   return s;
   }
}

bool lookForExit(char** arr, int arr_s)
{
    std::string ex = "exit";
    //int pos = 0;
    bool ret;
    int ch = 0;
    for(int pos; pos < arr_s; pos++)
    {
    	if(arr[pos] == ex)
        {
    	    //s = s.substr(0, pos);
    	    //return true;
    	    ch++;
    	    strcpy(arr[pos], "\0");
    	    break;
        }
        else
        {
    	    return false;
        }
    }
}

void parse(std::string &s)
{
    int pos = 0;
    for(std::string::iterator iter = s.begin(); iter < s.end(); iter++, pos++)
    {
        int cont = s.find(";", pos);
        if(cont != -1)
        {
        	s.insert(cont, " ");
        	s.insert((s.find(";", pos))+1, " ");
        	iter = s.begin() + s.find(";")+1;
        	pos = s.find(";", pos)+1;
        }
    }
    pos = 0;
    for(std::string::iterator iter = s.begin(); iter < s.end(); iter++, pos++)
    {
        int s_and = s.find("&&", pos);
        if(s_and != -1)
        {
        	s.insert(s_and, " ");
        	s.insert(s.find("&&", pos)+2, " ");
        	iter = s.begin() + s.find("&&")+2;
        	pos = s.find("&&", pos)+2;
        }
    }
    pos = 0;
    for(std::string::iterator iter = s.begin(); iter < s.end(); iter++, pos++)
    {
        int s_or = s.find("||", pos);
        if(s_or != -1)
        {
        	s.insert(s_or, " ");
        	s.insert(s.find("||", pos)+2, " ");
        	iter = s.begin() + s.find("||")+2;
        	pos = s.find("||", pos)+2;
        }
    }
}

bool pop(char** in_arr, char* in_cstr, int len)
{
    char* token = strtok(in_cstr, " ");
    int ch = 0;
    for(int i = 0; i < len; i++)
    {
    	if(strcmp(token, "exit") == 0)
        {
        	ch++;
        	break;
        }
        int length = strlen(token) + 1;
        //cout << length << endl;
        in_arr[i] = new char[length];
        strcpy(in_arr[i], token);
        cout << in_arr[i] << endl;
        //cout << token << endl;
        token = strtok(NULL, " ");
    }
    if(ch > 0)
    {
    	return true;
    }
    else 
    {
    	return false;
    }
}

int main (int argc, char **argv)
{
	string stop;
	bool exyn;
	//char** input;
	do
	{
        printcmd();
        getline(cin, stop);
        string temp = lookForComm(stop);
        //exyn = lookForExit(temp);
        parse(temp);
        size_t len = temp.size();
        char* str = new char[len];
        strcpy(str, temp.c_str());
        char* sec = new char[len];
        strcpy(sec, temp.c_str());
        char* tok = strtok(str, " ");
        int cop = 0;
        while(tok != 0)
        {
        	//cout << tok << endl;
            //strcpy(input[cop], tok);
            //std::cout << input[cop] << std::endl;
            cop++;
        	tok = strtok(NULL, " ");
        }
        //cout << cop << endl;
        char** input = new char*[cop];
        exyn = pop(input, sec, cop);
        int pid = fork();
        if(pid == -1)
        {
        	perror("fork");
        	_exit(1);
        }
        else if(pid == 0)
        {
            int check = execvp("ls", argv);
            if(check == -1)
            {
            	perror("execvp");
            	_exit(1);
            }
        	cout << "this is the child process" << endl;
        	_exit(pid);
        }
        else
        {
        	int status = wait(NULL);
        	if(status == -1)
            {
            	perror("wait");
            	_exit(1);
            }
        }
    }while(!exyn);

	return 0;
}
