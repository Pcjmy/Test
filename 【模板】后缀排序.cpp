#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=1e6+10;
int sa[N],x[N<<1],y[N<<1],c[N];
char s[N];
int n,m;

void get_sa()
{
	for(int i=1;i<=n;i++) c[x[i]=s[i]]++;
	for(int i=1;i<=m;i++) c[i]+=c[i-1];
	for(int i=n;i>=1;i--) sa[c[x[i]]--]=i;
	for(int k=1;k<=n;k<<=1)
	{
		int num=0;
		for(int i=n-k+1;i<=n;i++) y[++num]=i;
		for(int i=1;i<=n;i++)
		{
			if(sa[i]>k)
			{
				y[++num]=sa[i]-k;
			}
		}
		for(int i=1;i<=m;i++) c[i]=0;
		for(int i=1;i<=n;i++) c[x[i]]++;
		for(int i=1;i<=m;i++) c[i]+=c[i-1];
		for(int i=n;i>=1;i--) sa[c[x[y[i]]]--]=y[i],y[i]=0;
		swap(x,y);
		x[sa[1]]=1,num=1;
		for(int i=2;i<=n;i++)
		{
			x[sa[i]]=(y[sa[i]]==y[sa[i-1]]&&y[sa[i]+k]==y[sa[i-1]+k])?num:++num;
		}
		if(num==n) break;
		m=num;
	}
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	cin>>s+1;
	n=strlen(s+1);
	m=122;
	get_sa();
	for(int i=1;i<=n;i++) cout<<sa[i]<<" ";
	cout<<endl;
	
	return 0;
}


