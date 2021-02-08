#include "merge_sort.h"

int main() {
    linked_list_double<int>* list = new linked_list_double<int>;
    list->push_back(new int(5));
    list->push_back(new int(1));
    list->push_back(new int(10));
    list->push_back(new int(4));
    list->print();

    merge_sort::merge_sort(list);
    list->print();
    return 0;
}
