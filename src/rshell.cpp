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
#include <sys/mman.h>

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

std::vector<int> pos_split(char** in)
{
	std::vector<int> ret;
	int ch = 0;
	string col = ";";
	string chor = "||";
	string chand = "&&";
	for(int i = 0; in[i] != NULL; i++)
    {
    	if(strcmp(in[i], col.c_str()) != 0 && strcmp(in[i], chor.c_str()) != 0 && strcmp(in[i], chand.c_str()) != 0)
        {
        	ch++;
        }
    	else if(strcmp(in[i], col.c_str()) == 0 || strcmp(in[i], chor.c_str()) == 0 || strcmp(in[i], chand.c_str()) == 0)
        {
            ret.push_back(ch);
            ch=0;
        }
        if(in[i+1] == NULL)
        {
        	    ret.push_back(ch);
        }
    }
    return ret;
}

std::vector<string> pos_split_type(char** in)
{
	std::vector<string> ret;
	int ch = 0;
	string col = ";";
	string chor = "||";
	string chand = "&&";
	for(int i = 0; in[i] != NULL; i++)
    {
    	if(strcmp(in[i], col.c_str()) == 0)
        {
        	ret.push_back(col);
        }
    	else if(strcmp(in[i], chor.c_str()) == 0)
        {
        	ret.push_back(chor);
        }
    	else if(strcmp(in[i], chand.c_str()) == 0)
        {
        	ret.push_back(chand);
        }
    }
    return ret;
}
/*char** single_split(char** in, int pos)
{
    char** ret = new char*[pos];
    int check = 0;
    while(check <= pos)
    {
    	ret[check] = in[check];
    }
    return ret;
}*/
//void execComm(char **in, bool w)
//{
//}

int main (int argc, char **argv)
{
	string stop;
	bool exyn;
    int *worksQ;
	do
	{
        worksQ = (int*)mmap(NULL, sizeof *worksQ, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
        *worksQ = 1;
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
        //input[cop+1] = NULL;
        exyn = pop(input, sec, cop);
        //cout << input[0] << endl;
        std::vector<int> d_pos = pos_split(input);
        std::vector<string> d_typ = pos_split_type(input);
        //cout << d_pos.at(0) << endl;
        int sup = 0;
        int b = 0;
        for(size_t a = 0; a < d_pos.size(); a++)
        {
            cout << *worksQ << endl;
            char** single = new char*[d_pos.at(a)];
            int pos = 0;
            //int sup = 1;
            if((d_pos.at(a) == 1||d_pos.at(a) == 0)&&cop < 2)
            {
            	while(pos < cop)
                {    
            	    single[pos] = new char[strlen(input[sup+pos])];
    	            strcpy(single[pos], input[sup+pos]);
                    pos += 1;
                }
                single[pos] = NULL;
            }
            else
            {
            	if(cop == 2)
                {        		
                    while(pos < 2)
                    {
            	        single[pos] = new char[strlen(input[sup+pos])];
    	                strcpy(single[pos], input[sup+pos]);
                        pos += 1;
                    }
                }
                else{
                    while(pos < (d_pos.at(a)))
                    {
            	        single[pos] = new char[strlen(input[sup+pos])];
    	                strcpy(single[pos], input[sup+pos]);
                        pos += 1;
                    }
                }
                single[pos] = NULL;
            }
            sup += pos;
            sup++;
            int pid = fork();
            if(pid == -1)
            {
        	    perror("fork");
        	    _exit(1);
            }
            else if(pid == 0)
            {
                if(a == 0 || a > d_typ.size())
                {
                    int check = execvp(single[0], single);
                	if(check == -1)
                    {
                        *worksQ = 2;
                    	perror("execvp");
                    	_exit(1);
                    }
                    else{
                    	*worksQ = 1;
                    }
                }
            	else if(d_typ.at(a-1) == ";")
                {
                	//execComm(single, worksQ);
                    int check = execvp(single[0], single);
                    if(check == -1)
                    {
                    	*worksQ = 2;
                        perror("execvp");
                        _exit(1);
                    }
                    else{
                    	*worksQ = 1;
                    }
                }
                else if(d_typ.at(a-1) == "||" && *worksQ > 1)
                {
                	//execComm(single, worksQ);
                    int check = execvp(single[0], single);
                    if(check == -1)
                    {
                    	*worksQ = 2;
                        perror("execvp");
                        _exit(1);
                    }
                    else{
                    	*worksQ = 1;
                    }
                }
                else if(d_typ.at(a-1) == "&&" && *worksQ == 1)
                {
                	//execComm(single, worksQ);
                    int check = execvp(single[0], single);
                    if(check == -1)
                    {
                        *worksQ = 2;
                        perror("execvp");
                        _exit(1);
                    }
                    else{
                    	*worksQ = 1;
                    }
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

            /*for(int i = 0; i < pos; i++)
            {
            	delete[] single[i];
            }*/
            delete[] single;
        }
        munmap(worksQ, sizeof *worksQ);
    }while(!exyn);

	return 0;
}
