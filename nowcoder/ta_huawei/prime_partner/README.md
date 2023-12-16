
动态规划、穷举法我都试过了，最后发现这个问题很简单，是我想复杂了。

毕竟是机考题，1个小时内敲代码编译测试，哪会搞那么偏的东西给我们做？

首先要强调的是，一定得先分奇偶，有了奇偶两个数组，才会有后面的可能。

动态规划一般做法都是用二维数组，通过 dp[i][j] 和 dp[i-1][j-1] dp[i-1][j] dp[i][j-1] 的关系来推演。

dp[i][j] 就表示 奇数表前i项 和 偶数表前j项 的解。

但是它有个弊端就是存储每个 dp[i][j] 的状态（也就是奇偶表的匹配关系）很麻烦，当一个新的数加入计算时可能触发多个已有的配对关系重新组合，这会很耗时。

碰到一个数有多个匹配的情况，真的是焦头烂额。后来证实了，测试用例确实有很多这种多对多的配对关系。

```c++
        for (int i=1; i<=iCountOdd; i++) {
            for (int j=1; j<=iCountEven; j++) {
                TEST_INFO2(calc:, i, j);

                int num_odd = aNumbersOdd[i];
                int num_even = aNumbersEven[j];

                int lessOdd = aMaxPairCount[i-1][j];
                int lessEven = aMaxPairCount[i][j-1];
                aMaxPairCount[i][j] = lessEven;
                int minNum;

                if (lessOdd <= lessEven) {
                    minNum = (i<j-1) ? i : j-1;
                    if (lessEven<minNum) {
                        if (aMatchEven[j]) {
                            aMaxPairCount[i][j] = lessEven + 1;
                        } else {
                            int matchIdx = canPair(j, aNumbersEven, aNumbersOdd, i, aMatchOdd);
                            if (matchIdx) {
                                aMaxPairCount[i][j] = lessEven + 1;
                                aMatchEven[j] = matchIdx;
                                TEST_INFO(more pair 1:, aMaxPairCount[i][j]);
                                TEST_SHOW_ARRAY(aMatchOdd, iCountOdd+1);
                                TEST_SHOW_ARRAY(aMatchEven, iCountEven+1);
                                TEST_SHOW_ARRAY2(aMaxPairCount, i+1, j+1);
                            } else
                                aMaxPairCount[i][j] = lessEven;
                        }
                    } else 
                        aMaxPairCount[i][j] = lessEven;
                } else {
                    minNum = (i-1<j) ? (i-1):j;
                    if (lessOdd<minNum) {
                        if (aMatchOdd[i]) {
                            aMaxPairCount[i][j] = lessOdd + 1;
                        } else {
                            int matchIdx = canPair(i, aNumbersOdd, aNumbersEven, j, aMatchEven);
                            if (matchIdx) {
                                aMaxPairCount[i][j] = lessOdd + 1;
                                aMatchOdd[i] = matchIdx;
                                TEST_INFO(more pair 2:, aMaxPairCount[i][j]);
                                TEST_SHOW_ARRAY(aMatchOdd, iCountOdd+1);
                                TEST_SHOW_ARRAY(aMatchEven, iCountEven+1);
                                TEST_SHOW_ARRAY2(aMaxPairCount, i+1, j+1);
                            } else
                                aMaxPairCount[i][j] = lessOdd;
                        }
                    } else
                        aMaxPairCount[i][j] = lessOdd;
                }
            }
        }
```

穷举法就是利用递归的计算方式，用函数的局部变量保存状态。然后一步一步更新到最优解。python 的做法就是不断做列表裁剪，然后递归调用。C++的话，想到的就是冒泡。

```c++
void getMaxMatch(int *aShortNum, int sLen, int *aLongNum, int lLen, int totalLen) {
    bool hasMatched = false;
    for (int i=1; i<=sLen; i++) {
        for (int j=1; j<=lLen; j++) {
            if (isPrimePartner(aShortNum[i], aLongNum[j])) {
                swap(aShortNum, i, sLen);
                swap(aLongNum, j, lLen);

                getMaxMatch(aShortNum, sLen-1, aLongNum, lLen-1, totalLen);

                swap(aShortNum, i, sLen);
                swap(aLongNum, j, lLen);

                hasMatched = true;
            }
        }
    }
    if (!hasMatched) cout << totalLen-sLen << endl;
}
```

如上所说，这两个方法都失败了。所以我又回到原点去想，我们拥有什么：

1. 区分奇数，偶数的数组。
2. 因为是成对的，我们优先选择这两个数组最短的那个遍历能降低开销。

还有就是。如果真的存在`一个数有多个数可以与之配对`的情况，那我们为何不把这种配对的可能性统计一遍呢？

3. 统计所有可能的配对情况。因为可能有重复的数，所以统计的信息都是 `奇数表的下标` 对应 `偶数表的下标`。拿下标做key，就能建立两张配对表：

```bash
以奇数表为例
[奇数表的下标] = set([与该值对应的偶数表的下标集合])
```

我们要通过这个配对表，去建立配对最多的解。那就少不了遍历，假设最短的表是奇数表，那就遍历奇数配对表，来建立最优解。

我们会想到这个配对表里，有的数有很多种配对，有的可能一种，有的没有任何数与其配对。

那就肯定存在这种情况，我们优先从配对表中取出配对情况最少的数，就可以留给后面的数最大的配对可能性。所以

4. 遍历之前要排个顺序，优先遍历配对情况最少的数。

5. 遍历该数时，还得从与该数配对的集合中去除最少配对的情况。代码敲出来就是这样

```python

def getMaxPair(short_num, short_len, long_num, long_len):
    match_list = []
    short_matches = {}
    long_matches = {}

    for i in xrange(short_len):
        sn = short_num[i]
        for j in xrange(long_len):
            ln = long_num[j]
            if isPrime(sn+ln):
                match = short_matches.setdefault(i, set([]))
                match.add(j)
                match = long_matches.setdefault(j, set([]))
                match.add(i)
    
    for i in xrange(short_len):
        match_list.append((i, short_matches.get(i, set([]))))
    match_list = sorted(match_list, key=lambda x: len(x[1]))

    sum = 0
    for node in match_list:
        si, smatch = node
        if smatch:
            minlmatch = None
            for lj in smatch:
                lmatch = long_matches.get(lj)
                if minlmatch is None:
                    minlmatch = lmatch
                elif len(lmatch) < len(minlmatch):
                    minlmatch = lmatch
            for mi in minlmatch:
                short_matches[mi].discard(lj)
            sum += 1
    print(sum)
```

我发现，这其实是个贪心算法。一次遍历，没有递归和迭代。