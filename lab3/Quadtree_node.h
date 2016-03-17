#ifndef SINGLE_NODE_H
#define SINGLE_NODE_H

/****************************************
 * Name: Peter Hyungrok Sung
 * UW User ID:  phsung
 * Submitted for ECE 250
 * Department of Electrical and Computer Engineering
 * University of Waterloo
 * Calender Term of Submission:  (Winter) 2016
 *
 * By submitting this file, I affirm that
 * I am the author of all modifications to
 * the provided code.
 ****************************************/

#include "ece250.h"

template <typename T>
class Quadtree;

template <typename T>
class Quadtree_node {
	private:
		T       x_value;
		T       y_value;

		Quadtree_node *north_west;
		Quadtree_node *north_east;
		Quadtree_node *south_west;
		Quadtree_node *south_east;

	public:
		Quadtree_node( T const & = T(), T const & = T() );
        ~Quadtree_node();

		T retrieve_x() const;
		T retrieve_y() const;

		Quadtree_node *nw() const;
		Quadtree_node *ne() const;
		Quadtree_node *sw() const;
		Quadtree_node *se() const;

		T min_x() const;
		T min_y() const;

		T max_x() const;
		T max_y() const;

		T sum_x() const;
		T sum_y() const;

		bool member( T const &, T const & ) const;

		bool insert( T const &, T const & );
		void clear();

	friend class Quadtree<T>;
};


//Constructor
template <typename T>
Quadtree_node<T>::Quadtree_node( T const &x, T const &y ):
x_value( x ), 
y_value( y ), 
north_west( 0 ),
north_east( 0 ),
south_west( 0 ),
south_east( 0 ) {
	// empty constructor
}


//Destructor
template <typename T>
Quadtree_node<T>::~Quadtree_node(){
}


// Return the x values of the current node
template <typename T>
T Quadtree_node<T>::retrieve_x() const {
	return x_value;
}

// Return the y values of the current node
template <typename T>
T Quadtree_node<T>::retrieve_y() const {
	return y_value;
}

//Return the north-west pointer
template <typename T>
Quadtree_node<T> *Quadtree_node<T>::nw() const {
	return north_west;
}

//Return the north-east pointer
template <typename T>
Quadtree_node<T> *Quadtree_node<T>::ne() const {
	return north_east;
}

//Return the south-west pointer
template <typename T>
Quadtree_node<T> *Quadtree_node<T>::sw() const {
	return south_west;
}


//Return the south-east pointer
template <typename T>
Quadtree_node<T> *Quadtree_node<T>::se() const {
	return south_east;
}

//Return the minimum x value within the quadtree by recursively calling min_x function on the north west and south west nodes
template <typename T>
T Quadtree_node<T>::min_x() const {
    T min = retrieve_x();
    if (north_west != 0)
    {
        min = std::min(min, nw()->min_x());
    }
    if (south_west != 0)
    {
        min = std::min(min, sw()->min_x());
    }
    
    return min;
}

//Return the minimum y value within the quadtree by recursively calling min_y function on the south east and south west nodes
template <typename T>
T Quadtree_node<T>::min_y() const {
    T min = retrieve_y();
    if (south_east != 0)
    {
        min = std::min(min, se()->min_y());
    }
    if (south_west != 0)
    {
        min = std::min(min, sw()->min_y());
    }
    
    return min;
}


//Return the maximum x value within the quadtree by recursively calling max_x function on the north east and south east nodes
template <typename T>
T Quadtree_node<T>::max_x() const {
    T max = retrieve_x();
    if (north_east != 0)
    {
        max = std::max(max, ne()->max_x());
    }
    if (south_east != 0)
    {
        max = std::max(max, se()->max_x());
    }
    
    return max;
}


//Return the maximum y value within the quadtree by recursively calling max_y function on the north east and north west nodes
template <typename T>
T Quadtree_node<T>::max_y() const {
    T max = retrieve_y();
    if (north_east != 0)
    {
        max = std::max(max, ne()->max_y());
    }
    if (north_west != 0)
    {
        max = std::max(max, nw()->max_y());
    }
    
    return max;
}

//Calculates the sum of all x values in the tree by recursively calling all nodes in the tree
template <typename T>
T Quadtree_node<T>::sum_x() const {
    T sum = 0;
    if ( retrieve_x() == 0 ) {
		return 0;
	} else {
        sum = sum + retrieve_x();
        if (north_east != 0)
        {
            sum = sum + ne()->sum_x();
        }
        if (south_east != 0)
        {
            sum = sum + se()->sum_x();
        }
        if (north_west != 0)
        {
            sum = sum + nw()->sum_x();
        }
        if (south_west != 0)
        {
            sum = sum + sw()->sum_x();
        }
        
		return sum;
	}
}

//Calculates the sum of all y values in the tree by recursively calling all nodes in the tree
template <typename T>
T Quadtree_node<T>::sum_y() const {
    T sum = 0;
    if ( retrieve_y() == 0 ) {
        return 0;
    } else {
        sum = sum + retrieve_y();
        if (north_east != 0)
        {
            sum = sum + ne()->sum_y();
        }
        if (south_east != 0)
        {
            sum = sum + se()->sum_y();
        }
        if (north_west != 0)
        {
            sum = sum + nw()->sum_y();
        }
        if (south_west != 0)
        {
            sum = sum + sw()->sum_y();
        }
        
        return sum;
    }
}

//Returns true if the pair (x,y) is stored in the current node, or in the Quadtree starting at the current node. Done by recursively calling the member function based on the comparison of x's and y's. Parameters are the x and y values of node you are trying to find.
template <typename T>
bool Quadtree_node<T>::member( T const &x, T const &y ) const {
	if ( this == 0 ) {
		return false;
	}

    if (retrieve_y() == y && retrieve_x() == x){
        return true;
    } else if (retrieve_y() <= y && retrieve_x() <= x){
        return ne()->member(x,y);
    } else if (retrieve_y() <= y && retrieve_x() > x){
        return nw()->member(x,y);
    } else if (retrieve_y() > y && retrieve_x() <= x){
        return se()->member(x,y);
    } else{
        return sw()->member(x,y);
    }
    
	return false;
}


//If the pair (x,y) equals the pair stored in the current node, return false; otherwise, insert the pair into the appropriate sub-tree either by creating a new node and returning true or recursively calling insert and returning that call's return value. Parameters are the x and y values of node you are trying to insert.
template <typename T>
bool Quadtree_node<T>::insert( T const &x, T const &y ) {
    if ( this == 0 )
    {
        x_value = x;
        y_value = y;
        return true;
    }
    
    if (retrieve_y() == y && retrieve_x() == x){
        return false;
    } else if (retrieve_y() <= y && retrieve_x() <= x){
        if (ne() == 0)
        {
            north_east = new Quadtree_node<T>(x,y);
            return true;
        }
        return ne()->insert(x,y);
    } else if (retrieve_y() <= y && retrieve_x() > x){
        if (nw() == 0)
        {
            north_west = new Quadtree_node<T>(x,y);
            return true;
        }
        return nw()->insert(x,y);
    } else if (retrieve_y() > y && retrieve_x() <= x){
        if (se() == 0)
        {
            south_east = new Quadtree_node<T>(x,y);
            return true;
        }
        return se()->insert(x,y);
    } else{
        if (sw() == 0)
        {
            south_west = new Quadtree_node<T>(x,y);
            return true;
        }
        return sw()->insert(x,y);
    }
    
    return true;
}


//Clears all nodes in the tree by recursively calling clear() on all nodes in the tree
template <typename T>
void Quadtree_node<T>::clear() {
    if ( this != 0 ) {
        
        if (ne() != 0){
            ne()->clear();
        }
        if (nw() != 0) {
            nw()->clear();
        }
        if (sw() != 0) {
            sw()->clear();
        }
        if (se() != 0) {
            se()->clear();
        }
        
        delete this;
    }
}

#endif
