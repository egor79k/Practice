

template <typename ValueType, typename AllocType = std::allocator<ValueType>>
class list
{
private:
	struct Node
	{
		Node () = delete;
		Node (const ValueType &val) : value (val), next (nullptr), prev (nullptr) {}
		Node (ValueType &&val) : value(val), next(nullptr), prev(nullptr) {}
		~Node () = default;

		ValueType value;
		Node *next;
		Node *prev;
	};

	using Alloc  = typename std::allocator_traits<AllocType>::template rebind_alloc<Node>;
	using traits = std::allocator_traits<Alloc>;


	Node *head;
	Node *tail;
	size_t sz;
	AllocType allocator;

public:
	list (const AllocType &alloc = std::allocator<ValueType> ()) :
		head (nullptr),
		tail (nullptr),
		sz (0),
		allocator (alloc)
	{}

};