# 南川算法笔记之详解[Leetcode 300. 最长递增子序列](https://leetcode-cn.com/problems/longest-increasing-subsequence/)



## 思路一：二维vector暴力存储

### 代码实现

```c++
template<typename A> ostream& operator<<(ostream &cout, vector<A> const &v) {
    cout << "["; for(int i = 0; i < v.size(); i++) {if (i) cout << ", "; cout << v[i];} return cout << "]";
}

class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        vector<vector<int>> his;
        int minNum = nums[0];
        int maxLen = 1;
        his.push_back({nums[0]});
        cout << ">>> num: " << nums[0] << endl;
        cout << his[0] << endl;
        for(int i=1; i<nums.size(); ++i)
        {
            auto & num = nums[i];
            cout << ">>> num: " << num << endl;
            if(num < minNum) {
                minNum = num;
                his.push_back({num});
            } else {
                const int N = his.size();
                for(int j=0; j<N; ++j)
                {
                    auto & rec = his[j];
                    if(num > rec[rec.size()-1])
                    {
                        rec.emplace_back(num);
                        if(rec.size() > maxLen)
                            maxLen = rec.size();
                    }
                    else if(num > rec[0])
                    {
                        vector<int> newRec(rec.begin(), 
                            std::lower_bound(rec.begin(), rec.end(), num));
                        newRec.push_back(num);
                        his.push_back(newRec);
                        
                    }
                }
            }
            for(auto & rec: his)
                cout << rec << endl;

        }
        return maxLen;
    }
};
```

### 测例结果

![image-20210219113218444](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/20210219_113219_002865-image-20210219113218444.png)

### 结果分析

可以看到，在上述的单步记录中，有一些序列组合是可以明确排除的。

比如说，在执行完最后一步后，序列一共有5条，其中有一些是明显优于其他序列的。

比如 `[2, 5, 7, 101]` 就要明显优于 `[10, 101]`，因为首先前者长度比后者长，其次前者的第一个数（即最小数）比后者要小，这意味着在后续的所有输入中，但凡更大的数，两个序列都可以接收，但更小的数只有前者可以接收，所以后者没有任何存在的价值了，毕竟我们只需要求最终最长序列的长度。

如此分析，`[10, 101]`和`[9, 101]`直接可以被排除，接下来比较分析`[2, 5, 7, 101]`和`[2, 3, 7, 101]`，这两个之间是否需要抉择。

但易知，后者优于前者，因为后者还可以接收比3略大的数，即4，以衍生出可能更长的序列，比如说`[2, 3, 4, 5, 6, 7]`，这是前者所不具备的能力。基于此，`[2, 5, 7, 101]`也应在某个生成执行过程中给删除。

同理，`[2, 3, 5]`要优于`[2, 5]`。那么最后只剩下`[2, 3, 7, 101]`和`[2, 3, 5]`，这两者之间是否需要抉择。

易知，我们无法直接删除两者中的任何一条，因为`[2, 3, 7, 101]`更旧也更长，而`[2, 3, 5]`更新虽短却更有潜力。

这对于我们的启示，便是：**任一时刻，候选序列中只可能最多存在两条，一条更旧更长，一条更新更短，否则只会存在一条候选序列。**

长度我们很容易衡量，但“**新旧**”如何衡量呢？

结论是，**分析新值是否比候选序列的最大值要小**，基于此，我们回到测例，从头分析起。

![image-20210219120341803](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/20210219_120342_423735-image-20210219120341803.png)

## 思路二：只存储有潜力的候选序列的方案

### 代码实现

```c++
template<typename A> ostream& operator<<(ostream &cout, vector<A> const &v) {
    cout << "["; for(int i = 0; i < v.size(); i++) {if (i) cout << ", "; cout << v[i];} return cout << "]";
}

class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        vector<vector<int>> his;
        int maxLen = 1;
        his.push_back({nums[0]});
        cout << ">>> num: " << nums[0] << endl;
        cout << his[0] << endl;
        for(int i=1; i<nums.size(); ++i) {
            auto & num = nums[i];
            cout << ">>> num: " << num << endl;
            const int N = his.size();
            for(int j=0; j<N; ++j) {
                auto & rec = his[j];
                if(num > rec[rec.size()-1]) {
                    rec.emplace_back(num);
                    if(rec.size() > maxLen)
                        maxLen = rec.size();
                } else if(rec.size()==1 || num > rec[rec.size()-2]) {
                    rec[rec.size()-1] = num;
                } else {
                    vector<int> newSeq(rec.begin(), 
                        std::lower_bound(rec.begin(), rec.end(), num));
                    newSeq.push_back(num);
                    his.push_back(newSeq);
                }
            }
            for(auto & rec: his) cout << rec << endl;
        }
        return maxLen;
    }
};
```

### 测例结果

![image-20210219121418498](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/20210219_121419_162943-image-20210219121418498.png)

### 结果分析

可以看到，现在每一步生成的序列结果，就十分干净，并且保证都是有潜力的候选结果，要么只有一条，要么每一条在长度或者扩展性上更有优势。

然而尽管貌似在程序的迭代上已经基本不能执行更少的步骤，但是程序还是性能显得略慢了。它无法通过全部的测例。（所以思路一的暴力，显然更不能）

![image-20210219121808130](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/20210219_121808_567636-image-20210219121808130.png)

我们需要再做点什么优化。

此时由于力扣已经超时了，所以我们必须使用本地IDE进行调试，对于这个测例，事实上后续的迭代分枝已经爆炸，其中**我们遗漏了一些关键的剪枝操作，这是之前测例没有暴露出来的**。

![image-20210219123140872](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/20210219_123141_491798-image-20210219123140872.png)

可以看到，当我们在接收 -551 后，我们确实生成了一条更短的序列 `[-813, -728, -551]`，但是当我们接下来的数是324时，由于第一个序列等价于直接更新最后一个数，而第二个序列却延长了，此时由于两个序列的长度等长，因此可以剪枝。具体的，便是将之前的旧序列剪枝，因为它们的前缀更差一些。

在程序的实现上，我们**在更新完成后，可以从后往前扫描序列，当检测到长度相同时，即予以剔除**。

但是紧接着我们又发现，这个方案可能是不太行的，因为它们的顺序有时并不是紧密相连的，比如以下。

![image-20210219124451263](https://mark-vue-oss.oss-cn-hangzhou.aliyuncs.com/20210219_124451_902731-image-20210219124451263.png)

我们需要一种新的方法，**以保证序列的长度不会重复，并且每条序列都是有潜力的候选序列**。

但是这引发了我们的一个思考，是否可以存在两个序列长度相同，但都是有潜力的呢？

首先可以得出，如果序列长度为1，必然不存在，因为更小的那个数可以取更大的那个数而代之。

考虑长度为2时的可能。

不妨设第一个序列为`[5, 10]`，最后一个接收的数为`x`，并生成了一个新的长度为2的序列。

显然`x<=10`，不然第一个序列将更新为`[5, 10, x]`。

此外`5<x<10`，否则将更新为`[5, x]`。

若`x<=5`，由于基于一个最小数生成的序列长度为1，要想长度为2，需要有一个更小的数，比如`a`，

并且`a < x`，这样便有新的序列`[a, x]`为候选序列，但是，此时由于`a < x <=5`，因此明显优于`[5, 10]`。

所以必然有`x==10`，这样可以生成一个新的`[a, 10], a<5`。但这导致该新序列严格优于原来的`[5, 10]`，因此发生合并，即类似如下：

```c++
1. [5, 10]
2. [3]
>>> num: 10
1. [3, 10]
```



