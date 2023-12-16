import sys
charge_count = 3
while True:
    try:
        count = input()
    except:
        break

    times = 0
    borrow = 0
    while count >= charge_count:
        more = count / charge_count
        times += more
        count = more + count % charge_count - borrow
        if count == charge_count - 1:
            # borrow one
            borrow = 1
            count += 1
    print times
    # print times, count