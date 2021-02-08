#include <iostream>

template <typename T>
class linked_list_single_item {
private:
    T* value = nullptr;
    linked_list_single_item<T>* next = nullptr;

public:
    linked_list_single_item() {}
    linked_list_single_item(T* value) {
        set_value(value);
    }
    ~linked_list_single_item(){
        /// @todo implement destructor
    }

    void set_next(linked_list_single_item<T>* new_next) {
        this->next = new_next;
    }

    void set_value(T* value) {
        this->value = value;
    }
    linked_list_single_item<T>* get_next() {
        return this->next;
    }
};

template <typename T>
class linked_list_single {
private:
    linked_list_single_item<T>* start = nullptr;
    linked_list_single_item<T>* last = nullptr;
    int items_count = 0;
public:
    linked_list_single(){}
    ~linked_list_single(){
        /// @todo implement destructor
    }
    void push_back(T* value) {
        linked_list_single_item<T>* item = new linked_list_single_item<T>(value);
        if (start == nullptr) {
            start = item;
        } else {
            last->set_next(item);
        }
        last = item;
    }

    linked_list_single_item<T>* get_start() {
        return start;
    }
    linked_list_single_item<T>* get_last() {
        return last;
    }

    int length()
    {
        if (items_count != -1) {
            return items_count;
        }
        linked_list_single_item<T>* tmp = start;
        int count = 0;
        while (tmp) {
            tmp = tmp->next;
            count++;
        }
        return count;
    }

    void print() {
        linked_list_single_item<T>* item = this->get_start();
        std::cout << "Start of list" << std::endl;
        while(item) {
            std::cout << "Value: " << *(item->get_value()) << std::endl;
            item = item->get_next();
        }
        std::cout << "End of list" << std::endl;
    }
};
