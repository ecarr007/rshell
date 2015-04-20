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
   size_t pos = 0;
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
        	in_arr[i] = NULL;
        	break;
        }
        int length = strlen(token);
        in_arr[i] = new char[length];
        strcpy(in_arr[i], token);
        token = strtok(NULL, " ");
    }
    if(ch > 0)
    {
    	return true;
    }
    else 
    {
    	in_arr[len] = NULL;
    	return false;
    }
}

std::vector<int> pop_split(char** in)
{
	std::vector<int> ret;
	ret.push_back(0);
	for(int i = 0; in[i] != 0; i++)
    {
    	if(strcmp(in[i], ";") == 0 || strcmp(in[i], "||") == 0 || strcmp(in[i], "&&") == 0)
        {
        	ret.push_back(i);
        }
    }
    return ret;
}

int main (int argc, char **argv)
{
	string stop;
	bool exyn;
	do
	{
        printcmd();
        getline(cin, stop);
        string temp = lookForComm(stop);
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
            cop++;
        	tok = strtok(NULL, " ");
        }
        char** input = new char*[cop+1];
        exyn = pop(input, sec, cop);
        std::vector<int> d_pos = pop_split(input);
        int pid = fork();
        if(pid == -1)
        {
        	perror("fork");
        	_exit(1);
        }
        else if(pid == 0)
        {
            int check = execvp(input[0], input);
            if(check == -1)
            {
                perror("execvp");
            	_exit(1);
            }
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
