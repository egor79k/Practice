#include <iostream>
#include "shared_ptr.h"


int main ()
{
	shared_ptr<int> p (new int (1));
	shared_ptr<int> pp (new int (2));
	p = pp;
	std::cout << p.use_count () << pp.use_count ();
	std::cout << *p << *pp;

	return 0;
}