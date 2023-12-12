/*
给定一个连续不包含空格字符串，该字符串仅包含英文小写字母及英文文标点符号(逗号、分号、句号)
同时给定词库，对该字符串进行精确分词。

说明：
1.精确分词： 字符串分词后，不会出现重叠。
    即“ilovechina” ，不同词库可分割为 “i，love，china” “ilove，china”，
    不能分割出现重叠的"i，ilove，china",i重叠出现
2.标点符号不成词，仅用于断句
3.词库：根据外部知识库统计出来的常用词汇例：dictionary=["i","love","china","lovechina","ilove"], 
4.分词原则：采用分词顺序优先且最长匹配原则
“ilovechina”，假设分词结果  [ i,ilove,lo,love,ch,china,lovechina ] 则输出 [ilove，china] 
 错误输出：[i,lovechina],            原因："ilove ">优先于 "lovechina"成词
 错误输出：[i,love,china]            原因："ilove" >"i"  遵循最长匹配原则


*/