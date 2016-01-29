#ifndef DEQUE_AS_ARRAY_H
#define DEQUE_AS_ARRAY_H

/******************************************
 * UW User ID:  phsung
 * Submitted for ECE 250
 * Semester of Submission:  (Winter) 2016
 *
 * By submitting this file, I affirm that
 * I am the author of all modifications to
 * the provided  code.
 ******************************************/

#include "Exception.h"

#include <stdio.h>
#include <iostream>


class Deque_as_array {
	private:
		int array_size;
		int*array;
		int ihead;
		int itail;
		int count;

	public:
		Deque_as_array( int = 10 );
		~Deque_as_array();

		int head() const;
		int tail() const;
		int size() const;
		bool empty() const;
		int capacity() const;

		void enqueue_head( int const & );
		void enqueue_tail( int const & );
		int dequeue_head();
		int dequeue_tail();
		void clear();

	
};


//Constructor
Deque_as_array::Deque_as_array( int n ):
array_size( std::max( 1, n ) ), 
array( new int[array_size] ), 
count( 0 ) {
	// empty
}


//Destructor
Deque_as_array::~Deque_as_array() {
    count = 0;
    ihead = -1;
    itail = -1;
    delete [] array;
}


//Returns the count of number of items in deque
int Deque_as_array::size() const {
	return count;
}

//Returns the maximum capacity of deque
int Deque_as_array::capacity() const {
	return array_size;
}

//Returns a boolean whether deque is empty or not
bool Deque_as_array::empty() const {
	if (count > 0)
    {
        return false;
    }
    else
    {
        return true;
    }
}


//Returns the value in head of deque
int Deque_as_array::head() const {
	if (size() > 0)
    {
        return array[ihead];
    }
	throw underflow();     // Throw underflow
}

//Returns the value in tail of deque
int Deque_as_array::tail() const {
    if (size() > 0)
    {
        return array[itail];
    }
	throw underflow();     // Throw overflow
}

//Enqueues a value to head
void Deque_as_array::enqueue_head( int const &obj ) {
	//If there are no previous elements in queue add to front of array and set head and tail index
    if (size() == 0)
    {
        ihead = 0;
        itail = 0;
        array[0] = obj;
        count++;
    }
    else if (size() > capacity()-1)
    {
        //Throw overflow if number of elements exceeds maximum number of allowed elements
        throw overflow();
    }
    else
    {
        //Set the new head index as well as new value at head index
        ihead--;
        if (ihead<=-1)
        {
            ihead = capacity()-1;
        }
        array[ihead] = obj;
        count++;
    }
    
}

//Enqueues a value to tail
void Deque_as_array::enqueue_tail( int const &obj ) {
	//If there are no previous elements in queue add to front of array and set head and tail index
    if (size() == 0)
    {
        ihead = 0;
        itail = 0;
        array[0] = obj;
        count++;
    }
    else if (size() > capacity()-1)
    {
        //Throw overflow if number of elements exceeds maximum number of allowed elements
        throw overflow();
    }
    else
    {
        //Set the new tail index as well as new value at tail index
        itail++;
        if (itail>=capacity())
        {
            itail = 0;
        }
        array[itail] = obj;
        count++;
        //catch overflow
    }
    
    
    
}

 
int Deque_as_array::dequeue_head() {
    if (size() == 0)
    {
        //Throw underflow if trying to dequeue from an empty dequeu
        throw underflow();
    }
    else
    {
        //Deque value from head and return the value
        int returnValue = array[ihead];
        array[ihead] = 0;
        
        count--;
        ihead++;
        
        if (size() == 0)
        {
            ihead = -1;
        }else if (ihead >= capacity())
        {
            ihead = 0;
        }
        return returnValue;
    }
    return 0;
}

 
int Deque_as_array::dequeue_tail() {
	if (size() == 0)
    {
        //Throw underflow if trying to dequeue from an empty dequeu
        throw underflow();
    }
    else
    {
        //Deque value from tail and return the value
        int returnValue = array[itail];
        array[itail] = 0;
        count--;
        itail--;
        
        if (size() == 0)
        {
            itail = -1;
        } else if (itail <= -1)
        {
            itail = capacity() -1;
        }
        return returnValue;
    }
	return 0;     // This returns a default object
}

 
void Deque_as_array::clear() {
    //Reset the dequeu by clearing all elements
    for (int i = 0; i<size() ;i++)
    {
        array[i] = 0;
    }
    count = 0;
    ihead = -1;
    itail = -1;
}

#endif
