#include <cstddef>
#include <malloc.h>

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
		for (size_t i = 0; i < nSize; ++i) data[i] = (arrType*)malloc(sizeof(arrType));
	}

	void resize(size_t nSize)
	{
		if (nSize != size)
		{
			arrType* newData = arrType*realloc(data, sizeof(arrType) * nSize);
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
		for (size_t i = 0; i < size; ++i) free(data[i]);
		free(data);
	}

	size_t getSize() { return size; }

	AOS(size_t nSize) { init(nSize); };
	AOS() {} ;
	~AOS() { suicide(); }

	AOS& operator[](const size_t& index) { return this->data[index]; }
	AOS& operator=(const AOS& individual)
	{
		this->data = individual.data;
		this->size = size;
	}
};
