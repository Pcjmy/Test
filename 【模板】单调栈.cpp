#include <bits/stdc++.h>
#define endl '\n'
using namespace std;
typedef long long ll;
const int N=3e6+10;
int a[N],stk[N],R[N];
int n,tt;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	stk[++tt]=0; a[0]=1e9+10;
	for(int i=1;i<=n;i++)
	{
	    while(a[stk[tt]]<a[i]) R[stk[tt]]=i,tt--;
	    stk[++tt]=i;
	}
	for(int i=1;i<=n;i++) cout<<R[i]<<" ";
	cout<<endl;
	
	return 0;
}
