

#include <atomic>
#include <chrono>
#include <limits>


#include <iostream>
#include <iomanip>
using namespace std;

namespace{
	using ValueType = unsigned long long;
//	volatile
	ValueType volatile oldValue{};

}

	//	constexpr auto MAX = numeric_limits<ValueType>::max();
void demoCompareStoreVSCompareExchange(){
	cout << __PRETTY_FUNCTION__ << endl;
	cout << std::setw(9); // for double output

//	using ValueType = unsigned long long;
//	ValueType oldValue{};
	chrono::duration<double> storeDuration;
	chrono::duration<double> compareDuration;

	constexpr auto MemoryOrder = memory_order_relaxed;
//	constexpr auto MemoryOrder = memory_order_release;
//	constexpr auto MemoryOrder = memory_order_acq_rel;
//	constexpr auto MemoryOrder = memory_order_seq_cst;
	constexpr auto MAX = 10000000;
//===========================================================
	{
		atomic<ValueType> value{};
		cout << "value.is_lock_free(): " << value.is_lock_free() << endl;
		cout << "value.store: " << MAX << endl;
		ValueType old{};

		auto start = chrono::high_resolution_clock::now();
		for(ValueType newValue{1ULL}; newValue<MAX; ++newValue){
			value.store(newValue, MemoryOrder);
			old = oldValue = newValue;
		}
		auto end = chrono::high_resolution_clock::now();
		storeDuration = end - start;
		cout << "storeDuration: " << storeDuration.count() << " s " << old << endl;
	}
//===========================================================
	{
		atomic<ValueType> value{};
		cout << "value.compare_exchange_weak: " << MAX << endl;
		oldValue = 0ULL;
		ValueType old{};

		auto start = chrono::high_resolution_clock::now();
		for(ValueType newValue{1ULL}; newValue<MAX; ++newValue){
			value.compare_exchange_weak(old, newValue, MemoryOrder, MemoryOrder);
			old = oldValue = newValue;
		}
		auto end = chrono::high_resolution_clock::now();
		compareDuration = end - start;
		cout << "compareDuration: " << compareDuration.count() << " s" << endl;
	}
//===========================================================

	cout << "Store/Compare: " << storeDuration / compareDuration << endl;
}
