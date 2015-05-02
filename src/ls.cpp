#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <string>
#include <vector>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/param.h>
#include <sys/stat.h>
#include <cstring> 
#include <cctype>
#include <iomanip>
#include <map>
#include <errno.h>
#include <algorithm>
#include <fcntl.h>
#include <pwd.h>
#include <dirent.h>
#include <grp.h>
#include <ctype.h>

using namespace std;

bool check(char one, char two)
{
	bool ret = false;
	if(tolower(one) < tolower(two))
    {
    	ret = true;
    }
    return ret;
}

bool str_check(string j, string k)
{
    bool ret = lexicographical_compare(j.c_str(), j.c_str()+j.size(), k.c_str(), k.c_str()+k.size(), check);
    return ret;
}

void dir_check(vector<string> &inf, char* argv[], string passed)
{
    DIR *d;

    if((d = opendir(".")) == NULL)
    {
    	perror("opendir");
    	exit(1);
    }
    struct dirent *st;
    errno = 0;
    while((st = readdir(d)) != NULL)
    {
    	if(errno != 0)
        {
        	perror("readdir");
        	exit(1);
        }
        else
        {
    	    inf.push_back(st->d_name);
        }
    }
    if(closedir(d) == -1)
    {
    	perror("closedir");
    	exit(1);
    }
    sort(inf.begin(), inf.end(), str_check);
    return;
}

int main(int argc, char *argv[])
{
    vector<string> vec;
    vec.push_back("action");
    vec.push_back("let");
    vec.push_back("act");
    vec.push_back("Active");
    vec.push_back("test");
    vec.push_back("eddy");
    vec.push_back("bed");
    sort(vec.begin(), vec.end(), str_check);
    for(int i = 0; i < vec.size(); i++)
    {
    	cout << vec.at(i) << endl;
    }
	return 0;
}

