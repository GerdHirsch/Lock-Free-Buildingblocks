

#include <atomic>
#include <chrono>
#include <limits>


#include <iostream>
#include <iomanip>
using namespace std;

void demoCompareStoreVSCompareExchange(){
	cout << __PRETTY_FUNCTION__ << endl;
	using ValueType = unsigned long long;
	constexpr auto MemoryOrder = memory_order_relaxed;

	atomic<ValueType> value{};
	cout << "value.is_lock_free(): " << value.is_lock_free() << endl;

	ValueType oldValue{};
//	constexpr auto MAX = numeric_limits<ValueType>::max();
	constexpr auto MAX = 10000000;

	auto start = chrono::high_resolution_clock::now();

	for(ValueType newValue{1ULL}; newValue<MAX; ++newValue){
		//diff: 45 566 6200 diff: 0.61643 s
//		value.store(newValue, MemoryOrder);
		//diff: 85 2430 900 diff: 1.27338 s
		value.compare_exchange_weak(oldValue, newValue, MemoryOrder, MemoryOrder);
		oldValue = newValue;
	}
	auto end = chrono::high_resolution_clock::now();
	chrono::duration<double> diff = end - start;
	cout << std::setw(9);
	cout << "diff: " << diff.count() << " s"<< endl;


//	auto end = chrono::high_resolution_clock::now();
//	cout << "end: " << end << endl;
}
