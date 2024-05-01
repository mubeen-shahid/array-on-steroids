#include <cstddef>
#include <malloc.h>
#include <iostream>

template <typename arrType>
class AOS //AOS = array on steroids
{
private:
	size_t size;

public:
	arrType* data;

	void init(size_t nSize)
	{
		size = nSize;
		data = (arrType*)malloc(sizeof(arrType) * nSize);
	}

	void resize(size_t nSize)
	{
		if (nSize != size)
		{
			arrType* newData = (arrType*)realloc(data, sizeof(arrType) * nSize);
			if (newData) //realloc succeded!! :)
			{
				if (nSize > size) for (size_t i = size; i < nSize; ++i) newData[i] = arrType();
				data = newData;
				size = nSize;
			}
			else std::cout << "[ | AOS-LOG ]: AOS::resize(size_t) failed, keeping old array.\n"; //if failed :(
		}
	}

	void suicide()
	{
		free(data);
		data = nullptr;
	}

	size_t getSize() { return size; }

	AOS(size_t nSize) { init(nSize); };
	AOS() {} ;
	~AOS() { suicide(); }

	arrType &operator[](const size_t& index) { return this->data[index]; }
};
