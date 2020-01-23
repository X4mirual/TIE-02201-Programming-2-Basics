#include <iostream>


int main()
{
    std::cout << "How many numbers would you like to have? ";
    int maksimi = 0;
    std::cin >> maksimi;
    int luku = 0;

    while ( luku < maksimi )
    {
            ++luku;
        if ( luku % 3 == 0 ) {
             std::cout << "zip" << std::endl;
    }
        else {
            std::cout << luku << std::endl;
        }
}







}
