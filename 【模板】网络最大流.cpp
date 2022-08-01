#include <bits/stdc++.h>
#define endl '\n'
using namespace std;
typedef long long ll;
const int N=210;
const int M=10010;
const int inf=1<<30;
int head[N],e[M],ne[M],w[M],tot=1;
int v[N],pre[N],incf[N];
int n,m,s,t;
ll ans;

void add(int x,int y,int z)
{
	e[++tot]=y,ne[tot]=head[x],w[tot]=z,head[x]=tot;
}

bool bfs()
{
	memset(v,0,sizeof(v));
//	memset(pre,-1,sizeof(pre));
	queue<int> q;
	incf[s]=inf;
	q.push(s);
	v[s]=1;
	while(q.size()>0)
	{
		int x=q.front();
		q.pop();
		for(int i=head[x];i;i=ne[i])
		{
			int y=e[i];
			int z=w[i];
			if(!v[y]&&z)
			{
				v[y]=1;
				q.push(y);
				incf[y]=min(z,incf[x]);
				pre[y]=i;
				if(y==t) return true;
			}
		}
	}
	return false;
}

ll EK()
{
	ll maxflow=0;
	while(bfs())
	{
		int x=t;
		while(x!=s)
		{
			int i=pre[x];
			w[i]-=incf[t];
			w[i^1]+=incf[t];
			x=e[i^1];
		}
		maxflow+=incf[t];
	}
	return maxflow;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	cin>>n>>m>>s>>t;
	for(int i=1;i<=m;i++)
	{
		int x,y,z;
		cin>>x>>y>>z;
		add(x,y,z);
		add(y,x,0);
	}
	cout<<EK()<<endl;
	
	return 0;
}
