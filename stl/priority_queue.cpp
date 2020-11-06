#include <queue>
#include <iostream>

struct Packet {
    Packet(int seq, bool retransmission)
        : enqueue_order(seq), retransmission(retransmission) {}
    int enqueue_order;
    bool retransmission;

    bool operator<(const Packet& other) const {
        if (retransmission != other.retransmission)
            return other.retransmission;

        return enqueue_order > other.enqueue_order;
    }
};

// priority_queue 默认是大顶堆, 大的元素靠前, 小的元素靠后

int main() {
    std::priority_queue<Packet> queue;
    queue.push(Packet(4, false));
    queue.push(Packet(5, false));
    queue.push(Packet(3, true));

    while (!queue.empty()) {
        std::cout << queue.top().enqueue_order << std::endl;
        queue.pop();
    }
    return 0;
}

