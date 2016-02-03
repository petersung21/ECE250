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

template<typename T >
DoubleHashTable<T >::~DoubleHashTable() {
	count = 0;
	array_size = 0;
	power = 0;
	delete [] array;
	delete [] array_state;
}

template<typename T >
int DoubleHashTable<T >::size() const {
	return count;
}

template<typename T >
int DoubleHashTable<T >::capacity() const {
	return array_size;
}



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

template<typename T >
int DoubleHashTable<T >::h1( T const &obj ) const {
	int arrayIndex = static_cast<int>(obj) % array_size;

	if (arrayIndex < 0)
	{
		arrayIndex = arrayIndex + array_size;
	}

	return arrayIndex;
}

template<typename T >
int DoubleHashTable<T >::h2( T const &obj ) const {
	int jumpValue = (obj/array_size) % array_size;
	if (jumpValue < 0)
	{
		jumpValue = jumpValue + jumpValue;
	}
	if (jumpValue % 2 == 0)
	{
		jumpValue = jumpValue + 1;
	}
	return jumpValue;
}

template<typename T >
bool DoubleHashTable<T >::member( T const &obj ) const {
	int jumpValue = h2(obj);
	int arrayIndex = h1(obj);

	while(array_state[arrayIndex] == OCCUPIED || array_state[arrayIndex] == DELETED)
	{
		if (array[arrayIndex] == obj)
		{
			return true;
		}
		arrayIndex = arrayIndex + jumpValue;
		arrayIndex = arrayIndex % array_size;
	}
	

	return false;
}

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

template<typename T >
void DoubleHashTable<T >::insert( T const &obj ) {
	 //Error Handling
	if (size() == capacity())
	{
		throw overflow();
	}

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

template<typename T >
bool DoubleHashTable<T >::remove( T const &obj ) {
	 //Error Handling	
	if (size() == 0)
	{
		throw underflow();
	}

	int jumpValue = h2(obj);
	int arrayIndex = h1(obj);

	while(array_state[arrayIndex] == OCCUPIED || array_state[arrayIndex] == DELETED)
	{
		if (array[arrayIndex] == obj)
		{
			array[arrayIndex] = 0;
			array_state[arrayIndex] = DELETED;
			count--;
			return true;
		}
		arrayIndex = arrayIndex + jumpValue;
		arrayIndex = arrayIndex % array_size;
	}
	return false;
}

template<typename T >
void DoubleHashTable<T >::clear() {
	for ( int i = 0; i < array_size; ++i ) {
		array_state[i] = EMPTY;
		array[i] = 0;
	}
	count = 0;

	return; 
}

template<typename T >
void DoubleHashTable<T >::print() const {
     std::cout << "What am I supposed to print here lol" << std::endl;
	return;
}

#endif
