#include "aos.hpp"

// DEMO OF AOS / Array On Steroids.

int main()
{
	AOS<AOS<int>> myArray(10); //create two-dimensional array with the data-type of int

	{ //bracets cuz var "aSize" is tmp 
		const size_t aSize = myArray.getSize(); // aSize = array size
		for (size_t row = 0; row < aSize; ++row) //init each element
		{
			myArray[row].init(aSize);
			for (size_t column = 0; column < aSize; ++column) 
			{
				myArray[row][column] = row * column; //assign unique value
				std::cout << myArray[row][column] << " | "; // std::cout << myArray.data[row].data[column] would also work, operator was overloaded
			}
			std::cout << "\n--------------------\n";
		}
	}

	return 0;
}
