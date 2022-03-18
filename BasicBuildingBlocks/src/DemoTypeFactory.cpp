/*
 * experiment mit named parameters for templates
 * & type factory
 */
#include <iostream>
#include <type_traits>

struct Single;
struct Multi;
struct Other; // for testing static_assesrt

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
struct TypeFactory{
	using Producer = ProducerType_;
	using Consumer= ConsumerType_;
	using this_type = TypeFactory<Producer, Consumer>;

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
		using type = TypeFactory<MultiProducer, typename Types::Consumer>;
	};
	template<class Types>
	struct setProducerImpl<Single, Types>{
		using type = TypeFactory<SingleProducer, typename Types::Consumer>;
	};
//--------------
	template<class ConsumerType, class Types>
	struct setConsumerImpl{
		static_assert(std::is_same_v<ConsumerType, Single> || std::is_same_v<ConsumerType, Multi>,
						"ConsumerType must be of Single or Multi");
	};
	template<class Types>
	struct setConsumerImpl<Multi, Types>{
		using type = TypeFactory<typename Types::Producer, MultiConsumer>;
	};
	template<class Types>
	struct setConsumerImpl<Single, Types>{
		using type = TypeFactory<typename Types::Producer, SingleConsumer>;
	};

public:
	template<class ProducerType>
	using setProducer = typename this_type::template setProducerImpl<ProducerType, this_type>::type;

	template<class ConsumerType>
	using setConsumer = typename this_type::template setConsumerImpl<ConsumerType, this_type>::type;

};


using namespace std;

void demoTypeFactory(){
	cout << __PRETTY_FUNCTION__ << endl;
//		using MyTypeFactory = TypeFactory<>::setProducer<Other>;

	using DefaultTypeFactory = TypeFactory<>;
	cout << "=== Multi Multi" << endl;
	{
		using MyTypeFactory = DefaultTypeFactory;
		MyTypeFactory::Producer::print();
		MyTypeFactory::Consumer::print();
	}
	cout << "=== Single Multi" << endl;
	{
		using MyTypeFactory = DefaultTypeFactory
				::setProducer<Single>
		;

		MyTypeFactory::Producer::print();
		MyTypeFactory::Consumer::print();
	}
	cout << "=== Single Single" << endl;
	{
		using MyTypeFactory = DefaultTypeFactory
				::setConsumer<Single>
				::setProducer<Single>
		;

		MyTypeFactory::Producer::print();
		MyTypeFactory::Consumer::print();
	}
	cout << "=== Multi Single" << endl;
	{
		using MyTypeFactory = DefaultTypeFactory
				::setConsumer<Single>
				::setProducer<Multi>
		;

		MyTypeFactory::Producer::print();
		MyTypeFactory::Consumer::print();
	}
	cout << "=== Multi Single - Single Multi" << endl;
	{
		using MyTypeFactory = DefaultTypeFactory
				::setConsumer<Single>
				::setProducer<Multi>
		;
		using AnotherFactory =  MyTypeFactory
				::setProducer<Single>
				::setConsumer<Multi>
		;

		MyTypeFactory::Producer::print();
		MyTypeFactory::Consumer::print();
		AnotherFactory::Producer::print();
		AnotherFactory::Consumer::print();
	}
}
