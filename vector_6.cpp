class vector_6 {
    int capacity;
    int size;

    T* array;
public:
    vector_6() {
        capacity = 10;
        size = 0;
        array = new T[capacity];
    }

    void push(T item)
    {

        if (size == capacity) {
            T* temp = new T[2 * capacity];
            for (int i = 0; i < capacity; i++) {
                temp[i] = arr[i];
            }
            delete[] arr;
            arr = temp;

            capacity *= 2;
        }

        arr[size] = item;
        size++;
    }
};