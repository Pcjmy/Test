#include <bits/stdc++.h>
#define endl '\n'
using namespace std;
typedef long long ll;
const int N=1e5+10;
struct node {
	int c,x;
}p[N];
int a[N],tr[N<<2];
int n,tot;

int find(int x)
{
	return lower_bound(a+1,a+tot+1,x)-a;
}

void change(int p,int l,int r,int x,int d)
{
	if(l==r)
	{
		tr[p]+=d;
		return ;
	}
	int mid=(l+r)>>1;
	if(x<=mid) change(p<<1,l,mid,x,d);
	else change(p<<1|1,mid+1,r,x,d);
	tr[p]=tr[p<<1]+tr[p<<1|1];
}

int query(int p,int l,int r,int x)
{
	if(l==r) return l;
	int mid=(l+r)>>1;
	if(tr[p<<1]>=x) return query(p<<1,l,mid,x);
	else return query(p<<1|1,mid+1,r,x-tr[p<<1]);
}

int queryrk(int p,int l,int r,int x,int y)
{
	if(x<=l&&y>=r) return tr[p];
	int mid=(l+r)>>1;
	int ans=0;
	if(x<=mid) ans+=queryrk(p<<1,l,mid,x,y);
	if(y>mid)  ans+=queryrk(p<<1|1,mid+1,r,x,y);
	return ans;
}

int main()
{
	freopen("output.txt","w",stdout);
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		cin>>p[i].c>>p[i].x;
		if(p[i].c!=4) a[++tot]=p[i].x;
	}
	sort(a+1,a+tot+1);
	tot=unique(a+1,a+tot+1)-(a+1);
//	for(int i=1;i<=tot;i++) cout<<a[i]<<" ";
//	cout<<endl;
	for(int i=1;i<=n;i++)
	{
		int t=p[i].c,x=p[i].x;
		if(t!=4) x=find(x);
		if(t==1)
		{
			change(1,1,tot,x,1);
		}
		if(t==2)
		{
			change(1,1,tot,x,-1);
		}
		if(t==3)
		{
			if(x==1) cout<<1<<endl;
			else cout<<queryrk(1,1,tot,1,x-1)+1<<endl;
		}
		if(t==4)
		{
			cout<<a[query(1,1,tot,x)]<<endl;
		}
		if(t==5)
		{
			int rk=queryrk(1,1,tot,1,x-1);
			cout<<a[query(1,1,tot,rk)]<<endl;
		}
		if(t==6)
		{
			int rk=queryrk(1,1,tot,1,x)+1;
			cout<<a[query(1,1,tot,rk)]<<endl;
		}
	}
	
	return 0;
}
