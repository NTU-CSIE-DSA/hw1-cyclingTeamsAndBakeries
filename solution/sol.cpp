#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define kN 1003
#define kM kN*kN
#define rep(i,n) for(int i=0; i<(n); ++i)
#define fup(i,a,b) for(int i=(a); i<(b); ++i)

typedef struct ske{
	struct ske *d[4]; // r, u, l, d
	int id, hp, D[4];
}ske;

int max(int a, int b){return a>b?a:b;}
void swap(ske **a, ske **b){ske *tmp=*a; *a=*b, *b=tmp;}
void swapi(int *a, int *b){int tmp=*a; *a=*b, *b=tmp;}

void del(ske *a){
	rep(i, 4)(a->d[i]->d[i+2&3]=a->d[i+2&3])->D[i]+=a->D[i];
}
void ins(ske *a){
	rep(i, 4)(a->d[i]->d[i+2&3]=a)->d[i]->D[i+2&3]=a->D[i];
}

int n, m, nq, nr, nr2;
ske a[kN][kN], b[kN][kN], *pa[kM], *pb[kM], *qa[kM], *qb[kM], *ra[kM], *rb[kM], *r2a[kM], *r2b[kM];

void setDist(){
	rep(i, n+2)rep(j, m+2)rep(d, 4)a[i][j].D[d]=b[i][j].D[d]=1;
	fup(i, 1, n+1)a[i][0].d[0]->D[2]=a[i][m+1].d[2]->D[0]=b[i][0].d[2]->D[0]=b[i][m+1].d[0]->D[2]=kN+1;
	fup(j, 1, m+1)a[0][j].d[1]->D[3]=a[n+1][j].d[3]->D[1]=b[0][j].d[3]->D[1]=b[n+1][j].d[1]->D[3]=kN+1;
}

signed main(){
	scanf("%d%d", &n, &m);
	fup(i, 1, n+1)fup(j, 1, m+1)scanf("%d", &a[i][j].id), pa[a[i][j].id]=&a[i][j], pb[a[i][j].id]=&b[i][j];
	fup(i, 1, n+1)fup(j, 1, m+1)scanf("%d", &a[i][j].hp), b[i][j]=a[i][j];
	rep(i, n+2)rep(j, m+1)(a[i][j].d[0]=&a[i][j+1])->d[2]=&a[i][j], (b[i][j].d[2]=&b[i][j+1])->d[0]=&b[i][j];
	rep(i, n+1)rep(j, m+2)(a[i][j].d[1]=&a[i+1][j])->d[3]=&a[i][j], (b[i][j].d[3]=&b[i+1][j])->d[1]=&b[i][j];
	setDist();
	int T0, T1, T2, k, id, hp; bool flag=0;
	scanf("%d%d%d", &T0, &T1, &T2);
	while(1){
		if(flag)T0=T2;
		while(T0--){
			scanf("%d%d%d", &id, &k, &hp);
			ske *ia=pa[id], *ib=pb[id];
			rep(i, k+1){
				del(ra[nr]=ia), del(rb[nr++]=ib);
				if(ia->id!=id)ia->hp-=hp, ib->hp-=hp;
				if(ia->hp<=0)r2a[nr2]=ia, r2b[nr2++]=ib;
				int mn=0;
				fup(d, 1, 4)if(ia->D[d]<ia->D[mn]||ia->D[d]==ia->D[mn]&&ia->d[d]->id<ia->d[mn]->id)mn=d;
				if(ia->D[mn]>kN)break;
				ia=ia->d[mn], ib=ib->d[mn+2&3];
			}
			while(nr--)ins(ra[nr]), ins(rb[nr]);
			while(nr2--)del(qa[nq]=r2a[nr2]), del(qb[nq++]=r2b[nr2]);
			nr=nr2=0;
		}
		for(int i=nq-1; i>=0; --i)ins(qa[i]), ins(qb[i]);
		if(flag)break;
		while(T1--){
			scanf("%d%d", &id, &k), k>>=1;
			ske *ia=pa[id], *ib=pb[id];
			rep(i, k)ia=ia->d[2]->d[3], ib=ib->d[2]->d[3];
			for(int d=0, i; i=0, d<4; ++d)do swap(&ia->d[d+3&3], &ib->d[d+3&3]), ia->d[d+3&3]->d[d+1&3]=ia, ib->d[d+3&3]->d[d+1&3]=ib; while(i++<k<<1&&(ia=ia->d[d], ib=ib->d[d]));
		}
		setDist(), flag=1;
		rep(i, nq)del(qa[i]), del(qb[i]);
	}
	fup(i, 1, n+1){
		ske *p=&a[i][0];
		rep(j, m)p=p->d[0], printf("%d%c", max(p->hp, 0), " \n"[j==m-1]);
	}
}
