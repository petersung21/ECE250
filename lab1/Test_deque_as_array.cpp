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
        std::cout << "Proper underflow error thrown" << std::endl;
    }
    
    try {
        testDeque->dequeue_head();
    } catch (underflow ex) {
        std::cout << "Proper underflow error thrown" << std::endl;
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
        std::cout << "Proper overflow error thrown" << std::endl;
    }
    
    testDeque->dequeue_head();
    testDeque->dequeue_tail();
    
    if(testDeque->size() == 8)
    {
        std::cout << "Proper size" << std::endl;
    }
    else
    {
        std::cout << "Error: Wrong size" << std::endl;
    }
    if(testDeque->capacity() == 10)
    {
        std::cout << "Proper capacity" << std::endl;
    }
    else
    {
        std::cout << "Error: Wrong capacity" << std::endl;
    }
    if(testDeque->head() == 33)
    {
        std::cout << "Proper head value" << std::endl;
    }
    else
    {
        std::cout << "Error: Wrong head value" << std::endl;
    }
    if(testDeque->tail() == 88)
    {
        std::cout << "Proper tail value" << std::endl;
    }
    else
    {
        std::cout << "Error: Wrong tail value" << std::endl;
    }
    if(testDeque->empty() == false)
    {
        std::cout << "Proper empty boolean" << std::endl;
    }
    else
    {
        std::cout << "Error: Wrong empty boolean" << std::endl;
    }
    
    return 0;
}