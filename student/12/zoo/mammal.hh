#ifndef MAMMAL_HH
#define MAMMAL_HH
#include "animal.hh"


class Mammal: public Animal
{
public:
    Mammal();
    void suckle(std::ostream &output) const;
};

#endif // MAMMAL_HH

/*


#ifndef BIRD_HH
#define BIRD_HH
#include "animal.hh"


class Bird: public Animal
{
public:
    Bird();
    void fly(int x, int y, int z, std::ostream& output);
    void print_altitude(std::ostream& output) const;

private:
    int z_;


};

#endif // BIRD_HH


 */
