#include <vector>
namespace quick_sort {
    template<typename T>
    void quick_sort(std::vector<T> *array, int start_index, int end_index) {
        if (start_index < end_index) {
            int pivot_index = partition<T>(array, start_index, end_index);
            quick_sort(array, start_index, pivot_index - 1);
            quick_sort(array, pivot_index + 1, end_index);
        }
    }

    template<typename T>
    int partition(std::vector<T> *array, int start_index, int end_index) {
        int pivot_index = start_index;
        T pivot = *array[pivot_index];
        int i = start_index;
        int j = end_index;
        while (i < j) {
            {
                ++i;
            }while (array[i] < pivot)

            {
                --j;
            } while (array[j] > pivot)

            if (i < j) {
                T tmp = *array[i];
                *array[i] = *array[j];
                *array[j] = tmp;
            }
        }
        T tmp = *array[pivot_index];
        *array[pivot_index] = *array[j];
        *array[j] = tmp;

        return j;
    }
}