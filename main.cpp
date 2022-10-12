#include<bits/stdc++.h> 
//priority_queue next_permutation 
#define ll long long 
// #define int ll 
// #define double long double 
#define flot(n) cout << setprecision(n) << setiosflags(ios::fixed) << setiosflags(ios::showpoint) 
#define all(a) a.begin() , a.end() 
#define allr(a) a.rbegin() , a.rend() 
#define pb push_back 
#define mp make_pair 
#define pii pair<int,int> 
#define pll pair<ll,ll> 
#define piii pair<pii,int> 
#define plll pair<ll,pll> 
#define R return 
#define B break 
#define C continue 
#define SET(n , i) memset(n , i , sizeof(n)) 
#define SD ios::sync_with_stdio(0);cin.tie(0);cout.tie(0) 
#define rep(i , n) for(int i = 0 ; i < n ; i++) 
#define repn(i , j , n) for(int i = j ; i < n ; i++) 
#define repr(i,n,j) for(int i=n;i>=j;i--)
#define positive(x) (x%mod+mod)%mod
#define YES(f)cout<<(f?"YES":"NO")<<endl
#define F first 
#define S second 
#define endl '\n' 
using namespace std; 
void MAX(int32_t &x,int32_t y){x=max(x,y);} 
void MAX(ll &x,ll y){x=max(x,y);} 
void MIN(int32_t &x,int32_t y){x=min(x,y);} 
void MIN(ll &x,ll y){x=min(x,y);} 
const int INF = 0x3f3f3f3f; 
const ll INFLL = 0x3f3f3f3f3f3f3f3f; 
const double EPS = 1e-7; 
const double pi = 3.14159265358979323846;
const int mod = 1e9+7; 
const int N = 1e5+7; 
ll Mul(ll x,ll y){R((x%mod)*(y%mod))%mod;}
ll Add(ll x,ll y){R((x%mod)+(y%mod)+2ll*mod)%mod;} 
int n,k,a[N],parent[N];
vector<vector<int>> gr;
// sparse table + depth to find LCA in O(logn)
int mat[N][(int)log2(N)+5],dep[N],m;
void calc_sparse(int src , int par) {
    mat[src][0] = par;
    parent[src] = par;
    for(int i = 1 ; i < m ; i++) { // m = (int)log2(n)+1;
        mat[src][i] = mat[mat[src][i-1]][i-1];
    }
    for(int i = 0 ; i < gr[src].size() ; i++) {
        int nbr =  gr[src][i];
        if(nbr != par) {
            dep[nbr] = dep[src] + 1;
            calc_sparse(nbr,src);
        }  
    }
}
void build() {
    m = (int)log2(n) + 3;
    calc_sparse(1,0);
}
int lca(int x , int y) {
    if(x == y)return y;
    if(dep[x] > dep[y])swap(x,y);
    int dif = dep[y]-dep[x];
    for(int i = m - 1 ; i >= 0 ; i--) {
        if((dif >> i) & 1) {
            y = mat[y][i];
        }
    }
    if(y == x)return y;
    for(int i = m - 1 ; i >= 0 ; i--) {
        if(mat[y][i] != mat[x][i]) {
            y = mat[y][i];
            x = mat[x][i];
        }
    }
    return mat[y][0];
}
struct node;
extern node* null;
struct node {
    int freq;
    node *l , *r;
    node() {
        freq = 0;
        l=r=this;
    }
    node(int f,node *lft=null, node *rght=null) {
        freq = f;
        l = lft;
        r = rght;
    }
};
node *null = new node , *roots[N];
node *insert(node *root,int val,ll left = INT_MIN , ll right = INT_MAX) {
    if(left > val || right < val) R root;
    if(left == right) R new node(root->freq+1);
    ll mid = (left+right)/2;
    node *r1 = insert(root->l,val,left,mid);
    node *r2 = insert(root->r,val,mid+1,right);
    return new node(r1->freq+r2->freq,r1,r2);
}
void dfs(int src,int par) {
    roots[src] = insert(roots[par] , a[src]);
    for(auto it:gr[src]) {
        if(it == par) C;
        dfs(it,src);
    }
}
int query(node *u,node *v,node *lc ,node *plc,int x,ll left = INT_MIN , ll right = INT_MAX) {
    if(left == right) R left;
    ll mid = (left+right)/2;
    int suml = u->l->freq+v->l->freq-lc->l->freq-plc->l->freq;
    if(suml >= x) 
        return query(u->l,v->l,lc->l,plc->l,x,left,mid);
    return query(u->r,v->r,lc->r,plc->r,x-suml,mid+1,right);
}
void solve() {
    cin >> n >> k;
    gr.resize(n+3);
    repn(i,1,n+1)cin >> a[i];
    rep(i,n-1) {
        int x,y;
        cin >> x >> y;
        gr[x].pb(y);
        gr[y].pb(x);
    }
    build();
    roots[0] = null;
    dfs(1,0);
    while(k--) {
        int u,v,x,lc;
        cin >> u >> v >> x;
        lc = lca(u,v);
        cout << query(roots[u],roots[v],roots[lc],roots[parent[lc]],x) << endl;
    }
}
void sett(){ 
} 
int32_t main() { 
    SD; 
    int t = 1; 
    // cin >> t; 
    // scanf("%d" , &t); 
    while(t--){
        solve(); 
        sett(); 
    } 
}
