// Example program
#include <iostream>
#include <string>


class A  
{ 
public: 
    int x;
    virtual int ret()
    {
        return x*2;
    }
    
    int ret2()
    {
        return x*2;
    }
    
protected: 
    int y; 
private: 
    int z; 
}; 
  
class B : public A 
{ 
    public:
        int ret()
        {
            return x;
        }
        
        int ret2()
        {
            return x;
        }
    
    // x is public 
    // y is protected 
    // z is not accessible from B 
}; 
  
class C : protected A 
{ 
    // x is protected 
    // y is protected 
    // z is not accessible from C 
}; 
  
class D : private A    // 'private' is default for classes 
{ 
    // x is private 
    // y is private 
    // z is not accessible from D 
}; 




int main()
{
    B b;
    b.x = 5;
    A *a = &b;
    
    std::cout << b.x<< std::endl;// print 5
    
    std::cout << b.ret() <<std::endl; //ret in B class print 5
    
    std::cout << a->ret() <<std::endl;// ret in B class because of virtual function, print 5
    
    std::cout << b.ret2() <<std::endl; // print 5
    
    std::cout << a->ret2() <<std::endl; //print 10

}
