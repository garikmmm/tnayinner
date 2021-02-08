#include "../list/linked_list_double.h"
namespace merge_sort {
    template<typename T>
    void merge_sort(linked_list_double<T> *array) {
        int length = array->length();
        if (length <= 1) {
            return;
        }



    }

    template<typename T>
    linked_list_double<T> *merge_sorted_arrays(linked_list_double<T> *first, linked_list_double<T> *second) {
        linked_list_double<T>* result = new linked_list_double<T>;
        linked_list_double_item<T>* i = first->get_start();
        linked_list_double_item<T>* j = second->get_start();

        while(i && j) {
            if (i->get_value() > j->get_value()) {
                result->push_back(new T(j->get_value()));
                j = j->get_next();
            } else {
                result->push_back(new T(i->get_value()));
                i = i->get_next();
            }
        }

        while(i) {
            result->push_back(new T(i->get_value()));
            i = i->get_next();
        }
        while(j) {
            result->push_back(new T(j->get_value()));
            j = j->get_next();
        }

        return result;
    }
}