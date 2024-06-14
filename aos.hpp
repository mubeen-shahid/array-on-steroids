#include <malloc.h>
#include <iostream>
#include <thread>

template <typename arrType>
class AOS //AOS = array on steroids
{
private:
	std::uint64_t vsize = 0;

public:
	arrType* data;

	void init(std::uint64_t nSize)
	{
		vsize = nSize;
		data = (arrType*)malloc(sizeof(arrType) * nSize);
		if (!data)
		{
			std::cerr << "[ | AOS-LOG ]: Failed to allocate memory for array at aos.hpp, line 20." << std::endl;
			return;
		}
		for (std::uint64_t i = 0; i < nSize; ++i) this->data[i] = arrType();
	}

	void init(std::uint64_t nSize, arrType defaultVal)
	{
		vsize = nSize;
		data = (arrType*)malloc(sizeof(arrType) * nSize);
		if (!data)
		{
			std::cerr << "[ | AOS-LOG ]: Failed to allocate memory for array at aos.hpp, line 32." << std::endl;
			return;
		}
		for (std::uint64_t i = 0; i < nSize; ++i) this->data[i] = defaultVal;
	}

	void resize(std::uint64_t nSize)
	{
		if (nSize != vsize)
		{
			arrType* newData = (arrType*)realloc(data, sizeof(arrType) * nSize);
			if (newData) //realloc succeded!! :)
			{
				for (std::uint64_t i = vsize; i < nSize; ++i) newData[i] = arrType();
				data = newData;
				vsize = nSize;
			}
			else std::cerr << "[ | AOS-LOG ]: AOS::resize(std::uint64_t) failed, keeping old array." << std::endl; //if failed :(
		}
	}

	void suicide()
	{
		free(data);
		data = nullptr;
	}

	std::uint64_t size() { return vsize; }

	AOS(std::initializer_list<arrType> list)
	{
		vsize = list.size();
		data = (arrType*)malloc(sizeof(arrType) * vsize);
		std::copy(list.begin(), list.end(), data);
	}
	AOS(std::uint64_t nSize) { init(nSize); };
	AOS(std::uint64_t nSize, arrType defaultVal) { init(nSize, defaultVal); };
	AOS() {};
	~AOS() { std::thread(suicide); } //<-- Threading was tested, about 1.9 times faster than calling "suicide" from main thread

	arrType& operator[](const std::uint64_t index) { return this->data[index]; }
	AOS& operator=(std::initializer_list<arrType> list)
	{
		vsize = list.size();
		data = (arrType*)malloc(sizeof(arrType) * vsize);
		std::copy(list.begin(), list.end(), data);
		return *this;
	}
};
