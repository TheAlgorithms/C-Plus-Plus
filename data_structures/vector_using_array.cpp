#include<iostream>

using namespace std;

template <typename T> class vector
{
    int capacity = 8;
    int index = 0;
    T* arr = new T[capacity];

    public:

        void push_back(T e)
        {
            if (index == capacity)
            {
                T* temp = new T[2*capacity];

                for (int i = 0; i < capacity; i++)
                {
                    temp[i] = arr[i];
                }

                capacity *= 2;

                delete[] arr;

                arr = temp;
            }

            arr[index] = e;            
            index++;
        }

        T front() 
        {
            return arr[0];
        }

        T back()
        {
            return arr[index-1];
        }

        int capacity_()
        {
            return capacity;
        }

        int size()
        {
            return index;
        }

        T operator[](int i)
        {
            if(i <= this->size())
            {
                return arr[i];
            } else {
                return 0;
            }
        }

        void resize(int n)
        {
            T* temp = new T[n];

            for (int i = 0; i < n; i++)
            {
                temp[i] = arr[i];
            }

            delete[] arr;

            arr = temp;

            index = n;
        }

        T* data()
        {
            return &arr[0];
        }

        void pop_back()
        {
            index--;
        }
};

int main()
{
    vector<int> v;

    for (int i = 1; i <= 50; i++)
    {
        v.push_back(i);
    }

    for (int i = 1; i <= 50; i++)
    {
        cout << i << " ";
    }

    cout << v.capacity_() << " " << v.size() << " " << endl;

    return 0;
}
