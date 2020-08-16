#include <iostream>

#include "vector.h"


int main ()
{
	vector<int> v_1 (16);
	auto it = v_1.begin ();
	for (it; it < v_1.end (); ++it)
		std::cout << *it;
	for (int i = 0; i < v_1.size (); ++i)
		v_1[i] = i + 1;
	for (it; it >= v_1.begin (); --it)
		std::cout << *it;
	return 0;
}