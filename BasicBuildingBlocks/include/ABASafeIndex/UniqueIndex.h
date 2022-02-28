#ifndef INCLUDE_ABASAFEINDEX_UNIQUEINDEX_H_
#define INCLUDE_ABASAFEINDEX_UNIQUEINDEX_H_

#include "ABASafeIndex.h"

template<std::size_t NumElements>
class UniqueIndex : protected ABASafeIndex<NumElements>{
public:

	using base_type = ABASafeIndex<NumElements>;
	using this_type = UniqueIndex<NumElements>;
	using typename base_type::ValueType;

	UniqueIndex(this_type &&rhs):base_type(rhs.value){
		rhs.invalidate();
	}
	bool isValid(){ return operator bool();}
	explicit operator bool(){ return value & SPLIT_BIT; }
	/** UniqueIndex to be used as index in an array */
	operator std::size_t(){
		assert(isValid());
		return getIndex();
	}
protected:
	UniqueIndex(std::size_t index):base_type(index & INDEX_MASK){
		validate();
	}
	using base_type::value;
	using base_type::INDEX_MASK;
	using base_type::SPLIT_BIT;
	using base_type::getIndex;

private:
	void validate(){
		value |= SPLIT_BIT;
	}
	void invalidate(){
		value &= ~SPLIT_BIT;
	}
};



#endif /* INCLUDE_ABASAFEINDEX_UNIQUEINDEX_H_ */
