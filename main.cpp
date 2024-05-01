#include <iostream>
#include "aos.hpp"

int main()
{
	AOS<AOS<int>> myArray(10);
	myArray.data[0].init(10);

	return 0;
}