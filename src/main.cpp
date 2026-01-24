#include <iostream>
#include "string.h"

int main() 
{
    String s1;
    String s2("hello");
    String s3(s2);
    String *p = new String("helllo");
    s1 = *p;
    std::cout<<s3<<std::endl;
    std::cout<<s1<<std::endl;
}
