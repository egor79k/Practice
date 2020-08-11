#include <iostream>

#include "list.h"


int main ()
{
	list<int> l_1 (16, 1);
	list<int> l_2 (l_1);
	list<int> l_3 (4, 3);
	l_1.print ();
	l_2.print ();
	l_3.print ();

	l_3 = l_2;
	l_1.push_back (17);
	l_2.push_back (18);

	l_1.print ();
	l_2.print ();
	l_3.print ();

	l_1.pop_front ();
	l_2.pop_front ();

	l_1.print ();
	l_2.print ();
	l_3.print ();
	
	return 0;
}