#include <bits/stdc++.h>
#define endl '\n'
using namespace std;
typedef long long ll;
const int N=15;
ll r[N],m[N];
int n;

void exgcd(ll a,ll b,ll &x,ll &y)
{
	if(!b)
	{
		x=1,y=0;
		return ;
	}
	exgcd(b,a%b,y,x);
	y-=a/b*x;
	return ;
}

ll CRT()
{
    ll pro=1;
    for(int i=1;i<=n;i++) pro*=m[i];
    ll x,y,Mi;
	ll ans=0;
    for(int i=1;i<=n;i++)
    {
        Mi=pro/m[i];
        exgcd(Mi,m[i],x,y);
        ans=(ans+Mi*r[i]*x)%pro;
    }
    return (ans+pro)%pro;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++) cin>>m[i]>>r[i];
	cout<<CRT()<<endl;
	
	return 0;
}


