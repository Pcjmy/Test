#include <bits/stdc++.h>
#define endl '\n'
using namespace std;
typedef long long ll;
const int N=5e5+10;
const int M=1e6+10;
int head[N],e[M],ne[M],tot;
int f[N][20],d[N];
queue<int> q;
int n,m,s,t;

void add(int x,int y)
{
	e[++tot]=y,ne[tot]=head[x],head[x]=tot;
}

void bfs(int s)
{
    d[s]=1;  
	q.push(s);
    while(q.size()) 
	{
        int x=q.front(); q.pop();
        for(int i=head[x];i;i=ne[i]) 
		{
            int y=e[i];
			if(d[y]) continue;
            d[y]=d[x]+1;  
            f[y][0]=x;
            for(int j=1;j<=t;j++)
                f[y][j]=f[f[y][j-1]][j-1];
            q.push(y);
        }
    }
}

int lca(int x,int y)
{
    if(d[x]>d[y]) swap(x,y);
    for(int i=t;i>=0;i--) if(d[f[y][i]]>=d[x]) y=f[y][i];
    if(x==y) return x;
    for(int i=t;i>=0;i--) {
        if(f[x][i]!=f[y][i])
            x=f[x][i],y=f[y][i];
    }
    return f[x][0];
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
    cin>>n>>m>>s;
    t=(int)(log(n)/log(2))+1;
    for(int i=1;i<n;i++)
    {
    	int x,y;
    	cin>>x>>y;
    	add(x,y);
    	add(y,x);
	}
    bfs(s);
    while(m--)
	{
		int x,y;
		cin>>x>>y;
		cout<<lca(x,y)<<endl;
    }
    
    return 0;
}



