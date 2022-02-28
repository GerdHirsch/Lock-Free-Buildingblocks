#ifndef INCLUDE_BASICBUILDINGBLOCKS_RINGBUFFERPOSITION_H_
#define INCLUDE_BASICBUILDINGBLOCKS_RINGBUFFERPOSITION_H_

#include <BasicBuildingBlocks/ABASafeIndex.h>

/** Specialization for isPowerOfTwo(NumElements) is possible but not implemented yet */
template<std::size_t NumElements, bool = CalculateHelper<NumElements>::isPowerOfTwo()>
class RingbufferPosition;


template<std::size_t NumElements>
class RingbufferPosition<NumElements, true> : protected ABASafeIndex<NumElements>{
public:
	using this_type = RingbufferPosition<NumElements>;
	using base_type = ABASafeIndex<NumElements>;
	using ValueType = typename base_type::ValueType;

	RingbufferPosition():base_type(0){}

	bool isOptimized(){ return true; }
	this_type& operator++(){
		++value;
		return *this;
	}

	ValueType getABACounter(){
		return value & ~INDEX_MASK;
	}
	void setABACounter(ValueType counter){
		value = (value & INDEX_MASK) + (counter &~INDEX_MASK);
	}
	using base_type::INDEX_MASK;
	using base_type::SPLIT_BIT;
	using base_type::getIndex;
	using base_type::setIndex;
	using base_type::getValue;
protected:
	using base_type::value;
};

template<std::size_t NumElements>
class RingbufferPosition<NumElements, false> : protected ABASafeIndex<NumElements>{
public:
	// Todo implement
	using this_type = RingbufferPosition<NumElements>;
	using base_type = ABASafeIndex<NumElements>;
	using ValueType = typename base_type::ValueType;

	RingbufferPosition():base_type(0){}
	bool isOptimized(){ return false; }

	this_type& operator++(){
		if(getIndex() >= NumElements-1){
			setIndex(0);
			value += SPLIT_BIT;
		}else{
			setIndex(getIndex()+1);
		}
		return *this;

	}
	ValueType getABACounter(){
		return value & ~INDEX_MASK;
	}
	void setABACounter(ValueType counter){
		value = (value & INDEX_MASK) + (counter &~INDEX_MASK);
	}
	using base_type::INDEX_MASK;
	using base_type::SPLIT_BIT;
	using base_type::getIndex;
	using base_type::setIndex;
	using base_type::getValue;
protected:
	using base_type::value;
};



#endif /* INCLUDE_BASICBUILDINGBLOCKS_RINGBUFFERPOSITION_H_ */
