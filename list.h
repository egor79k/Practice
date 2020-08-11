

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

	void destroy ();

public:
	list (const AllocType &alloc = std::allocator<ValueType> ()) :
		head (nullptr),
		tail (nullptr),
		sz (0),
		allocator (alloc)
	{}

	list (size_t size, const ValueType &val, const AllocType &alloc = std::allocator<ValueType> ());
	
	list (const list &other);
	list (list &&other);

	list &operator= (const list &other);
	list &operator= (list &&other);

	~list () { destroy (); }
};