/*
glen Wiltshire



Namespace ordered doubaly linked list



*/

#include <iostream>
#ifndef _MYLIB_H
#define _MYLIB_H

namespace MYLIB {
    template <class T>
    class ListNode{ // a single "Node"
    private:
        ListNode* next;
        ListNode* previous;
        T data;

    public:
        ListNode(){next=NULL;previous=NULL;}
        ListNode(T var){data=var;}
        void setNull(T);
        ListNode<T>* Next();
        ListNode<T>* Previous();
        T getData();
        void setNext(ListNode<T>*);
        void setPrevious(ListNode<T>*);
    };

    template <class T>
    void ListNode<T>::setNull(T var){
        next = NULL;
        previous = NULL;
        data = var;
    }
    template <class T>
    ListNode<T>* ListNode<T>::Next(){
        return next;
    }
    template <class T>
    ListNode<T>* ListNode<T>::Previous(){
        return previous;
    }
    template <class T>
    T ListNode<T>::getData(){
        return data;
    }

    template <class T>
    void ListNode<T>::setNext(ListNode<T>* toSet){
        next = toSet;
    }
    template <class T>
    void ListNode<T>::setPrevious(ListNode<T>* toSet){
        previous = toSet;
    }   


    //ordered list stuff below

    template <class T>
    class OrderedList{ //the list that connects the "Nodes"
    private:
        MYLIB::ListNode<T>* head;
        MYLIB::ListNode<T>* tail; 
        
    public:
        ~OrderedList();
        OrderedList(){head=NULL;tail=NULL;}
        void insert(T);
        class iterator{ //nested class iterator
            private:
                MYLIB::ListNode<T>* current;

            public:
                iterator(){current=NULL;}
                void set(ListNode<T>* temp){current = temp;}
                ListNode<T>& operator++();
                bool operator!=(iterator b){
                    if(b.current->Next() == NULL){
                        if(current == NULL){
                            return false;
                        }
                        else if(b.current->Previous()==NULL && current->Next() == NULL){
                            return true; //last element in list
                        }
                    }
                    else{
                        if(current->Next() == b.current->Next()){
                            return false;
                        }        
                    }
                    return true;
                    ;}
                typename OrderedList<T>::iterator  operator++ (int);
                T operator*();
        };
        iterator begin();
        iterator end();
    };

    //iterator stuff
    template <class T>
    typename OrderedList<T>::iterator OrderedList<T>::begin(){
        iterator temp;
        temp.set(head);
        return temp;
    }
    template <class T>
    typename OrderedList<T>::iterator OrderedList<T>::end(){
        iterator temp;
        temp.set(tail);
        return temp;
    }
    template <class T>
    ListNode<T>& OrderedList<T>::iterator::operator++(){
        if(current->Next() == NULL){
            current = NULL;
                                         //this way if it's the last node there's a way
            return *current;            //to check without having to set some sort of global flag
        }                      
            current = current->Next();
    return *current;
    }

    template <class T>
    typename OrderedList<T>::iterator OrderedList<T>::iterator::operator++(int){
      typename OrderedList<T>::iterator tmp = *this;
      ++(*this);
      return tmp;
    }

    template <class T>
    T OrderedList<T>::iterator::operator*(){
      return current->getData();
    }

    //end iterator stuff

    //insert (build the linked list)
    template <class T>
    void OrderedList<T>::insert(T var){
        MYLIB::ListNode<T>* node = new MYLIB::ListNode<T>;
        node->setNull(var);

        if(head == NULL){ //no list, create one
            head=node;
            tail=node;
        }
        else{
            MYLIB::ListNode<T>* curr;
            curr = head;
            while(curr->getData() < var && curr->Next() != tail->Next()){//find the node AFTER the one you want to insert into
                curr = curr->Next(); //continue through list
            }
            if(curr == head){ //single element in list, add the current one
                if(curr != tail || var < head->getData()){  //either add it to the start
                node->setNext(head);
                node->setPrevious(NULL);
                head->setPrevious(node);
                head = node;
                }
                else{
                    node->setPrevious(curr); //or just add it to the end
                    node->setNext(head->Next());
                    head->setNext(node);
                    if(tail == curr){ //check if we need to re-point the tail
                      tail=node;
                    }
                }
            }
            else{
                if(curr == tail && curr->getData() < var){ //is a list, element needs to be at the end
                    tail->setNext(node);
                    node->setPrevious(tail); 
                    node->setNext(NULL);
                    tail = node;
                }
                else{
                    node->setNext(curr); //is a list, element needs to go somewhere in the list
                    (curr->Previous())->setNext(node);
                    node->setPrevious(curr->Previous());
                    curr->setPrevious(node);
                }
            }
        }

    }//close insert

    //delete linked list
    template <class T>
    OrderedList<T>::~OrderedList(){
        MYLIB::ListNode<T>* curr;
        for (curr = head; curr != NULL;curr=curr->Next()) {
            delete curr->Previous();
            if(curr->Next() == NULL)
                delete curr;
        }
    }

} //cloase namespace 


#endif