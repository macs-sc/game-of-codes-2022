#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include<map>
#include<set>
#include<queue>
#include <functional>
using namespace std;


int dfs(int i, int j, vector<vector<int>>& seats, vector<vector<bool>>& visited) {
	if (i < 0 || i >= seats.size()
		|| j < 0 || j >= seats[i].size()
		|| visited[i][j]
		|| seats[i][j] == 1)
		return 0;
	visited[i][j] = true;
	return 1 + dfs(i + 1, j, seats, visited) + dfs(i, j + 1, seats, visited) + dfs(i - 1, j, seats, visited) + dfs(i, j - 1, seats, visited);
}



int main()
{
	ios::sync_with_stdio(0);

	//freopen("in", "r", stdin);
	int n, m;
	cin >> n >> m;
	vector<vector<int>> seats(n, vector<int>(m));
	vector<vector<bool>> visited(n, vector<bool>(m,false));
	for (auto& seat_i : seats)
		for (auto& seat_ij : seat_i)
			cin >> seat_ij;
	int membersNumber;
	cin >> membersNumber;
	vector<int> connectedCellsSizes;
	for(int i=0;i<seats.size();i++)
		for (int j = 0;j < seats[i].size();j++)
		{
			
			if (!visited[i][j] && seats[i][j] == 0) {
				auto connectedCellSize = dfs(i, j, seats, visited);
				if (connectedCellSize > 1)
					connectedCellsSizes.push_back(connectedCellSize);
			}
		}
	sort(connectedCellsSizes.begin(), connectedCellsSizes.end());
	for (int i = connectedCellsSizes.size() - 1;i >= 0;i--) {
		if (membersNumber >= connectedCellsSizes[i]) {
			membersNumber -= connectedCellsSizes[i];
		}
		else {
			if (membersNumber == 1) {
				if (connectedCellsSizes.back() > 2)
					membersNumber = 0;
			}
			else {
				membersNumber = 0;
			}
		}
	}
	if (membersNumber == 0)
		cout << "Yes\n";
	else
		cout << "No\n";
	return 0;
}


