#include <memory>

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
	Alloc allocator;

	void destroy ();



public:
	void print() {
        Node* current = head;
        std::cout << "\nsize:" << sz << '\n';
        for (size_t i = 0; i < sz; ++i){
            std::cout << current->value << ' ';
            current = current->next;
        }
        std::cout << std::endl;
    }

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


	void push_back  (const ValueType &val);
	void pop_back   ();
	void push_front (const ValueType &val);
	void pop_front  ();


	#ifdef BIDIRECTIONAL_ITERATOR_INCLUDED
	typedef bidirectional_iterator<Node> iterator;

	iterator &begin ()
	{ iterator (head); }

	const iterator &begin () const
	{ iterator (head); }


	iterator &end ()
	{ iterator (tail); }

	const iterator &end () const
	{ iterator (tail); }
	
	#endif
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
list<ValueType, AllocType>::list (size_t _sz, const ValueType &val, const AllocType &alloc) :
	sz (_sz),
	allocator (alloc)
{
	if (sz != 0)
	{
		head = traits::allocate (allocator, 1);
		traits::construct (allocator, head, val);
		Node *current   = head;
		Node *previous  = head;
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
		traits::construct (allocator, head, other.head->value);
		Node *current    = head;
		Node *previous   = head;
		Node *other_next = other.head;
		for (size_t i = 1; i < sz; ++i)
		{
			current = traits::allocate (allocator, 1);
			traits::construct (allocator, current, other_next->value);
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

	destroy ();

	if (traits::propagate_on_container_copy_assignment::value)
		allocator = other.allocator;

	sz = other.sz;

	if (sz != 0)
	{
		head = traits::allocate (allocator, 1);
		traits::construct (allocator, head, other.head->value);
		Node *current    = head;
		Node *previous   = head;
		Node *other_next = other.head;
		for (size_t i = 1; i < sz; ++i)
		{
			current = traits::allocate (allocator, 1);
			traits::construct (allocator, current, other_next->value);
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
		if (sz != 0)
		{
			head = traits::allocate (allocator, 1);
			traits::construct (allocator, head, other.head->value);
			Node *current    = head;
			Node *previous   = head;
			Node *other_next = other.head;
			for (size_t i = 1; i < sz; ++i)
			{
				current = traits::allocate (allocator, 1);
				traits::construct (allocator, current, other_next->value);
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



template <typename ValueType, typename AllocType>
void list<ValueType, AllocType>::push_back (const ValueType &val)
{
	tail->next = traits::allocate (allocator, 1);
	traits::construct (allocator, tail->next, val);
	tail->next->prev = tail;
	tail = tail->next;
	++sz;
}



template <typename ValueType, typename AllocType>
void list<ValueType, AllocType>::pop_back ()
{
	Node *new_tail = tail->prev;
	traits::destroy (allocator, tail);
	traits::deallocate (allocator, tail, 1);
	tail = new_tail;
	--sz;
}



template <typename ValueType, typename AllocType>
void list<ValueType, AllocType>::push_front (const ValueType &val)
{
	head->prev = traits::allocate (allocator, 1);
	traits::construct (allocator, head->prev, val);
	head->prev->next = head;
	head = head->prev;
	++sz;
}



template <typename ValueType, typename AllocType>
void list<ValueType, AllocType>::pop_front ()
{
	Node *new_head = head->next;
	traits::destroy (allocator, head);
	traits::deallocate (allocator, head, 1);
	head = new_head;
	--sz;
}