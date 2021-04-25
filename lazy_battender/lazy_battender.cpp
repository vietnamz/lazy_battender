// lazy_battender.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;


struct Pair {
	int drink;
	unordered_set<int> those;
};

struct customHash {
	size_t operator()(const Pair  p) const
	{
		return hash<int>()(p.drink);
	}
};
struct customEqual {
	bool operator()(const Pair p1, const Pair p2) const {
		if (p1.drink == p2.drink) {
			return true;
		}
		return false;
	}
};
struct SimpleCompare {
	bool  operator()(const Pair p1, const Pair p2) const {
		return p1.those.size() < p2.those.size();
	}
};
void printMap(unordered_set<Pair, customHash, customEqual> convertToAnotherMap)
{
	for (auto iter = convertToAnotherMap.begin(); iter != convertToAnotherMap.end(); iter++)
	{
		cout << "iter->drink = " << iter->drink << endl;
		cout << "iter->those: " << endl;
		for (const int i : iter->those)
		{
			cout << "    " << i << endl;
		}
	}
}
int minimumRecipe(const unordered_map<int, vector<int>> preferences)
{
	unordered_set<Pair, customHash, customEqual> alreadySeen;
	for (auto iter = preferences.begin(); iter != preferences.end(); iter++)
	{
		auto items = iter->second;
		for (const int item : items)
		{
			Pair p; 
			p.drink = item;
			if (alreadySeen.find(p) != alreadySeen.end())
			{
				unordered_set<int> tmp = alreadySeen.find(p)->those;
				alreadySeen.erase(p);
				tmp.insert(iter->first);
				p.those = tmp;
			}
			else {
				p.those.insert(iter->first);
			} 
			alreadySeen.insert(p);
		}
	}
	//printMap(alreadySeen);
	vector<int> ans;
	while(!alreadySeen.empty()) {
		Pair maxElem = *max_element(alreadySeen.begin(), alreadySeen.end(), SimpleCompare());
		ans.push_back(maxElem.drink);
		vector<int> deleted;
		for (int i : maxElem.those) {
			auto iter = alreadySeen.begin();
			while(iter != alreadySeen.end() )
			{ 
				bool found = false;
				for(const int j : iter->those )
				{
					if(i == j) {
						deleted.push_back(iter->drink);
						break;
					}
				}
				iter++;
			}
		}
		for (int k : deleted) {
			Pair p;
			p.drink = k;
			alreadySeen.erase(p);
		}
	}
	cout << "ans.size() = " << ans.size() << endl;
	return ans.size();
}
/*
preferences = {
    0: [0, 1, 3, 6],
    1: [1, 4, 7],
    2: [2, 4, 7, 5],
    3: [3, 2, 5],
    4: [5, 8]
}

newSet =  {
	0: [0],
	1: [0,1],
	2: [2,3],
	3: [0,3],
	4: [1],
	5: [2,3,4],
	6: [0],
	7: [1,2],
	8: [4]
}

preferences = {
    0: [0],
    1: [0,1],
    2: [2,3],
    3: [0,3],
    4: [1,2],
	5: [2,3,4],
	6: [0],
	7: [1,2],
	8: [4]
}
*/
int main()
{
	unordered_map<int, vector<int>> aMap;
	vector<int> v1 = {0,1,3,6};
	aMap[0] = v1;
	vector<int> v2 = {1,4,7};
	aMap[1] = v2;
	vector<int> v3 = {2,4,7,5};
	aMap[2] = v3;
	vector<int> v4 = {3,2,5};
	aMap[3] = v4;
	vector<int> v5 = {5,8};
	aMap[4] = v5;
	minimumRecipe(aMap);
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
