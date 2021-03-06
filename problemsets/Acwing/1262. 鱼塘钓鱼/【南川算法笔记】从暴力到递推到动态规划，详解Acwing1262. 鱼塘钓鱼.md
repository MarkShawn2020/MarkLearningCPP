# 【南川算法笔记】从暴力法到动态规划，详解Acwing1262. 鱼塘钓鱼

## 题目描述

有 N 个鱼塘排成一排，每个鱼塘中有一定数量的鱼，例如：N = 5 时，如下表：

| 鱼塘编号                                         | 1    | 2    | 3    | 4    | 5    |
| :----------------------------------------------- | :--- | :--- | :--- | :--- | :--- |
| 第1分钟能钓到的鱼的数量（1..1000）               | 10   | 14   | 20   | 16   | 9    |
| 每钓鱼1分钟钓鱼数的减少量（1..100)               | 2    | 4    | 6    | 5    | 3    |
| 当前鱼塘到下一个相邻鱼塘需要的时间（单位：分钟） | 3    | 5    | 4    | 4    |      |

即：在第 1 个鱼塘中钓鱼第 1 分钟内可钓到 10 条鱼，第 2 分钟内只能钓到 8 条鱼，……，第 5分钟以后再也钓不到鱼了。

从第 1 个鱼塘到第 2 个鱼塘需要 3 分钟，从第 2 个鱼塘到第 3 个鱼塘需要 5 分钟，……

给出一个截止时间 T，设计一个钓鱼方案，从第 1 个鱼塘出发，希望能钓到最多的鱼。

假设能钓到鱼的数量仅和已钓鱼的次数有关，且每次钓鱼的时间都是整数分钟。

#### 输入格式

共 5 行，分别表示：

第 1 行为 N；

第 2 行为第 1 分钟各个鱼塘能钓到的鱼的数量，每个数据之间用一空格隔开；

第 3 行为每过 1 分钟各个鱼塘钓鱼数的减少量，每个数据之间用一空格隔开；

第 4 行为当前鱼塘到下一个相邻鱼塘需要的时间；

第 5 行为截止时间 T。

#### 输出格式

一个整数（不超过$2^{31}-1$），表示你的方案能钓到的最多的鱼。

#### 数据范围

$1 \le N \le 100$
$1 \le T \le 1000$

#### 输入样例：

```c++
5
10 14 20 16 9
2 4 6 5 3
3 5 4 4
14
```

#### 输出样例：

```c++
76
```

## 从暴力法到动态规划

以前我很排斥暴力法，原因也是众人皆知的，暴力法几乎无法用于任何题目的求解，时间复杂度太高。

但是后来，我意识到，这是个思维陷阱，暴力法并非一无是处。

相反，暴力法往往是高级方法的基石与源泉。

尤其是对于动态规划这种问题，往深了去想，动态规划无非就是在暴力法的基础上，使用记忆化的方式，逆向得出最终的解，本质上是一种偷懒的暴力，难道不是吗？

仔细想一下，动态规划并没有用一种超自然的技术（例如：心灵感性、跨学科降维打击等）得到问题的答案，它只不过一步步确定了一个迷宫中所有不可能走的道路，从枝繁叶茂的一颗大树的叶子一步步确定了一条通往根的路，例如如下：

![image-20210210123610144](../Pictures/image-20210210123610144.png)

暴力法由于不知道前方的信息，所以只能无脑的对所有分支都进行搜索，直到找到目标。

但动态规划却可以从终点处一步步回溯，确定每个分支处的最佳与唯一选择，步步正确步步局优，直到汇成一条全优。

所以动态规划的关键在于，确定暴力法过程中的分支选择依据，也就是：**状态转移方程**。在动态转移方程的基础上利用“**记忆化信息**”，就是动态规划的全部了。如果只有动态转移方程，没有记忆化信息，这就是剪枝。

所以**动态规划 = 记忆化信息 +状态态转移方程（剪枝） + 逆向（暴力）**。

## 状态转移方程的确定

显然，暴力的关键在于列出所有可能的选项，并排除一切不可能的选项。

那么，从“原点”出发，我们此时拥有 T 分钟，并处在第 1 个池塘处，已消耗 0 分钟。

所以我们可以用一个三元组表达现在的状态 $(T, i, t) = (14, 1, 0)$，基于此生成一个函数 $F(T, i, t)$ 表示在此状态下，能钓到的最大鱼数。比如$f(0, 1, 0) = 0$，因为我们已经没有剩余时间了，但凡我们有一分钟，则至少能钓 10 条鱼。

问题在于，$F(14, 1, 0)$ 等于多少呢？我们不知道，因为我们的选择太多了，在接下来的第一分钟，我们可以选择钓一分钟鱼，这样状态就变成了$(13, 1, 1)$，同时我们拥有了 10 条鱼。但我们害怕这消耗的一分钟可能使我们错过能钓到更多鱼的可能，比如，若在第二个池塘的第一分钟我们能钓到100条鱼，那我们驻足在第一个池塘的这一分钟就显得浪费了。

显然，我们的每一个状态都至多有两种选择，要么继续留在这个池塘钓一分钟鱼，要么花在奔往下一个池塘的路上，考虑在路上是不产生收益的，我们可以直接定位到抵达下一个池塘时的状态。

由于第一个池塘到第二个池塘需要花3分钟，所以如果我们在钓鱼的开始，直接奔往下一个池塘，那么就等于状态 $(11, 2, 0)$，即我们抵达第二个池塘后，i = 2， 剩余时间 T = 11，已在第二个池塘消耗的时间为 t = 0。

于是，自然而然地，我们意识到，我们需要从两个状态中进行选择：留在第一个池塘钓一分钟鱼后的状态，与奔赴下一个池塘后的状态。这个问题等价于，在留下or离开两个选择中作一个决定，决定好坏的唯一判定依据是，是否能钓到更多鱼。

于是，一个状态转移方程呼之欲出：

 $F(T, i, t) = max\{F(T-1,\ i,\ t+1) + W(i, t),\  F(T-C(i),\ i+1,\ 0)\}$，

其中$W(i, t)$表示在第 $i$ 个池塘第 $t$ 分钟能钓到的鱼数， $C(i)$ 表示从第 $i$ 个池塘奔赴第 $i+1$ 个池塘所需要消耗的时间。

于是，原问题就直接转化成相对来说更容易解决的两个子问题，因为 T 变小了（T会逐渐变为0，直到终止），i 也可能增大（i是有界的，直到终止）。

现在的难点，是如何确定每个子问题的答案。

方法就是逆推！

## 逆推分析（一）：考虑 F(T, i+1, 0)

很显然，最后一个鱼塘是最容易分析，因为它只能选择安静地钓鱼，给定它每分钟能钓到鱼的数量信息（题目已有），我们就能知道，当我们位于最后一个鱼塘时，若我们剩余 $T'$ 分钟，我们能钓到多少鱼。

回到题目，题目给出 $T = 14$，而 $C = \{3, 5, 4, 4\}$，即我们从第一个鱼塘奔赴最后一个鱼塘需要 $3+5+4+4=16$ 分钟，直接超过了最大时间限制，所以最后一个鱼塘无论如何我们都去不了，可以直接不用考虑。

那么倒数第二个鱼塘，便成为我们能去的最后一个鱼塘，在路上的代价是 $3 + 5 + 4 = 12$ ，也就是说，我们抵达倒数第二个鱼塘后，最多只剩 2 分钟，所以我们可以分别求出 $T <= 2$ 时，在倒数第二个鱼塘分别能钓到的最大的鱼数，显然 $F(1, 4, 0) = 16,\ F(1, 4, 1) = 11,\ F(2, 4, 0) = 27$。而其他都是不用考虑的，身在倒数第二个鱼塘，我们所有的状态仅有此三种，而实际对倒数第三个鱼塘有用的信息只有两个：$F(1, 4, 0)$ 与 $F(2, 4, 0)$。

也就是说，当第三个鱼塘还剩 5 分钟时，他需要考虑继续在第三个鱼塘钓 5 分钟鱼，还是奔赴第四个鱼塘钓 1 分钟鱼；而当第三个鱼塘还剩 6 分钟时，他需要考虑继续在第三个鱼塘钓 6 分钟鱼，还是奔赴第四个鱼塘钓 2 分钟鱼。

先来分析第一种情况，当他身在第三个鱼塘，并且只剩5分钟，他该做什么决定。

首先，记 $W(i, t)$ 为在第 i 个池塘第 t 分钟能钓到的鱼数，则有：
$$
\begin{aligned}
W(3,0) &                    &=& &20,\\ 
W(3,1) &=W(3, 0) - D(3)     &=& &14, \\ 
W(3,2) &=W(3, 0) - D(3) * 2 &=& &8, \\
W(3,3) &=W(3, 0) - D(3) * 3 &=& &2, \\ 
W(3,4) &=W(3, 0) - D(3) * 4 &=& &0.  \\
\end{aligned}
$$


其次，由于抵达第三个池塘需要 8 分钟，而最大只有 14 分钟，所以抵达第三个池塘后最后只剩 6 分钟，所以我们需要求出 $F(T', 3, 0)\  |\  T' \in \{6, 5, 4, 3, 2, 1\}$ 的值。

显然，我们有：
$$
\begin{aligned}
F(6, 3, 0) &= \max\{F(5, 3, 1) + C(3, 0),\ F(2, 4, 0)\} &= \max\{ F(5, 3, 1) + 20,\ 27\} \\
F(5, 3, 0) &= \max\{F(4, 3, 1) + C(3, 0),\ F(1, 4, 0)\} &= \max\{ F(4, 3, 1) + 20,\ 16\} \\
\end{aligned}
$$
注意到两点：

1. 当身处第三个池塘，且剩余时间 $T' \le 4$ 时，只能选择一直呆在第三个池塘钓鱼，其接下来的总量都是可预测的，取决于已呆在第三个池塘的时间长度。
2. 在 $F(5, 3, 0)$ 的递推式中，$F(4,3,1)+20$ 显然大于 16，也就是说无需考虑奔赴第四个池塘，这里可以被剪枝。而 $F(4, 3, 1) = 14 + 8 + 2 + 0 = 24$。

既然 $F(1, 4, 0)$ 可以被剪枝，那么 $F(2, 4, 0)$ 可不可以呢？需要进一步分析 $F(5,3,1) + 20$ 与 27 之间的关系。

由于
$$
\begin{aligned}
F(5, 3, 1) 
&= \max\{F(4, 3, 2) + W(3, 1), \ F(1, 4, 0)\ \\
&= \max\{10+5+0+0+15, \ 16\} 								\\
&= 30
\end{aligned}
$$
显然，$F(2, 4, 0)$ 也是需要被剪枝的，不过这里剪不剪枝倒已经不是那么重要的事了，因为我们已经确定了
$$
F(6, 3, 0) = \max\{F(5, 3, 1)+ 20, \ 27\} = 50, \\
F(5, 3, 0) = \max\{F(4, 3, 1)+ 20, \ 16\} = 50
$$
这两个均是在总时间为 14 的情况下，抵达第三个池塘后还需要考虑第四个池塘时的最优结果，我们已经不用考虑第四个池塘了（毕竟不用输出路径，只需要输出总值）。

当然，值得警惕的是，虽然基于 $F(6,3,0)$ 和 $F(5, 3, 0)$ 不用在考虑第四个池塘的情况，但是要想通过第三个池塘推出第二个池塘，还得求出 $F(4, 3, 0), F(3, 3, 0), F(2, 3, 0), F(1, 3, 0)$ 的值，不过这已经是顺水推舟的事了。

以此类推，直到程序推演出$F(14, 1, 0)$的答案。

## 递推分析（二）：考虑 F(T-1, i, t+1)

在上的递推分析中，我们已经知道，可以从最后一个池塘的最小时间状态开始，逐步往前面的池塘、逐步往时间更多的状态推。这样的思路，代码如何实现比较方便呢？

这主要取决于，我们的递推式有哪些核心变量，回顾一下我们的递推式：
$$
F(T, i, t) = max\{F(T-1,\ i,\ t+1) + W(i, t),\  F(T-C(i),\ i+1,\ 0)\}
$$
由于第一个子式的求解需要继续往下分解（选择多呆一分钟，或者奔赴下一个池塘），因此第二个子式更容易求解（已经位于下一个池塘，如果该池塘是最后一个池塘的话，则只可以选择一直钓鱼）。

所以我们不妨开辟一个数组 $F(T)$，表示当我们处于下一个池塘并剩余 $T$ 分钟时，我们能钓到的最大鱼数。

很显然当我们处于第四个池塘（即倒数第二个），我们有
$$
\begin{aligned}
F(0, 4, 0) &= 0 \\
F(1, 4, 0) &= 16 \\ 
F(2, 4, 0) &= 16 + 11 = 27 \\
F(3, 4, 0) &= 16 + 11 + 6 = 33 \\
F(4, 4, 0) &= 16 + 11 + 6 + 1 = 34 \\
F(5, 4, 0) &= 34 \\
\dots \\
F(14, 4, 0)&= 34
\end{aligned}
$$
接着，我们可以利用这个数组的信息，求出求一个池塘剩余 $T$ 分钟时，我们能钓到的最大鱼数。
$$
\begin{aligned}
F(0, 3, 0) &= 0 \\
F(1, 3, 0) &= 20 \\
F(2, 3, 0) &= 20 + 14 = 34 \\
F(3, 3, 0) &= 20 + 14 + 8 = 42 \\
F(4, 3, 0) &= 20 + 14 + 8 + 2 = 44 \\
F(5, 3, 0) &= \max\{F(4, 3, 1)+20, F(1, 4, 0)\} \\
&= \max\{24+20,\  16\} = 44 \\
F(6, 3, 0) &= \max\{F(5, 3, 1)+20, F(2, 4, 0)\} \\ 
&= \max\{30+20,\  27\} = 50 \\
F(7, 3, 0) &= \max\{F(6, 3, 1)+20, F(3, 4, 0)\} = \dots
\end{aligned}
$$
其实，我们的实现过程中，出现了两个小问题。

第一个小问题，是关于剪枝的，根据我们之前的递推分析， $F(3, 4, 0)$ 根本就不存在，但是我们在代码实现部分还是考虑了，主要是为了统一方便，相当于开辟了一个很大数组，只取部分使用。

第二个小问题，如何快速求出 $F(4, 3, 1)$、$F(5, 3, 1)$ 等这些从 1、2、3……开始的函数值。

如果我们不考虑空间复杂度，我们完全可以给每个鱼塘开一个二维数组，记录第 i 个池塘 T 与 t 之间的关系，准确地说，记录每个 $T, i, t$ 的函数值 $F(T, i, t)$，显然空间复杂度至少为 $n * T^2 $，n是池塘总数，对于超过 T 的 t，我们可以直接截断处理。

现为方便分析，我们假设 $T = 8$， 这样我们只需要分析前两个池塘就可以，第一个池塘初始值为10，递减值为2；第二个池塘初始值为14，递减值为4，从第一个池塘奔往第二个池塘需要3分钟。

我们可以列出如下的表格：

| 剩余时间\池塘 | 池塘 1                                                       | 增量1 | 池塘 2 | 增量2 |
| ------------- | ------------------------------------------------------------ | ----- | ------ | ----- |
| 0             | 0                                                            | 10    | 0      | 14    |
| 1             | 10                                                           | 8     | 14     | 10    |
| 2             | 18                                                           | 6     | 24     | 6     |
| 3             | 18 + 6 = 24                                                  | 4     | 30     | 2     |
| 4             | Max{**24+4**, 14} = 28<br />呆4分钟池塘1 vs 1分钟池塘2       | 2     | 32     | 0     |
| 5             | Max{**28+2**, 10+14, 24} = 30<br />**(5,0)** vs (1, 1) vs (0, 2) | 0     | 32     | 0     |
| 6             | Max{30, 18+14, **10+24**, 30} = 34<br />(6, 0) vs (2, 1) vs **(1, 2)** vs (0, 3) | 0     | 32     | 0     |
| 7             | Max{30, 24+14, **18+24**,10+30,32}=42<br />(7, 0 ) vs (3,1) vs **(2, 2)** vs (1, 3) vs (0, 4) | 0     | 32     | 0     |
| 8             | Max{30, 28+14, **24+24**,18+30,10+32, 32}=48<br />(8, 0 ) vs (4,1) vs **(3, 2)** vs (2, 3) vs (1, 4) vs (0, 5) | 0     | 32     | 0     |



从上面的表格可以看出，虽然基于池塘 2 的已有信息，对池塘 1 的最大化利益进行分析，稍显有些复杂，因为状态会越来越多，但我们依旧还是能捕捉到一些规律。

首先可以得到一个何时选择下一个池塘的简单判断，那就是交叉点，即由于奔赴下一个池塘在路上导致的损失（原来在该池塘能收获的机会成本）与在下一个池塘慢慢得到的增量利益之差。

由于从第一个池塘奔往第二个池塘，需要3分钟，因此若时间允许，在钓到池塘 1 第一分钟的 10 条鱼后，奔赴第二个池塘，在接下来的 3 + 2 分钟内收获池塘 2 的 14 + 10 = 24 条鱼，这比继续留在第一个池塘收获从第二分钟起的 8 + 6 + 4 + 2 + 0 = 20 条鱼要划算。

不过，如果时间不够6分钟，则老老实实呆在池塘 1 更靠谱。

如此一个个地比较，自然程序可以实现，只是有些慢而已。我们在设计算法的时候，还可以更简单点吗？

## 考虑时间、空间复杂度的最优转移方程













