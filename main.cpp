/* 
 * File:   main.cpp
 * Author: shijiex
 *
 * Created on November 7, 2013, 3:55 PM
 */

#include <string.h>
#include <iostream>
#include <set>
#include <cstdlib>

class Node{
public:
    struct comparator
    {
        bool operator() (Node *one, Node *two )
        {
                return one->_card < two->_card;
        }
     };
    std::string _card;
    std::set<Node*, comparator> _children;
    
public:
   
    Node(std::string card):_card(card){
    }
    
 
};

class CardTree{
    Node* _root;
    int _count ;
    std::set<Node*> nodes;
public:
    void print(){
        if(_count == 0) return ;
        std::cout<<_count<<std::endl;
    }
    CardTree():_count(0){
        _root = new Node("");
    }
    ~CardTree(){
        for(std::set<Node*>::iterator iter = nodes.begin();
                iter != nodes.end(); iter++){
            Node* node = *iter;
            delete node;
        }
        delete _root;
    }
    
    void addOneString(std::string line){
        int cardsNumber = 0, i =0;
        std::string::size_type prev_pos = 0, pos = 0;
        std::string* cards = NULL;
         while( (pos = line.find(' ', pos)) != std::string::npos ||  pos != -1 )
         {
                if(cardsNumber ==0 ){
                    cardsNumber = atoi(line.substr(prev_pos, pos-prev_pos).c_str());
                    cards = new std::string[cardsNumber+1];
                }else{
//                    if( i>= cardsNumber ){
//                        break;
//                    }
                    std::string onecard = line.substr(prev_pos, pos-prev_pos);
                    cards[i++] = onecard;
                }
                
                prev_pos = ++pos;
         }
         if( i< cardsNumber ){
             /* Hard code 2 len makes it is not scaleable*/
             std::string onecard =  line.substr(prev_pos, 2); 
             cards[i++] = onecard;
         }

         addNode(cards, cardsNumber-1, _root);
    }
    
    void addNode(std::string* cards, int number, Node* root){
        std::string card = cards[number];
        Node *node =new Node(card);
        std::set<Node*, Node::comparator>::iterator iter = root->_children.find(node);
        if(root->_children.size() !=0 && iter!=root->_children.end() ){
            Node* oneNode = *iter;
            delete node;
            if(number==0) return;   //The current cards is sub tail string of previous one.
            addNode(cards, number-1, oneNode);
        }else{
            Node *cur = root ;
            for(; number >=0; number--){
                _count++;
                cur->_children.insert(node);
                nodes.insert(node);
                cur = node;
                if(number!=0)
                     node = new Node(cards[number-1]);
            }
        }
    }
};

int main(int argc, char** argv) {

   using namespace std;
  
   CardTree* tree = new CardTree();
   int handlesCount = 0;
    while(true){
        string line;
        getline(cin, line);
        if(line == "0" || line == "" ){
            break;
        }else{
            if(index(line.c_str(), ' ') == NULL ){
                handlesCount = atoi(line.c_str());
                tree->print();
                delete tree;
                tree = new CardTree();
            }else{
                tree->addOneString(line);
            }
        }
            
    }
   tree->print();
   return 0;
}

