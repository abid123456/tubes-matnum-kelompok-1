#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cmath>

using namespace std;
const double eps=1e-6;
const int INF=1e9;
const int mxn=1010;
int cnt=0;
int lct=0;
int n;
bool del[mxn];

struct line{
    double l,r;
    friend bool operator < (const line a,const line b){return a.l<b.l;}
}a[mxn],b[mxn];
struct cir{
    double x,y,r;
    friend bool operator < (const cir a,const cir b){return a.r<b.r;}
}c[mxn];

inline double dist(cir a,cir b){return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));}

int read(){
    int x=0,f=1;char ch=getchar();
    while(ch<'0' || ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0' && ch<='9'){x=x*10-'0'+ch;ch=getchar();}
    return x*f;
}

double f(double x){
    int i,j;
    lct=0;
    for(i=1;i<=cnt;i++){
        if(fabs(c[i].x-x)>=c[i].r)continue;
        double h= sqrt(c[i].r*c[i].r-(c[i].x-x)*(c[i].x-x));
        a[++lct].l=c[i].y-h;
        a[lct].r=c[i].y+h;
    }
    if(!lct)return 0;
    double len=0,last=-INF;
    sort(a+1,a+lct+1);
    for(i=1;i<=lct;i++){
        if(a[i].l>last){len+=a[i].r-a[i].l;last=a[i].r;}
        else if(a[i].r>last){len+=a[i].r-last;last=a[i].r;}
    }
    return len;
}
inline double sim(double l,double r){
    return (f(l)+4*f((l+r)/2)+f(r))*(r-l)/6;
}
double solve(double l,double r,double S){
    double mid=(l+r)/2;
    double ls=sim(l,mid);
    double rs=sim(mid,r);
    if(fabs(rs+ls-S)<eps)return ls+rs;
    return solve(l,mid,ls)+solve(mid,r,rs);
}
int main(){
    cout << "Masukkan banyak lingkaran: ";
    n=read();
    int i,j;
    double L=INF,R=-INF;
    for(i=1;i<=n;i++){
        cout << "Lingkaran ke-" << i << " (x y r): ";
        c[i].x=read();
        c[i].y=read();
        c[i].r=read();
    }
    cout << endl;

    sort(c+1,c+n+1);
    for (i=1;i<=n;i++) {
        cout << "Circle " << i << ": c(" << c[i].x << "," << c[i].y << "); r = " << c[i].r << endl;
    }

    for(i=1;i<n;i++) {
        for(j=i+1;j<=n;j++) {
            if(c[j].r-c[i].r>=dist(c[i],c[j])) {
                del[i]=1;
                cout << "Deleting circle " << i << endl;
                break;
            }
        }
    }
    cout << "New list 1:" << endl;
    for (i=1;i<=cnt;i++) {
        cout << "Circle " << i << ": c(" << c[i].x << "," << c[i].y << "); r = " << c[i].r << endl;
    }
    cout << "start: i,cnt = " << i << "," << cnt << endl;
    for(i=1;i<=n;i++) {
        if(!del[i])c[++cnt]=c[i];
    }
    cout << "New list 2:" << endl;
    for (i=1;i<=cnt;i++) {
        cout << "Circle " << i << ": c(" << c[i].x << "," << c[i].y << "); r = " << c[i].r << endl;
    }

    double tmp=-INF;
    for(i=1;i<=cnt;i++){
        b[i].l=c[i].x-c[i].r;
        b[i].r=c[i].x+c[i].r;
    }
    for (i=1;i<=cnt;i++) {
        cout << "Line " << i << ": l = " << b[i].l << ", r = " << b[i].r << endl;
    }
    sort(b+1,b+cnt+1);
    cout << "Sorted:" << endl;
    for (i=1;i<=cnt;i++) {
        cout << "Line " << i << ": l = " << b[i].l << ", r = " << b[i].r << endl;
    }
    double ans=0, ans_inc=0;
    for(i=1;i<=cnt;i++){
        cout << "start iterate i = " << i << ": (" << b[i].l << " -- " << b[i].r << ") tmp = " << tmp;
        if(b[i].r<=tmp)continue;
        L=max(tmp,b[i].l);
        ans_inc=solve(L,b[i].r,sim(L,b[i].r));
        ans += ans_inc;
        cout << " ans_inc = " << ans_inc << " [ans = " << ans << "]" << endl;
        tmp=b[i].r;
    }

    printf("Luasnya adalah %.3f\n",ans);
    return 0;
}
