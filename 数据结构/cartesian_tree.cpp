int ch[N][2];
template<typename T>
int build(const T &a, int n) {
	vector<int> stk;
	int nowroot = 0;
	for(int i = 1; i <= n; i++) {
		while(!stk.empty() && a[i] > a[stk.back()]) stk.pop_back();
		if(!stk.empty()) ch[i][0] = ch[stk.back()][1], ch[stk.back()][1] = i;
		else ch[i][0] = nowroot, nowroot = i;
		stk.push_back(i);
	}
	return nowroot;
}
