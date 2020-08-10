#include <iostream>

#include "vector.h"


template<typename T>
void display (vector<T> &vec)
{
	std::cout << "\nsize: " << vec.size () << "\ncapacity: " << vec.capacity () << '\n';

	for (size_t i = 0; i < vec.size (); ++i)
		std::cout << vec.at(i) << ' ';
	std::cout << std::endl;

	return;
}



int main ()
{
	vector<int> vec_1 (16);
	vector<int> vec_2 (vec_1);
	vector<int> vec_3 (4, 25);
	vec_2 = vec_3;
	vec_1[7] = 11;
	vec_1.at (8) = 12;
	display<int> (vec_1);
	display<int> (vec_2);
	display<int> (vec_3);
	
	vec_1.push_back (17);
	vec_2.push_back (18);
	vec_3.push_back (19);
	display<int> (vec_1);
	display<int> (vec_2);
	display<int> (vec_3);
	return 0;
}