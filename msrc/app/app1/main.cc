#include <iostream>
#include <exception>
#include "libgp_api.h"

int main(int argc, char **argv)
{
    Box box;
    box.set(1,2,3);
    cout<<box.get()<<std::endl;
}
