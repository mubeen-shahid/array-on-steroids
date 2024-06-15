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
		try { data = new arrType[nSize]; }
		catch (const std::bad_alloc& e)
		{
			std::cerr << "[ | AOS-LOG ]: Failed to allocate memory for array at aos.hpp, first init function.\n" << e.what() << std::endl;
			exit(-1);
		}
		for (std::uint64_t i = 0; i < nSize; ++i) this->data[i] = arrType();
	}

	void init(std::uint64_t nSize, arrType defaultVal)
	{
		vsize = nSize;
		try { data = new arrType[nSize]; }
		catch (const std::bad_alloc& e)
		{
			std::cerr << "[ | AOS-LOG ]: Failed to allocate memory for array at aos.hpp, second init function.\n" << e.what() << std::endl;
			exit(-1);
		}
		for (std::uint64_t i = 0; i < nSize; ++i) this->data[i] = defaultVal;
	}

	void resize(std::uint64_t nSize)
	{
		if (nSize != vsize)
		{
			if (data)
			{
				arrType* newData = new arrType[nSize];
				for (std::uint64_t i = 0; i < vsize; ++i) newData[i] = data[i];
				for (std::uint64_t i = vsize; i < nSize; ++i) newData[i] = arrType();
				delete[] data;
				data = newData;
				vsize = nSize;
			}
			else
			{
				data = new arrType[nSize];
				for (std::uint64_t i = 0; i < nSize; ++i) data[i] = arrType();
				vsize = nSize;
			}
		}
	}

	void suicide()
	{
		if (data) delete[] data;
		data = nullptr;
	}

	std::uint64_t size() { return vsize; }

	AOS(std::initializer_list<arrType> list)
	{
		vsize = list.size();
		data = new arrType[vsize];
		std::copy(list.begin(), list.end(), data);
	}
	AOS(std::uint64_t nSize) { init(nSize); };
	AOS(std::uint64_t nSize, arrType defaultVal) { init(nSize, defaultVal); };
	AOS() : data(nullptr) {};
	~AOS() { if (data) delete[] data; }

	arrType& operator[](const std::uint64_t index) { return this->data[index]; }
	AOS& operator=(const std::initializer_list<arrType> list)
	{
		vsize = list.size();
		if (data) delete[] data;
		try { data = new arrType[vsize]; }
		catch (const std::bad_alloc& e)
		{
			std::cerr << "[ | AOS-LOG ]: Failed to allocate memory for array at aos.hpp at overloaded = std::init... operator.\n" << e.what() << std::endl;
			exit(-1);
		}
		std::copy(list.begin(), list.end(), data);
		return *this;
	}

	AOS(AOS& other)
	{
		vsize = other.size();
		data = new arrType[vsize];
		if (!data)
		{
			std::cerr << "[ | AOS-LOG ]: Failed to allocate memory for array at aos.hpp at AOS(const AOS&)." << std::endl;
			exit(-1);
		}
		std::copy(other.data, other.data + vsize, data);
	}

	AOS& operator=(const AOS& other)
	{
		if (this != &other)
		{
			if (data) delete[] data;
			vsize = other.vsize;
			data = new arrType[vsize];
			if (!data)
			{
				std::cerr << "[ | AOS-LOG ]: Failed to allocate memory for array at aos.hpp at AOS& operator=(const AOS&)." << std::endl;
				exit(-1);
			}
			std::copy(other.data, other.data + vsize, data);
		}
		return *this;
	}
};
