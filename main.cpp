#include "aos.hpp"

// This is a demo of the "AOS" library, devoloped by XeTute. 
// XeTutes website: "https://xetute.neocities.org/"

int main()
{
	constexpr std::uint64_t elems = 10000000; // 10 000 000
	const std::uint64_t threads = std::thread::hardware_concurrency(); // Get num of physical threads on CPU

	AOS<int> a(elems); // 10.000.000
	AOS<int> b(elems);
	AOS<int> c(elems);

	a.setThreads(threads);
	b.setThreads(threads);
	c.setThreads(threads);

	timePoint start = std::chrono::high_resolution_clock::now();

	a.random(AOS<float>({ -10, 10 }));
	b.random(AOS<float>({ -10, 10 }));

	c = a + b;

	timePoint end = std::chrono::high_resolution_clock::now();

	std::cout << "Took " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << "ms.\n";
	return 0;
}
