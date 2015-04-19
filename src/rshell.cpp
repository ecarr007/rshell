#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <vector>
#include <string.h>

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

bool lookForExit(std::string s)
{
    std::string ex = "exit";
    int pos = 0;
    if((pos = s.find(ex)) != std::string::npos)
    {
    	s = s.substr(0, pos);
    	std::cout << s << std::endl;
    	return true;
    }
    else
    {
    	return false;
    }
}

void parse(std::string s)
{
    int pos = 0;
    for(std::string::iterator iter = s.begin(); iter != s.end(); iter++, pos++)
    {
        int cont = s.find(";", pos);
        if(cont != -1)
        {
        	s.insert(cont, " ");
        	s.insert((cont + 1), " ");
        	iter += (cont + 1);
        	pos = cont + 1;
        }
    }
    pos = 0;
    for(std::string::iterator iter = s.begin(); iter != s.end(); iter++, pos++)
    {
        int s_and = s.find("&&", pos);
        if(s_and != -1)
        {
        	s.insert(s_and, " ");
        	s.insert((s_and + 1), " ");
        	iter += (s_and + 1);
        	pos = s_and + 1;
        }
    }
    pos = 0;
    for(std::string::iterator iter = s.begin(); iter != s.end(); iter++, pos++)
    {
        int s_or = s.find("||", pos);
        if(s_or != -1)
        {
        	s.insert(s_or, " ");
        	s.insert((s_or + 1), " ");
        	iter += (s_or + 1);
        	pos = s_or + 1;
        }
    }
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
        exyn = lookForExit(temp);
        parse(temp);
        char* str = new char[temp.size()];
        strcpy(str, temp.c_str());
        char* tok = strtok(str, " ");
        while(tok != NULL)
        {
        	cout << tok << endl;
        	tok = strtok(NULL, " ");
        }
        int pid = fork();
        if(pid == -1)
        {
        	perror("fork");
        	_exit(1);
        }
        else if(pid == 0)
        {
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