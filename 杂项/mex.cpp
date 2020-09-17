int mex(set<int> &s) {
  int ret = 0;
  while(s.find(ret) != s.end()) ret++;
  return ret;
}
