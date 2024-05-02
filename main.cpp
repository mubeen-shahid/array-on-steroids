#include "aos.hpp"

// DEMO OF AOS / Array On Steroids.

int main()
{
	AOS<AOS<int>> myArray(3); //create two-dimensional array with the data-type of int

	{ //bracets cuz var "aSize" is tmp 
		const size_t aSize = myArray.size(); // aSize = array size
		for (size_t row = 0; row < aSize; ++row) //init each element
		{
			myArray[row].init(aSize, 9);
			//myArray[row].init(aSize); <-- This line would automatically set every value to "NULL" / 0. Nice, right? :3

			for (size_t column = 0; column < aSize; ++column) 
			{
				myArray[row][column] = row * column; //assign unique value. It would not crash, because AOS auto-inits to zero if not value was provided
				std::printf("%d | ", myArray[row][column]); // std::cout << myArray.data[row].data[column] would also work, operator was overloaded
			}
			std::printf("\n-----------\n");
		}
	}
	
	myArray.suicide(); //Let the array kill itself. This prevents memory leaks

	return 0;
}
