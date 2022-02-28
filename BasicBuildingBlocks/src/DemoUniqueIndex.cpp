
#include <BasicBuildingBlocks/UniqueIndex.h>

#include <iostream>
using namespace std;


template<std::size_t NumElements>
struct MyIndex : UniqueIndex<NumElements>{
	using base_type = UniqueIndex<NumElements>;

	MyIndex(std::size_t index):base_type(index){}
	MyIndex(MyIndex&& rhs):base_type(std::move(rhs)){}
	MyIndex(base_type&& rhs):base_type(std::move(rhs)){}
};

void demoUniqueIndex(){
	cout << __PRETTY_FUNCTION__ << endl;
	constexpr auto MAX_Size_t = std::numeric_limits<std::size_t>::max();
	using Index = MyIndex<5>;
//	using BigIndex = UniqueIndex<MAX_Size_t>;
	using SmallIndex = UniqueIndex< (MAX_Size_t>>9) >;
	using BigIndex = UniqueIndex< (MAX_Size_t>>9)+1 >;
	using Unique = UniqueIndex<5>;
	cout << "sizeof(Index)   : " << sizeof(Index) << endl;
	cout << "sizeof(SmallIndex): " << sizeof(SmallIndex) << endl;
	cout << "sizeof(BigIndex): " << sizeof(BigIndex) << endl;

	Index index(4);

	cout <<"index.isValid(): " << index.isValid() << endl;
	Unique idx(std::move(index));
	cout <<"index.isValid(): " << index.isValid() << endl;
	cout <<"idx.isValid(): " << idx.isValid() << endl;
//	cout <<"idx.getIndex(): " << idx.getIndex() << endl;
	cout <<"idx: " << idx << endl;
	Index index2(std::move(idx));
	cout <<"idx.isValid(): " << idx.isValid() << endl;
//	cout <<"idx.getIndex(): " << idx.getIndex() << endl;
//	cout <<"idx: " << idx << endl;
	cout <<"index2.isValid(): " << index2.isValid() << endl;
//	cout <<"index2.getIndex(): " << index2.getIndex() << endl;
	cout <<"index2" << index2 << endl;


	// check static_assert
//	cout << "max size_t: " << std::numeric_limits<std::size_t>::max() << endl;
//	cout << "max ValueType: " << std::numeric_limits<ValueType>::max() << endl;
//	static constexpr ValueType toMuchElements = static_cast<ValueType>
//		(std::numeric_limits<std::size_t>::max()) +1;
//	using ToMuchElements = MyIndex<unsigned long long, toMuchElements>;
//	ToMuchElements assertIndex(0);
}
