//
//  Test_deque_as_array.cpp
//  ece250
//
//  Created by Peter Hyungrok Sung on 2016-01-25.
//  Copyright (c) 2016 Peter Hyungrok Sung. All rights reserved.
//

#include <stdio.h>

#include "Deque_as_array.h"

int main() {
    Deque_as_array *testDeque = new Deque_as_array(10);
    
    try {
        testDeque->dequeue_tail();
    } catch (underflow ex) {
        std::cout << "Dequeue on Empty Tail: Proper underflow error thrown" << std::endl;
    }
    
    try {
        testDeque->dequeue_head();
    } catch (underflow ex) {
        std::cout << "Dequeue on Empty Tail: Proper underflow error thrown" << std::endl;
    }
    
    try {
        testDeque->enqueue_head(33);
        testDeque->enqueue_head(53);
        testDeque->enqueue_tail(73);
        testDeque->enqueue_tail(83);
        testDeque->enqueue_tail(84);
        testDeque->enqueue_tail(85);
        testDeque->enqueue_tail(86);
        testDeque->enqueue_tail(87);
        testDeque->enqueue_tail(88);
        testDeque->enqueue_tail(89);
        testDeque->enqueue_tail(90);
    } catch (overflow ex){
        std::cout << "Enqueue more than capacity: Proper overflow error thrown" << std::endl;
    }
    
    testDeque->dequeue_head();
    testDeque->dequeue_tail();
    
    if(testDeque->size() == 8)
    {
        std::cout << "Size of Deque Test: Proper size returned" << std::endl;
    }
    else
    {
        std::cout << "Size of Deque Test: ERROR Wrong size" << std::endl;
    }
    if(testDeque->capacity() == 10)
    {
        std::cout << "Capacity of Deque Test: Proper capacity" << std::endl;
    }
    else
    {
        std::cout << "Capacity of Deque Test: ERROR Wrong capacity" << std::endl;
    }
    if(testDeque->head() == 33)
    {
        std::cout << "Head Value Test: Proper head value" << std::endl;
    }
    else
    {
        std::cout << "Head Value Test: ERROR Wrong head value" << std::endl;
    }
    if(testDeque->tail() == 88)
    {
        std::cout << "Tail Value Test: Proper tail value" << std::endl;
    }
    else
    {
        std::cout << "Tail Value Test: ERROR Wrong tail value" << std::endl;
    }
    if(testDeque->empty() == false)
    {
        std::cout << "Empty Deque Test: Proper empty boolean" << std::endl;
    }
    else
    {
        std::cout << "Empty Deque Test: ERROR Wrong empty boolean" << std::endl;
    }
    
    return 0;
}