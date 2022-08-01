#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
const int N=10;
const double PI = acos(-1);
const double eps = 1e-8;
int sign(double x) {return x <= -eps ? -1 : (x < eps ? 0 : 1);}
struct Point3{
    double x, y, z;
    void in(){scanf("%lf%lf%lf",&x,&y,&z);}
    void out(){printf("%lf %lf %lf\n",x,y,z);}
    Point3(double _x = 0, double _y = 0, double _z = 0): x(_x), y(_y), z(_z) {}
    bool operator ==(Point3 b) {return !sign(x - b.x) && !sign(y - b.y) && !sign(z - b.z);}
    bool operator <(Point3 b) {return !sign(x - b.x) ? (!sign(y - b.y) ? sign(z - b.z) < 0 : y < b.y) : x < b.x;}
    Point3 operator -(Point3 b) {return Point3(x - b.x, y - b.y, z - b.z);}
    Point3 operator +(Point3 b) {return Point3(x + b.x, y + b.y, z + b.z);}
    Point3 operator *(double k) {return Point3(x * k, y * k, z * k);}
    Point3 operator /(double k) {return Point3(x / k, y / k, z / k);}
    double operator *(Point3 b) {return x * b.x + y * b.y + z * b.z;}//点乘
    Point3 operator ^(Point3 b) {return Point3(y * b.z - z * b.y, z * b.x - x * b.z, x * b.y - y * b.x);}//叉乘
    double len2() {return x * x + y * y + z * z;}
    double len() {return sqrt(len2());}
    double dis(Point3 b) {return (*this - b).len();}
    Point3 cross(Point3 b,Point3 c) {return (b-*this)^(c-*this);}//ab^ac
    double rad(Point3 a, Point3 b) { //计算pa和pb的夹角（弧度制）
        Point3 p = *this;
        return acos( ((a - p) * (b - p)) / (a.dis(p) * b.dis(p)) );
    }
    Point3 trunc(double r) {//更改为长度为r的向量，可以负数改变方向
        double l = len();
        if(!sign(l)) return *this;
        r/= l;
        return Point3(x * r, y * r, z * r);
    }
};
struct Line3{
    Point3 s, e;
    Line3() {}
    Line3(Point3 _s, Point3 _e): s(_s), e(_e) {}
    bool operator ==(Line3 v) {return (s == v.s) && (e == v.e);}
    double length() {return s.dis(e);}
    //点到直线距离
    double dispointtoline(Point3 p){return ((e - s) ^ (p - s)).len() / s.dis(e);}
    double dispointtoseg(Point3 p) { //点到线段距离
        if(sign((p - s) * (e - s)) < 0 || sign((p - e) * (s - e)) < 0)
            return min(p.dis(s), e.dis(p));
        return dispointtoline(p);
    }
    //返回点 p 在直线上的投影
    Point3 lineprog(Point3 p){return s + ( ((e - s) * ((e - s) * (p - s))) / ((e - s).len2()) );}
    Point3 rotate(Point3 p, double arg) { //p绕此向量逆时针 arg 角度
        if(sign(((s - p) ^ (e - p)).len()) == 0) return p;
        Point3 f1 = (e - s) ^ (p - s);
        Point3 f2 = (e - s) ^ (f1);
        double len = ((s - p) ^ (e - p)).len() / s.dis(e);
        f1 = f1.trunc(len);
        f2 = f2.trunc(len);
        Point3 h = p + f2;
        Point3 pp = h + f1;
        return h + ((p - h) * cos(arg)) + ((pp - h) * sin(arg));
    }
    //点在直线上
    bool pointonseg(Point3 p){return !sign((s-p^e-p).len())&&!sign((s-p)*(e-p));}
};
struct Plane{
    Point3 a, b, c, o; //平面上的三个点,以及法向量
    Plane() {}
    Plane(Point3 _a, Point3 _b, Point3 _c):a(_a),b(_b),c(_c){o = pvec();}
    Point3 pvec() {return (b - a) ^ (c - a);}
    Plane(double _a, double _b, double _c, double _d) { //ax+by+cz+d = 0
        o = Point3(_a, _b, _c);
        if(sign(_a) != 0)a = Point3((-_d - _c - _b) / _a, 1, 1);
        else if(sign(_b) != 0)a = Point3(1, (-_d - _c - _a) / _b, 1);
        else if(sign(_c) != 0)a = Point3(1, 1, (-_d - _a - _b) / _c);
    }
    //点在平面上的判断
    bool pointonplane(Point3 p){return sign((p - a) * o) == 0;}
    //两平面夹角
    double angleplane(Plane f){return acos(o * f.o) / (o.len() * f.o.len());}
    int crossline(Line3 u, Point3 &p) { //平面和直线的交点，返回值是交点个数
        double x = o * (u.e-a);
        double y = o * (u.s - a);
        double d = x - y;
        if(sign(d) == 0)return 0;
        p = ((u.s * x) - (u.e * y)) / d;
        return 1;
    }
    Point3 pointtoplane(Point3 p) { //点到平面最近点 (也就是投影)
        Line3 u = Line3(p, p + o);
        crossline(u, p);
        return p;
    }
    int crossplane(Plane f, Line3 &u) { //平面和平面的交线
        Point3 oo = o ^ f.o;
        Point3 v = o ^ oo;
        double d = fabs(f.o * v);
        if(sign(d) == 0) return 0;
        Point3 q = a + (v * (f.o * (f.a - a)) / d);
        u = Line3(q, q + oo);
        return 1;
    }
};

struct Pol{
	struct face{
        int a,b,c;//表示凸包一个面上的三个点的编号
		bool ok;//表示该面是否属于最终的凸包上的面
	};
	int n; //初始顶点数
	Point3 P[N]; //多面体所有的点
	int num; //凸包表面的三角形数
	face F[8*N]; //凸包表面的三角形，法向量朝外，下标从0开始
	int g[N][N]; //方向为i->j的边所在的表面三角形的编号
	//三角形面积*2
	double area(Point3 a,Point3 b,Point3 c) {return a.cross(b,c).len();}
	//四面体有向面积*6
	double volume(Point3 a,Point3 b,Point3 c,Point3 d) {return a.cross(b,c)*(d-a);}
    //点p和面f形成的四面体的有向面积,当点和面同向时为正
	double dblcmp(Point3 p,face f){return volume(P[f.a],P[f.b],P[f.c],p);}
	void deal(int p,int a,int b) {
		int f = g[a][b];
		face add;
		if(F[f].ok)
        {
			if(dblcmp(P[p],F[f]) > eps)dfs(p,f);
			else
            {
                add={b,a,p,true};
				g[p][b] = g[a][p] = g[b][a] = num;
				F[num++] = add;
			}
		}
	}
	void dfs(int p,int now) { //递归搜索所有应该从凸包内删除的面
		F[now].ok = false;
		deal(p,F[now].b,F[now].a);
		deal(p,F[now].c,F[now].b);
		deal(p,F[now].a,F[now].c);
	}
	void getconvex()
	{//增量法求三维凸包
	//*****************此段是为了保证前四个点不共面******************
		bool flag = true;
		for(int i = 1; i < n; i++)if(!(P[0] == P[i]))
            {swap(P[1],P[i]);flag = false;break;}
		if(flag)return;flag = true;
		for(int i = 2; i < n; i++)if(area(P[0],P[1],P[i]) > eps)
			{swap(P[2],P[i]);flag = false;break;}
		if(flag)return;flag = true;
		for(int i = 3; i < n; i++)if(fabs(volume(P[0],P[1],P[2],P[i])) > eps)
            {swap(P[3],P[i]);flag = false;break;}
		if(flag)return;
	//***************************************************************
		num = 0;
		face add;
		for(int i = 0; i < 4; i++){
            add={(i+1)%4,(i+2)%4,(i+3)%4,true};
			if(dblcmp(P[i],add) > 0)swap(add.b,add.c);
			g[add.a][add.b] = g[add.b][add.c] = g[add.c][add.a] = num;
			F[num++] = add;
		}
		for(int i = 4; i < n; i++)for(int j = 0; j < num; j++)
            if(F[j].ok && dblcmp(P[i],F[j]) > eps){dfs(i,j);break;}
		int tmp = num;
		num = 0;
		for(int i = 0; i < tmp; i++)
			if(F[i].ok)F[num++] = F[i];
	}
	double area() { //多边体的表面积
		if(n == 3)return area(P[0],P[1],P[2])/2;
		double ret = 0;
		for(int i = 0; i < num; i++)
			ret += area(P[F[i].a],P[F[i].b],P[F[i].c]);
		return ret/2.0;
	}
	double volume() { //多边体的体积
		double ret = 0;
		Point3 tmp = Point3(0,0,0);
		for(int i = 0; i < num; i++)
			ret += volume(tmp,P[F[i].a],P[F[i].b],P[F[i].c]);
		return fabs(ret/6);
	}
	int polygon() { //表面多边形个数，判断多边形F[i]和F[j]是否在同一平面
		int ret = 0;
		for(int i = 0; i < num; i++){
            bool f=1;
			for(int j = 0; j < i; j++)
                if(!sign(dblcmp(P[F[i].a],F[j]))&&
                   !sign(dblcmp(P[F[i].b],F[j]))&&
                   !sign(dblcmp(P[F[i].c],F[j])))f=0;
            ret+=f;
		}
		return ret;
	}
	Point3 barycenter() { //多面体的重心
		Point3 ret = Point3(0,0,0);
		Point3 o = Point3(0,0,0);
		double all = 0;
		for(int i = 0; i < num; i++){
			double vol = volume(o,P[F[i].a],P[F[i].b],P[F[i].c]);
			ret = ret + (((o+P[F[i].a]+P[F[i].b]+P[F[i].c])/4)*vol);
			all += vol;
		}
		ret = ret/all;
		return ret;
	}
	double ptoface(Point3 p,int i) { //点到面的距离
		double tmp1 = fabs(volume(P[F[i].a],P[F[i].b],P[F[i].c],p));
		double tmp2 = area(P[F[i].a],P[F[i].b],P[F[i].c]);
		return tmp1/tmp2;
	}
};


int main()
{
	int n;
	Pol P;
	scanf("%d",&P.n);
	for(int i=0;i<P.n;i++) scanf("%lf %lf %lf",&P.P[i].x,&P.P[i].y,&P.P[i].z);
	P.getconvex();
	cout<<fixed<<setprecision(3)<<P.area()<<endl;
	
	return 0;
}


