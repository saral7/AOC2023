#include <bits/stdc++.h>

using namespace std;
#define lli long long int
const int N = 100100;
int t, n, m;

void parse (string line, string &node, string &left, string &right) {
	node = left = right = "";
	for (int i = 0; i < 3; i++) node += line[i];
	for (int i = 7; i < 10; i++) left += line[i];
	for (int i = 12; i < 15; i++) right += line[i];
}

void read (string name, string &moves, map<string, pair<string, string> > &m) {
	fstream file;
	file.open(name, ios::in);
	
	string line;
	getline (file, line);
	moves = line;
	getline(file, line);
	while (getline(file, line)) {
		string node, left, right;
		parse (line, node, left, right);
		m[node] = {left, right};
	}
	
	file.close();
}

void solve (string moves, map<string, pair<string, string> >&m) {
	int ind = 0, cnt = 0, n = moves.size();
	string curr = "AAA";
	while (curr != "ZZZ") {
		if (moves[ind] == 'L') curr = m[curr].first;
		else curr = m[curr].second;
		cnt++;
		ind = (ind+1)%n;
	}
	cout << cnt << endl; 
}

int main () {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    string moves;
    map<string, pair<string, string> >m;
    read ("input.txt", moves, m);
    /*for (auto it = m.begin(); it != m.end(); it++) {
    	cout << it->first << " " << (it->second).first << " " << (it->second).second << endl;
	}*/
	solve(moves, m);

return 0;
}

