#include <vector>

template <typename T>
class queue_vector {
private:
    std::vector<T>* buffer;
    int start = 0;
    int end = 0;
    int capacity;

    void resize_buffer() {
        std::vector<T>* tmp = new std::vector<T>(capacity * 2);
        for (int i = start; i < capacity; ++i) {
            tmp->push_back(buffer->at(i));
        }
        for (int i = 0; i <= end; ++i) {
            tmp->push_back(buffer->at(i));
        }
        delete buffer;
        buffer = tmp;

        start = 0;
        end = capacity;
        capacity = buffer->capacity();
    }
public:
    queue_vector() {
        capacity = buffer->capacity();
    }
    void push(T value) {
        bool needs_to_be_resized = ((end + 1) % capacity) == start;
        if (needs_to_be_resized) {
            resize_buffer();
        } else {
            end = (end + 1) % capacity;
        }
        buffer->at(end) = value;
    }

    T pop() {
        int old_start = start;
        start = (start + 1) % capacity;
        if (start == end) {
            start = 0;
            end = 0;
            return NULL;
        }
        return buffer->at(old_start);
    }
};