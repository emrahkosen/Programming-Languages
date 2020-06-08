#include <iostream>
#include <string>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include <vector>
#include <cstdlib>
using namespace std;

vector<int> Split_String(string line)
{
	vector<int> ret;
	string word = "";

	for(auto c : line)
	{
		if(c == ' ')
		{
			int num = std::stoi(word);
			ret.push_back(num);
			word = "";
		}
		else
		{
			word+= c;
		}
	}

	int num = std::stoi(word);
	ret.push_back(num);
	return ret;

}

int main ( )
{
		vector<int> mn;

		 string line;
		 std::getline (std::cin,line);

		 mn = Split_String(line);
		 cout<< "m = "<< mn[0] << " n = "<<mn[1]<<	"\n";


		int count = 0;
		int count_plus = 0;
		int neededN = 0;





		while(++count)
		{
			if(mn[0] < count*count)
				break;
		}

		neededN = 4*(count*count - mn[0]);

		if(mn[1] >= neededN)
		{
			mn[1] -= neededN;

			while (++count_plus)
			{
				if(4*count_plus*count + (count_plus*count_plus) > mn[1])
				{
						count_plus--;
						break;
				}
			}
		}
		else
			count--;

		std::cout <<"MAX LEN = " <<count*2 + count_plus << '\n';




	return 0;

}
