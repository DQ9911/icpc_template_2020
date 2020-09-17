#include<bits/stdc++.h>
#include<windows.h>
using namespace std;

void out_test() {
	ifstream in("in.txt", ios::in);
	string s;
	while(getline(in, s)) {
		cout << s << '\n';
	}
}

bool same() {
  ifstream in1("out1.txt", ios::in);
  ifstream in2("out2.txt", ios::in);
	string s1, s2;
	string a1, a2;
	while(getline(in1, s1)) {
		a1 += s1; a1.push_back('\n');
	}
	cout << "my_ans:\n";
	cout << a1;
	while(getline(in2, s2)) {
		a2 += s2; a2.push_back('\n');
	}
	cout << "bf_ans:\n";
	cout << a2;
  return a1 == a2;
}

int main() {
	const int times = 1000;
	int nowcase = 0;
  while (true) {
    system("gen");
    system("main");
    system("aa");
    cout << "Case #" << ++nowcase << ":\n";
    out_test();
    if(!same()) {
			cout << "fail\n\n";
			break;
		}
		cout << "ok\n\n";
		if(nowcase == times){
			break;
		}
//		Sleep(50);
  }
  return 0;
}
