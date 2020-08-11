

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

	list (size_t _sz, const ValueType &val, const AllocType &alloc = std::allocator<ValueType> ());
	
	list (const list &other);
	list (list &&other);

	list &operator= (const list &other);
	list &operator= (list &&other);

	~list () { destroy (); }
};



template <typename ValueType, typename AllocType>
void list<ValueType, AllocType>::destroy ()
{
	Node *next    = head;
	Node *current = head;
	for (size_t i = 0; i < sz; ++i)
	{
		next = current->next;
		traits::destroy (allocator, current);
		traits::deallocate (allocator, current, 1);
		current = next;
	}
}



template <typename ValueType, typename AllocType>
list (size_t _sz, const ValueType &val, const AllocType &alloc) :
	sz (_sz),
	allocator (alloc)
{
	if (count != 0)
	{
		head = traits::allocate (allocator, 1);
		traits::construct (allocator, head, val);
		Node *current   = head;
		Node * previous = head;
		for (size_t i = 1; i < _sz; ++i)
		{
			current = traits::allocate (allocator, 1);
			traits::construct (allocator, current, val);
			previous->next = current;
			current->next = previous;
			previous = current;
		}
		tail = current;
	}
}



template <typename ValueType, typename AllocType>
list<ValueType, AllocType>::list (const list &other) :
	sz (other.sz),
	allocator (other.allocator)
{
	if (sz != 0)
	{
		head = traits::allocate (allocator, 1);
		traits::construct (allocator, head, other.head->data);
		Node *current    = head;
		Node *previous   = head;
		Node *other_next = other.head;
		for (size_t i = 1; i < sz; ++i)
		{
			current = traits::allocate (allocator, 1);
			traits::construct (allocator, current, other_next->data);
			previous->next = current;
			current->prev = previous;
			previous = current;
			other_next = other_next->next;
		}
		tail = current;
	}
}



template <typename ValueType, typename AllocType>
list<ValueType, AllocType>::list (list &&other) :
	sz (other.sz),
	allocator (std::move (other.allocator)),
	head (other.head),
	tail (other.tail)
{
	other.head = nullptr;
	other.tail = nullptr;
}



template <typename ValueType, typename AllocType>
list<ValueType, AllocType> &list<ValueType,AllocType>::operator= (const list &other)
{
	if (this == &other)
		return *this;

	//Node *current    = nullptr;
	//Node *previous   = nullptr;
	//Node *other_curr = other.head;

	destroy ();

	if (traits::propagate_on_container_copy_assignment::value)
		allocator = other.allocator;

	sz = other.sz;

	if (sz != 0)
	{
		head = traits::allocate (allocator, 1);
		traits::construct (allocator, head, other.head->data);
		Node *current    = head;
		Node *previous   = head;
		Node *other_next = other.head;
		for (size_t i = 1; i < sz; ++i)
		{
			current = traits::allocate (allocator, 1);
			traits::construct (allocator, current, other_next->data);
			previous->next = current;
			current->prev = previous;
			previous = current;
			other_next = other_next->next;
		}
		tail = current;
	}

	return *this;
}



template <typename ValueType, typename AllocType>
list<ValueType, AllocType> &list<ValueType, AllocType>::operator= (list&& other)
{
	if (this == &other)
		return *this;

	destroy ();

	sz = other.sz;

	if (allocator != other.allocator && !traits::propagate_on_container_move_assignment::value)
	{
		//Node *current = nullptr;
		//Node *previous = nullptr;
		//Node *other_curr = other.head;

		if (sz != 0)
		{
			head = traits::allocate (allocator, 1);
			traits::construct (allocator, head, other.head->data);
			Node *current    = head;
			Node *previous   = head;
			Node *other_next = other.head;
			for (size_t i = 1; i < sz; ++i)
			{
				current = traits::allocate (allocator, 1);
				traits::construct (allocator, current, other_next->data);
				previous->next = current;
				current->prev = previous;
				previous = current;
				other_next = other_next->next;
			}
			tail = current;
		}
	}
	else
	{
		if (traits::propagate_on_container_move_assignment::value)
			allocator = std::move (other.allocator);
		head = other.head;
		tail = other.tail;
	}
	return *this;
}