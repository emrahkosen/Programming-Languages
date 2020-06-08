#include <iostream>
#include <string>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include <vector>
#include <cstdlib>
using namespace std;

vector<string> Split_String(string line, char by)
{
	vector<string> ret;
	string word = "";

	for(auto c : line)
	{
		if(c == by)
		{
			if(word != "")
				ret.push_back(word);
			word = "";
		}
		else
		{
			word+= c;
		}
	}
	if(word != "")
		ret.push_back(word);
	return ret;

}

int main ( )
{
		vector<string> split;
		 std::cout << "write whatever you want:" << '\n';
		 string line;
		 std::getline (std::cin,line);

		 split = Split_String(line,' ');

		 for(auto i : split)
		 		cout<<i<<"\n";

		 return 0;

}
