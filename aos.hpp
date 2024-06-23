#include <iostream>
#include <stdexcept>
#include <algorithm>

template <typename arrType>
class AOS // AOS = array on steroids
{
private:
    std::uint64_t vsize = 0;

public:
    arrType* data = nullptr;

    void init(std::uint64_t nSize)
    {
        vsize = nSize;
        try
        {
            if (data) delete[] data;
            data = new arrType[nSize];
        }
        catch (const std::bad_alloc& e)
        {
            std::cerr << "[ | AOS-LOG ]: Failed to allocate memory for array at aos.hpp, first init function.\n" << e.what() << std::endl;
            exit(-1);
        }
        std::fill_n(data, nSize, arrType());
    }

    void init(std::uint64_t nSize, arrType defaultVal)
    {
        vsize = nSize;
        try
        {
            if (data) delete[] data;
            data = new arrType[nSize];
        }
        catch (const std::bad_alloc& e)
        {
            std::cerr << "[ | AOS-LOG ]: Failed to allocate memory for array at aos.hpp, second init function.\n" << e.what() << std::endl;
            exit(-1);
        }
        std::fill_n(data, nSize, defaultVal);
    }

    void resize(std::uint64_t nSize)
    {
        if (nSize != vsize)
        {
            arrType* newData = new arrType[nSize];
            std::uint64_t minSize = std::min(vsize, nSize);
            std::copy(data, data + minSize, newData);
            std::fill(newData + minSize, newData + nSize, arrType());
            if (data) delete[] data;
            data = newData;
            vsize = nSize;
        }
    }

    void suicide()
    {
        if (this->data)
        {
            delete[] this->data;
            data = nullptr;
        }
    }

    std::uint64_t size() const { return vsize; }

    AOS(std::initializer_list<arrType> list)
    {
        vsize = list.size();
        data = new arrType[vsize];
        std::copy(list.begin(), list.end(), data);
    }
    
    AOS(std::uint64_t nSize) { init(nSize); }
    
    AOS(std::uint64_t nSize, arrType defaultVal) { init(nSize, defaultVal); }
    
    AOS() : data(nullptr) {}
    
    ~AOS() { delete[] data; }

    arrType& operator[](const std::uint64_t index) { return data[index]; }
    
    AOS& operator=(const std::initializer_list<arrType> list)
    {
        if (data) delete[] data;
        vsize = list.size();
        try { data = new arrType[vsize]; }
        catch (const std::bad_alloc& e)
        {
            std::cerr << "[ | AOS-LOG ]: Failed to allocate memory for array at aos.hpp at overloaded = std::init... operator.\n" << e.what() << std::endl;
            exit(-1);
        }
        std::copy(list.begin(), list.end(), data);
        return *this;
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

    AOS(const AOS& other)
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
};
