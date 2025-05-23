# G 「至暗之处」的秘密

## 题目背景

在粉色妖精小姐的指引下，芽衣渐渐意识到了「逐火之蛾」的暗面，那是一处名为「至暗之处」的监牢，其中关押着逐火十三英桀之一的「戒律」阿波尼亚。她决定，只身一人深入往世乐土，查清埋藏在「至暗之处」的秘密。

## 题目描述

前往「至暗之处」的途中，芽衣遇见了一道阿波尼亚设下的谜题。

芽衣面前横着一条河流，在河两岸各有一排 $n$ 块可以移动的石碑，共 $2n$ 块。每一块石碑上写着一个 $[1,\ 2n]$ 范围内的正整数，且每一个数都出现了一次。根据芽衣从梅比乌斯博士口中套出的情报，你需要将河两岸的石碑均按照升序排序，才能通过这条河流。

然而，阿波尼亚的金线纠缠着这些石碑，使得他们只能按照一个固定的方式移动。具体而言，芽衣可以选择两个 $[1,\ n]$ 内的不同正整数 $i,\ j$，然后金线便会将岸边的第 $i$ 块石碑与河对岸的第 $j$ 块石碑对换，同时将对岸的第 $i$ 块石碑与岸边的第 $j$ 块石碑对换。

如此一来，芽衣便不一定能够穿过河流了，于是她希望爱莉希雅告诉她是否能够解开这道谜题。然而此刻的爱莉希雅正在和伊甸小姐赏月，于是只好把这个问题交给你了。

## 形式化题面

给定一个正整数 $n$ ，给定两个长度为 $n$ 的数组 $a, b$ 满足：$[1, 2n]$ 中所有正整数都在 $a \cup b$ 中出现且仅出现一次。给出一种操作 $\mathrm{swap}(i,\ j),\ i \not = j$ ，每次操作交换 $(a_i,\ b_j)$ 与 $(a_j,\ b_i)$ ，问：能否通过这种操作将 $a, b$ 均从小到大排序。

## 输入格式

第一行一个正整数 $T$ 表示数据组数。

此后对于每组测试数据：

- 第一行一个正整数 $n$
- 第二行 $n$ 个正整数表示 $a_i$
- 第三行 $n$ 个正整数表示 $b_i$

## 输出格式

对于每组测试数据，输出 `YES` 表示可以排序，否则输出 `NO`。

## 输入样例

```plaintext
5
3
2 1 3
4 6 5
3
2 1 5
4 3 6
4
1 6 4 3
5 2 8 7
4
5 3 7 1
8 6 4 2
7
5 1 9 12 3 13 7
2 4 11 14 6 10 8
```

## 输出样例

```plaintext
NO
YES
NO
YES
YES
```

## 提示

数据范围：

对于 $20\%$ 的数据

- $3 \leq n \leq 1000$

对于另外 $20\%$ 的数据，有特殊性质：

- 对于每一个 $i$，满足：$(a_i,\ b_i)\in \{ (i,\ i+n),\ (i+n,\ i)\}$

对于另外 $20\%$ 的数据，有特殊性质：

- $\forall\ i \leq n,\ a_i\leq n,\ b_i\gt n$

对于 $100\%$ 的数据

- $1 \leq T \leq 200$
- $3 \leq n \leq 2\cdot 10^5$
- $\sum n \leq 2\cdot 10^5$