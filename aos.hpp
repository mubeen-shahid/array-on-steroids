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

	void suicide() { for (size_t i = 0; i < size; ++i) free(data[i]); }

	size_t size() { return size; }

	AOS(size_t nSize) { init(nSize); };
	AOS() {} ;
	~AOS() { suicide(); }
};