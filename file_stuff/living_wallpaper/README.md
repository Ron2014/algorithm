## 想做个动态壁纸

对于 Windows Terminal (Preview) 的配置有背景图设置:

```json

                "backgroundImage" : "%GITHUB_PATH%\\Pictures\\Gif\\GhostintheShell.gif",
                "backgroundImageOpacity" : 0.3,
                "backgroundImageAlignment" : "bottomRight",
                "backgroundImageStretchMode" : "none"
```

现在想要这样的功能, 每次打开一个 panel 会读取不同的背景图 (格式为gif/jpg/png)

保证每个 panel 的背景图是不一样的, 以免切换窗口时会认错.

## 分析

只用关注 backgroundImage 这一项即可.

backgroundImage 支持环境变量读取.

但是我们又不能把所有 panel 的设置都指向一个环境变量.

直接修改文件也是可行的, lua-cjson, 但是这种读入文件转格式, 又要转回来的话, 会破坏注释的内容. 不太推荐

还是老老实实列10个环境变量来做这种事情吧.