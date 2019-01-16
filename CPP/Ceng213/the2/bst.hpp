#ifndef _BIN_SEARCH_TREE_H_
#define _BIN_SEARCH_TREE_H_

#include <functional>
#include <cstddef>
#include <stack>
#include <list>
#include <ostream>




//do not add any other library
//modify parts as directed by assignment text & comments here

template <typename Key, typename Object,
          typename Comparator=std::less<Key> >
class BinarySearchTree
{
  private: //do not change
    struct BinaryNode //node definition: a dependent type
    {
      Key key; //keys will be kept constant
      Object data; //objects that are referred to by keys may change
      BinaryNode * left;
      BinaryNode * right;
      size_t height; //height info should be updated per insert & delete

      BinaryNode(const Key &, const Object &,
                 BinaryNode *, BinaryNode *, size_t =0);
    };

  public: //do not change except for your own private utility functions







    class Iterator //iterator class will encapsulate the location within the BST
    {
      public:
        Iterator( ); //dummy constructor for type declaration purposes
        Iterator & operator++( ); //inorder increment

        Object & operator*( );  //update data
        const Object & operator*( ) const; //view data

        bool operator==(const Iterator & rhs) const; //compare iterators
        bool operator!=(const Iterator & rhs) const; //compare iterators

      private:
        BinaryNode * current; //position
        const BinaryNode * root; //for error check not implemented
        std::stack<BinaryNode *> s; //will be used to conduct in order traversal if
        bool useStack; //this variable is set to true, ignored in == and !=

      private:
        Iterator(BinaryNode *, const BinarySearchTree &, bool =true);
        //other private utility functions can be declared by you

      friend class BinarySearchTree<Key, Object, Comparator>;
    };













  public: //do not change
    BinarySearchTree( ); //empty tree
    ~BinarySearchTree( ); //reclaim all dyn allocated mem

    void insert(const Key &, const Object &); //to insert new key,item
    void remove(const Key &); //remove the node with the key value (and also data)

  public: //do not change
    Iterator find(const Key &) const; //single item
    std::list<Iterator> find(const Key &, const Key &) const;//range queries

    Iterator begin( ) const; //inorder begin
    Iterator end( ) const; //dummy NULL iterator

  public: //do not change
    int height( ) const; //return height of the tree
    size_t size( ) const; //return the number of items in the tree
    bool empty( ) const; //return whether the tree is empty or not
    void print(std::ostream &) const;

  private: //do not change
    BinaryNode * root; //designated root
    size_t nodes; //number of nodes
    Comparator isLessThan; //function object to compare keys

  private:
    /* private utility functions that are implemented */
    void makeEmpty(BinaryNode * &);

    BinaryNode * find(const Key &, BinaryNode *) const;
    int height(BinaryNode *) const;
    void print(BinaryNode *, std::ostream &) const;

    template <typename T> //static utility function
    static const T & max(const T &, const T &);

    //balancing functions
    void rotateWithLeftChild(BinaryNode * &);
    void rotateWithRightChild(BinaryNode * &);
    void doubleWithLeftChild(BinaryNode * &);
    void doubleWithRightChild(BinaryNode * &);

    //you may add your own private utility functions down here

    void myinsert(const Key & k, const Object & x,BinaryNode *&curroot);
    void myremove(const Key & k,BinaryNode *&curroot);
    void makeAvl(BinaryNode *&curroot);
    BinaryNode *findRsmall(BinaryNode * curroot);
    BinaryNode *findpreRsmall(BinaryNode * curroot);
    size_t correctheight(BinaryNode *rt);


  private: //not copiable, DO NOT IMPLEMENT or change
    BinarySearchTree(const BinarySearchTree &);
    const BinarySearchTree & operator=(const BinarySearchTree &);

};







/*-------------------------------------------------------------------------------------*/


//node constructor, implemented do not change
template <typename K, typename O, typename C>
BinarySearchTree<K,O,C>::BinaryNode::
BinaryNode(const K & _k, const O & _d,
           BinaryNode * _l, BinaryNode * _r, size_t _h)
  : key(_k), data(_d), left(_l), right(_r), height(_h)
{
}

//default constructor, implemented do not change
template <typename K, typename O, typename C>
BinarySearchTree<K,O,C>::BinarySearchTree( )
  : root(NULL), nodes(0)
{
}

//destructor, implemented do not change
template <typename K, typename O, typename C>
BinarySearchTree<K,O,C>::~BinarySearchTree( )
{
  makeEmpty(root);
}

//private utility function for destructor, do not change
template <typename K, typename O, typename C>
void
BinarySearchTree<K,O,C>::makeEmpty(BinaryNode * & t)
{
  if (t != NULL)
  {
    makeEmpty(t->left);
    makeEmpty(t->right);
    delete t;
    --nodes;
  }

  t = NULL;
}













/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

template <typename K, typename O, typename C>
void BinarySearchTree<K,O,C>::myinsert(const K & k, const O & x,BinaryNode *&curroot)
{
  if(isLessThan(k,curroot->key) && curroot->left == NULL)
  {

    curroot->left = new BinaryNode(k,x,NULL,NULL);
    curroot->left->height = 0;
    nodes +=1;
  }
  else if(isLessThan(curroot->key,k) && curroot->right == NULL)
  {

    curroot->right = new BinaryNode(k,x,NULL,NULL);
    curroot->right->height =0;
    nodes +=1;
  }
  else if(!isLessThan(k,curroot->key) && !isLessThan(curroot->key,k)) //(curroot->key == k)
  {
    curroot->data = x;
  }
  else
  {
    if(isLessThan(k,curroot->key) )
    {

      myinsert(k,x,curroot->left);

      if((curroot->right == NULL && curroot->left->height == 1) )
      {
        if(isLessThan(k,curroot->left->key))  
          rotateWithLeftChild(curroot);
        else
          doubleWithLeftChild(curroot);
      }
      else if( (curroot->left->height -curroot->right->height) == 2)
      {
        if(isLessThan(k,curroot->left->key))
          rotateWithLeftChild(curroot);
        else
          doubleWithLeftChild(curroot);

      }
    }
    else if(isLessThan(curroot->key,k))
    {

            myinsert(k,x,curroot->right);

            if((curroot->left == NULL && curroot->right->height == 1) )
            {

              if(isLessThan(curroot->right->key,k)) 
                rotateWithRightChild(curroot);
              else
                doubleWithRightChild(curroot);

            }
            else if( (curroot->right->height - curroot->left->height) == 2)
            {
              if(isLessThan(curroot->right->key,k))
                rotateWithRightChild(curroot);
              else
                doubleWithRightChild(curroot);

            }


    }
    else return;
  }


  if(curroot->left ==  NULL && curroot->right == NULL)
    return;
  else if(curroot->left && curroot->right == NULL)
    curroot->height = curroot->left->height + 1;
  else if(curroot->left == NULL && curroot->right)
    curroot->height = curroot->right->height+1;
  else
  {
    curroot->height = BinarySearchTree<K,O,C>::max(height(curroot->left),
                                            height(curroot->right)) + 1;
  }



}





























//public function to insert into BST, IMPLEMENT
template <typename K, typename O, typename C>
void BinarySearchTree<K,O,C>::insert(const K & k, const O & x)
{
  if(root == NULL)
  {
    root = new BinaryNode(k,x,NULL,NULL);
    root->height = 0;
    nodes = 1;
  }
  else
    myinsert(k,x,root);


}








template <typename K, typename O, typename C>
size_t BinarySearchTree<K,O,C>::correctheight(BinaryNode *rt)
{
  if(rt)
  {
      if(rt->left == NULL && rt->right == NULL)
    {
      rt->height = 0;
      return 0;

    }
  else
  {
    if(rt->left == NULL)
    {
      rt->height = 1 + correctheight(rt->right);
      return rt->height;
    }
    else if(rt->right == NULL)
    {
      rt->height = 1+ correctheight(rt->left);
      return rt->height;
    }
    else
    {
      size_t a = correctheight(rt->left);
      size_t b = correctheight(rt->right);
      if(a < b)
        rt->height = b+1;
      else
        rt->height = a+1;
      return rt->height;

    }
  }
  }
}




template <typename K, typename O, typename C>
typename BinarySearchTree<K,O,C>::BinaryNode * BinarySearchTree<K,O,C>::findRsmall(BinaryNode *curroot)
{
  while(curroot && curroot->left)
    curroot = curroot->left;
  return curroot;
}


template <typename K, typename O, typename C>
typename BinarySearchTree<K,O,C>::BinaryNode * BinarySearchTree<K,O,C>::findpreRsmall(BinaryNode *curroot)
{
  if(!curroot || !curroot->left)
    return NULL;

  while(curroot && curroot->left && curroot->left->left)
    curroot = curroot->left;
  return curroot;
}



template <typename K, typename O, typename C>
void BinarySearchTree<K,O,C>::makeAvl(BinaryNode *&curroot)
{
  
    if(!curroot)
      {

      }
    else if(curroot->left == NULL && curroot->right == NULL)
    {
       
      curroot->height = 0;     
    }   

      else if((curroot->left == NULL && curroot->right) )
      {

        if(curroot->right->height > 0)       
         {
          if(curroot->right->left == NULL ||(curroot->right->right && curroot->right->right->height >= curroot->right->left->height))
            rotateWithRightChild(curroot);
          else
           doubleWithRightChild(curroot);
         }

      }
      else if((curroot->right == NULL && curroot->left) )
      {

        if(curroot->left->height > 0)        
        {
          if(curroot->left->right == NULL ||(curroot->left->left && curroot->left->left->height >= curroot->left->right->height))
            rotateWithLeftChild(curroot);
          else
            doubleWithLeftChild(curroot);
        }
      }


      else if( (curroot->right->height - curroot->left->height) == 2)
      {
        
          if(curroot->right->left == NULL ||(curroot->right->right && curroot->right->right->height > curroot->right->left->height))
            rotateWithRightChild(curroot);
          else
            doubleWithRightChild(curroot);

      }  


      else if( (curroot->left->height -curroot->right->height) == 2)
      {
       
          if(curroot->left->right == NULL ||(curroot->left->left && curroot->left->left->height > curroot->left->right->height))
            rotateWithLeftChild(curroot);
          else
            doubleWithLeftChild(curroot);

      }


}









template <typename K, typename O, typename C>
void
BinarySearchTree<K,O,C>::myremove(const K & k,BinaryNode *&curroot )
{

  if(!curroot)
    return;
  else if(!isLessThan(curroot->key,k) && !isLessThan(k,curroot->key)) //(curroot->key == k) 
  {      
    BinaryNode *tmp = curroot;
    BinaryNode *tmpRL = findRsmall(curroot->right); 
    BinaryNode *tmpRLpre = findpreRsmall(curroot->right);// burda small in pre sını bulmamız gerek
    if(!tmpRL)
    {
      curroot = curroot->left;    
      correctheight(root);
      makeAvl(curroot);

    nodes--;
    tmp->right = NULL;
    tmp->left = NULL;
    delete tmp;

      
    }
    else if(!tmpRLpre)
    {
     
      curroot = tmpRL;
      curroot->left = tmp->left;
     
//std::cout << "508  else if::" << std::endl;        
/*
      myremove(k,curroot->right);
  */ 
      correctheight(root);
      makeAvl(curroot);
    
    nodes--;
    tmp->right = NULL;
    tmp->left = NULL;
    delete tmp;

    }
    else
    {
      BinaryNode *tmpRR = tmpRL->right;
     
      curroot = tmpRL;
      curroot->left = tmp->left;
      curroot->right = tmp->right;
      tmpRLpre->left = tmp;
      tmp->right = tmpRR;
      tmp->left = NULL;
      myremove(k,curroot->right);
   
      correctheight(root);

      makeAvl(curroot);

    }





  }

  else
  {
     

    if(isLessThan(k,curroot->key))  //(curroot->key > k) ()
    {
      if(!curroot->left)
        return;
      myremove(k,curroot->left);
      correctheight(root);
      makeAvl(curroot);
    }
    else if(isLessThan(curroot->key,k)) //(curroot->key < k)
    {

      if(!curroot->right)
        return;     
      myremove(k,curroot->right);
      correctheight(root);
      makeAvl(curroot);
    }
    else
      return;
  }

}

//public function to remove key, IMPLEMENT
template <typename K, typename O, typename C>
void
BinarySearchTree<K,O,C>::remove(const K & k)
{

  if(root)
    myremove(k,root);


}










/*---------------------------------------------------------------------------------------------------*/


//public function to search elements, do not change
template <typename K, typename O, typename C>
typename BinarySearchTree<K,O,C>::Iterator
BinarySearchTree<K,O,C>::find(const K & key) const
{
  BinaryNode * node = find(key, root);

  if (node == NULL)
  {
    return end();
  }
  else
  {  

               //not inorder iterator
    return Iterator(node, *this, false);
  }
}


/*
 * private utility function to search elements
 * do not change
 */
template <typename K, typename O, typename C>
typename BinarySearchTree<K,O,C>::BinaryNode *
BinarySearchTree<K,O,C>::find(const K & key, BinaryNode * t) const
{

  if (t == NULL)
  {
    return NULL;
  }
  else if (isLessThan(key, t->key))
  {
    return find(key, t->left);
  }
  else if (isLessThan(t->key, key))
  {  

    return find(key, t->right);
  }
  else //found
  {
 

    return t;
  }
}
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/



//range queries those within range are inserted to the list
//IMPLEMENT
template <typename K, typename O, typename C>
std::list<typename BinarySearchTree<K,O,C>::Iterator>
BinarySearchTree<K,O,C>::find(const K & lower, const K & upper) const
{
  
  std::stack<BinaryNode *> s;
  BinaryNode *tmp = root;
  std::list<Iterator> inorder;
  while(true)
  {
    while(tmp)
    {
      s.push(tmp);
      tmp = tmp->left;
    }
    if(s.empty())
      break;
    else
    {
      tmp = s.top();
      s.pop();
      Iterator it = find(tmp->key);
      inorder.push_back(it);
      tmp = tmp->right;
    }
  }
  std::list<Iterator> inorderreturn;

  typename // :( use typedefs
  std::list<typename BinarySearchTree<K,O,C>::Iterator>::const_iterator i;

  for (i = inorder.begin(); i != inorder.end(); ++i)
  {

    if(isLessThan(lower,i->current->key) && isLessThan(i->current->key,upper))
    {
      
      Iterator newit = find(i->current->key);
      inorderreturn.push_back(newit);

    }
    else if((!isLessThan(lower,i->current->key) && !isLessThan(i->current->key,lower)))
      {
      Iterator newit = find(i->current->key);
      inorderreturn.push_back(newit);        
      }
    else if((!isLessThan(upper,i->current->key) && !isLessThan(i->current->key,upper)))
      {
      Iterator newit = find(i->current->key);
      inorderreturn.push_back(newit);        
      }
    else
      ;
  }



  return inorderreturn;


}












/*------------------------------------------------------------------------------------------------------*/



//INORDER iterator begins at ++root, do not change
template <typename K, typename O, typename C>
typename BinarySearchTree<K,O,C>::Iterator
BinarySearchTree<K,O,C>::begin() const
{
  return Iterator(root, *this);
}

//no more increment after end() also
//returned in case of unsuccessful search
//or when no more applicance of ++ is possible
//do not change
template <typename K, typename O, typename C>
typename BinarySearchTree<K,O,C>::Iterator
BinarySearchTree<K,O,C>::end() const
{
  return Iterator(NULL, *this);
}

//public function to return height, do not change
template <typename K, typename O, typename C>
int
BinarySearchTree<K,O,C>::height( ) const
{
  return height(root);
}

/* private utility function for computing height */
//do not change
template <typename K, typename O, typename C>
int
BinarySearchTree<K,O,C>::height(BinaryNode * t) const
{
  return (t == NULL) ? -1 : t->height;
}

//public function to return number of nodes in the tree
//do not change
template <typename K, typename O, typename C>
size_t
BinarySearchTree<K,O,C>::size( ) const
{
  return nodes;
}

//public true if empty false o.w.
//do not change
template <typename K, typename O, typename C>
bool
BinarySearchTree<K,O,C>::empty( ) const
{
  return nodes == 0;
}

//public function to print keys inorder to some ostream
//do not change
template <typename K, typename O, typename C>
void
BinarySearchTree<K,O,C>::print(std::ostream & out) const
{
  print(root, out);
  out << '\n';
}

/* private utility function to print, do not change */
template <typename K, typename O, typename C>
void
BinarySearchTree<K,O,C>::print(BinaryNode * t, std::ostream & out) const
{
  if (t != NULL && t->left != NULL)
  {
    out << '[';
    print( t->left, out );
  }
  else if (t != NULL && t->left == NULL && t->right != NULL)
  {
    out << "[";
  }

  if (t != NULL)
  {
    if (t->left == NULL && t->right == NULL)
    {
      out << '(' << (t->key) << ')';
    }
    else if (t->left != NULL || t->right != NULL)
    {
      out << '{' << (t->key) << ",H" << t->height << '}';
    }
  }

  if (t != NULL && t->right != NULL)
  {
    print( t->right, out );
    out << ']';
  }
  else if (t != NULL && t->left != NULL && t->right == NULL)
  {
    out << "]";
  }
}

/* static function to compute maximum of two elements */
//do not change
template <typename K, typename O, typename C>
template <typename T>
const T &
BinarySearchTree<K,O,C>::max(const T & el1, const T & el2)
{
  return el1 > el2 ? el1 : el2;
}

/* ROTATIONS, do not change */
template <typename K, typename O, typename C>
void
BinarySearchTree<K,O,C>::rotateWithLeftChild(BinaryNode * & k2)
{
  BinaryNode *k1 = k2->left;
  k2->left = k1->right;
  k1->right = k2;
  k2->height = BinarySearchTree<K,O,C>::max(height(k2->left),
                                            height(k2->right)) + 1;
  k1->height = BinarySearchTree<K,O,C>::max(height(k1->left),
                                            height(k2)) + 1;
  k2 = k1;
}


template <typename K, typename O, typename C>
void
BinarySearchTree<K,O,C>::rotateWithRightChild(BinaryNode * & k1)
{
  BinaryNode *k2 = k1->right;
  k1->right = k2->left;
  k2->left = k1;
  k1->height = BinarySearchTree<K,O,C>::max(height(k1->left),
                                            height(k1->right)) + 1;
  k2->height = BinarySearchTree<K,O,C>::max(height(k2->right),
                                            height(k1)) + 1;
  k1 = k2;
}

template <typename K, typename O, typename C>
void
BinarySearchTree<K,O,C>::doubleWithLeftChild(BinaryNode * & k3)
{
  rotateWithRightChild(k3->left);
  rotateWithLeftChild(k3);
}

template <typename K, typename O, typename C>
void
BinarySearchTree<K,O,C>::doubleWithRightChild(BinaryNode * & k1)
{
  rotateWithLeftChild(k1->right);
  rotateWithRightChild(k1);
}

/* ITERATOR functions */

// dummy constructor, do not change
template <typename K, typename O, typename C>
BinarySearchTree<K,O,C>::Iterator::Iterator( )
  : current(NULL), root(NULL), useStack(false)
{
}



/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/



// dereferencing operator non-const version, IMPLEMENT
template <typename K, typename O, typename C>
O &
BinarySearchTree<K,O,C>::Iterator::operator*( )
{
  if(current)
    return current->data;

}

// dereferencing operator const version, IMPLEMENT
template <typename K, typename O, typename C>
const O &
BinarySearchTree<K,O,C>::Iterator::operator*( ) const
{
  if(current)
    return current->data;

}



/*-----------------------------------------------------------------------------------*/


// compare Iterators ignoring useStack var, do not change
template <typename K, typename O, typename C>
bool
BinarySearchTree<K,O,C>::Iterator::
operator==(const Iterator & rhs) const
{
  return current == rhs.current &&
         root == rhs.root;
}

// compare Iterators ignoring useStack var, do not change
template <typename K, typename O, typename C>
bool
BinarySearchTree<K,O,C>::Iterator::
operator!=(const Iterator & rhs) const
{
  return !(*this == rhs);
}




/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/



// increment Iterator to point to the inorder next
// node of then-current node, in case that no further
// advances are possible return an Iterator that is
// equal to end( ) , IMPLEMENT
template <typename K, typename O, typename C>
typename BinarySearchTree<K,O,C>::Iterator &
BinarySearchTree<K,O,C>::Iterator::operator++( )
{
 // cout<<"\n\n\n\n";

 if(!useStack)
    {


       current = NULL;
    }

  else
  {
//cout<<"in else\n";

    if(current)
    {
//cout<<"in else-if\n";
    
   
      if(current->right)
      {
//      cout<<"right\n";


        current= current->right;

        while(current->left)
        {
          s.push(current);
          current = current->left;
        }
      }
      else
        {
   //  cout<<"no right\n";
         if(s.empty())
          current = NULL;
          else
          { 
              
              if(current == NULL)
                {}
              else
              {
                current = s.top();   
                s.pop();
              }
          }  
        }

   //  cout<<"\n\n\n\n";
       

    }

    return *this;
  }

  



   

}

/* real Iterator constructor will be invoked by
 * BST member function only. if no inorder iterator
 * is required by the computation designer should
 * explicitly set useStack variable to false, o.w.
 * it will be assumed to be true. IMPLEMENT
 */
template <typename K, typename O, typename C>
BinarySearchTree<K,O,C>::Iterator::
Iterator(BinaryNode * p, const BinarySearchTree & rhs, bool stk)
{

  current = p;
  useStack = stk;
  root = rhs.root;
  if(!stk)
    ;

    
  else
  {

    while(current && current->left)
    {
     

      s.push(current);
      

      current = current->left;
    }
  }

  
}


#endif

