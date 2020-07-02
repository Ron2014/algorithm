## 规定

公民身份号码是特征组合码，由十七位数字本体码和一位校验码组成。

18位数字组合的方式是：

| 1 1 0 1 0 2 | Y Y Y Y M M D D | 8 8 | 8 | X |
|--|--|--|--|--|
|区域码(6位)|出生日期码(8位)|顺序码(2位)|性别码(1位)|校验码(1位)|

1. 区域码: 公民常住户口所在县（市、镇、区）的[行政区划代码](https://zh.wikipedia.org/wiki/%E4%B8%AD%E5%8D%8E%E4%BA%BA%E6%B0%91%E5%85%B1%E5%92%8C%E5%9B%BD%E8%A1%8C%E6%94%BF%E5%8C%BA%E5%88%92%E4%BB%A3%E7%A0%81)
2. 出生日期
3. 顺序码: 同一天出生的人用该序号区分
4. 性别码: 奇数-男, 偶数-女
5. 校验码: 采用的是ISO 7064:1983,MOD 11-2校验码系统. 可能产生'10', 则替换为'X'

## 校验码计算

1. $a_i$ 表示每一位的数
2. i 的顺序: 低位->高位. 所以顺着读过去是 $a_{17} \ a_{16} ...\  a_{0}$
3. 每一位数对应一个权重 $W_i = 2^i\ mod\ 11$
4. 每一位加权求和
$$
S = \sum_{\substack{i=1}}^{\substack{17}} a_i × W_i
$$
因为我们要算的是 $a_0$ 所以这个和从 $a_1$算起.
5. $a_0=(12-(S\ mod\ 11))\ mod\ 11$