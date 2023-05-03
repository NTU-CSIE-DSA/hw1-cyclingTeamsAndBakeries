# Tutorial

Keywords: ```linked list``` ```reverse linked list```

## Training Period

For each bakery, maintain the following things:
1. the bakeries to the right, up, left, down of this bakery
2. the distance to the bakeries to the right, up, left, down of this bakery
3. the rank of this bakery
4. the number of toasts remaining

Maintain the pointer of the bakery of each rank, so that we can find a bakery by its rank in $O(1)$ time complexity.

Operations we can do to the bakeries:
1. delete a bakery
2. insert the last deleted bakery, that is, the reverse of 1

The way to maintain the visited and closed bakeries:
1. delete all bakeries that are visited
2. insert all visited bakeries by the reverse order
3. among the visited bakeries, delete all bakeries that are closed

## Racing Period

One can insert all closed bakeries before the racing period, and delete them after the racing period.

Maintain the reverse map:

Original: $\begin{array}{|c|c|c|c|}\hline
1&2&3&4\\\hline
5&6&7&8\\\hline
9&10&11&12\\\hline
13&14&15&16\\\hline
\end{array}$ Reverse: $\begin{array}{|c|c|c|c|}\hline
16&15&14&13\\\hline
12&11&10&9\\\hline
8&7&6&5\\\hline
4&3&2&1\\\hline
\end{array}$

Reversing a square is equivalent to swap the squares in the two maps.

One can find the border of the square from the center bakery in $O(l)$ time complexity, then run through the border and maintain the corresponding neighbor.

## Coding Tips

1. use ```struct``` to maintain the information of each bakery
2. use array (like ```d[4]```) to store the bakeries to the four directions instead of ```r, u, l, d```
3. commonly used operations can be written in function (```del()```, ```ins()```, ```max()```, ```swap()```)

## Solution

```cpp=
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
```