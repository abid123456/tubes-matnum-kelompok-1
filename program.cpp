#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cmath>
using namespace std;
const double eps=1e-6;
const int INF=1e9;
const int mxn=1010;
int read(){
    int x=0,f=1;char ch=getchar();
    while(ch<'0' || ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0' && ch<='9'){x=x*10-'0'+ch;ch=getchar();}
    return x*f;
}
//
struct cir{
    double x,y,r;
    friend bool operator < (const cir a,const cir b){return a.r<b.r;}
}c[mxn];int cnt=0;
inline double dist(cir a,cir b){return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));}
//round
struct line{
    double l,r;
    friend bool operator <(const line a,const line b){return a.l<b.l;}
}a[mxn],b[mxn];int lct=0;
double f(double x){
    int i,j;
    lct=0;
    for(i=1;i<=cnt;i++){//Calculate straight cut round arc length
        if(fabs(c[i].x-x)>=c[i].r)continue;
        double h= sqrt(c[i].r*c[i].r-(c[i].x-x)*(c[i].x-x));
        a[++lct].l=c[i].y-h;
        a[lct].r=c[i].y+h;
    }
    if(!lct)return 0;
    double len=0,last=-INF;
    sort(a+1,a+lct+1);
    for(i=1;i<=lct;i++){//Line segment length
        if(a[i].l>last){len+=a[i].r-a[i].l;last=a[i].r;}
        else if(a[i].r>last){len+=a[i].r-last;last=a[i].r;}
    }
//    printf("x:%.3f  len:%.3f\n",x,len);
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
int n;
double ans=0;
bool del[mxn];
int main(){
    n=read();
    int i,j;
    double L=INF,R=-INF;
    for(i=1;i<=n;i++){
        c[i].x=read();    c[i].y=read();    c[i].r=read();
//        L=min(L,c[i].x-c[i].r);
//        R=max(R,c[i].x+c[i].r);
    }
    //
    sort(c+1,c+n+1);
    for(i=1;i<n;i++)
        for(j=i+1;j<=n;j++){
//            printf("%d %.3f %.3f %.3f %.3f\n",j,c[j].x,c[i].r,c[j].r,dist(c[i],c[j]));
            if(c[j].r-c[i].r>=dist(c[i],c[j]))
                {del[i]=1;break;}
        }
    for(i=1;i<=n;i++)
        if(!del[i])c[++cnt]=c[i];
    //Delete the included circle
//    printf("cnt:%d\n",cnt);
    double tmp=-INF;int blct=0;
    for(i=1;i<=cnt;i++){
        b[++blct].l=c[i].x-c[i].r;
        b[blct].r=c[i].x+c[i].r;
    }
    sort(b+1,b+blct+1);
//    printf("lct:%d\n",blct);
//    int tlct=t;
    for(i=1;i<=blct;i++){
//        printf("%.3f %.3f\n",b[i].l,b[i].r);
//        printf("tmp:%.3f\n",tmp);
        if(b[i].r<=tmp)continue;
        L=max(tmp,b[i].l);
//        printf("%d: %.3f %.3f\n",i,L,a[i].r);
        ans+=solve(L,b[i].r,sim(L,b[i].r));
//        printf("ANS:%.3f\n",ans);
//        printf("nlct:%d\n",lct);
        tmp=b[i].r;
    }


//    ans=solve(L,R,f((L+R)/2));
    printf("%.3f\n",ans);
    return 0;
}
