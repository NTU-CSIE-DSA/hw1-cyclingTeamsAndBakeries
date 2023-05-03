## Description

<style>
	.center{
		text-align:center;
		font-style:italic;
	}
</style>

<p class='center'>
Cycling teams resemble swarms of locusts,<br>
swiftly moving through and consuming everything in their path.
</p>

Seven city consists of a street grid with $n$ horizontal roads and $m$ vertical roads. The horizontal roads are numbered by their position relative to the north, indexed by $i$, while the vertical roads are numbered by their position relative to the west, indexed by $j$. The distance between any two consecutive horizontal roads ($i$ and $i+1$) is equal to the distance between any two consecutive vertical roads ($j$ and $j+1$), for all $1\leq i\leq n-1$ and $1\leq j\leq m-1$. At every intersection of a horizontal road $i$ and a vertical road $j$, there is an open bakery denoted by $b_{ij}$. Based on its Google Map reviews and ratings, each bakery is assigned a \textit{unique} rank $u_{ij}$ between $1$ and $mn$. Furthermore, each bakery is initially stocked with a certain number of toasts, denoted by $t_{ij}$.

There are two training periods for cycling teams, and one racing period in between. The first training period is of $T_1$ days, the second training period is of $T_2$ days, and the racing period is for $R$ days. On each day $k$ within the training periods ($1\leq k\leq T_1$ or $T_1+R+1\leq k\leq T_1+R+T_2$), a cycling team with $s_k$ members would be at an open bakery of rank $r_k$ as the initial gathering bakery, and plans a tour of length at most $l_k$ to other bakeries based on the following steps.

1. Select all open bakeries that are located on the same horizontal or vertical road as the team's current position but have not been visited on day $k$, excluding the gathering bakery at the current position. If no such open bakeries exist, the team ends its training and returns home.
2. Among the selected bakeries, choose the ones with the minimum distance to the gathering bakery.
3. Among the chosen bakeries, visit the one with the smallest rank.
4. Let each member of the team eat a piece of toast to restore energy at the bakery being visited. That is, decrease the number of toasts $t_{ij}$ by $s_k$ for the bakery. If the new $t_{ij} \le 0$, the bakery being visited would then need to be closed.
5. If the number of bakeries that the team has visited does not exceed $l_k$, set the bakery being visited as the new gathering bakery, and go to step 1. Otherwise, the team ends its training and returns home.

On each day $k$ within the racing period ($T_1 + 1\leq k\leq T_1+R$), the 80kings would choose an open bakery with rank $r_k$ as the center of the racing track. 
The track is a square with a side length of $l_k - 1$, with an odd number $l_k$ of intersections on each side. The many cycling teams would race through the streets at breakneck speeds, their powerful legs propelling them forward with such force that a mighty tornado formed in their wake. As they hurtled around the square track, the tornado wreaked havoc on the surrounding area, lifting and rotating bakeries within the square, including those on the racing track, by $180$ degrees with tremendous force.

Given the plan on each day of the training and racing periods, output the final number of toasts of the bakeries.

## Input

There are $2$ integers $n, m$ separated by a space in the first line.

Each of the next $n$ lines contains $m$ integers separated by spaces. The $j$-th integer of the $i$-th line is $u_{ij}$ (the rank of $b_{ij}$).

Each of the next $n$ lines contains $m$ integers separated by spaces. The $j$-th integer of the $i$-th line is $t_{ij}$ (the initial number of toasts of $b_{ij}$).

There are $3$ integers $T_1, R, T_2$ separated by spaces in the next line, which denote the number of days for the first training period, the racing period, and the second training period, respectively.

Each of the next $T_1$ lines corresponds to each day in the first training period, and contains $3$ integers $r_k$ (the rank of the initial gathering bakery), $l_k$ (the maximum riding length), and $s_k$ (the size of the cycling team), separated by spaces.

Each of the next $R$ lines corresponds to each day in the racing period, and contains $2$ integers $r_k$ (the rank of the center bakery) and $l_k$ (the \textit{odd} side length of the square track), separated by spaces.

Each of the next $T_2$ lines corresponds to each day in the second training period, and contains $3$ integer $r_k$ (the rank of the initial gathering bakery), $l_k$ (the maximum riding length), and $s_k$ (the size of the cycling team), separated by spaces.

## Output Format

Output $n$ lines, each line contains $m$ integers separated by spaces. The $j$-th integer of the $i$-th line should be $t_{ij}$, which is the final number of toasts of $b_{ij}$, for any open bakery. If the bakery is closed (i.e. $t_{ij} \le 0$), simply output $0$.

## Constraints

* $1\leq n, m\leq1000$
* $1\leq t_{ij}, s_k\leq10^9, \forall i, j, k$
* $1\leq u_{ij}, r_k\leq nm, \forall i, j, k$. All $u_{ij}$ are distinct.
* $l_k\geq0$
* $T_1+R+T_2\leq10^6$
* $\sum_k l_k\leq10^6$

## Subtasks

### Subtask 1 (10 pts)

* $\sum l_k\leq10^3$
    
### Subtask 2 (15 pts)

* $R=0$

### Subtask 3 (15 pts)

* $T_1=T_2=0$

### Subtask 4 (60 pts)

* no other constraints

## Sample Cases

### Sample Input 1

```
5 5
8 9 10 11 17
7 15 16 12 18
6 14 4 13 19
5 3 2 1 20
25 24 23 22 21
49 1 7 14 7
2 14 49 7 7
7 49 14 2 7
7 7 1 49 14
14 7 7 7 49
1 1 1
1 11 4
4 3
1 10 9
```

### Sample Output 1

```
45 0 0 1 7
0 49 0 0 7
0 0 5 40 7
0 0 40 5 14
14 7 7 7 49
```

## Hint

This is the animation of the example:

![](https://i.imgur.com/GVaHHjd.gif)

