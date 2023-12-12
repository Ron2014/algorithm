class Checkout {
    list<int> m_data;
    multiset<int> m_max;

public:
    Checkout() {
    }
    
    int get_max() {
        if (m_data.empty()) return -1;
        return *m_max.rbegin();
    }
    
    void add(int value) {
        m_data.push_back(value);
        m_max.insert(value);
    }
    
    int remove() {
        if (m_data.empty()) return -1;
        int res = m_data.front();
        m_data.pop_front();
        m_max.erase(m_max.find(res));
        return res;
    }
};

/**
 * Your Checkout object will be instantiated and called as such:
 * Checkout* obj = new Checkout();
 * int param_1 = obj->get_max();
 * obj->add(value);
 * int param_3 = obj->remove();
 */