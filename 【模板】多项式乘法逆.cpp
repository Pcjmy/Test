#include <bits/stdc++.h>
#define endl '\n'
using namespace std;
typedef long long ll;
typedef vector<int> vi;
const int mod=998244353;

vi rev,roots{0,1};
ll pm(ll a,ll b){
    ll ret=1;
    for(;b;b>>=1,a=a*a%mod)if(b&1)ret=ret*a%mod;
    return ret;
}
void dft(vi &a){
    int n=a.size();
    if (int(rev.size()) != n){
        int k=__builtin_ctz(n)-1;
        rev.resize(n);
        for (int i=0;i<n;i++)rev[i]=rev[i>>1]>>1|(i&1)<<k;
    }
    for (int i=0;i<n;i++)if (rev[i]<i)swap(a[i],a[rev[i]]);
    if (int(roots.size())<n){
        int k=__builtin_ctz(roots.size());
        roots.resize(n);
        while ((1 << k)<n){
            int e=pm(3,(mod-1) >>(k+1));
            for(int i=1<<(k-1);i<(1<<k);i++)
                roots[2*i]=roots[i],roots[2*i+1]=1ll*roots[i]*e%mod;
            ++k;
        }
    }
    for (int k=1;k<n;k*=2){
        for (int i=0;i<n;i += 2*k){
            for (int j=0;j<k;++j){
                int u=a[i+j];
                int v=1ll*a[i+j+k]*roots[k+j] % mod;
                int x=u+v;
                if (x>=mod)x -= mod;
                a[i+j]=x;
                x=u-v;
                if (x<0)x += mod;
                a[i+j+k]=x;
            }
        }
    }
}
void idft(vi &a){
    int n=a.size();
    reverse(a.begin()+1,a.end());
    dft(a);
    int inv=pm(n,mod-2);
    for (int i=0;i<n;++i)
        a[i]=(ll)a[i]*inv % mod;
}

struct Poly{
    vector<int>a;
    Poly(){}
    Poly(int a0){if (a0)a={a0};}
    Poly(const vector<int>&a1) : a(a1){
        while (!a.empty() && !a.back())a.pop_back();
    }
    int size() const{return a.size();}
    int operator[](int idx) const{
        if (idx<0||idx>=size())return 0;
        return a[idx];
    }
    Poly mulxk(int k) const{
        auto b=a;
        b.insert(b.begin(),k,0);
        return Poly(b);
    }
    Poly modxk(int k) const{
        k=min(k,size());
        return Poly(vector<int>(a.begin(),a.begin()+k));
    }
    Poly divxk(int k) const{
        if (size()<=k)return Poly();
        return Poly(vector<int>(a.begin()+k,a.end()));
    }
    friend Poly operator+(const Poly a,const Poly &b){
        vector<int>ret(max(a.size(),b.size()));
        for (int i=0;i<int(ret.size());++i){
            ret[i]=a[i]+b[i];
            if (ret[i]>=mod) ret[i] -= mod;
        }
        return Poly(ret);
    }
    friend Poly operator-(const Poly a,const Poly &b){
        vector<int>ret(max(a.size(),b.size()));
        for (int i=0;i<int(ret.size());++i){
            ret[i]=a[i]-b[i];
            if (ret[i]<0)ret[i] += mod;
        }
        return Poly(ret);
    }
    friend Poly operator*(Poly a,Poly b){
        int sz=1,tot=a.size()+b.size()-1;
        while (sz<tot) sz*=2;
        a.a.resize(sz);
        b.a.resize(sz);
        dft(a.a);
        dft(b.a);
        for (int i=0;i<sz;++i) a.a[i]=1ll*a[i]*b[i] % mod;
        idft(a.a);
        return Poly(a.a);
    }
    Poly &operator+=(Poly b){return (*this)=(*this)+b;}
    Poly &operator-=(Poly b){return (*this)=(*this)-b;}
    Poly &operator*=(Poly b){return (*this)=(*this)*b;}
    Poly deriv() const{
        if (a.empty())return Poly();
        vector<int>ret(size()-1);
        for (int i=0;i<size()-1;++i)
            ret[i]=1ll*(i+1)*a[i+1] % mod;
        return Poly(ret);
    }
//    Poly integr() const{
//        if (a.empty())return Poly();
//        vector<int>ret(size()+1);
//        for (int i=0;i<size();++i)
//            ret[i+1]=1ll*a[i]*pm(i+1,mod-2) % mod;
//        return Poly(ret);
//    }
    Poly inv(int m) const{
        Poly x(pm(a[0],mod-2));
        int k=1;
        while (k<m){
            k*=2;
            x=(x*(2-modxk(k)*x)).modxk(k);
        }
        return x.modxk(m);
    }
//    Poly log(int m) const{
//        return (deriv()*inv(m)).integr().modxk(m);
//    }
//    Poly exp(int m) const{
//        Poly x(1);
//        int k=1;
//        while (k<m){
//            k*=2;
//            x=(x*(1-x.log(k)+modxk(k))).modxk(k);
//        }
//        return x.modxk(m);
//    }
//    Poly sqrt(int m) const{
//        Poly x(1);
//        int k=1;
//        while (k<m){
//            k*=2;
//            x=(x+(modxk(k)*x.inv(k)).modxk(k))*((mod+1) / 2);
//        }
//        return x.modxk(m);
//    }
//    Poly mulT(Poly b) const{
//        if (b.size() == 0)return Poly();
//        int n=b.size();
//        reverse(b.a.begin(),b.a.end());
//        return ((*this)*b).divxk(n-1);
//    }
};

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	Poly P;
	vi v;
	int n;
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		int x;
		cin>>x;
		v.push_back(x);
	}
	P.a=v;
	Poly ans=P.inv(n);
	for(auto x:ans.a) cout<<x<<" ";
	cout<<endl;
	
	return 0;
}


