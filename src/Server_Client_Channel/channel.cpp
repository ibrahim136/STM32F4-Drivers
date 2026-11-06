#include "channel.h"
/*
static u8 heap_arr[heap_size];
static u8 offset =0;



static inline void *operator new[](size_t size)
{
    if (offset + size > heap_size -1)
    {
        return nullptr;
    }
    void * ptr = &heap_arr[offset];
    offset += size;
    return ptr;
}

Channel::Channel()
{
    capacity = DEFAULT_CAPACITY;
    array = new size_t[DEFAULT_CAPACITY];
    read_index = 0;
    write_index = 0;
    count =0;
}

Channel::Channel(int capacity)
{
    this->capacity = capacity;
    array = new int[capacity];
    read_index = 0;
    write_index = 0;
    count =0;
}

Channel::Channel(int *array, int capacity)
{
    this->capacity = capacity;
    this->array = new int[capacity];
    for (int i{0}; i < capacity; i++)
    {
        this->array[i] = array[i];
    }
    read_index = 0;
    write_index = 0;
    count = this->capacity;
}

void operator delete[](void *)
{
    
}

Channel::~Channel()
{
    delete [] array;
    array = nullptr;
}

int Channel::increment_index(int index)
{
    return (++index % capacity);
}

bool Channel::is_empty()
{
    return count ==0;
}

bool Channel::is_full()
{
    return count == capacity;
}

int Channel::read()
{
    if (is_empty()){
        return INT_MIN;
    }
    int ret = array[read_index];
    read_index = increment_index(read_index);
    count--;
    return ret;
}

bool Channel::write(int value)
{
    if (is_full()){
        return false;
    }
    array[write_index] = value;
    write_index = increment_index(write_index);
    count++;
    return true;
}
*/