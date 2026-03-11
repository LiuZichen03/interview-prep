#include <stdexcept>
#ifndef _DYNAMIC_ARRAY_
#define _DYNAMIC_ARRAY_

class array
{
    public:
    array(int s = 0,int c = 10,const int* d = 0)
    :size(s),capacity(c),data(new int[c])
    {}//普通构造
    array(const array& str);
    ~array();//析构函数
    array& operator = (const array& str);//拷贝赋值
    int Size() const;
    int Capacity()const;
    bool is_empty()const;
    int at(int index) const;
    void push_back(int x);
    void pop_back();
    void insert(int index,int x);
    void prepend(int x);
    void erase(int index);
    int find(int x) const;
    void remove(int x);

    private:
    int* data;
    int size;
    int capacity;
    void resize(int new_cap);

};
inline array::~array()
{
    delete[] data;
}
inline array::array(const array& str)
{
    if(str.data)
    {
        size = str.size;
        capacity = str.capacity;
        data = new int[capacity];
        for(int i = 0;i<size;i++)
        data[i] = str.data[i];
    }
}
inline array& array::operator=(const array& str)
{
    if(this==&str)
    {
        return *this;
    }
    size = str.size;
    capacity = str.capacity;
    delete[] data;
    data = new int[capacity];
    for(int i = 0;i<size;i++)
    data[i] = str.data[i];

    return *this;
}
inline int array::Size() const
{
    return this->size;
}
inline int array::Capacity() const
{
    return this->capacity;
}
inline bool array::is_empty() const
{
    if(this->size == 0)
    return true;
    else return false;
}
inline int array::at(int index) const
{
    if(index < 0 || index >= this->size)
        throw std::out_of_range("array::at: index out of range");
    return this->data[index];
}
inline void array::resize(int new_cap)
{
    int *new_data = new int[new_cap];
    for(int i = 0;i<this->size;i++)
    {
        new_data[i] = data[i];
    }
    delete[] data;
    this->data = new_data;
    this->capacity = new_cap;
}
inline void array::push_back(int x)
{
    if(size == capacity)
        resize(capacity*2);
    data[size] = x;
    size++;
}
inline void array::pop_back()
{
    if(size == 0)
      throw std::out_of_range("array::pop_back: index out of range");
    size--;
}
inline void array::insert(int index,int x)
{
    if(index < 0||index > size)
      throw std::out_of_range("array::insert: index out of range");
    if(size == capacity )
      resize(capacity*2);
    for(int i = size;i>index;i--)
    {
        data[i] = data[i - 1];
    }
    data[index] = x;
    size++;
}
inline void array::prepend(int x)
{
    insert(0,x);
}
inline void array::erase(int index)
{
    if(index<0||index>=size)
      throw std::out_of_range("array::erase: index out of range");
    for(int i = index;i <size-1;i++)
     data[i] = data[i+1];
    size--;
}
inline int array::find(int x) const
{
    for(int i = 0;i < size;i++)
    {
        if(data[i] == x)
          return i;
    }
    return -1;
}
inline void array::remove(int x)
{
    int i = find(x);
    while(i != -1)
    {
        erase(i);
        i = find(x);
    }
}
#endif