#include <vector>

class deque {
private:
    std::vector<int>* buffer;
    int start = 0;
    int end = 0;
    int capacity;

    void resize_buffer();
public:
    deque();
    void push_back(int value); // add data from end
    void push_front(int value); // add data from begin
    void pop_back(); // remove data from end
    void pop_front(); //  remove data from begin
    int front(); // return start element of the deque
    int back(); // return end element of the deque

};
