#ifndef INCLUDE_BASICBUILDINGBLOCKS_TYPEBUILDER_H_
#define INCLUDE_BASICBUILDINGBLOCKS_TYPEBUILDER_H_

#include <iostream>

struct Single;
struct Multi;
struct Other; // for testing static_assesrt

template<class ElementType, std::size_t MaxElements, class ProducerType, class ConsumerType>
struct Queue;

template<class ElementType, std::size_t MaxElements>
struct Queue<ElementType, MaxElements, Multi, Multi>{
	void print() { std::cout << "MultiProducerMultiConsumerLockfreeQueue" << std::endl; }
};
template<class ElementType, std::size_t MaxElements>
struct Queue<ElementType, MaxElements, Single, Multi>{
	void print() { std::cout << "SingleProducerMultiConsumerLockfreeQueue" << std::endl; }
};
template<class ElementType, std::size_t MaxElements>
struct Queue<ElementType, MaxElements, Multi, Single>{
	void print() { std::cout << "MultiProducerSingleConsumerLockfreeQueue" << std::endl; }
};
template<class ElementType, std::size_t MaxElements>
struct Queue<ElementType, MaxElements, Single, Single>{
	void print() { std::cout << "SingleProducerSingleConsumerLockfreeQueue" << std::endl; }
};

template<class ProducerType=Multi, class ConsumerType=Multi>
struct TypeRepository{
	using Producer = ProducerType;
	using Consumer = ConsumerType;
};

template<class TypeRepository_=TypeRepository<>>
struct TypeBuilder2{
	using Properties = TypeRepository_;
	using this_type = TypeBuilder2<Properties>;
//--------------
	template<class ProducerType, class Builder>
	struct setProducerImpl{
		static_assert(std::is_same_v<ProducerType, Single> || std::is_same_v<ProducerType, Multi>,
				"ProducerType must be of Single or Multi");
	};

	template<class Builder>
	struct setProducerImpl<Multi, Builder>{
		using type = TypeBuilder2<TypeRepository<Multi, typename Builder::Properties::Consumer>>;
	};
	template<class Builder>
	struct setProducerImpl<Single, Builder>{
		using type = TypeBuilder2<TypeRepository<Single, typename Builder::Properties::Consumer>>;
	};
//--------------
	template<class ConsumerType, class Builder>
	struct setConsumerImpl{
		static_assert(std::is_same_v<ConsumerType, Single> || std::is_same_v<ConsumerType, Multi>,
						"ConsumerType must be of Single or Multi");
	};
	template<class Builder>
	struct setConsumerImpl<Multi, Builder>{
		using type = TypeBuilder2<TypeRepository<typename Builder::Properties::Producer, Multi>>;
	};
	template<class Builder>
	struct setConsumerImpl<Single, Builder>{
		using type = TypeBuilder2<TypeRepository<typename Builder::Properties::Producer, Single>>;
	};

public:
	template<class ProducerType>
	using setProducer = typename this_type::template setProducerImpl<ProducerType, this_type>::type;

	template<class ConsumerType>
	using setConsumer = typename this_type::template setConsumerImpl<ConsumerType, this_type>::type;

	template<class ElementType, std::size_t MaxElements>
	using getQueue = Queue<ElementType, MaxElements,
			typename Properties::Producer, typename Properties::Consumer>;

};


//===================================================================
// Single/Multi Producer/Consumer types
struct SingleProducer{
	static void print() { std::cout << "SingleProducer" << std::endl; }
};
struct MultiProducer{
	static void print() { std::cout << "MultiProducer" << std::endl; }
};
struct SingleConsumer{
	static void print() { std::cout << "SingleConsumer" << std::endl; }
};
struct MultiConsumer{
	static void print() { std::cout << "MultiConsumer" << std::endl; }
};


// TypeFactory creates Producer & Consumer types see demo
// with setProducer<Single/Multi> & setConsumer<Single/Multi>
// in arbitrary order
template<class ProducerType_=MultiProducer, class ConsumerType_=MultiConsumer>
struct TypeBuilder{
	using Producer = ProducerType_;
	using Consumer= ConsumerType_;
	using this_type = TypeBuilder<Producer, Consumer>;

//--------------
private:
	// generic programming member-type-functions
	template<class ProducerType, class Types>
	struct setProducerImpl{
		static_assert(std::is_same_v<ProducerType, Single> || std::is_same_v<ProducerType, Multi>,
				"ProducerType must be of Single or Multi");
	};
	template<class Types>
	struct setProducerImpl<Multi, Types>{
		using type = TypeBuilder<MultiProducer, typename Types::Consumer>;
	};
	template<class Types>
	struct setProducerImpl<Single, Types>{
		using type = TypeBuilder<SingleProducer, typename Types::Consumer>;
	};
//--------------
	template<class ConsumerType, class Types>
	struct setConsumerImpl{
		static_assert(std::is_same_v<ConsumerType, Single> || std::is_same_v<ConsumerType, Multi>,
						"ConsumerType must be of Single or Multi");
	};
	template<class Types>
	struct setConsumerImpl<Multi, Types>{
		using type = TypeBuilder<typename Types::Producer, MultiConsumer>;
	};
	template<class Types>
	struct setConsumerImpl<Single, Types>{
		using type = TypeBuilder<typename Types::Producer, SingleConsumer>;
	};

public:
	template<class ProducerType>
	using setProducer = typename this_type::template setProducerImpl<ProducerType, this_type>::type;

	template<class ConsumerType>
	using setConsumer = typename this_type::template setConsumerImpl<ConsumerType, this_type>::type;

};





#endif /* INCLUDE_BASICBUILDINGBLOCKS_TYPEBUILDER_H_ */
