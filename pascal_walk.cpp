#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 150;
const ll INF = 1e9+5;
ll P[N][N], Q[N][N];

void solve(int TC) {
  ll n; cin >> n;
  ll sum = 1;
  int r=0, c=0;
  vector<pair<int,int>> ans = {{r,c}};
  while(sum < n) {
    if(sum + Q[r+1][c+1] <= n) {
      sum += P[r+1][c+1];
      r++; c++;
    } else if(sum + Q[r+1][c] <= n) {
      sum += P[r+1][c];
      r++;
    } else {
      bool cond = c && (sum + P[r][c-1] <= n);
      if(!cond) {
	printf("sum: %d r: %d \n",sum,r);
	for(auto it: ans) {
	  printf("%d %d\n",it.first+1,it.second+1);
	}
	assert(0);
      }
      sum += P[r][--c];
    }
    ans.push_back({r,c});
  }
  //  printf("final sum: %lld\n",sum);
  // assert(sum == n);
  printf("Case #%d:\n",TC);
  for(auto it: ans) {
    printf("%d %d\n",it.first+1,it.second+1);
  }
}

int main() {
  int t; cin >> t;
  P[0][0] = Q[0][0] = 1;
  for(int i=1;i<N;i++) {
    Q[i][0] = P[i][0] = 1;
    for(int j=1;j<=i;j++) {
      P[i][j] = min(INF,P[i-1][j-1] + P[i-1][j]);
      Q[i][j] = min(INF,Q[i][j-1] + P[i][j]);
    }
  }
  for(int i=1;i<=t;i++) solve(i);
}
