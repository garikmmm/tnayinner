#include "deque.h"

deque::deque() {
    buffer = new std::vector<int>;
    capacity = buffer->capacity();
}

void deque::resize_buffer() {
    std::vector<int>* tmp = new std::vector<int>(capacity * 2);
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
    // update capacity
    capacity = buffer->capacity();
}

void deque::push_front(int value) {
    bool needs_to_be_resized = ((start - 1) % capacity) == end;
    if (needs_to_be_resized) {
        resize_buffer();
    }
    start = (start - 1) % capacity;
    buffer->at(start) = value;
}

void deque::pop_front() {
    bool needs_to_be_reset = ((start + 1) % capacity) == end;
    if (needs_to_be_reset) {
        start = 0;
        end = 0;
    } else {
        start = (start + 1) % capacity;
    }
}

void deque::push_back(int value) {
    bool needs_to_be_resized = ((end + 1) % capacity) == start;
    if (needs_to_be_resized) {
        resize_buffer();
    }
    end = (end + 1) % capacity;
    buffer->at(end) = value;
}

void deque::pop_back() {
    bool needs_to_be_reset = ((end - 1) % capacity) == start;
    if (needs_to_be_reset) {
        start = 0;
        end = 0;
    } else {
        end = (end - 1) % capacity;
    }
}

int deque::back() {
    return buffer->at(end);
}
int deque::front() {
    return buffer->at(start);
}