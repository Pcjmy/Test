#include <bits/stdc++.h>
#define endl '\n'
using namespace std;
typedef long long ll;
const int N=2e5+10;
struct node {
	int l,r,sum;
}tr[N<<5];
int a[N],b[N],root[N];
int n,m,num,tot;

int find(int x)
{
	return lower_bound(b+1,b+num+1,x)-b;
}

int change(int p,int l,int r,int x)
{
	int q=++tot;
	tr[q]=tr[p];
	if(l==r)
	{
		tr[q].sum++;
		return q;
	}
	int mid=(l+r)>>1;
	if(x<=mid) tr[q].l=change(tr[p].l,l,mid,x);
	else tr[q].r=change(tr[p].r,mid+1,r,x);
	tr[q].sum=tr[tr[q].l].sum+tr[tr[q].r].sum;
	return q;
}

int query(int p,int q,int l,int r,int k)
{
	if(l==r) return l;
	int tmp=tr[tr[q].l].sum-tr[tr[p].l].sum;
	int mid=(l+r)>>1;
	if(tmp>=k) return query(tr[p].l,tr[q].l,l,mid,k);
	else return query(tr[p].r,tr[q].r,mid+1,r,k-tmp);
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=n;i++) cin>>a[i],b[i]=a[i];
	sort(b+1,b+n+1);
	num=unique(b+1,b+n+1)-(b+1);
	for(int i=1;i<=n;i++)
	{
		int x=find(a[i]);
		root[i]=change(root[i-1],1,num,x);
	}
	while(m--)
	{
		int l,r,k;
		cin>>l>>r>>k;
		cout<<b[query(root[l-1],root[r],1,num,k)]<<endl;
	}
	
	return 0;
}


