#ifndef MYSTACK_HPP
#define MYSTACK_HPP
#include "Node.hpp"

/*You are free to add private/public members inside this template..*/
template <class T>
class MyStack{
    private:
    Node<T> *top;
    public:
    /*Default constructor*/
    MyStack();
    /*copy constructor*/
    MyStack(const MyStack<T>& rhs);
    /*destructor*/
    ~MyStack();
    /*overloaded = operator*/
    MyStack<T>& operator=(const MyStack<T>& rhs);
    /*returns true if stack is empty*/
    bool isEmpty() const;
    /*push newItem to stack*/
    void push(const T& newItem);
    /*pop item from stack*/
    void pop();

    /*return top item of the stack*/
    Node<T>* Top() const;
	/*Prints the stack entries. This method was already implemented. Do not modify.*/
    void print() const;

};

template <class T>
void MyStack<T>::print() const{
  
    const Node<T>* node = top;
    while (node) {
        std::cout << node->getData();
        node = node->getNext();
    }
    cout<<std::endl;

  
    
}


/* TO-DO: method implementations below */
template <class T>
MyStack<T>::MyStack()
{
  top = NULL;
}







template <class T>
MyStack<T>::MyStack(const MyStack<T>& rhs)
{



  Node<T> *tmprhs = rhs.Top();
  Node<T> *tmp = new Node<T>(tmprhs->getData());
  top = tmp;

  tmprhs = tmprhs->getNext();


  while(tmprhs)
  {
    

    Node<T> *nextt = new Node<T>(tmprhs->getData());
    tmp->setNext(nextt);
    tmprhs = tmprhs->getNext();
    tmp = tmp->getNext();




  }





  




}





template <class T>
MyStack<T>::~MyStack()
{
  
    while(top)
    {
        this->pop();
    }
    
}















template <class T>
MyStack<T> &MyStack<T>::operator=(const MyStack<T>& rhs)
{
  if(this != &rhs)
  {
    if(!rhs.Top())
      {

        
        while(top)
        {
          pop();
        }
        top = NULL;
      }
    else
    {
      Node<T> *tmp = rhs.Top();
      top = new Node<T>(tmp->getData());
      Node<T> *q = rhs.Top();
      q = q->getNext();
      Node<T> *p = this->top;
      
      while(q)
      {
        Node<T> *n = new Node<T>(q->getData()); 
        p->setNext(n);

        q = q->getNext();
        p = p->getNext();
      }

    }
  }
  return *this;
}



















template <class T>
bool MyStack<T>::isEmpty() const
{
  
    return top == NULL;
}


template <class T>
void MyStack<T>::push(const T& newItem)
{

    Node<T> *tmp = new Node<T>(newItem);
    tmp->setNext(top);
    top = tmp;
    
}



template <class T>
void MyStack<T>::pop()
{

  if(top)
    {
        Node<T> *tmp = top;
    
        top = tmp->getNext();
     
        delete tmp;


    }
   
}




template <class T>
Node<T>*MyStack<T>::Top() const
{
 
    return top;
}










#endif /* MYSTACK_HPP */
