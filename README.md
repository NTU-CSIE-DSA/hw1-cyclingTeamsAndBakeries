# Tutorial

Keywords: `linked list` `reverse linked list`

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

Original: 
| 01  | 02  | 03  | 04  |
| --- | --- | --- | --- |
| 05  | 06  | 07  | 08  |
| 09  | 10  | 11  | 12  |
| 13  | 14  | 15  | 16  |

Reverse: 
| 16  | 15  | 14  | 13  |
| --- | --- | --- | --- |
| 12  | 11  | 10  | 09  |
| 08  | 07  | 06  | 05  |
| 04  | 03  | 02  | 01  |


Reversing a square is equivalent to swap the squares in the two maps.

One can find the border of the square from the center bakery in $O(l)$ time complexity, then run through the border and maintain the corresponding neighbor.

## Coding Tips

1. use ```struct``` to maintain the information of each bakery
2. use array (like ```d[4]```) to store the bakeries to the four directions instead of `r, u, l, d`
3. commonly used operations can be written in function (`del()`, `ins()`, `max()`, `swap()`)

## Testdata

Generated by [TPS](https://github.com/ioi-2017/tps)
```
tps gen
```

## Solution

[Source Code](./solution/sol.c)

[Compressed Version](./solution/sol_compressed.c)
