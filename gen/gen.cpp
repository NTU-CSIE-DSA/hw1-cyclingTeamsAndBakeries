#include <bits/stdc++.h>
#include "testlib.h"
#define kN 1003
#define maxn 1000
#define maxhp 1000000000
#define int long long
using namespace std;
int maxk=1000000;

typedef struct ske{
	struct ske *d[4]; // r, u, l, d
	int id, hp, D[4];
}ske;

int min(int a, int b){return a<b?a:b;}
int max(int a, int b){return a>b?a:b;}

stack<int> stk;

void del(ske *a){
	for(int i=0; i<4; ++i)a->d[i+2&3]->d[i]=a->d[i], a->d[i+2&3]->D[i]+=a->D[i];
	stk.push(a->id);
}

void ins(ske *a){
	for(int i=0; i<4; ++i)a->d[i]->d[i+2&3]=a, a->d[i]->D[i+2&3]=a->D[i];
	assert(stk.top()==a->id), stk.pop();
}

void swap(ske **a, ske **b){ske *tmp=*a; *a=*b, *b=tmp;}

void swapi(int *a, int *b){int tmp=*a; *a=*b, *b=tmp;}

int n, m, nq, nr, nr2, perm[kN*kN];
ske a[kN][kN], b[kN][kN], *pa[kN*kN], *pb[kN*kN], *qa[kN*kN], *qb[kN*kN], *ra[kN*kN], *rb[kN*kN], *r2a[kN*kN], *r2b[kN*kN];

void stat(){
	assert(stk.empty());
	for(int i=1; i<n+1; ++i){
		ske *p=&a[i][0];
		for(int j=0; j<m; ++j)p=p->d[0], assert(0==0&&p->id);//printf("%d%c", p->id, "\t\n"[j==m-1]);
		p=&a[i][m+1];
		for(int j=0; j<m; ++j)p=p->d[2], assert(2==2&&p->id);
	}
	for(int j=1; j<m+1; ++j){
		ske *p=&a[0][j];
		for(int i=0; i<n; ++i)p=p->d[1], assert(1==1&&p->id);//printf("%d%c", p->hp, "\t\n"[j==m-1]);
		p=&a[n+1][j];
		for(int i=0; i<n; ++i)p=p->d[3], assert(3==3&&p->id);
	}
	for(int i=1; i<n+1; ++i){
		ske *p=&b[i][m+1];
		for(int j=0; j<m; ++j)p=p->d[0], assert(0==0&&p->id);//printf("%d%c", p->id, "\t\n"[j==m-1]);
		p=&b[i][0];
		for(int j=0; j<m; ++j)p=p->d[2], assert(2==2&&p->id);
	}
	for(int j=1; j<m+1; ++j){
		ske *p=&b[n+1][j];
		for(int i=0; i<n; ++i)p=p->d[1], assert(1==1&&p->id);//printf("%d%c", p->hp, "\t\n"[j==m-1]);
		p=&b[0][j];
		for(int i=0; i<n; ++i)p=p->d[3], assert(3==3&&p->id);
	}
}

void stat2(){
	for(int i=0; i<n+2; ++i)for(int j=0; j<m+1; ++j)
		assert(a[i][j].d[0]==&a[i][j+1]&&a[i][j+1].d[2]==&a[i][j]),
		assert(b[i][j].d[2]==&b[i][j+1]&&b[i][j+1].d[0]==&b[i][j]);
	for(int i=0; i<n+1; ++i)for(int j=0; j<m+2; ++j)
		assert(a[i][j].d[1]==&a[i+1][j]&&a[i+1][j].d[3]==&a[i][j]),
		assert(b[i][j].d[3]==&b[i+1][j]&&b[i+1][j].d[1]==&b[i][j]);

}

signed main(int argc, char **argv){
	registerGen(argc, argv, 1);
	int typ=atoi(argv[1]), tcnt=atoi(argv[2]);
	if(typ==1)maxk=maxn;
	n=(tcnt%3&&(tcnt&3)!=3)?rnd.next(1, maxn):rnd.next(maxn-10, maxn), m=(tcnt%3&&(tcnt&3)!=3)?rnd.next(1, maxn):rnd.next(maxn-10, maxn), printf("%lld %lld\n", n, m);
	for(int i=0; i<n*m; ++i)perm[i]=i+1;
	shuffle(perm, perm+n*m);
	for(int i=0; i<n+2; ++i)for(int j=0; j<m+2; ++j)for(int d=0; d<4; ++d)a[i][j].D[d]=1;
	for(int i=1; i<n+1; ++i)a[i][1].D[2]=a[i][m].D[0]=kN+1;
	for(int j=1; j<m+1; ++j)a[1][j].D[3]=a[n][j].D[1]=kN+1;
	for(int i=1; i<n+1; ++i)for(int j=1; j<m+1; ++j)
		a[i][j].id=perm[(i-1)*m+j-1], printf("%lld%c", a[i][j].id, " \n"[j==m]), pa[a[i][j].id]=&a[i][j], pb[a[i][j].id]=&b[i][j];
	for(int i=1; i<n+1; ++i)for(int j=1; j<m+1; ++j)a[i][j].hp=rnd.next(1, maxhp), printf("%lld%c", a[i][j].hp, " \n"[j==m]), b[i][j]=a[i][j], swapi(&b[i][j].D[0], &b[i][j].D[2]), swapi(&b[i][j].D[1], &b[i][j].D[3]);
	for(int i=0; i<n+2; ++i)for(int j=0; j<m+1; ++j)
		a[i][j].d[0]=&a[i][j+1], a[i][j+1].d[2]=&a[i][j],
		b[i][j].d[2]=&b[i][j+1], b[i][j+1].d[0]=&b[i][j];
	for(int i=0; i<n+1; ++i)for(int j=0; j<m+2; ++j)
		a[i][j].d[1]=&a[i+1][j], a[i+1][j].d[3]=&a[i][j],
		b[i][j].d[3]=&b[i+1][j], b[i+1][j].d[1]=&b[i][j];
	int T0, T1, T2, k, id, hp; bool flag=0;
	vector<int> kk; int smk=0, ksz=tcnt&1?rnd.next(1, 3):rnd.next(maxk>>1, maxk);
	//if(typ==3&&!(tcnt&1))ksz>>=2;
	while(smk<maxk){
		kk.push_back(rnd.next(1ll, (maxk-smk+ksz-1)/ksz));
		if((tcnt&3)==3)kk[(int)kk.size()-1]=min(kk[(int)kk.size()-1], min(n, m));
		smk+=kk[(int)kk.size()-1];
	}
	shuffle(kk.begin(), kk.end());
	int kksz=kk.size();
	if(typ==2)T0=rnd.next(1ll, kksz), T2=kksz-T0, T1=0;
	else if(typ==3)T0=T2=0, T1=kksz;
	else T1=rnd.next(1ll, kksz/(tcnt%6?1:50)-1), T0=rnd.next(1ll, kksz/(tcnt%6?1:50)-T1), T2=kksz-T0-T1;
	if(rnd.next(0, 1))swap(T0, T2);
	printf("%lld %lld %lld\n", T0, T1, T2);
	assert(T0+T1+T2==kk.size());
	int kcnt=0;
	set<int> alive;
	for(int i=1; i<=n*m; ++i)alive.insert(i);
	int king=rnd.next(1ll, n*m);
	//stat();
	while(1){
		if(flag)T0=T2;
		while(T0--){
			assert(alive.size());
			if(tcnt%6)id=*alive.lower_bound(rnd.next(*alive.begin(), *alive.rbegin())), hp=rnd.next(1, maxhp);
			else id=king, hp=rnd.next(maxhp-100, maxhp);
			k=kk[kcnt++];
			printf("%lld %lld %lld\n", id, k, hp);
			ske *ia=pa[id], *ib=pb[id];
			//assert(ia->hp>0&&ib->hp>0);
			for(int i=0; i<k+1; ++i){
				//printf("%d %d\n", ia->id, ib->id);
				assert(ia->hp>0&&ib->hp>0);
				del(ia), del(ib);
				if(ia->id!=id)ia->hp-=hp, ib->hp-=hp;
				ra[nr]=ia, rb[nr]=ib, ++nr;
				if(ia->hp<=0)r2a[nr2]=ia, r2b[nr2]=ib, ++nr2, alive.erase(ia->id);
				int mn=0;
				for(int d=1; d<4; ++d)if(ia->D[d]<ia->D[mn]||ia->D[d]==ia->D[mn]&&ia->d[d]->id<ia->d[mn]->id)mn=d;
				if(ia->D[mn]>kN)break;
				ia=ia->d[mn], ib=ib->d[mn+2&3];
			}
			while(nr--)ins(ra[nr]), ins(rb[nr]);
			while(nr2--)del(qa[nq]=r2a[nr2]), del(qb[nq]=r2b[nr2]), ++nq;
			nr=nr2=0;
		}
		for(int i=nq-1; i>=0; --i)ins(qa[i]), ins(qb[i]);
		//stat();
		if(flag)break;
		stat();
		stat2();
		while(T1--){
			assert(alive.size());
			id=*alive.lower_bound(rnd.next(*alive.begin(), *alive.rbegin()));
			k=max(kk[kcnt++]-1>>1, 0);
			ske *ia=pa[id], *ib=pb[id], *iaa=ia, *ibb=ib;
			for(int i=0; i<k; ++i){
				iaa=iaa->d[0]->d[1], ibb=ibb->d[0]->d[1],
				ia=ia->d[2]->d[3], ib=ib->d[2]->d[3];
				if(ia->id==0||ib->id==0||iaa->id==0||ibb->id==0){ia=ia->d[0]->d[1], ib=ib->d[0]->d[1], k=i; break;}
			}
			printf("%lld %lld\n", id, k*2+1);
			//stat();
			for(int d=0; d<4; ++d){
				swap(&ia->d[d+3&3], &ib->d[d+3&3]), ia->d[d+3&3]->d[d+1&3]=ia, ib->d[d+3&3]->d[d+1&3]=ib;
				for(int i=0; i<(k<<1); ++i)ia=ia->d[d], ib=ib->d[d],
					swap(&ia->d[d+3&3], &ib->d[d+3&3]), ia->d[d+3&3]->d[d+1&3]=ia, ib->d[d+3&3]->d[d+1&3]=ib, assert(ia->id&&ib->id&&49==49);
			}
		}
		stat();
		for(int i=0; i<n+2; ++i)for(int j=0; j<m+2; ++j)for(int d=0; d<4; ++d)a[i][j].D[d]=b[i][j].D[d]=1;
		for(int i=1; i<n+1; ++i)a[i][0].d[0]->D[2]=a[i][m+1].d[2]->D[0]=kN+1,
								b[i][0].d[2]->D[0]=b[i][m+1].d[0]->D[2]=kN+1;
		for(int j=1; j<m+1; ++j)a[0][j].d[1]->D[3]=a[n+1][j].d[3]->D[1]=kN+1,
								b[0][j].d[3]->D[1]=b[n+1][j].d[1]->D[3]=kN+1;

		for(int i=0; i<nq; ++i)del(qa[i]), del(qb[i]), assert(qa[i]->hp<=0&&qb[i]->hp<=0);
		flag=1;
	}
	/*for(int i=1; i<n+1; ++i){
		ske *p=&a[i][0];
		for(int j=0; j<m; ++j)p=p->d[0], printf("%d%c", max(p->hp, 0), " \n"[j==m-1]);
	}*/
}
