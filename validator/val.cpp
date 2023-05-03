#include <bits/stdc++.h>
using namespace std;
#include "testlib.h"
const int kN=1003, kM=1000006, maxn=1000, maxk=1000000, maxhp=1000000000;

bool p[kN*kN];

signed main(int argc, char *argv[]) {
    registerValidation(argc, argv);
	int n, m;
    n=inf.readInt(1, maxn, "n"), inf.readSpace(), m=inf.readInt(1, maxn, "m");
    inf.readEoln();
	for(int i=0; i<n; ++i)for(int j=0; j<m; ++j){
		int k=inf.readInt(1, n*m, "id");
		if(j<m-1)inf.readSpace();
		else inf.readEoln();
		p[k]=1;
	}
	for(int i=1; i<=n*m; ++i)ensuref(p[i], "invalid id");
	for(int i=0; i<n; ++i)for(int j=0; j<m; ++j){
		int k=inf.readInt(1, maxhp, "hp");
		if(j<m-1)inf.readSpace();
		else inf.readEoln();
	}
	int T0, T1, T2;
	T0=inf.readInt(0, maxk, "T0"), inf.readSpace(), T1=inf.readInt(0, maxk, "T1"), inf.readSpace(), T2=inf.readInt(0, maxk, "T2"), inf.readEoln();
	ensuref(T0+T1+T2<=maxk, "T exceed");
	int id, k, hp, sm=0;
	while(T0--){
		id=inf.readInt(1, n*m, "id"), inf.readSpace(),
		k=inf.readInt(0, maxk, "k"), inf.readSpace(),
		hp=inf.readInt(1, maxhp, "hp"), inf.readEoln(),
		sm+=k;
	}
	while(T1--){
		id=inf.readInt(1, n*m, "id"), inf.readSpace(),
		k=inf.readInt(0, maxk, "k"), inf.readEoln(),
		//hp=inf.readInt(1, maxhp, "hp"), inf.readEoln(),
		sm+=k;
	}
	while(T2--){
		id=inf.readInt(1, n*m, "id"), inf.readSpace(),
		k=inf.readInt(0, maxk, "k"), inf.readSpace(),
		hp=inf.readInt(-maxhp, maxhp, "hp"), inf.readEoln(),
		sm+=k;
	}
	ensuref(sm<=maxk, "k exceed");
    inf.readEof();
}
