#include <bits/stdc++.h>
#define endl '\n'
using namespace std;
typedef long long ll;
int n;

int sgn(ll x)
{
	if(!x) return 0;
	return x>0?1:-1;
}

struct Point {
	ll x,y;
	Point() {}
	Point(ll x,ll y): x(x),y(y) {}
	void in() { cin>>x>>y; }
	Point operator-(Point b) { return Point(x-b.x,y-b.y); }
	bool operator <(Point b) const {return sgn(x-b.x)==0?sgn(y-b.y)<0:x<b.x;}
	ll operator ^(Point b){return x*b.y-y*b.x;}
	ll len2() { return x*x+y*y; }
	ll dis(Point p) {return (*this-p).len2();}
	ll cross(Point b,Point c) { return (b-*this)^(c-*this); }
};

struct Pol {
	vector<Point> p;
	Pol(int n=0) { p.resize(n); }
	void in() { for(auto &x:p) x.in(); }
	void get_convex() {
	    sort(p.begin(),p.end());
	    vector<Point> u,d;
	    for(int i=0;i<p.size();i++) {
	 	   while(d.size()>1&&sgn(d[d.size()-2].cross(d.back(),p[i]))<=0) d.pop_back();
	        d.push_back(p[i]);
	    }
	    for(int i=p.size()-1;~i;i--) {
	    	while(u.size()>1&&sgn(u[u.size()-2].cross(u.back(),p[i]))<=0) u.pop_back();
	        u.push_back(p[i]);
	    }
	    p=d;
	    for(int i=1;i<(int)u.size()-1;i++) p.push_back(u[i]);
	}
	ll RotateCalipers() {
		ll ans=0;
		int t=1,n=p.size();
		p.push_back(p[0]);
		for(int i=0;i<n;++i) {
			while(((p[t]-p[i+1])^(p[i]-p[i+1]))<((p[t+1]-p[i+1])^(p[i]-p[i+1]))) t=(t+1)%n;
			ans=max(ans,max(p[t].dis(p[i]),p[t+1].dis(p[i+1])));
		}
		p.pop_back();
		return ans;
	}
};

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	cin>>n;
	Pol A(n);
	A.in();
	A.get_convex();
	cout<<A.RotateCalipers()<<endl;
	
	return 0;
}
