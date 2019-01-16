#ifndef _author_h__
#define _author_h__

#include "book.hpp"
#include <cstring>

class AuthorComparator
{
  public:
    bool operator( ) (const Book::SecondaryKey & key1, 
                      const Book::SecondaryKey & key2) const
    {
      //if key1 is less than key2 wrt specifications
      //return true
      //otherwise
      //return false
      std::string author1 = key1.getAuthor();
      std::string author2 = key2.getAuthor();
      size_t i = 0,j = 0;
      while(author1[i])
      {
        if(author1[i] > 96)
          author1[i] -= 32;
        i++;
      }
      i = 0;
      while(author2[i])
      {
        if(author2[i] > 96)
          author2[i] -= 32;
        i++;
      }

      i = 0;
      while(author1[i] && author2[i])
      {
        if(author1[i] < author2[i])
          return true;
        else if(author1[i] > author2[i])
          return false;
        i++;
      }

    if(author1[i] && !author2[i])
        return false;
    if(!author1[i] && author2[i])
        return true;




      std::string title1 = key1.getTitle();
      std::string title2 = key2.getTitle();

      i = 0,j = 0;
      while(title1[i])
      {   
        if(title1[i] > 96)
          title1[i] -= 32;    
        i++;
      }
      while(title2[j])
      {
        if(title2[j] > 96)
          title2[j] -= 32;
        j++;
      }
      i = j = 0;

      for(title1[i],title2[j];title1[i],title2[j];i++,j++)
      {
        
        if(title1[i] < title2[j])
          return true;
        else if(title1[i] > title2[j])
          return false;
      }
        if(title1[i] && !title2[i])
        return false;
        if(!title1[i] && title2[i])
        return true;


      return false;
    }





};

#endif
