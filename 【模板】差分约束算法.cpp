#include <bits/stdc++.h>
#define endl '\n'
using namespace std;
typedef long long ll;
const int N=1e4+10;
const int M=2e4+10;
int head[N],e[M],ne[M],w[M],tot;
int dis[N],cnt[N];
bool vis[N];
queue<int> q;
int n,m;

void add(int x,int y,int z)
{
	e[++tot]=y,ne[tot]=head[x],w[tot]=z,head[x]=tot;
}

bool spfa()
{
	memset(dis,0x3f,sizeof(dis));
	dis[0]=0;
	q.push(0);
	vis[0]=true;
	while(q.size()>0)
	{
		int x=q.front();
		q.pop();
		vis[x]=false;
		for(int i=head[x];i;i=ne[i])
		{
			int y=e[i];
			if(vis[y]) continue;
			if(dis[y]>dis[x]+w[i])
			{
				cnt[y]=cnt[x]+1;
				if(cnt[y]>n) return false;
				dis[y]=dis[x]+w[i];
				q.push(y);
			}
		}
	}
	return true;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=m;i++)
	{
		int x,y,z;
		cin>>x>>y>>z;
		add(y,x,z);
		add(0,x,0);
		add(0,y,0);
	}
	if(spfa())
	{
		for(int i=1;i<=n;i++) cout<<dis[i]<<" ";
		cout<<endl;
	}
	else
	{
		cout<<"NO"<<endl;
	}
	
	return 0;
}
