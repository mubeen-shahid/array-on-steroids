#include "aos.hpp"

// DEMO OF AOS / Array On Steroids.

int main()
{
	AOS<AOS<int>> myArray(5); //create two-dimensional array with the data-type of int
	//myArray.resize(10); //arrays can be resized. Appearently doesn't work. Why? Because I told ChatGPT to write the function.

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
	
	myArray.suicide();

	return 0;
}
