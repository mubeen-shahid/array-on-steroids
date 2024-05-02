AOS / Array On Steriods is a alternative to std::vector.
AOS is compatible with the CUDA runtime and only includes the most used / wanted std::vector functions, with the same naming, making it a great choice if you want to / are planning to convert your C/C++ code, which uses std::vector to C/C++ CUDA code.

Most functions are documented in main.cpp, and since most are copied from std::vector, you won't have to learn the whole "library" - most functions are copied from std::vector and take in the same params.
AOS might be faster or slower than std::vector, I've not tested it yet.
