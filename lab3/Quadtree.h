#ifndef QUADTREE_H
#define QUADTREE_H

/***************************************
 * Name: Peter Hyungrok Sung
 * UW User ID:  phsung
 * Submitted for ECE 250
 * Department of Electrical and Computer Engineering
 * University of Waterloo
 * Calender Term of Submission:  (Winter) 2015
 *
 * By submitting this file, I affirm that
 * I am the author of all modifications to
 * the provided code.
 ***************************************/

#include "ece250.h"
#include "Quadtree_node.h"
#include "Exception.h"
#include <iostream>

template <typename T>
class Quadtree {
	private:
		Quadtree_node<T> *tree_root;
		int count;

	public:
		Quadtree();
		~Quadtree();

		// Accessors

		int size() const;
		bool empty() const;

		T min_x() const;
		T min_y() const;

		T max_x() const;
		T max_y() const;

		T sum_x() const;
		T sum_y() const;

		Quadtree_node<T> *root() const;
		bool member( T const &, T const & ) const;

		// Mutators

		void insert( T const &, T const & );
		void clear();

	
};

/*
 Precede each function with comments indicating:
 
 What it does
 What each parameter is used for
 Assumptions that it makes
 How it handles errors
 */

//Constructor for Quadtree
template <typename T>
Quadtree<T>::Quadtree():
tree_root( 0 ), 
count( 0 ) {
	// empty constructor
}

//Destructor of Quadtree. Sets count to 0 and deletes the tree root
template <typename T>
Quadtree<T>::~Quadtree() {
    tree_root->clear();
}

//Returns the count of the quadtree
template <typename T>
int Quadtree<T>::size() const {
	return count;
}

//Returns true if the Quadtree is empty, false otherwise.
template <typename T>
bool Quadtree<T>::empty() const {
    if (count == 0){
        return true;
    }else{
        return false;
    }
}


//Returns the minimum x value within the quadtree. Throw an underflow exception if the tree is empty.
template <typename T>
T Quadtree<T>::min_x() const {
    if(empty()){
        throw underflow();
    }
    
    return tree_root->min_x();
}

//Returns the minimum y value within the quadtree. Throw an underflow exception if the tree is empty.
template <typename T>
T Quadtree<T>::min_y() const {
    if(empty()){
        throw underflow();
    }
    
    return tree_root->min_y();
}

//Returns the maximum x value within the quadtree. Throw an underflow exception if the tree is empty.
template <typename T>
T Quadtree<T>::max_x() const {
    if(empty()){
        throw underflow();
    }
    
    return tree_root->max_x();
}

//Returns the maximum y value within the quadtree. Throw an underflow exception if the tree is empty.
template <typename T>
T Quadtree<T>::max_y() const {
    if(empty()){
        throw underflow();
    }
    
    return tree_root->max_y();
}

//Returns the sum of the x values within the Quadtree, respectively. The sum of the nodes of an empty tree is 0
template <typename T>
T Quadtree<T>::sum_x() const {
    if(empty()){
        return 0;
    }
    
    return tree_root->sum_x();
}

//Returns the sum of the y values within the Quadtree, respectively. The sum of the nodes of an empty tree is 0
template <typename T>
T Quadtree<T>::sum_y() const {
    if(empty()){
        return 0;
    }
    
    return tree_root->sum_y();
}


//Returns the address of the root node. If the tree is empty, the root node should be 0
template <typename T>
Quadtree_node<T> *Quadtree<T>::root() const {
    if (empty())
    {
        return tree_root;
    }
    
    return tree_root;
}

//Returns true if the pair (x,y) is stored in one of the nodes of the Quadtree and false otherwise. Parameters are the x and y values of node you are trying to find.
template <typename T>
bool Quadtree<T>::member( T const &x, T const &y ) const {
    if (empty())
    {
        return false;
    }
    
    return tree_root->member(x,y);
}


//Inserts the pair (x, y) into the Quadtree. If the root is 0, a new quadtree node is created; otherwise, the task of insertion is passed to the root node. Parameters are the x and y values of node you are trying to find.
template <typename T>
void Quadtree<T>::insert( T const &x, T const &y ) {
    if (empty())
    {
        tree_root = new Quadtree_node<T>(x,y);
        count++;
    }
    bool inserted = tree_root->insert(x,y);
    if (inserted)
    {
        count++;
    }
}


//Calls clear on the root if necessary and sets the root and count to 0
template <typename T>
void Quadtree<T>::clear() {
    tree_root->clear();
    count = 0;
    tree_root = 0;
}

#endif
