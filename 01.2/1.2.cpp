#include <bits/stdc++.h>

using namespace std;
#define lli long long int
const int N = 100100;
int t, n, m;

void read(vector<string> &v, string name) {
	fstream file;
	file.open(name, ios::in);
	string line;
	while (getline(file, line)) {
		v.push_back(line);
	}
	file.close();
	return;
}

bool check (string s, int &flag) {
	string nums[] = {"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
	flag = -1;
	for (int i = 0; i < 10; i++) {
		if (nums[i] == s) {
			flag = i;
			return true;
		}
	}
	return false;
}

int parse (string s) {
	int first = -1, last = -1;
	for (int i = 0; i < s.size(); i++) {
		if ('a' <= s[i] && s[i] <= 'z') {
			string curr = "";
			int flag;
			for (int j = 0; j < 5; j++) {
				curr += s[i+j];
				if (check(curr, flag)) {
					if (first == -1) first = flag;
					last = flag;
				}
			}
		}
		if ('0' <= s[i] && s[i] <= '9') {
			int flag = s[i]-'0';
			if (first == -1) first = flag;
			last = flag;
		}
	}
	return first*10+last;
}

void solve (vector<string> &v) {
	int sol = 0;
	for (int i = 0; i < v.size(); i++) {
		sol += parse(v[i]);
	}
	cout << sol;
return;
}

int main () {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    
    vector<string> v;
	read(v, "input.txt");
	solve(v);

return 0;
}

