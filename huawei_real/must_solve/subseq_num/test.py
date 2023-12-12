import sys
def countDistinctSubsequences(S):
    MOD = 10 ** 9 + 7
    last = {}  # 用于记录字符上次出现的位置
    dp = [0] * (len(S) + 1)
    dp[0] = 1  # 空字符串算一个子序列
    
    for i in range(len(S)):
        if S[i] in last:
            # 如果当前字符已经出现过，则新增加的子序列个数为当前位置减去上次出现位置的子序列数
            dp[i + 1] = (dp[i] * 2 - dp[last[S[i]]]) % MOD
        else:
            # 如果当前字符是第一次出现，则新增加的子序列个数为当前位置的子序列数加一
            dp[i + 1] = (dp[i] * 2) % MOD
        last[S[i]] = i
        
    return (dp[len(S)] - 1) % MOD  # 减去空字符串的情况

# 测试
result = countDistinctSubsequences(sys.argv[1])
print("不同非空子序列的个数为:", result)