#include <bits/stdc++.h>
#define endl '\n'
using namespace std;
typedef long long ll;

void exgcd(ll a,ll b,ll &x,ll &y)
{
	if(!b)
	{
		x=1,y=0;
		return ;
	}
	exgcd(b,a%b,y,x);
	y-=a/b*x;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	int _;
	cin>>_;
	while(_--)
	{
		ll a,b,c;
		cin>>a>>b>>c;
		ll d=__gcd(a,b);
		if(c%d) cout<<-1<<endl;
		else
		{
			ll x,y;
			exgcd(a,b,x,y);
			x=x*c/d,y=y*c/d;
			a/=d,b/=d;
			ll xn=(x%b+b)%b;
			ll yn=(y%a+a)%a;
			if(!xn) xn+=b;
			if(!yn) yn+=a;
			ll u=(-x+1)/b,v=(y-1)/a;
			if(-x+1>0) u=(-x+1+b-1)/b;
			else u=(-x+1)/b;
			if(y-1<0) v=(y-1-a+1)/a;
			else v=(y-1)/a;
			if(u<=v)
			{
				cout<<v-u+1<<" "<<xn<<" "<<yn<<" "<<x+v*b<<" "<<y-u*a<<endl;
			}
			else
			{
				cout<<xn<<" "<<yn<<endl;
			}
		}
	}
	
	return 0;
}


