class vectorItem {
    void* value;
};


class vector_6_2 {
    int capacity;
    int size;

    vectorItem* array;
public:
    vector_6_2() {
        capacity = 10;
        size = 0;
        array = new vectorItem[capacity];
    }

    void push(vectorItem item)
    {
        if (size == capacity) {
            vectorItem* temp = new vectorItem[2 * capacity];
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