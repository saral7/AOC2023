#include <bits/stdc++.h>

using namespace std;
#define lli long long int
const int N = 100100;
int t, n, m;

void read (string name, vector<pair<string, int> > &v) {
	fstream file;
	file.open(name, ios::in);
	string line;
	while (getline (file, line)) {
		string curr = "";
		int val = 0;
		for (int i = 0; i < 5; i++) {
			curr += line[i];
		}
		for (int i = 6; i < line.size(); i++) {
			val = 10*val + line[i]-'0';
		}
		v.push_back({curr, val});
	}
	
	file.close();
}

int getValue (string s) {
	char arr[13] = {'A', 'K', 'Q', 'T', '9', '8', '7', '6', '5', '4', '3', '2', 'J'};
	int cnt[13];
	memset (cnt, 0, sizeof(cnt));
	for (int i = 0; i < s.size(); i++) {
		for (int j = 0; j < 12; j++) {
			if (arr[j] == s[i]) cnt[j]++;
		}
	}
	int maxi = 1;
	for (int i = 0; i < 12; i++) {
		for (int j = 0; j < 5; j++) {
			if (s[j] == 'J') cnt[i]++;
		}
		int cnt2[6] = {0, 0, 0, 0, 0, 0};
		for (int k = 0; k < 12; k++) {
			cnt2[cnt[k]]++;
		} 
		if (cnt2[5] == 1) maxi = max(maxi, 7);
		else if (cnt2[4] == 1) maxi = max(maxi, 6);
		else if (cnt2[3] == 1 && cnt2[2] == 1) maxi = max(maxi, 5);
		else if (cnt2[3] == 1) maxi = max(maxi, 4);
		else if (cnt2[2] == 2) maxi = max(maxi, 3);
		else if (cnt2[2] == 1) maxi = max(maxi, 2);
		for (int j = 0; j < 5; j++) {
			if (s[j] == 'J') cnt[i]--;
		}
	}
	return maxi;
	/*int j = cnt[12];
	if (cnt[12] == 0) {
		if (cnt2[5] == 1) return 7;
		if (cnt2[4] == 1) return 6;
		if (cnt2[3] == 1 && cnt2[2] == 1) return 5;
		if (cnt2[3] == 1) return 4;
		if (cnt2[2] == 2) return 3;
		if (cnt2[2] == 1) return 2;
		return 1;
	} else {
		if ((cnt2[4] == 1 && j == 1) || (cnt2[3] == 1 && j == 2) || (cnt2[2] == 1 && j == 3) || j == 4) return 7;
		if ((cnt2[3] == 1 && j == 1) || (cnt2[2] == 1 && j == 2) || j == 3) return 6;
		if ((cnt2[2] == 2 && j == 1) || (cnt2[3] == 1 && cnt2[1] == 1 && j == 1) || (cnt2[2] == 1 && j == 2) || (cnt2[3] == 1 && j == 2)) return 5;
		if ((cnt2[2] == 1 && j == 1) || j == 2) return 4;
		return 2;
	}*/
 	
}

bool cmp (pair<string, int> a, pair<string, int> b) {
	char arr[13] = {'A', 'K', 'Q', 'T', '9', '8', '7', '6', '5', '4', '3', '2', 'J'};
	int valA = getValue(a.first);
	int valB = getValue(b.first);
	if (valA != valB) return valA < valB;
	for (int i = 0; i < 5; i++) {
		if (a.first[i] != b.first[i]) {
			int posA, posB;
			for (int j = 0; j < 13; j++) {
				if (arr[j] == a.first[i]) posA = j;
				if (arr[j] == b.first[i]) posB = j;
			}
			return posA > posB;
		}
	}
	return false;
}

void solve (vector<pair<string, int> > &v) {
	lli sol = 0;
	sort (v.begin(), v.end(), cmp);
	for (int i = 0; i < v.size(); i++) {
		cout << v[i].first << " " << v[i].second << endl;
		cout << getValue(v[i].first) << endl;
		sol += (lli)(i+1) * (v[i].second);
	}
	cout << sol;
return;
}

int main () {
    vector<pair<string, int> >v;
    read("input.txt", v);
	solve(v);

return 0;
}

