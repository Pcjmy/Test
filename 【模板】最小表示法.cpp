#include <bits/stdc++.h>
#define endl '\n'
using namespace std;
const int N=3e5+10;
int s[N<<1];
int n;

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++) cin>>s[i];
	for(int i=1;i<=n;i++) s[n+i]=s[i];
	int i=1,j=2,k;
	while(i<=n&&j<=n)
	{
		for(k=0;k<n&&s[i+k]==s[j+k];k++);
		if(k==n) break;
		if(s[i+k]>s[j+k])
		{
			i=i+k+1;
			if(i==j) i++;
		}
		else
		{
			j=j+k+1;
			if(i==j) j++;
		}
	}
	int ans=min(i,j);
	for(int i=ans;i<n+ans;i++) cout<<s[i]<<" ";
	cout<<endl;
	
	return 0;
}
