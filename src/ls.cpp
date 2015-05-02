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

void noP(char *argv[])
{
	string p = "ls";
	vector<string> inf;
	dir_check(inf, argv, p);
	int count = 3;
	for(size_t i = 0; i < inf.size(); i++)
    {
        if(count == 0)
        {
            cout << '\n';
            count = 3;
        }
        if(inf[i][0] != '.')
        {
            cout << std::left << setw(24) << inf.at(i);
            --count;
        }
    }
    cout << endl;
    return;
}

void aP(char *argv[])
{
    string p = "a";
    vector<string> inf;
    dir_check(inf, argv, p);
    int count = 3;
    for(size_t i = 0; i < inf.size(); i++)
    {
    	if(count == 0)
        {
        	cout << '\n';
        	count = 3;
        }
        cout << std::left << setw(24) << inf.at(i);
        --count;
    }
    cout << endl;
    return;
}

int main(int argc, char *argv[])
{
    //noP(argv);
    //aP(argv);
    bool aPassed = false;
    bool check = true;
    for(int i = 1; i < argc; i++)
    {
        string st;
        st = argv[i];
        if(st.find("-") == 0)
        {
        	if((st.find("a")) == 0)
            {
            	aPassed = true;
            }
            for(size_t b = 1; b < st.size(); b++)
            {
            	if((st.at(b)) == 'a')
                {
                	aPassed = true;
                }
                else
                {
                	check = false;
                }
            }
        }
    }
    if(!check)
    {
    	return 1;
    }
    if(!aPassed)
    {
        noP(argv);
    }
    else if(aPassed)
    {
      	aP(argv);
    }
	return 0;
}

