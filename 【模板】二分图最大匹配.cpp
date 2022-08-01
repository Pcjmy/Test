#include <bits/stdc++.h>
#define endl '\n'
using namespace std;
typedef long long ll;
const int N=1e5;
const int M=1e5;
int head[N],e[M],ne[M],tot;
int match[N];   
bool vis[N];
int n,m,z;

void add(int x,int y)
{
	e[++tot]=y,ne[tot]=head[x],head[x]=tot;
}

bool find(int x) {
	for(int i=head[x];i;i=ne[i]) {
		int y=e[i];
		if(!vis[y]) {
			vis[y]=true;
			if(match[y]==0||find(match[y])) {
				match[y]=x;
				return true;
			}
		}
	}
	return false;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	cin>>n>>m>>z;
	for(int i=1;i<=z;i++)
	{
		int x,y;
		cin>>x>>y;
		add(x,y);
	}
	int res=0;
	for(int i=1;i<=n;i++) {
		memset(vis,0,sizeof(vis));
		if(find(i)) res++;
	}
	cout<<res<<endl;
	
	return 0;
}


