#ifndef DOUBLE_HASH_TABLE_H
#define DOUBLE_HASH_TABLE_H

/****************************************
 * UW User ID:  phsung
 * Submitted for ECE 250
 * Semester of Submission:  (Winter) 2016
 *
 * By submitting this file, I affirm that
 * I am the author of all modifications to
 * the provided code.
 ****************************************/

#include "Exception.h"
#include "ece250.h"

enum state { EMPTY, OCCUPIED, DELETED };

template<typename T>
class DoubleHashTable {
private:
    int count;
    int power;
    int array_size;
    T *array;
    state *array_state;
    
    int h1( T const & ) const; // first hash function
    int h2( T const & ) const; // second hash function
    
public:
    DoubleHashTable( int = 5 );
    ~DoubleHashTable();
    int size() const;
    int capacity() const;
    bool empty() const;
    bool member( T const & ) const;
    T bin( int ) const;
    
    void print() const;
    
    void insert( T const & );
    bool remove( T const & );
    void clear();
};

//Constructor
template<typename T >
DoubleHashTable<T >::DoubleHashTable( int m ):
count( 0 ), power( m ),
array_size( 1 << power ),
array( new T [array_size] ),
array_state( new state[array_size] ) {
    
    for ( int i = 0; i < array_size; ++i ) {
        array_state[i] = EMPTY;
    }
}

//Destructor
template<typename T >
DoubleHashTable<T >::~DoubleHashTable() {
    count = 0;
    array_size = 0;
    power = 0;
    delete [] array;
    delete [] array_state;
}


//Returns the count of elements in hashtable
template<typename T >
int DoubleHashTable<T >::size() const {
    return count;
}

//Returns the capacity of the hashtable
template<typename T >
int DoubleHashTable<T >::capacity() const {
    return array_size;
}


//Returns a boolean whether hashmap is empty or not
template<typename T >
bool DoubleHashTable<T >::empty() const {
    if (size() > 0)
    {
        return false;
    }
    else
    {
        return true;
    }
}

//First hashing function. Obj is the value you wish to put in hashmap.
//This value divded by array size and applying the module of M. Made positive by adding  M if necessary.
template<typename T >
int DoubleHashTable<T >::h1( T const &obj ) const {
    int arrayIndex = static_cast<int>(obj) % array_size;
    
    if (arrayIndex < 0)
    {
        arrayIndex = arrayIndex + array_size;
    }
    
    return arrayIndex;
}

//Second hashing function or the step function. Obj is the value you wish to put in hashmap.
//This value divded by array size and applying the module of M. Made positive by adding  M if necessary.
//Add 1 if value is even to make it positive
template<typename T >
int DoubleHashTable<T >::h2( T const &obj ) const {
    int jumpValue = (static_cast<int>(obj)/array_size) % array_size;
    if (jumpValue < 0)
    {
        jumpValue = jumpValue + array_size;
    }
    if (jumpValue % 2 == 0)
    {
        jumpValue = jumpValue + 1;
    }
    return jumpValue;
}

//Return true if object obj is in the hash table and false otherwise. Takes in obj as parameter to find that value in hashtable
template<typename T >
bool DoubleHashTable<T >::member( T const &obj ) const {
    int jumpValue = h2(obj);
    int arrayIndex = h1(obj);
    int counter = 0;
    
    while(array_state[arrayIndex] == OCCUPIED || array_state[arrayIndex] == DELETED)
    {
        if (array[arrayIndex] == obj && array_state[arrayIndex] != DELETED)
        {
            return true;
        }
        arrayIndex = arrayIndex + jumpValue;
        arrayIndex = arrayIndex % array_size;
        counter++;
        //Prevent Infinte loop
        if (counter >= capacity())
        {
            break;
        }
    }
    
    
    return false;
}

//Return the entry in bin n. Takes in obj as parameter to find that value in hashtable.
//Throws out of bounds exception if n is greater than capacity
template<typename T >
T DoubleHashTable<T >::bin( int n ) const {
    // enter your implemetation here
    if (n > capacity())
    {
        throw out_of_bounds();
    }
    else if (array_state[n] == OCCUPIED)
    {
        return array[n];
    }
    return T();
}

// Insert the new object into the hash table in the appropriate bin based on hash functions and step counter if space is full.
// If the table is full, throw an overflow exception. Takes in obj as parameter (can be int or double)
template<typename T >
void DoubleHashTable<T >::insert( T const &obj ) {
    //Error Handling
    if (size() == capacity())
    {
        throw overflow();
    }
    if (member(obj))
    {
        return;
    }
    int counter = 0;
    int jumpValue = h2(obj);
    int arrayIndex = h1(obj);
    
    while(array_state[arrayIndex] == OCCUPIED)
    {
        arrayIndex = arrayIndex + jumpValue;
        arrayIndex = arrayIndex % array_size;
    }
    array[arrayIndex] = obj;
    array_state[arrayIndex] = OCCUPIED;
    count++;
}

//Remove the object from the hash table if it is in the hash table (returning false if it is not) by setting the corresponding flag of the bin to deleted.
//Takes in obj as parameter (can be int or double)
template<typename T >
bool DoubleHashTable<T >::remove( T const &obj ) {
    
    int jumpValue = h2(obj);
    int arrayIndex = h1(obj);
    int counter = 0;
    
    while(array_state[arrayIndex] == OCCUPIED || array_state[arrayIndex] == DELETED)
    {
        if (array[arrayIndex] == obj && array_state[arrayIndex] != DELETED)
        {
            array[arrayIndex] = 0;
            array_state[arrayIndex] = DELETED;
            count--;
            return true;
        }
        counter++;
        arrayIndex = arrayIndex + jumpValue;
        arrayIndex = arrayIndex % array_size;
        //Prevent Infinite Loop
        if (counter >= capacity())
        {
            break;
        }
    }
    return false;
}

//Remove all the elements in the hash table.
template<typename T >
void DoubleHashTable<T >::clear() {
    for ( int i = 0; i < array_size; ++i ) {
        array_state[i] = EMPTY;
        array[i] = 0;
    }
    count = 0;
    
    return;
}

//Prints the class status
template<typename T >
void DoubleHashTable<T >::print() const {
    std::cout << "size: " << size() << std::endl;
    
    std::cout << "capacity: " << capacity() << std::endl;
    
    
    
    for (int i = 0; i < array_size ; i++) {
        
        std::cout << i << " " << array[i] << " " << array_state[i] << std::endl;
        
    }
    
    
    
    return ;
}

#endif
