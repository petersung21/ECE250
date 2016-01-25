#ifndef DEQUE_AS_ARRAY_H
#define DEQUE_AS_ARRAY_H

/******************************************
 * UW User ID:  uwuserid
 * Submitted for ECE 250
 * Semester of Submission:  (Winter|Spring|Fall) 20NN
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

 
Deque_as_array::Deque_as_array( int n ):
array_size( std::max( 1, n ) ), 
array( new int[array_size] ), 
count( 0 ) {
	// empty
}

 
Deque_as_array::~Deque_as_array() {
    count = 0;
    ihead = -1;
    itail = -1;
    delete [] array;
}

 
int Deque_as_array::size() const {
	return count;
}

 
int Deque_as_array::capacity() const {
	return array_size;
}

 
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


int Deque_as_array::head() const {
	if (size() > 0)
    {
        return array[ihead];
    }
	throw underflow();     // This returns a default object
}

 
int Deque_as_array::tail() const {
    if (size() > 0)
    {
        return array[itail];
    }
	throw underflow();     // This returns a default object
}


void Deque_as_array::enqueue_head( int const &obj ) {
	if (size() == 0)
    {
        ihead = 0;
        itail = 0;
        array[0] = obj;
        count++;
    }
    else if (size() > 9)
    {
        throw overflow();
    }
    else
    {
        ihead--;
        if (ihead<=-1)
        {
            ihead = capacity()-1;
        }
        array[ihead] = obj;
        count++;
    }
    
}


void Deque_as_array::enqueue_tail( int const &obj ) {
	// enter your implementation here
    if (size() == 0)
    {
        ihead = 0;
        itail = 0;
        array[0] = obj;
        count++;
    }
    else if (size() > 9)
    {
        throw overflow();
    }
    else
    {
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
        throw underflow();
    }
    else
    {
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
        throw underflow();
    }
    else
    {
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
    for (int i = 0; i<size() ;i++)
    {
        array[i] = 0;
    }
    count = 0;
    ihead = -1;
    itail = -1;
}

#endif
