#include <bits/stdc++.h>

using namespace std;
#define lli long long int

const int INF = 1e7;
string xmas = "xmas";

struct flow {
	string name;
	string order;
	vector<int>upper;	//for each letter, upper bound
	vector<int>lower;	//lower bound
	vector<string>next;	//for each letter, next stop
	string other;			//destination if no condition is met

};

struct part {
	map<char, int>val;
};

void parseFlow (string s, flow &f) {
	f.name = "";
	int i = 0;
	while (s[i] != '{') {
		f.name += s[i];
		i++;
	}
	int lastComma = i+1;
	for (int i = s.size()-1; i >= 0; i-=1) {
		if (s[i] == ',') {
			lastComma = i;
			break;
		}
	}
	i++;
	int bound = 0; //0 - lower, 1 - upper
	char z; 
	int val = 0;
	string next = "";
	string order = "";
	int cnt = 0;
	for (; i < lastComma; ) {
		z = s[i];
		order += s[i];
		next = "";
		f.lower.push_back(0);
		f.upper.push_back(INF);
		f.next.push_back(next);
		
		if (s[i+1] == '<') bound = 1;
		else bound = 0;
		i += 2;
		val = 0;
		while ('0' <= s[i] && s[i] <= '9') {
			val = 10*val+s[i]-'0';
			i++;
		}
		
		if (bound == 0) f.lower.back() = val;
		else f.upper.back() = val;
		
		i++;
		while (('a' <= s[i] && s[i] <= 'z') || ('A' <= s[i] && s[i] <= 'Z')) {
			next += s[i]; 
			i++;
		}
		f.next.back() = next;
		i++;
		cnt++;
	}
	next = "";
	for (; i < s.size()-1; i++) {
		next += s[i];
	}
	f.other = next;
	f.order = order;
}

void parsePart (string s, part &p) {
	int i = 1;
	int val = 0;
	char z;
	while (i != s.size()) {
		z = s[i];
		i+=2;
		val = 0;
		while ('0' <= s[i] && s[i] <= '9') {
			val = 10*val+s[i]-'0';
			i++;
		}
		i++;
		p.val[z] = val;
	}
}

void read (string name, vector<flow>&f, vector<part>&p) {
	fstream file;
	file.open(name, ios::in);
	string line;
	part currPart;
	while (getline(file, line)) { 
		if (line == "") break;
		flow currFlow;
		parseFlow(line, currFlow);
		f.push_back(currFlow);
	}
	
	while (getline(file, line)) {
		parsePart(line, currPart);
		p.push_back(currPart);
	}
	file.close();
}

void debug (vector<flow>&f, vector<part>&p) {
	for (int i = 0; i < f.size(); i++) {
		cout << "now: " << f[i].name << endl;
		cout << f[i].order << endl;
		for (int j = 0; j < f[i].next.size(); j++) {
			cout << f[i].lower[j] << " " << f[i].upper[j] << " " << f[i].next[j] << endl;
		}
		cout << f[i].other << endl;
	}
	for (int i = 0; i < p.size(); i++) {
		cout << "now: " << i << endl;
		for (char c : "xmas") {
			cout << c << " " << p[i].val[c] << endl;
		}
	}
	cout << endl;
return;
}

string getNext (flow &f, part &p) {
	for (int i = 0; i < f.next.size(); i++) {
		int l = f.lower[i];
		int r = f.upper[i];
		int val = p.val[f.order[i]];
		if (l < val && val < r) return f.next[i];
	}
	return f.other;
}

void solve (vector<flow>&f, vector<part>&p) {
	int sol = 0;
	map<string, flow>m;
	for (int i = 0; i < f.size(); i++) {
		m[f[i].name] = f[i];
	}
	string curr = "in";
	for (int i = 0; i < p.size(); i++) {
		curr= "in";
		while (curr != "A" && curr != "R") {
			curr = getNext(m[curr], p[i]);
		}
		int val = 0;
		for (char c : "xmas") {
			val += p[i].val[c];
		}
		sol += (curr == "A")*val;
	}
	cout << sol << endl;
return;
}

int main () {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    vector<flow>f;
	vector<part>p;
    read("input.txt", f, p);
	solve(f, p);

return 0;
}

