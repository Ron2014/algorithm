import sys, os

def is_binary(filepath):
    if filepath.endswith(".exe"):
        return True
    if filepath.endswith("/main"):
        return True
    return False

def main():
    if len(sys.argv) < 2:
        print("usage: %s <path>" % (sys.argv[0]))
        return

    directory = sys.argv[1]
    for root, dirs, files in os.walk(directory):
        for file in files:
            filepath = os.path.join(root, file)
            # 判断文件是否为二进制文件
            if os.path.isfile(filepath) and is_binary(filepath):
                print("%s is removed" % (filepath))
                os.remove(filepath)

if __name__ == "__main__":
    main()
