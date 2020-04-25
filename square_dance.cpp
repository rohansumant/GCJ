#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> pii;
typedef long long ll;

class FLL {
  class Node {
  public:
    int val;
    Node *next, *prev;
    Node(int v) {
      val = v;
      next = prev = NULL;
    }
  };

  Node *head, *tail;
  unordered_map<int,Node*> mp;
  
public:
  
  FLL() {
    head = tail = NULL;
  }

  FLL(const FLL&) = delete;
  FLL& operator=(const FLL&) = delete;
  
  ~FLL() {
    for(Node *it = head;it; it=it->next) {
      if(it->prev) delete it->prev;
    }
    if(tail) delete tail;
  }
  
  void add_tail(int val) {
    assert(!mp[val]);
    Node *nd = new Node(val);
    mp[val] = nd;
    if(!head) {
      head = tail = nd;
    } else {
      tail->next = nd;
      nd->prev = tail;
      tail = nd;
    }
  }

  void erase(int val) {
    /*printf("Deleted val: %d\n");
    for(auto it = head; it; it = it->next) {
      printf("%d, ",it->val);
    }
    printf("\n");*/
    auto it = mp.find(val);
    Node *nd = it->second;
    assert(nd);
    mp.erase(it);
    if(nd == head) {
      head = head->next;
    }
    if(nd == tail) {
      tail = tail->prev;
    }
    Node *prev = nd->prev, *next = nd->next;
    if(prev) {
      prev->next = next;
    }
    if(next) {
      next->prev = prev;
    }
    /*for(auto it = head; it; it = it->next) {
      printf("%d, ",it->val);
    }
    printf("\n");*/
    delete nd;
  }

  pii get_prev_next(int val) {
    /*printf("val: %d\n");
    for(auto it = head; it; it = it->next) {
      printf("%d, ",it->val);
    }
    printf("\n");*/
    auto it = mp.find(val);
    assert(it != mp.end());
    Node *nd = it->second;
    Node *prev = nd->prev, *next = nd->next;
    return make_pair((prev?prev->val:-1),(next?next->val:-1));
  }
};    

void solve(int TC) {
  int R,C; cin >> R >> C;
  vector<vector<int>> grid(R,vector<int>(C));
  vector<FLL*> rl(R), cl(C);
  ll sum = 0;
  queue<pii> Q;
  for(int i=0;i<R;i++) {
    for(int j=0;j<C;j++) {
      cin >> grid[i][j];
      sum += grid[i][j];
      if(!rl[i]) rl[i] = new FLL();
      if(!cl[j]) cl[j] = new FLL();
      rl[i]->add_tail(j);
      cl[j]->add_tail(i);
      Q.push({i,j});
    }
  }
  ll ans = 0, rem = sum;
  vector<vector<int>> vis(R,vector<int>(C));
  vector<vector<bool>> del(R,vector<bool>(C));
  int iter = 0;

  auto get_neighbors = [&](int x,int y) -> vector<pii> {
    pii row_pn = rl[x]->get_prev_next(y);
    pii col_pn = cl[y]->get_prev_next(x);
    vector<pii> result;
    if(row_pn.first != -1) result.push_back({x,row_pn.first});
    if(row_pn.second != -1) result.push_back({x,row_pn.second});
    if(col_pn.first != -1) result.push_back({col_pn.first,y});
    if(col_pn.second != -1) result.push_back({col_pn.second,y});
    return result;
  };
  
  while(!Q.empty()) {
    int curr_size = Q.size();
    iter++;
    ans += rem;
    vector<pii> elim;
    while(curr_size--) {
      auto pr = Q.front(); Q.pop();
      int x = pr.first, y = pr.second;
      if(del[x][y]) continue;
      //printf("x: %d y: %d\n",x,y);
      int nc = 0;
      int nbr_sum = 0;
      vector<pii> neighbors = get_neighbors(x,y);
      for(const auto &nbr: neighbors) {
	++nc;
	nbr_sum += grid[nbr.first][nbr.second];
	//printf("nbr %d: %d %d\n",nc,nbr.first,nbr.second);
      }
      if(nc*grid[x][y] < nbr_sum) {
	elim.push_back({x,y});
	rem -= grid[x][y];
	for(const auto &nbr: neighbors) {
	  if(vis[nbr.first][nbr.second] != iter) {
	    vis[nbr.first][nbr.second] = iter;
	    Q.push(nbr);
	  }
	}
      }
    }
    while(!elim.empty()) {
      auto &pr = elim.back();
      int x = pr.first, y = pr.second;
      del[x][y] = true;
      //printf("Deleting %d %d\n",x,y);
      rl[x]->erase(y);
      cl[y]->erase(x);      
      elim.pop_back();
    }
  }
  printf("Case #%d: %lld\n",TC,ans);
  for(auto ptr: rl) delete ptr;
  for(auto ptr: cl) delete ptr;
}

int main() {
  int t; cin >> t;
  for(int i=1;i<=t;i++) solve(i);
}
