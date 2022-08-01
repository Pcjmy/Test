#include <bits/stdc++.h>
#define endl '\n'
using namespace std;
typedef long long ll;
set<string> s;
int n;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		string x;
		cin>>x;
		s.insert(x);
	}
	cout<<s.size()<<endl;
	
	return 0;
}


