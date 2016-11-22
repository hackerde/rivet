#include "barcode.h"

#include <math.h>
#include <debug.h>

MultiBar::MultiBar(double b, double d, unsigned m)
    : birth(b)
    , death(d)
    , multiplicity(m)
{
}

MultiBar::MultiBar(const MultiBar& other)
    : birth(other.birth)
    , death(other.death)
    , multiplicity(other.multiplicity)
{
}

//comparison operator for sorting long bars first
//uses approximate comparisons to avoid "flickering" of bars of nearly equal length
bool MultiBar::operator<(const MultiBar other) const
{
    double epsilon = pow(10, -8);

    //first, sort by length of bar
    if ((death - birth) > (other.death - other.birth + epsilon))
        return true;

    //if bars have (almost) the same length, then sort by birth time
    if ((death - birth) >= (other.death - other.birth - epsilon))
        return (birth < other.birth);

    //else
    return false;
}

Barcode::Barcode()
{
}

//adds a bar to the barcode
void Barcode::add_bar(double b, double d, unsigned m)
{
    bars.insert(MultiBar(b, d, m));
}

//returns an iterator to the first bar in the barcode
std::set<MultiBar>::const_iterator Barcode::begin() const
{
    return bars.cbegin();
}

//returns an iterator to the pst-the-end element the barcode
std::set<MultiBar>::const_iterator Barcode::end() const
{
    return bars.cend();
}

//returns the number of multibars in the barcode
unsigned Barcode::size() const
{
    return bars.size();
}

//for testing only
void Barcode::print() const
{
    Debug qd = debug(true);
    qd << "      rescaled barcode: ";
    for (std::multiset<MultiBar>::iterator it = bars.begin(); it != bars.end(); ++it) {
        MultiBar b = *it;
        qd << "(" << b.birth << "," << b.death << ")x" << b.multiplicity << ", ";
    }
}