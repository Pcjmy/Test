#include <bits/stdc++.h>
#define endl '\n'
using namespace std;
typedef long long ll;
const int N=1e5+10;
ll a[N];
int n;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	ll ans=__gcd(a[1],a[2]);
	for(int i=3;i<=n;i++) ans=__gcd(ans,a[i]);
	cout<<abs(ans)<<endl;
	
	return 0;
}


