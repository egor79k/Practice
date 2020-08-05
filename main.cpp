#include <iostream>

#include "span.h"



int main ()
{
	const int span_sz = 20;
	span<int> S (new int[span_sz], span_sz);
	for (int i = 0; i < span_sz; ++i)
	{
		std::cout << S[i];
	}
	span<int> S_small = S.subspan (5, 15);
	return 0;
}