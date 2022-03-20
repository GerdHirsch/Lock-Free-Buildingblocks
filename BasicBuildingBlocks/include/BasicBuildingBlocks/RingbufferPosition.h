#ifndef INCLUDE_BASICBUILDINGBLOCKS_RINGBUFFERPOSITION_H_
#define INCLUDE_BASICBUILDINGBLOCKS_RINGBUFFERPOSITION_H_

#include <BasicBuildingBlocks/ABASafeIndex.h>

/** Specialization for isPowerOfTwo(NumElements) is possible but not implemented yet */
template<std::size_t NumElements, bool = CalculateHelper<NumElements>::isPowerOfTwoWithoutOne()>
class RingbufferPosition;


template<std::size_t NumElements>
class RingbufferPosition<NumElements, true> : protected ABASafeIndex<NumElements>{
public:
	using this_type = RingbufferPosition<NumElements>;
	using base_type = ABASafeIndex<NumElements>;
	using ValueType = typename base_type::ValueType;

	RingbufferPosition():base_type(0){}

	bool isOptimized() const { return true; }
	this_type& operator++(){
		++value;
		return *this;
	}

	ValueType getABACounter()const{
		return value & ~INDEX_MASK;
	}
	void setABACounter(ValueType counter){
		value = (value & INDEX_MASK) + (counter &~INDEX_MASK);
	}
	/**
		 * defines a follow up relation of two positions
		 * lhs.isbehind(rhs)
		 * lhs (this) is behind rhs if it is in the same block (same ABACount)
		 * and it큦 index is less than rhs.getIndex()
		 * or
		 * lhs is in the previous block and it큦 index is greater or equal than rhs.getIndex()
		 *
		 * must be implemented consistently with operator==()
		 * uses unsigned overflow to turn numOverruns infinitely around
		 */
		bool isBehind(this_type rhs)const{
			bool retVal{false};
			std::size_t rhsIdx = getIndex();
			std::size_t lhsIdx = rhs.getIndex();
			std::size_t rhsABA = getABACounter();
			std::size_t lhsABA = rhs.getABACounter();

			if(rhsABA == lhsABA && rhsIdx < lhsIdx){
				// both in the same Block
				retVal = true;
			}else if(rhsABA+1 == lhsABA && rhsIdx >= lhsIdx){
				// lhs (e.g. writer) one Block ahead
				// rhs.Idx == lhs.Idx => queue is full
				retVal = true;
			}

			return retVal;
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
	bool isOptimized() const { return false; }

	this_type& operator++(){
		if(getIndex() >= NumElements-1){
			setIndex(0);
			value += SPLIT_BIT;
		}else{
			setIndex(getIndex()+1);
		}
		return *this;

	}
	ValueType getABACounter() const{
		return value & ~INDEX_MASK;
	}
	void setABACounter(ValueType counter){
		value = (value & INDEX_MASK) + (counter &~INDEX_MASK);
	}
	/**
		 * defines a follow up relation of two positions
		 * lhs.isbehind(rhs)
		 * lhs (this) is behind rhs if it is in the same block (same ABACount)
		 * and it큦 index is less than rhs.getIndex()
		 * or
		 * lhs is in the previous block and it큦 index is greater or equal than rhs.getIndex()
		 *
		 * must be implemented consistently with operator==()
		 * uses unsigned overflow to turn ABACounter infinitely around
		 */
		bool isBehind(this_type rhs)const{
			bool retVal{false};
			std::size_t rhsIdx = getIndex();
			std::size_t lhsIdx = rhs.getIndex();
			ValueType rhsABA = getABACounter();
			ValueType lhsABA = rhs.getABACounter();

			if(rhsABA == lhsABA && rhsIdx < lhsIdx){
				// both in the same Block
				retVal = true;
			}else if(rhsABA+SPLIT_BIT == lhsABA && rhsIdx >= lhsIdx){
				// lhs (e.g. writer) one Block ahead
				// rhs.Idx == lhs.Idx => queue is full
				retVal = true;
			}

			return retVal;
		}
	using base_type::INDEX_MASK;
	using base_type::SPLIT_BIT;
	using base_type::getIndex;
	using base_type::setIndex;
	using base_type::getValue;
protected:
	using base_type::value;
};

// special case for one element
//template<bool isPowerOfTwo>
//class RingbufferPosition<1, isPowerOfTwo> : public RingbufferPosition<1, false>{};

#endif /* INCLUDE_BASICBUILDINGBLOCKS_RINGBUFFERPOSITION_H_ */
