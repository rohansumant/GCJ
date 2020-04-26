#include <bits/stdc++.h>
using namespace std;

vector<int> process(int x) {
  if(x < 0) x = -x;
  vector<int> ans(33);
  for(int i=0;i<31;i++) {
    if(x & (1<<i)) ans[i] = 1;
  }
  return ans;
}

void solve(int TC) {
  int x, y;
  cin >> x >> y;
  vector<int> a = process(x), b = process(y);
  char opts[] = {'E','W','N','S'};
  int x_base = 0, y_base = 2;
  if(x < 0) {
    x_base ^= 1;
    x = -x;
  }
  if(y < 0) {
    y_base ^= 1;
    y = -y;
  }
    
  auto flip = [](vector<int> &tgt,int ix) {
    assert(tgt[ix] == 1);
    int i;
    for(i=ix;tgt[i] == 1;i++) {
      tgt[i] = 0;
    }
    assert(i < 30 && tgt[i] == 0);
    tgt[ix] = -1; tgt[i] = 1;
  };
    
  string ans = "IMPOSSIBLE";
  if(a[0] ^ b[0]) {
    for(int i=1;i<a.size();i++) {
      vector<int> &target = a[i-1] == 1 ? a:b;      
      if(a[i] ^ b[i]) continue;
      else if(a[i]) { // both are 1
	flip(target,i-1);
      } else { // both are 0
	bool any = false;
	for(int j=i;j<a.size();j++) any |= a[j] || b[j];
	if(any) {
	  target[i-1] = -1;
	  target[i] = 1;
	} else {
	  // we are done
	  break;
	}
      }
    }
  }
    
  while(!a.empty() && (a.back() == 0 && b.back() == 0)) {
    a.pop_back();
    b.pop_back();
  }
    
    
  for(int i=0;i<a.size();i++) {
    if(!i) ans = "";
    if((a[i] && b[i]) || (!a[i] && !b[i])) {
      ans = "IMPOSSIBLE";
      break;
    } else {
      if(a[i]) ans += opts[a[i] > 0 ? x_base : 1^x_base];
      else ans += opts[b[i] > 0 ? y_base : 1^y_base];
    }
  }
  printf("Case #%d: %s\n",TC,ans.c_str());
}

int main() {
  int t; cin >> t;
  for(int i=1;i<=t;i++) solve(i);
}
