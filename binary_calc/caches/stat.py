# 使用python3执行
filenames = ["nocache_log", "cache_log", "cache0_log"]

def average ():
    for name in filenames:
        with open(name, 'r') as f:
            lines = f.readlines()
            sum = 0
            for line in lines:
                sum = sum + int(line)
            print("%s ... %0.4f" % (name, (sum * 1.0) / len(line)))

def list2normal(name, peak_array) :
    import numpy as np
    import matplotlib.pyplot as plt

    d = np.array(peak_array)
    #  matplotlib.axes.Axes.hist() 方法的接口
    n, bins, patches = plt.hist(x=d, bins='auto', color='#0504aa',
                                alpha=0.7, rwidth=0.85)
    plt.grid(axis='y', alpha=0.75)
    plt.xlabel('Value')
    plt.ylabel('Frequency')
    plt.title(name)
    plt.text(23, 45, r'$\mu=15, b=3$')
    maxfreq = n.max()
    # 设置y轴的上限
    plt.ylim(ymax=np.ceil(maxfreq / 10) * 10 if maxfreq % 10 else maxfreq + 10)
    plt.show()

def normal():
    for name in filenames:
        peak_array = []
        with open(name, 'r') as f:
            lines = f.readlines()
            for line in lines:
                peak_array.append(int(line))
        list2normal(name, peak_array)

if __name__ == "__main__":
    average()
    normal()
            