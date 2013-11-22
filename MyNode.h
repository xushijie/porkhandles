/* 
 * File:   MyNode.h
 * Author: shijiex
 *
 * Created on November 22, 2013, 3:06 PM
 */

#ifndef MYNODE_H
#define	MYNODE_H
#include <string>

class MyNode {
    std::string data;
public:
    MyNode();
    MyNode(std::string str);
    MyNode(const MyNode& orig);
    virtual ~MyNode();
    
    std::string getData();
    
   
    bool operator<(const MyNode& node){
        return data<node.data;
    }
    
    bool operator<( const MyNode* node){
        return data<node->data;
    }
   

};


#endif	/* MYNODE_H */

