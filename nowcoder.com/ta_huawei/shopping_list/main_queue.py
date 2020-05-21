import sys
import Queue

info_list = {}
map_weight = {}
calc_queue = Queue.Queue()
money = 0

try:
    while True:
        info_list = {}
        calc_queue = Queue.Queue()

        line = sys.stdin.readline().strip()
        if line == "":
            break

        max_weight = 0
        money, goods_count = map(int, line.split())
        for i in xrange(goods_count):
            goods_id = i+1
            line = sys.stdin.readline().strip()
            price, weight, major = map(int, line.split())
            weight *= price
            info_list[goods_id] = (price, weight, major)     # key for id
            if major == 0 and price <= money:
                key = (goods_id,)
                map_weight[key] = (price, weight)
                calc_queue.put(key)
                if max_weight < weight:
                    max_weight = weight

        while not calc_queue.empty():
            key = calc_queue.get()
            cur_price = map_weight[key][0]
            cur_weight = map_weight[key][1]

            if cur_price == money:
                continue

            goods_set = set(key)
            
            for i, v in info_list.iteritems():
                if i in goods_set:
                    continue
                
                price = v[0] + cur_price
                weight = v[1] + cur_weight
                major = v[2]

                new_set = set(key)
                new_set.add(i)

                if major == 0 or major in new_set:
                    if price > money:
                        continue

                    new_key = tuple(new_set)
                    if new_key not in map_weight:
                        map_weight[new_key] = (price, weight)
                        calc_queue.put(new_key)
                        if max_weight < weight:
                            max_weight = weight
                else:
                    v = info_list[major]
                    price += v[0]
                    weight += v[1]
                    if price > money:
                        continue

                    new_set.add(major)
                    new_key = tuple(new_set)
                    if new_key not in map_weight:
                        map_weight[new_key] = (price, weight)
                        calc_queue.put(new_key)
                        if max_weight < weight:
                            max_weight = weight
        print(max_weight)
except:
    pass

