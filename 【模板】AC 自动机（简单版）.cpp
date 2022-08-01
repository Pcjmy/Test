#include <bits/stdc++.h>
#define endl '\n'
using namespace std;
typedef long long ll;
const int N=2e5+10;
const int M=2e6+10;
char str[M];
struct ACAM {
	int tr[N][26],cnt;
	int ed[N];
	int fail[N];
	ACAM()
	{
	    memset(tr,0,sizeof(tr));
	    memset(ed,0,sizeof(ed));
	    memset(fail,0,sizeof(fail));
	    cnt=0;
	}
	void insert(char s[])
	{
		int p=0;
		for(int i=0;s[i];i++) {
			int u=s[i]-'a';
			if(!tr[p][u]) tr[p][u]=++cnt;
			p=tr[p][u];
		}
		ed[p]++;
	}
	void build()
	{
		queue<int> q;
		for(int i=0;i<26;i++) if(tr[0][i]) q.push(tr[0][i]);
		while(q.size()>0) {
			int k=q.front();  q.pop();
			for(int i=0;i<26;i++) {
				if(tr[k][i]) {
					fail[tr[k][i]]=tr[fail[k]][i];
					q.push(tr[k][i]);
				}
				else tr[k][i]=tr[fail[k]][i];
			}
		}
	}
	int query(char s[])
	{
		int p=0,ans=0;
		for(int i=0;s[i];i++) {
			p=tr[p][s[i]-'a'];
			for(int j=p;j&&~ed[j];j=fail[j]) ans+=ed[j],ed[j]=-1;
		}
		return ans;
	}
}ac;  

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	int n;
	cin>>n;
	while(n--)
	{
		cin>>str;
		ac.insert(str);
	}
	ac.build();
	cin>>str;
	cout<<ac.query(str)<<endl;
	
	return 0;
}


