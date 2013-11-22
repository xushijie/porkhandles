/* 
 * File:   main.cpp
 * Author: shijiex
 *
 * Created on November 7, 2013, 3:55 PM
 */

#include <list>
#include <vector>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <cstdlib>
#include <set>

class Node;



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
    bool _visited;
    int i;
    int _ref;
    Node* _parent;
    std::set<Node*, comparator> _children;
    
public:
    
    Node(int no){ i =no;}
    Node(std::string card):_ref(1){
        _visited = false;
        _card =card;
    }
    
    Node(const Node& node){
        _visited = node._visited;
        _card = node._card;
    }
    
    Node(const Node* node){
        _visited = node->_visited;
        _card = node->_card;
    
    }
    void setVisited(){
        _visited = true;
    }
    
    bool isVisited(){
        return _visited;
    }
    
    bool equal(Node* node){
        return strcmp(this->_card.c_str(), node->_card.c_str()) == 0? true: false;
    }
    
    bool equal(std::string card){
        return strcmp(this->_card.c_str(), card.c_str())==0? true: false;
    }
    
    std::string toString(){
        return _card;
    }
    
};

/**
 *  @TODO: concat current _cards with tails which is shared with others. This is bug, currently only for output length
 */
class CardList{
private:
    std::string _line; 
    int _count;
    int _realCount;
    std::list<Node*> _cards;
    
public: 
   
    int getRealCount(){
        return _realCount;
    }
    std::list<Node*>  getHandleCards(){
        return _cards;
    }
    
    CardList(std::string line, std::list<CardList*>* handles):_count(0),_realCount(0){
        _line =line;
       
        int i =0 ;
        std::string* cCards ;
        std::string::size_type prev_pos = 0, pos = 0;
         while( (pos = line.find(' ', pos)) != std::string::npos ||  pos != -1 )
         {
                if(_count ==0 ){
                    _count = atoi(line.substr(prev_pos, pos-prev_pos).c_str());
                    
                    cCards = new std::string[_count+1];
                }else{
                    if( i>= _count ){
                        cCards[i] ='\0';
                        break;
                    }
                    cCards[i++] = line.substr(prev_pos, pos-prev_pos);
                }
                
                prev_pos = ++pos;
         }
         if( i< _count ){
             cCards[i++] =  line.substr(prev_pos, pos-prev_pos);  // Last word 
         }
         
        initCardHanleList( cCards, handles);
         
        delete[] cCards;
    }
    
    ~CardList(){
        //delete[] array;
    }
    
    int getRealCountSize(){
        return _realCount;
    }
    
    
    void initCardHanleList(std::string* cards, std::list<CardList*>* handles){
        using namespace std;    
        int curse = 0; 
        CardList* handle = getNodeWithLogestTailmatch(cards, handles, &curse);
        _realCount = _count - curse ;
        
        
        for(int i=0; i < _count; i++){
            if(i<_realCount){
                 Node* node = new Node(cards[i]);
                _cards.push_back(node);
            }else{
                handle->copylastcards(&_cards, curse);
                break;
            }
        }
        
    }
    
    void copylastcards(std::list<Node* >* cards, int n){
        std::list<Node*>::iterator iter = _cards.begin();
        int i=0; 
        while(iter!= _cards.end() && i++ <_count - n){
            iter++; 
        }
        
        //std::copy(iter, _cards.end(), std::back_inserter(*cards));
        while(iter != _cards.end()){
            Node* node = *iter;
            cards->push_back(*iter);
            iter++;
        }
    }
    
    CardList* getNodeWithLogestTailmatch(std::string* cards, std::list<CardList*>* handles, int* matched){
        
        std::list<CardList*>::iterator handleIter = handles->begin();
        CardList* matchedHandle = NULL;
        while(handleIter!=handles->end()){
            
            
            CardList* handle = *handleIter++;
            int hMatch = handle->getTailMacth(cards, _count);
            if(*matched < hMatch){
                *matched = hMatch;
                matchedHandle = handle;
            }
        }
        return matchedHandle;
    
    }
    
    
    int getTailMacth(std::string* cards, int count){
        std::list<Node*>::reverse_iterator rIter = _cards.rbegin();
        int matched = 0;
        while(rIter != _cards.rend() && count >0){
            Node* node = *rIter++ ;
            --count;
            if(strcmp(node->_card.c_str(), cards[count].c_str()) ==0 ){
                matched ++;
            }else{
                break;
            }
        }
        
        return matched;
    }
    
    void dump(){
        
        std::cout<<"  "<<_count<<" "<<_realCount<<"  :";
        std::list<Node*>::iterator iter = _cards.begin();
       
        while(iter != _cards.end()){
            std::cout<< (*iter)->_card<<"  ";
            iter++;
            
        }
        std::cout<<"  "<<std::endl;
    }
    
};

void printResult(std::list<CardList*>* handles) {
    using namespace std;
    list<CardList*>::iterator iterc = handles->begin();
    int min = 0;
    while (iterc != handles->end()) {
        CardList* list = *iterc++;
        if (list != NULL) {
           //list->dump();
            min += list->getRealCount();
            //list->clear();
        }
       
       
    }
    handles->clear();
    if(min == 0)  return;
    
    
    cout << min<<endl;
}


std::string trim(const std::string& str,
                 const std::string& whitespace = " \t")
{
    int strBegin = str.find_first_not_of(whitespace);
    if (strBegin == -1)
        return ""; // no content

    int strEnd = str.find_last_not_of(whitespace);
    int strRange = strEnd - strBegin + 1;
    if(str.find("\r") !=-1 )  strRange --;  //Maybe bug
    
    return  str.substr(strBegin, strRange);;
}


//
//void test(){
//    
//    using namespace std;
//    list<Node*>  list1;
//    
//    for(int i =0 ; i< 3; i++ ){
//        Node* str = new Node(i);
//        list1.push_back(str);
//        cout<< "  "<<str<<" -> ";
//    }
//    cout<<endl;
//    list<Node*>  list2;
//    for(int i =0 ; i< 3; i++ ){
//        Node* str = new Node(i);
//        list2.push_back(str);
//        cout<< "  "<<str<<" -> ";
//    }
//    
//    Node* node = new Node("node");
//    list1.push_back(node);
//    list2.push_back(node);
//    cout<<endl<<" both add "<<node<<endl<<"  ................"<<endl;
//    cout<<"list 1"<<endl;
//    list<Node*>::reverse_iterator iter = list1.rbegin();
//    while(iter!= list1.rend()){
//        Node* str = *iter;
//        cout<<" "<<str<<" <-";
//        iter++;
//    }
//    cout<<endl;
//    
//    cout<<"list 2"<<endl;
//    iter = list2.rbegin();
//    while(iter!= list2.rend()){
//        Node* str = *iter;
//        cout<<" "<<str<<" <-";
//        iter++;
//    }
//    cout<<endl;
//    
//}
//
//

//struct predicate
//{
//    predicate(Node* uCode ) : _node(uCode) {}
//
//    bool operator() ( Node* node )
//    {
//        return _node->_card == node->_card;
//    }
//private:
//    Node* _node;
//};


//void testset(){
//    MyNode* node1 = new MyNode("5S");
//    
//    MyNode* node2 = new MyNode("AH");
//    MyNode* node3 = new MyNode("AH");
//    std::cout<<"  "<<node2<<std::endl;
//    std::set<MyNode*, predicate>  sets;
//    sets.insert(node1);
//    sets.insert(node2);
//    
//    std::set<MyNode*, predicate>::iterator iter =sets.find(node3);
//    if(iter != sets.end()){
//        MyNode* no = *iter;
//        std::cout<<"find it "<<no<<std::endl;
//    }
//    
//
//}

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
        if(line.find("2 AS KH")!=-1){
            int j =0; 
            j++;
        }
        std::string::size_type prev_pos = 0, pos = 0;
        std::string* cards = NULL;
         while( (pos = line.find(' ', pos)) != std::string::npos ||  pos != -1 )
         {
                if(cardsNumber ==0 ){
                    cardsNumber = atoi(line.substr(prev_pos, pos-prev_pos).c_str());
                    cards = new std::string[cardsNumber+1];
                }else{
                    if( i>= cardsNumber ){
                        break;
                    }
                    std::string onecard = line.substr(prev_pos, pos-prev_pos);
                    cards[i++] = onecard;
                    //addNode(onecard);
                }
                
                prev_pos = ++pos;
         }
         if( i< cardsNumber ){
//             int range = pos-prev_pos;
//             if(line.find_last_of('\r') !=-1)  range--;   
             /* Hard code 2 len makes it is not scaleable*/
             std::string onecard =  line.substr(prev_pos, 2); 
             cards[i++] = onecard;
             //addNode(onecard);
         }

         addNode(cards, cardsNumber-1, _root);
    }
    
    
    
    void addNode(std::string* cards, int number, Node* root){
        if(number<0) return ;    //The current cards is sub tail string of previous one.
        std::string card = cards[number];
        Node *node =new Node(card);
        std::set<Node*, Node::comparator>::iterator iter = root->_children.find(node);
        if(root->_children.size() !=0 && iter!=root->_children.end() ){
            Node* oneNode = *iter;
            delete node;
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

/*
 * 
 */
int main(int argc, char** argv) {

   using namespace std;
   list<CardList*> handles; 
   
   CardTree* tree = new CardTree();
   int handlesCount = 0;
    while(true){
        string line;
        getline(cin, line);
        //line = trim(line," ");
        if(line == "0" || line == "" ){
            break;
        }else{
            if(index(line.c_str(), ' ') == NULL ){
                handlesCount = atoi(line.c_str());
                //printResult(&handles);
                //handles.clear();
                tree->print();
                delete tree;
                tree = new CardTree();
            }else{
                //CardList* cardList = new CardList(line, &handles);
                //handles.push_back(cardList);
                tree->addOneString(line);
            }
        }
            
    }
   //printResult(&handles);
   tree->print();
   return 0;
}

