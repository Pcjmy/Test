#include <bits/stdc++.h>
#define endl '\n'
using namespace std;
typedef long long ll;
const int N=1e5+10;
const int M=2*N;
int head[N],e[M],ne[M],tot;
int a[N],nw[N],dep[N],fa[N],son[N],sz[N],top[N],id[N];
ll tr[N<<2],tag[N<<2];
int n,m,root,mod,cnt;

void add(int x,int y)
{
	e[++tot]=y,ne[tot]=head[x],head[x]=tot;
}

void dfs1(int x,int f,int depth)
{
	dep[x]=depth; fa[x]=f; sz[x]=1;
	for(int i=head[x];i;i=ne[i])
	{
		int y=e[i];
		if(y==f) continue;
		dfs1(y,x,depth+1);
		sz[x]+=sz[y];
		if(sz[y]>sz[son[x]]) son[x]=y;
	}
}

void dfs2(int x,int t)
{
	id[x]=++cnt; nw[cnt]=a[x]; top[x]=t;
	if(!son[x]) return ;
	dfs2(son[x],t);
	for(int i=head[x];i;i=ne[i])
	{
		int y=e[i];
		if(y==fa[x]||y==son[x]) continue;
		dfs2(y,y);
	}
}

void build(int p,int l,int r)
{
	if(l==r)
	{
		tr[p]=nw[l];
		return ;
	}
	int mid=(l+r)>>1;
	build(p<<1,l,mid);
	build(p<<1|1,mid+1,r);
	tr[p]=(tr[p<<1]+tr[p<<1|1])%mod;
}

void addtag(int p,int l,int r,ll d)
{
	tr[p]+=(r-l+1)*d;
	tag[p]+=d;
	tr[p]%=mod;
	tag[p]%=mod;
}

void pushdown(int p,int l,int r)
{
	if(tag[p])
	{
		int mid=(l+r)>>1;
		addtag(p<<1,l,mid,tag[p]);
		addtag(p<<1|1,mid+1,r,tag[p]);
		tag[p]=0;
	}
}

void change(int p,int l,int r,int x,int y,ll d)
{
	if(x<=l&&y>=r)
	{
		tr[p]+=(r-l+1)*d;
		tag[p]+=d;
		tr[p]%=mod;
		tag[p]%=mod;
		return ;
	}
	pushdown(p,l,r);
	int mid=(l+r)>>1;
	if(x<=mid) change(p<<1,l,mid,x,y,d);
	if(y>mid)  change(p<<1|1,mid+1,r,x,y,d);
	tr[p]=(tr[p<<1]+tr[p<<1|1])%mod;
}

ll query(int p,int l,int r,int x,int y)
{
	if(x<=l&&y>=r) return tr[p];
	pushdown(p,l,r);
	int mid=(l+r)>>1;
	ll ans=0;
	if(x<=mid) ans+=query(p<<1,l,mid,x,y);
	if(y>mid)  ans+=query(p<<1|1,mid+1,r,x,y);
	ans%=mod;
	return ans;
}

void update_path(int x,int y,int z)
{
	while(top[x]!=top[y])
	{
		if(dep[top[x]]<dep[top[y]]) swap(x,y);
		change(1,1,n,id[top[x]],id[x],z);
		x=fa[top[x]];
	}
	if(dep[x]<dep[y]) swap(x,y);
	change(1,1,n,id[y],id[x],z);
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

void update_tree(int x,int z)
{
	change(1,1,n,id[x],id[x]+sz[x]-1,z);
}

ll query_tree(int x)
{
	return query(1,1,n,id[x],id[x]+sz[x]-1);
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	cin>>n>>m>>root>>mod;
	for(int i=1;i<=n;i++) cin>>a[i];
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


