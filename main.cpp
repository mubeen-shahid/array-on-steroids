#include "aos.hpp"

// This is a demo of the "AOS" library, devoloped by XeTute. 
// XeTutes website: "https://xetute.neocities.org/"
// AOS GitHub: "https://www.github.com/N0CTRON/array-on-steriods/"
// cuMM GitHub: "https://www.github.com/N0CTRON/cuMM/"

int main()
{
	AOS<AOS<int>> myArray(6); //create two-dimensional array with the data-type of int
	myArray.resize(3); //Resize the array. Got it working, finally =)

	{ //bracets cuz var "aSize" is tmp 
		const size_t aSize = myArray.size(); // aSize = array size
		for (size_t row = 0; row < aSize; ++row) //init each element
		{
			myArray[row].init(aSize, 9);
			//myArray[row].init(aSize); <-- This line would automatically set every value to "NULL" / 0. Nice, right? :3

			for (size_t column = 0; column < aSize; ++column) 
			{
				myArray[row][column] = row * column; //assign unique value. It would not crash, because AOS auto-inits to zero if not value was provided
				std::cout << myArray[row][column] << " | "; // std::cout << myArray.data[row].data[column] would also work, operator was overloaded
			}
			std::cout << "\n-----------\n";
		}
	}
	
	myArray.suicide(); //Let the array kill itself. This prevents memory leaks

	return 0;
}
