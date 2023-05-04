#include <stdio.h>

#define MAXN 1000
#define DIR_CNT 4
#define DIR_LEFT 0
#define DIR_DOWN 1
#define DIR_RIGHT 2
#define DIR_UP 3

#define norm(x) ((x) << 1)
#define mirr(x) (((x) << 1) + 1)
#define rev(x) (((x) + 2) & 3)
#define nxt(x) (((x) + 1) & 3)

typedef struct _Pos {
  int x, y;
} Pos;

typedef struct _Data {
  int nei[4];
  int sid;
} Data;

int seats[MAXN + 2][MAXN + 2];
long long conf[MAXN * MAXN + 1];
int path[MAXN * MAXN];
Pos neighbors[MAXN * MAXN + 1][DIR_CNT];
Pos dir[DIR_CNT] = {{0, -1}, {1, 0}, {0, 1}, {-1, 0}};
Data lst[(MAXN * MAXN + 1) * 2];


void swap_int(int *a, int *b) {
  int tmp = *a;
  *a = *b;
  *b = tmp;
}

void mirror(int sid, int len) {
  int curr_norm = norm(sid), curr_mirr = mirr(sid);
  for (int i = 0; i < len; ++i)
    curr_norm = lst[lst[curr_norm].nei[DIR_UP]].nei[DIR_LEFT],
    curr_mirr = lst[lst[curr_mirr].nei[DIR_UP]].nei[DIR_LEFT];
  
  for (int i = 0; i < DIR_CNT; ++i) {
    lst[lst[curr_norm].nei[i]].nei[rev(i)] = curr_mirr;
    lst[lst[curr_mirr].nei[i]].nei[rev(i)] = curr_norm;
    swap_int(&lst[curr_norm].nei[i], &lst[curr_mirr].nei[i]);
    for (int j = 0; j < 2 * len; ++j) {
      curr_norm = lst[curr_norm].nei[nxt(i)];
      curr_mirr = lst[curr_mirr].nei[nxt(i)];
      lst[lst[curr_norm].nei[i]].nei[rev(i)] = curr_mirr;
      lst[lst[curr_mirr].nei[i]].nei[rev(i)] = curr_norm;
      swap_int(&lst[curr_norm].nei[i], &lst[curr_mirr].nei[i]);
    }
  }
}

void gen_data(int n, int m) {
  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= m; ++j) {
      for (int k = 0; k < DIR_CNT; ++k) {
        lst[norm(seats[i][j])].nei[k] = norm(seats[i + dir[k].x][j + dir[k].y]);
        lst[mirr(seats[i][j])].nei[rev(k)] = mirr(seats[i + dir[k].x][j + dir[k].y]);
        lst[norm(seats[i][j])].sid = lst[mirr(seats[i][j])].sid = seats[i][j];
      }
    }
  lst[norm(0)].nei[DIR_RIGHT] = norm(seats[1][1]);
  lst[mirr(0)].nei[DIR_RIGHT] = mirr(seats[n][m]);
}

void gen_neighbor(int n, int m) {
  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= m; ++j)
      for (int k = 0; k < DIR_CNT; ++k)
        neighbors[seats[i][j]][k] = (Pos){seats[i + dir[k].x][j + dir[k].y], 1};
}

void absent(int sid) {
  for (int i = 0; i < DIR_CNT; ++i) {
    neighbors[neighbors[sid][i].x][rev(i)].x = neighbors[sid][rev(i)].x;
    neighbors[neighbors[sid][i].x][rev(i)].y += neighbors[sid][rev(i)].y;
  }
}

void deabsent(int sid) {
  for (int i = 0; i < DIR_CNT; ++i)
    neighbors[neighbors[sid][i].x][rev(i)] = (Pos){sid, neighbors[sid][i].y};
}

int elec(int sid, int len, int dam, int layer) {
  if (!len) return layer;
  int tar = -1;
  for (int i = 0; i < DIR_CNT; ++i)
    if (neighbors[sid][i].x)
      tar = i;
  for (int i = 0; i < DIR_CNT; ++i) {
    if (!neighbors[sid][i].x) continue;
    if (neighbors[sid][i].y < neighbors[sid][tar].y || (neighbors[sid][i].y == neighbors[sid][tar].y && neighbors[sid][i].x < neighbors[sid][tar].x))
      tar = i;
  }
  if (tar == -1) return layer;
  conf[neighbors[sid][tar].x] -= dam;
  path[layer] = neighbors[sid][tar].x;
  absent(sid);
  int ret = elec(neighbors[sid][tar].x, len - 1, dam, layer + 1);
  deabsent(sid);
  return ret;
}

void reset(int n, int m) {
  int start_pt = lst[norm(0)].nei[DIR_RIGHT];
  while (lst[start_pt].nei[DIR_UP]) start_pt = lst[start_pt].nei[DIR_UP];
  while (lst[start_pt].nei[DIR_LEFT]) start_pt = lst[start_pt].nei[DIR_LEFT];
  for (int i = 1; i <= n; ++i) {
    int tmp = start_pt;
    for (int j = 1; j <= m; ++j)
      seats[i][j] = lst[tmp].sid,
      tmp = lst[tmp].nei[DIR_RIGHT];
    start_pt = lst[start_pt].nei[DIR_DOWN];
  }
  gen_neighbor(n, m);
  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= m; ++j)
      if (conf[seats[i][j]] <= 0)
        absent(seats[i][j]);
}

int main (int argc, char** argv) {
  int n, m;
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= m; ++j)
      scanf("%d", &seats[i][j]);

  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= m; ++j)
      scanf("%lld", &conf[seats[i][j]]);

  gen_neighbor(n, m);
  int a1, r, a2;
  scanf("%d%d%d", &a1, &r, &a2);

  int total_len = 0;
  for (int i = 1; i <= a1; ++i) {
    int sid, len;
    long long dam;
    scanf("%d%d%lld", &sid, &len, &dam);
    total_len += len;
    len = elec(sid, len, dam, 0);
    for (int j = 0; j < len; ++j)
      if (conf[path[j]] <= 0) absent(path[j]);
  }

  gen_data(n, m);

  for (int i = 1; i <= r; ++i) {
    int sid, len;
    scanf("%d%d", &sid, &len);
    total_len += len;
    len /= 2;
    mirror(sid, len);
  }

  reset(n, m);

  for (int i = 1; i <= a2; ++i) {
    int sid, len;
    long long dam;
    scanf("%d%d%lld", &sid, &len, &dam);
    total_len += len;
    len = elec(sid, len, dam, 0);
    for (int j = 0; j < len; ++j)
      if (conf[path[j]] <= 0) absent(path[j]);
  }

  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= m; ++j)
      printf("%lld ", conf[seats[i][j]] > 0 ? conf[seats[i][j]] : 0);
    printf("\n");
  }

  return 0;
}

