#include <bits/stdc++.h>
#define lc(x) (x<<1)
#define rc(x) (lc(x)|1)
#define endl '\n'
using namespace std;
typedef long long ll;
const int N=1e5+10;
const int M=2*N;
int head[N],w[N],e[M],ne[M],tot;
int id[N],nw[N],cnt;
int dep[N],siz[N],top[N],fa[N],son[N];
ll tr[N<<2],tag[N<<2];
int n,m,root,mod;

void add(int x,int y)
{
	e[++tot]=y,ne[tot]=head[x],head[x]=tot;
}

void dfs1(int x,int f,int depth)
{
	dep[x]=depth;
	fa[x]=f;
	siz[x]=1;
	for(int i=head[x];i;i=ne[i])
	{
		int y=e[i];
		if(y==f) continue;
		dfs1(y,x,depth+1);
		siz[x]+=siz[y];
		if(siz[son[x]]<siz[y]) son[x]=y;
	}
}

void dfs2(int x,int t)
{
	id[x]=++cnt;
	nw[cnt]=w[x];
	top[x]=t;
	if(!son[x]) return ;
	dfs2(son[x],t);
	for(int i=head[x];i;i=ne[i])
	{
		int y=e[i];
		if(y==fa[x]||y==son[x]) continue;
		dfs2(y,y);
	}
}
	
void addtag(ll p,ll l,ll r,ll k)
{
	tag[p]+=k;
	tr[p]+=(r-l+1)*k;
	tag[p]%=mod;
	tr[p]%=mod;
}

void pushdown(ll p,ll l,ll r) {
	if(tag[p])
	{
		int mid=(l+r)>>1;
		addtag(p*2,l,mid,tag[p]);
		addtag(p*2+1,mid+1,r,tag[p]);
		tag[p]=0;
	}
}

void pushup(int p)
{
	tr[p]=(tr[lc(p)]+tr[rc(p)])%mod;
}

void build(int p,int l,int r) {
	if(l==r) { tr[p]=nw[l]; return; }
	int mid=(l+r)>>1;
	build(lc(p),l,mid);
	build(rc(p),mid+1,r);
	pushup(p);
}

void change(int p,int l,int r,int x,int y,ll d) {
	if(x<=l&&y>=r)
	{ 
		tr[p]+=d*(r-l+1);
		tag[p]+=d;
		tag[p]%=mod;
		tr[p]%=mod;
		return;
	}
	int mid=(l+r)>>1;
	pushdown(p,l,r);
	if(x<=mid) change(lc(p),l,mid,x,y,d);
	if(y>mid)  change(rc(p),mid+1,r,x,y,d);
	pushup(p);
}

int query(int p,int l,int r,int x,int y) {
	if(x<=l&&r<=y) return tr[p];
	pushdown(p,l,r);
	int mid=(l+r)>>1;
	ll sum=0;
	if(x<=mid) sum+=query(lc(p),l,mid,x,y),sum%=mod;
	if(y>mid)  sum+=query(rc(p),mid+1,r,x,y),sum%=mod;
	return sum;
}

void update_path(int x,int y,ll k)
{
	while(top[x]!=top[y])
	{
		if(dep[top[x]]<dep[top[y]]) swap(x,y);
		change(1,1,n,id[top[x]],id[x],k);
		x=fa[top[x]];
	}
	if(dep[x]<dep[y]) swap(x,y);
	change(1,1,n,id[y],id[x],k);
}

ll query_path(int x,int y)
{
	ll ans=0;
	while(top[x]!=top[y])
	{
		if(dep[top[x]]<dep[top[y]]) swap(x,y);
		ans+=query(1,1,n,id[top[x]],id[x]);
		ans%=mod;
		x=fa[top[x]];
	}
	if(dep[x]<dep[y]) swap(x,y);
	ans+=query(1,1,n,id[y],id[x]);
	ans%=mod;
	return ans;
}

void update_tree(int x,ll k)
{
	change(1,1,n,id[x],id[x]+siz[x]-1,k);
}

ll query_tree(int x)
{
	return query(1,1,n,id[x],id[x]+siz[x]-1);
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	cin>>n>>m>>root>>mod;
	for(int i=1;i<=n;i++) cin>>w[i];
	for(int i=1;i<n;i++)
	{
		int x,y;
		cin>>x>>y;
		add(x,y);
		add(y,x);
	}
	dfs1(root,-1,1);
	dfs2(root,root);
	build(1,1,n);
	while(m--)
	{
		int t,x,y,z;
		cin>>t;
		if(t==1)
		{
			cin>>x>>y>>z;
			update_path(x,y,z);
		}
		if(t==2)
		{
			cin>>x>>y;
			cout<<query_path(x,y)<<endl;
		}
		if(t==3)
		{
			cin>>x>>z;
			update_tree(x,z);
		}
		if(t==4)
		{
			cin>>x;
			cout<<query_tree(x)<<endl;
		}
	}
	
	return 0;
}
