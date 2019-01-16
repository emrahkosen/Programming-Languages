#include "Article.h"

/*#############################
#               NOTE!         #
#    Please don't forget to   #
#     check PDF. Fuctions     #
#    may have more detailed   #
#     tasks which are not     #
#       mentioned here.       #
#############################*/

Article::Article( int table_size,int h1_param, int h2_param )
:table_size(table_size), h1_param(h1_param), h2_param(h2_param)
{    
    /*#############################
    #            TO-DO            #
    # Write a default constructor #
    #   for the Article Class     #
    #############################*/
    table = new std::pair<std::string, int>[table_size];
    int i=0;
    while(i != table_size)
    {
        table[i].second = -1;
        i++;
    }
    n = 0;
 

}

Article::~Article()
{
    /*#############################
    #             TO-DO           #
    #  Write a deconstructor for  #
    #     the Article Class       #
    #############################*/
    delete [] table;
}

int Article::get( std::string key, int nth, std::vector<int> &path ) const
{
    
//  std::cout<<"in get function \n\n"<<"\n";
    int oc = 0;
    for(int i = 0;i< table_size;i++)
    {
      
        int has = hash_function(key,i);
  

              if(i )
                path.push_back(has);

         
        if(table[has].first == key )
        {   
            
            oc++;
            if(oc == nth)
            {
 // std::cout<<has <<"---------------------------<<<" <<"\n";

                int ret = table[has].second;
                return ret;
            }
        }
           
           if( table[has].second == EMPTY_INDEX )
           { 
            return -1; 
           
           }


            

    }
 //std::cout <<"***********enson" <<"\n";    
    return -1;
}



int Article::insert( std::string key, int original_index )//-------------------------
{
    int cindex = original_index;
    double lf = getLoadFactor();
    if(lf > MAX_LOAD_FACTOR)
        expand_table();
    int procount = 0;
    for (int i = 0; i < table_size; ++i)
    {
        int ikey = hash_function(key,i);
        if(table[ikey].second == EMPTY_INDEX || table[ikey].second ==  MARKED_INDEX || (table[ikey].first == key && table[ikey].second > cindex))
        { 


            if(table[ikey].second == EMPTY_INDEX || table[ikey].second ==  MARKED_INDEX)
            {
                table[ikey].first = key;
                table[ikey].second = cindex;
                break;
            }
            else
            {
                int tindex = table[ikey].second;
                table[ikey].second = cindex;
             
                cindex = tindex;
            }
        }
        
        
    
    
        if(table[ikey].first != EMPTY_KEY )
            ++procount;
                
        
        
    }
    n++;
    
    
    return procount;
}


int Article::remove( std::string key, int nth )
{
 //    std::cout<<"                in remove function \n\n"<<"\n";
    /*#########################################
    #                  TO-DO                  #
    #      Remove the nth key at the hash     #
    #                  table.                 #
    #  Return the total number of probes you  #
    #      encountered while inserting.       #
    #   If there is no such a key, return -1  #
    #     If there, put a mark to the table   #
    #########################################*/
    
    int oc = 0;
    //int a =-1;
    for(int i = 0;i<= table_size;i++)
    {
        
      //  a++; 
        int has = hash_function(key,i);
 //   std::cout<<i<<"-->"<<has<<"---"<<table[has].first<<"\n";    
        if(table[has].first == EMPTY_KEY && table[has].second == EMPTY_INDEX)
            return -1;
     
        
        if(table[has].first == key)
        {
            oc++;
            if(oc == nth)
            {
                int ret = table[has].second;
                table[has].first = EMPTY_KEY;
                table[has].second = MARKED_INDEX;
                n--;
                return i;
            }
            
        }
        
        
        
    }
    
    return -1;
}

double Article::getLoadFactor() const //--------------------------------------
{
    /*#########################################
    #                TO-DO                    #
    #      Return the load factor of the      #
    #                table                    #
    #########################################*/
  
    return n*1.0/table_size;
}

void Article::getAllWordsFromFile( std::string filepath )
{
    
    int indexnumber  = 0;
    std::ifstream file;
    file.open(filepath.c_str());
    std::string word;
    while(file >> word)
        {
            indexnumber++;
            insert(word,indexnumber);
        }
    file.close();
/*
   std::ifstream file;
       char c;
    
    file.open(filepath.c_str());
    int indexnumber  = 0;
    while(!file.eof())
    {
        std::string word;
        indexnumber++;
        c = file.get();
    
        if(c > 122 || c < 65)
            break;
     

        while(c == ' ')
            c = file.get();
        while(c != ' ')
        {
            word = word+c;
            c = file.get();
        }
        insert(word,indexnumber);
    }
    file.close();


*/
/*
    std::ifstream file;
    char c;
    std::string word;
    file.open(filepath.c_str());
    int indexnumber  = 0;
    while(!file.eof())
    {
        indexnumber++;
        c = file.get();
        while(c == ' ')
            c = file.get();
        while(c != ' ')
        {
            word = word+c;
            c = file.get();
        }
        insert(word,indexnumber);
std::cout<<word<<"-**-*-*-*--*-*-*-*-*-"<<std::endl;
    }
    file.close();
    
    */
}

void Article::expand_table()    //-------------------------------------------
{
    /*#########################################
    #                  TO-DO                  #
    #   Implement the expand table function   #
    #   in order to increase the table size   #
    #   to the very first prime number after  #
    #      the value of (2*table size).       #
    #         Re-hash all the data.           #
    #       Update h2_param accordingly.      #
    #########################################*/
    int prime = nextPrimeAfter(2*table_size);
       h2_param = firstPrimeBefore(prime);
    std::pair<std::string,int>*oldtable = table;
    table = new std::pair<std::string, int>[prime];
    int oldtablesize = table_size;
    table_size = prime;
    n = 0;
    int i = 0;
    while(i != table_size)
    {
        table[i].second = -1;
        i++;
    }
    
    for(int i = 0;i<oldtablesize;i++)
    {
        if(oldtable[i].first == EMPTY_KEY && oldtable[i].second !=  MARKED_INDEX)
            ;
        else
        {
            insert(oldtable[i].first,oldtable[i].second);
        }
    }
    
    delete[] oldtable;


}

int Article::hash_function( std::string& key, int i ) const//------------------
{
    /*#########################################
    #                TO-DO                    #
    #       Implement the main hashing        #
    #    function. Firstly, convert key to    #
    #    integer as stated in the homework    #
    #      text. Then implement the double    #
    #            hashing function.            #
    #      use convertStrToInt function to    #
    #      convert key to a integer for       #
    #         using it on h1 and h2           #
    #               reminder:                 #
    #            you should return            #
    #    ( h1(keyToInt) + i*h2(keyToınt) )    #
    #            modulo table_size            #
    #########################################*/
    int ikey = convertStrToInt(key);
    int myh1 = h1(ikey);
    int myh2 = h2(ikey);

    int ret =  (myh1 + i*myh2)%table_size;
    if(ret < 0)
        ret += table_size;
    return ret;
}

int Article::h1( int key ) const//----------------------------------------
{
    /*###############################
    #              TO-DO            #
    #      First Hash function      #
    # Don't forget to use h1_param. #
    ###############################*/
    int popcount = 0;
    int divi = key;
    while(divi != 0)
    {
        popcount += divi%2;
        divi /= 2;  
    }



    return h1_param*popcount;
}

int Article::h2( int key ) const //----------------------------------------
{
    /*###############################
    #              TO-DO            #
    #     Second Hash function      #
    # Don't forget to use h2_param. #
    ###############################*/


    return h2_param - key%h2_param;
}

