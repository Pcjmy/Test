#include <bits/stdc++.h>
#define endl '\n'
using namespace std;
typedef long long ll;
const int N=2e5+10;
const int M=2e6+10;
int n;
struct ACAM {
	int tr[N][26],cnt;
	int fail[N],ref[N],ans[N],in[N];
	void insert(string s,int x)
	{
		int p=0;
		for(int i=0;i<s.size();i++)
		{
			int u=s[i]-'a';
			if(!tr[p][u]) tr[p][u]=++cnt;
			p=tr[p][u];
		}
		ref[x]=p;
	}
	void build()
	{
		queue<int> q;
		for(int i=0;i<26;i++) if(tr[0][i]) q.push(tr[0][i]);
		while(q.size()>0)
		{
			int x=q.front();
			q.pop();
			for(int i=0;i<26;i++)
			{
				if(tr[x][i])
				{
					fail[tr[x][i]]=tr[fail[x]][i];
					in[tr[fail[x]][i]]++;
					q.push(tr[x][i]);
				}
				else
				{
					tr[x][i]=tr[fail[x]][i];
				}
			}
		}
	}
	void query(string s)
	{
		int p=0;
		for(int i=0;i<s.size();i++)
		{
			int u=s[i]-'a';
			p=tr[p][u];
			ans[p]++;
		}
	}
	void top()
	{
		queue<int> q;
		for(int i=1;i<=cnt;i++) if(!in[i]) q.push(i);
		while(q.size()>0)
		{
			int x=q.front();
			q.pop();
			ans[fail[x]]+=ans[x];
			if(--in[fail[x]]==0) q.push(fail[x]);
		}
		for(int i=1;i<=n;i++) cout<<ans[ref[i]]<<endl;
	}
}ac;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	cin>>n;
	string s;
	for(int i=1;i<=n;i++)
	{
		cin>>s;
		ac.insert(s,i);
	}
	ac.build();
	cin>>s;
	ac.query(s);
	ac.top();
	
	return 0;
}


