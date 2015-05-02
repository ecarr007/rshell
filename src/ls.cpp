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

int main()
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
