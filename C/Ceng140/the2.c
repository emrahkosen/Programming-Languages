#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "the2.h"


node *init(int branch)
{
  node *head = (struct node *)malloc(sizeof(struct node));
  node *zero = (struct node *)malloc(sizeof(struct node));
  head->key = branch*1000;
  head->next = NULL;
  head->down = zero;
  zero->key = 0;
  zero->next = NULL;
  zero->down = NULL;

  return head; 
}


int branch_factor(node *list)/**********/
{
    return list->key%1000;
}


int num_nodes(node *list)
{
  node *tmp;
  int i = 0;
  tmp = list->down;
  while(tmp->down)
  {
    tmp = tmp->down; 
  }

  tmp = tmp->next;
  while(tmp)
  {
    i++;
    tmp = tmp->next;
  }

  return i;



}








void dellevel(node *level)
{
  node *tmplevel;
  if(level == NULL)
    ;
  else
    {
      tmplevel = level->next;
      free(level);
      dellevel(tmplevel);
    }
}








void clear(node *list)

{
  node *level,*levelhead,*tmp;

  levelhead = list->down;
  
  while(levelhead != NULL)
  {
    level = levelhead->next;
    dellevel(level);
    tmp = levelhead;
    levelhead = levelhead->down;
    free(tmp);
  }
  free(list);


}






int is_empty(node *list)

{
  if(list->down->down == NULL && list->down->next == NULL)
    return 1;
  else 
    return 0;
}


int num_levels(node *list)
{
  int i=0;
  list = list->down;
  while(list)
  {
    i++;
    list = list->down;
  }
  return i;

}





node *createnode(int key, char *value)
{
  int i=0;
  node *nexLevelNode = (struct node *)malloc(sizeof(struct node));
  nexLevelNode->key = key;

  while(value[i])
        {
          nexLevelNode->value[i] = value[i];
          i++;
          nexLevelNode->value[i] = '\0';
        }
    nexLevelNode->next = NULL;
    nexLevelNode->down = NULL;    

    return nexLevelNode;    
} 



node *createlevel(int n)
  {
    node *nexlevel = (struct node *)malloc(sizeof(struct node));
    nexlevel->key = n;
    nexlevel->next = NULL;
    nexlevel->down = NULL;
    return nexlevel;
    
  }


  int keyvar(node *list,int key)
  {
    while(list->down)
    {
      list = list->down;
    }
    while(list)
    {
      if(list->key == key)
        return 1;
      list = list->next;
    }
    return 0;
  }



node *insert(node *list,int key,char *value)
{
  node *ret;
  if(keyvar(list,key))
  {
    node *levelhead,*level;
    levelhead = list->down;
    while(levelhead)
    {
      level = levelhead->next;
      while(level)
      {
        if(level->key == key)
        {
          int i=0;
          ret = level; /* */
          while(value[i])
          {
            level->value[i] = value[i];
            i++;
            level->value[i] = '\0';
          }   
        }
        level = level->next;
      }
      levelhead = levelhead->down;
    }

  }

  else
  {
    node *cur,*prev,*newnode;
    node *levelhead = list->down;
    node *lastlevel = NULL,*tmplist = list;
    
   
    int N = (list->key)%1000;
    int levelno = 0;



    list->key +=1;
    
    
    
    while(N%2 == 0)
      {
        levelno--;
        N /= 2;
      }

      
     
     if(levelhead->key > levelno)
     {
      while(levelhead->key > levelno)
      {
        node *newlevelhead = createlevel(levelno);
        newlevelhead->next = createnode(key,value);
        if(lastlevel != NULL)
        {
          lastlevel->down = newlevelhead->next;
        }

        lastlevel = newlevelhead->next;

        tmplist->down = newlevelhead;
        tmplist = tmplist->down;
        tmplist->down = levelhead;
        levelno++;
        

      }
     }

     while(levelno > levelhead->key)
     {
      levelhead = levelhead->down;
     }
      
      while(levelhead)
        {
          cur = levelhead->next;
          prev = levelhead;

          while(cur && cur->key < key )
          {
            cur = cur->next;
            prev = prev->next;
          }
          newnode = createnode(key,value);
          prev->next = newnode;
          newnode->next = cur;
          if(lastlevel != NULL)
          {
            lastlevel->down = newnode;
          }
          lastlevel = newnode;

          levelhead = levelhead->down;

        }

    ret = lastlevel;

  }
  return ret;
  
}















int delete(node *list,int key)
{
  node *levelhead = list->down;
  node *prelevelhead = list;
  if(!keyvar(list,key))
  {
    return 0;
  }


  else
  {
    node *cur,*prev;
    list->key -= 1;



    while(levelhead)
    {
      cur = levelhead->next;
      prev = levelhead;
      while(cur && cur->key != key)
      {
     
        cur = cur->next;
        prev = prev->next;
      }
      

      if(cur != NULL && cur->key == key )
      {
        prev->next = cur->next;
        free(cur); 
      }




      if(levelhead->next == NULL && levelhead->key != 0)
      {
        node *tmp = levelhead;
      
        levelhead = levelhead->down;
        prelevelhead->down = levelhead; /*bos olan level head i silerken bir üstteki level head ile birliştirdik*/
        free(tmp);
      }
      else
      {
      
        prelevelhead = prelevelhead->down;
        levelhead = levelhead->down;
      
      }




     
    }


    return 1;
  }

}
 











node *find(node *list, int key){
    return list;

}


void path(node *list, int key){
    
}











void printnode(int key,char *value,int levelno)
{
  int i=0;
  printf("%3d:",key );
  printf("%5s ",value );
  while(i < levelno)
  {
    printf("+ ");
    i++;
  }
  printf("+\n");
}



void print(node *list)
{
  int N = (list->key)%1000;
  int leveldebth = -1*(list->down->key) ;
  int i= 0,levelno = 0;
  node *levelhead = list;
  node *mynode,*levelnode;

  printf("%3d%7s",N," ");/******/




  while(i < leveldebth)
  {
    printf("%d ",i );
    i++;
  }
  
  printf("%d\n%10s",i," ");

  while(i >= 0)
  {
    printf("+ ");
    i--;
  }
  printf("-\n");


  while(levelhead->down != NULL)
  {
    levelhead = levelhead->down;
  }

  mynode = levelhead->next;

  while(mynode)
  {

    levelno =0;
    levelhead = list->down;





    while(levelhead)
    {
      
      levelnode = levelhead->next;
      while(levelnode)
      {
        
        if(levelnode->key == mynode->key)
        {
          levelno = -1*levelhead->key;
          break;
        }
           
          levelnode = levelnode->next;
      }
      if(levelno)
        break;

      levelhead = levelhead->down;

    }


    printnode(mynode->key,mynode->value,levelno);


    mynode = mynode->next;
  }



}






























void print_level(node *list, int level){

}
