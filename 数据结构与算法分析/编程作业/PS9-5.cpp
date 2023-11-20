#include<bits/stdc++.h>
using namespace std;
struct node {
    int n;
    node *next;
    int d;
    int f;
};

node *adj[10000000];

pair<vector<int>,vector<pair<int,int>>> gen(int n, int q,int seed, int parameter){
    vector<int> res(n,-1);
    vector<pair<int,int>> queries(q);
    mt19937 rng(seed);
    for (int i=1;i<n;++i){
        int w=i-1;
        for (int j=0;j<parameter;++j){
            w=rng()%(w+1);
        }
        res[i]=i-1-w;       
    }
    for (int i=0;i<q;++i){
        queries[i].first=rng()%n;
        queries[i].second=rng()%n; 
    }
    return {res,queries};
}

void adj_insert(int u, int v) {
    node *tmp = adj[u]->next;
    node *tmp_v = (node *)malloc(sizeof(node *));
    tmp_v->n = v;
    tmp_v->next = tmp;
    adj[u]->next = tmp_v;
}

int mytime = 0;
void dfs(node *s) {
    mytime += 1;
    s->d = mytime;
    node *tmp = s->next;
    while (tmp != NULL) {
        dfs(adj[tmp->n]);
        tmp = tmp->next;
    }
    mytime += 1;
    s->f = mytime;
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int n,q,seed,parameter;
    cin>>n>>q>>seed>>parameter;
    auto ret=gen(n,q,seed,parameter);

    // for (int i = 0; i < n; i++) {
    //     cout << ret.first[i] << endl;
    // }
    // for (int i = 0; i < q; i++) {
    //     cout << ret.second.at(i).first << " " << ret.second.at(i).second << endl;
    // }
    
    // 生成树T的邻接表
    for (int i = 0; i < n; i++) {
        node *tmp = (node *)malloc(sizeof(node *));
        tmp->n = i;
        tmp->next = NULL;
        adj[i] = tmp;
    }
    for (int i = 0; i < n; i++) {
        int child = i;
        int parent = ret.first[child];
        if (parent != -1) {
            adj_insert(parent, child);
        }
    }
    // for (int i = 0; i < n; i++) {
    //     node *tmp = adj[i];
    //     while (tmp != NULL) {
    //         cout << tmp->n << " ";
    //         tmp = tmp->next;
    //     }
    //     cout << endl;
    // }

    // dfs
    int root = -1;
    for (int i = 0; i < n; i++) {
        if (ret.first[i] == -1) {
            root = i;
            break;
        }
    }
    dfs(adj[root]);
    // for (int i = 0; i < n; i++) {
    //     cout << adj[i]->d << " " << adj[i]->f << endl;
    // }
    uint64_t ans = 0;
    uint64_t add = 1;
    for (int i = 0; i < q; i++) {
        int p = ret.second.at(i).first;
        int c = ret.second.at(i).second;
        if (p == c) {
            ans += add;
            ans %= 998244353;
        } else if ( adj[p]->d <= adj[c]->d && adj[p]->f >= adj[c]->f) {
            ans += add;
            ans %= 9982443253;
        }
        add = (add << 1) % 998244353;
    }
    cout << ans << endl;
}