#include "bookstore.hpp"

BookStore::BookStore( ) //implemented, do not change
{
}

void
BookStore::insert(const Book & book)//  1
{

  primaryIndex.insert(book.getISBN( ),book);
  

  typename BinarySearchTree<std::string, Book>::Iterator it;
  for (it = primaryIndex.begin(); it != primaryIndex.end(); ++it)
  {
    Book *mybook = &(*it);
    if(book.getISBN() == mybook->getISBN())
    {
      
      Book *mybook = &(*it);
      secondaryIndex.insert(Book::SecondaryKey(book),mybook);
      ternaryIndex.insert(Book::SecondaryKey(book),mybook);
    }
  }

}



void
BookStore::remove(const std::string & isbn) // 2 
{
  typename BinarySearchTree<std::string, Book>::Iterator it;
  for (it = primaryIndex.begin(); it != primaryIndex.end(); ++it)
  {
    Book *mybook = &(*it);
    if(isbn == mybook->getISBN())
    {
      
      Book *mybook = &(*it);
      secondaryIndex.remove(Book::SecondaryKey(*mybook));
      ternaryIndex.remove(Book::SecondaryKey(*mybook));
    }
  }

 primaryIndex.remove(isbn);


}




void
BookStore::remove(const std::string & title,
                  const std::string & author)
{
 
  std::string Title = title;
  int i = 0;
  while(Title[i])
  {
    if(Title[i] > 96)
      Title[i] -= 32;
    i++;
  }

  std::string Author = author;
  i = 0;
  while(Author[i])
  {
    if(Author[i] > 96)
      Author[i] -= 32;
    i++;
  }





  Book *mybook;
  typename BinarySearchTree<std::string, Book>::Iterator it;
  for (it = primaryIndex.begin(); it != primaryIndex.end(); ++it)
  {
    mybook = &(*it);
    std::string TTitle = mybook->getTitle( );
    i = 0;
    while(TTitle[i])
    {
      if(TTitle[i] > 96)
        TTitle[i] -= 32;
      i++;
    }

    std::string TAuthor = mybook->getAuthor( );
    i = 0;
    while(TAuthor[i])
    {
      if(TAuthor[i] > 96)
        TAuthor[i] -= 32;
      i++;
    }







    if(title == TTitle && author == TAuthor)
    {

      break;
    }
  }

  remove((*it).getISBN());
  /*
  secondaryIndex.remove(Book::SecondaryKey(*mybook));
  ternaryIndex.remove(Book::SecondaryKey(*mybook));
  primaryIndex.remove(mybook->getISBN());
*/

}










void
BookStore::removeAllBooksWithTitle(const std::string & title)
{
  std::string Title = title;
  int i = 0;
  while(Title[i])
  {
    if(Title[i] > 96)
      Title[i] -= 32;
    i++;
  }
  Book *mybook;
  typename BinarySearchTree<SKey, const Book *, AuthorComparator>::Iterator it;
  for (it = secondaryIndex.begin(); it != secondaryIndex.end(); ++it)
  {
     std::string tmp = (*it)->getTitle(); 
    i = 0;
    while(tmp[i])
    {
      if(tmp[i] > 96)
        tmp[i] -= 32;
      i++;
    }
     if(Title.compare(tmp) == 0)
     {
        remove((*it)->getISBN());
        it = secondaryIndex.begin();
     }
  }
}





void
BookStore::makeAvailable(const std::string & isbn)
{
  typename BinarySearchTree<std::string, Book>::Iterator it;
  for (it = primaryIndex.begin(); it != primaryIndex.end(); ++it)
  {
    Book *mybook = &(*it);
    if(isbn == mybook->getISBN())
    {
      
      Book *mybook = &(*it);
      mybook->setAvailable( );

    }
  }



}

void
BookStore::makeUnavailable(const std::string & title,
                           const std::string & author)
{
  std::string Title = title;
  int i = 0;
  while(Title[i])
  {
    if(Title[i] > 96)
      Title[i] -= 32;
    i++;
  }
  std::string Author = author;
  i = 0;
  while(Author[i])
  {
    if(Author[i] > 96)
      Author[i] -= 32;
    i++;
  }

  typename BinarySearchTree<std::string, Book>::Iterator it;
  for (it = primaryIndex.begin(); it != primaryIndex.end(); ++it)
  {
    Book *mybook = &(*it);

    std::string TTitle = mybook->getTitle( );
    i = 0;
    while(TTitle[i])
    {
      if(TTitle[i] > 96)
        TTitle[i] -= 32;
      i++;
    }
    std::string TAuthor = mybook->getAuthor( );
    i = 0;
    while(TAuthor[i])
    {
      if(TAuthor[i] > 96)
        TAuthor[i] -= 32;
      i++;
    }


    if(TTitle == TTitle && TAuthor == Author)
    {
      mybook->setUnavailable( );
    }
  }


}





void
BookStore::updatePublisher(const std::string & author, 
                           const std::string & publisher)
{
  std::string Author = author;
  int i = 0;
  while(Author[i])
  {
    if(Author[i] > 96)
      Author[i] -= 32;
    i++;
  }





  typename BinarySearchTree<std::string, Book>::Iterator it;
  for (it = primaryIndex.begin(); it != primaryIndex.end(); ++it)
  {
    Book *mybook = &(*it);
    std::string TAuthor = mybook->getAuthor( );
    i = 0;
    while(TAuthor[i])
    {
      if(TAuthor[i] > 96)
        TAuthor[i] -= 32;
      i++;
    }
    if(Author == TAuthor)
    {
      mybook->setPublisher(publisher);
    }


  }


}




void
BookStore::printBooksWithISBN(const std::string & isbn1,
                              const std::string & isbn2,
                              unsigned short since) const
{
  typename BinarySearchTree<std::string, Book>::Iterator it;
  for (it = primaryIndex.begin(); it != primaryIndex.end(); ++it)
  {
    Book *mybook = &(*it);
    if(mybook->getYear( ) >= since && mybook->getISBN() >= isbn1 && mybook->getISBN() <= isbn2)
      std::cout << *it << std::endl;
  }





}

void
BookStore::printBooksOfAuthor(const std::string & author,
                              const std::string & first,
                              const std::string & last) const
{
  std::string Author = author;
  int i = 0;
  while(Author[i])
  {
    if(Author[i] > 96)
      Author[i] -= 32;
    i++;
  }

  std::string First = first;
  i = 0;
  while(First[i])
  {
    if(First[i] > 96)
      First[i] -= 32;
    i++;
  }

  std::string Last = last;
  i = 0;
  while(Last[i])
  {
    if(Last[i] > 96)
      Last[i] -= 32;
    i++;
  }





  typename BinarySearchTree<SKey, Book *, TitleComparator>::Iterator it;
  for (it = ternaryIndex.begin(); it != ternaryIndex.end(); ++it)
  {

    Book *mybook = (*it);
    std::string TAuthor = mybook->getAuthor( );
    i = 0;
    while(TAuthor[i])
    {
      if(TAuthor[i] > 96)
        TAuthor[i] -= 32;
      i++;
    }

    std::string Ttitle = mybook->getTitle();
    i = 0;
    while(Ttitle[i])
    {
      if(Ttitle[i] > 96)
        Ttitle[i] -= 32;
      i++;
    }



    

    if(Author == TAuthor && Ttitle >= First && Ttitle <= Last)
      std::cout << *(*it) << std::endl;

  }






}








void //implemented, do not change
BookStore::printPrimarySorted( ) const
{
  BSTP::Iterator it;

  for (it=primaryIndex.begin(); it != primaryIndex.end(); ++it)
  {
    std::cout << *it << std::endl;
  }
}

void //implemented, do not change
BookStore::printSecondarySorted( ) const
{
  BSTS::Iterator it;

  for (it = secondaryIndex.begin(); it != secondaryIndex.end(); ++it)
  {
    std::cout << *(*it) << std::endl;
  }
}

void //implemented, do not change
BookStore::printTernarySorted( ) const
{
  BSTT::Iterator it;

  for (it = ternaryIndex.begin(); it != ternaryIndex.end(); ++it)
  {
    std::cout << *(*it) << std::endl;
  }
}


