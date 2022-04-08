

#include <atomic>
#include <chrono>
#include <limits>


#include <iostream>
#include <iomanip>
using namespace std;

//namespace{
//	using ValueType = unsigned long long;
//	//volatile
//	ValueType oldValue{};
//
//}

	//	constexpr auto MAX = numeric_limits<ValueType>::max();
void demoCompareStoreVSCompareExchange(){
	cout << __PRETTY_FUNCTION__ << endl;
	cout << std::setw(9); // for double output

	using ValueType = unsigned long long;
	ValueType oldValue{};

	constexpr auto MemoryOrder = memory_order_relaxed;
	atomic<ValueType> value{};
	cout << "value.is_lock_free(): " << value.is_lock_free() << endl;
	constexpr auto MAX = 1000000;
//===========================================================
	cout << "value.store: " << MAX << endl;
	auto start = chrono::high_resolution_clock::now();

	for(ValueType newValue{1ULL}; newValue<MAX; ++newValue){
		value.store(newValue, MemoryOrder);
		oldValue = newValue;
	}
	auto end = chrono::high_resolution_clock::now();
	chrono::duration<double> diffStore = end - start;
	cout << "diffStore: " << diffStore.count() << " s" << endl;
//===========================================================
	cout << "value.compare_exchange_weak: " << MAX << endl;
	value.store(0, MemoryOrder);
	oldValue = 0ULL;
	start = chrono::high_resolution_clock::now();

	for(ValueType newValue{1ULL}; newValue<MAX; ++newValue){
		value.compare_exchange_weak(oldValue, newValue, MemoryOrder, MemoryOrder);
		oldValue = newValue;
	}
	end = chrono::high_resolution_clock::now();
	chrono::duration<double> diffCompare = end - start;
	cout << "diffCompare: " << diffCompare.count() << " s" << endl;

	cout << "Store/Compare: " << diffStore / diffCompare << endl;
}
