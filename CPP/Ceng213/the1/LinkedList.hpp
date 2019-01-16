#ifndef _LINKEDLIST_H_
#define _LINKEDLIST_H_

#include <iostream>
#include "Node.hpp"

using namespace std;

/*....DO NOT EDIT BELOW....*/
template <class T>
class LinkedList {
    private:
        Node<T>* head;
        Node<T>* tail;
          size_t  size;
    public:

        LinkedList();
        LinkedList(const LinkedList<T>& ll);
        LinkedList<T>& operator=(const LinkedList<T>& ll);
        ~LinkedList();

        /* Return head of the linked-list*/
        Node<T>* getHead() const;
        /* Set head of the linked-list*/
        Node<T>* setHead(Node<T>* n);
        /* Return tail of the linked-list*/
        Node<T>* getTail() const;
        /* Set tail of the linked-list*/
        Node<T>* setTail(Node<T>* n);
        /* Get the previous node of the node that contains the data item.
         * If the head node contains the data item, this method returns NULL.*/
        Node<T>* findPrev(const T& data) const;
        /* Get the node that stores the data item.
         * If data is not found in the list, this function returns NULL.*/
        Node<T>* findNode(const T& data) const;
        /* Insert a new node to store the data item.
         * The new node should be placed after the “prev” node.
         * If prev is NULL then insert new node to the head.*/
        void insertNode(Node<T>* prev, const T& data);
        /* This method is used to delete the node that is next to “prevNode”.
         * PS:prevNode is not the node to be deleted. */
        void deleteNode(Node<T>* prevNode);
        /* This method is used to clear the contents of the list.*/
        void clear();
        /* This method returns true if the list empty, otherwise returns false.*/
        bool isEmpty() const;
        /* This method returns the current size of the list. */
        size_t getSize() const;
        /*Prints the list. This method was already implemented. Do not modify.*/
        void print() const;
};

template <class T>
void LinkedList<T>::print() const{
    const Node<T>* node = head;
    while (node) {
        std::cout << node->getData();
        node = node->getNext();
    }
    cout<<std::endl;
}

/*....DO NOT EDIT ABOVE....*/

/* TO-DO: method implementations below */


template <class T>
LinkedList<T>::LinkedList()
{
  head = NULL;
  tail = NULL;
  size = 0;
}




template <class T>
LinkedList<T>::LinkedList(const LinkedList<T>& ll)
{
    Node<T> *lltmp = ll.getHead();
    Node<T> *tmp = new Node<T>(lltmp->getData());
    head = tmp;
    size = 1;
    lltmp = lltmp->getNext();





    while(lltmp)
    {
        Node<T> *nextn =new  Node<T>(lltmp->getData());
        tmp->setNext(nextn);
        lltmp = lltmp->getNext();
        tmp = tmp->getNext();
        tail = tmp;
        size++;

    }

}







template <class T>
LinkedList<T>::~LinkedList()
{

    


    if(head != NULL)
    {
    this->clear();
    }



}













template <class T>
LinkedList<T> &LinkedList<T>::operator=(const LinkedList<T>& ll)
{

    
    




     
        if(ll.isEmpty())
        {
           this->clear();
           head = NULL;
        }

       
        else
        {

           
            this->clear();

            Node<T> *tmp = ll.getHead();
            head = new Node<T>(tmp->getData());





            Node<T> *q = tmp->getNext();
            Node<T> *p = head;
            while(q)
            {
                Node<T> *n = new Node<T>(q->getData());
                p->setNext(n);

                q = q->getNext();
                p = p->getNext(); 


            } 

        }





  return *this;

}

























template <class T>
Node<T> *LinkedList<T>::getHead() const
{
    return head;
}
template <class T>

Node<T> *LinkedList<T>::setHead(Node<T>* n)
{
    Node<T> *p = head;
    head = n;
    head->setNext(p);
    this->deleteNode(head);
    size = 1;
    tail = head;


    while(tail->getNext())
    {

        tail = tail->getNext();
        size++;
    }
    return head;
}






template <class T>

Node<T> *LinkedList<T>::getTail() const
{
    return tail;
}









template <class T>
Node<T> *LinkedList<T>::setTail(Node<T>* n)
{
    Node<T> *p = this->getHead();
    if(p == tail)
    {
        this->setHead(n);
    }

    else
    {


        while(p->getNext() != tail)
        {
           
            p = p->getNext();
        }
        this->deleteNode(p);
        this->insertNode(p,n->getData());









        /*



            Node<T> *tmp = this->getHead();
            size = 0;
            while(tmp)
            {
                tmp = tmp->getNext();
                size++;
            }



        tail->setNext(n);
        tail = tail->getNext();
        size++;

        */


         Node<T> *tmp = this->getHead();
            size = 0;
            while(tmp)
            {
                tmp = tmp->getNext();
                size++;
            }




        return tail;
    }    

}











template <class T>
Node<T> *LinkedList<T>::findPrev(const T& data) const
{
    Node<T> *tmp = head;
    Node<T> *tmp2;
    if(data == tmp->getData())
        return NULL;
    else
    {

        while(tmp)
        {
            tmp2 = tmp->getNext();
            if(data == tmp2->getData())
                return tmp;
            tmp = tmp->getNext();
        }
        return NULL;
    }
}









template <class T>
Node<T> *LinkedList<T>::findNode(const T& data) const
{
    Node<T> *tmp = head;
    while(tmp)
    {
        if(data == tmp->getData())
            return tmp;
        tmp = tmp->getNext();
    }
    return NULL;
}








template <class T>
void  LinkedList<T>::insertNode(Node<T>* prev, const T& data)
{
    Node<T> *newnode = new Node<T>(data);
    if(prev == NULL)
    {
        Node<T> *ph = head;
        head = newnode;
        head->setNext(ph);

    /*
        setHead(newnode);
    */
        
    }
    /*
    else if(prev == tail)
        this->setTail(newnode);
    */
    else
    {
       newnode->setNext(prev->getNext());
       prev->setNext(newnode);
    }
    tail= head;
    size = 1;
    while(tail->getNext())
    {
        size++;
        tail = tail->getNext();

    }
    
    
}




template <class T>
void LinkedList<T>::deleteNode(Node<T>* prevNode)
{
    if(prevNode)
    {
        Node<T> *tmp = prevNode->getNext();
    
        if(tmp->getNext() == NULL)
        {   
            prevNode->setNext(NULL);
            tail = prevNode;


        }


        else
            prevNode->setNext(tmp->getNext());
        delete tmp;
        --size;
    }

}




template <class T>
void LinkedList<T>::clear()
{

    
    if(head)
    {
 

      





        while(head->getNext() != NULL)
        {

 

            
            deleteNode(head);
            size--;





               Node<T> *tmp2 = head;


            
        }






        
        Node<T> *tmp = head;
        head = NULL;
        size = 0;
        
        delete tmp;

   
    }    
}





template <class T>
bool LinkedList<T>::isEmpty() const
{

    return head == NULL;
}



template <class T>
size_t LinkedList<T>::getSize() const
{

    return size;
}




/* end of your implementations*/

#endif
