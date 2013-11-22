/* 
 * File:   MyNode.cpp
 * Author: shijiex
 * 
 * Created on November 22, 2013, 3:06 PM
 */

#include "MyNode.h"

MyNode::MyNode() {
}

MyNode::MyNode(const MyNode& orig) {
}

MyNode::MyNode(std::string str):data(str){
}

MyNode::~MyNode() {
}

std::string MyNode::getData(){
    return data;
}

