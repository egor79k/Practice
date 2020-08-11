#include <exception>
#include <iostream>




template <typename ValueType, typename AllocType = std::allocator<ValueType>>
class vector
{
private:
	using traits = std::allocator_traits<AllocType>;
	static const size_t DEFAULT_SIZE = 8;
	static const int CAPACITY_RESIZE_COEFF = 2;

	size_t sz;
	size_t cap;
	ValueType *data;
	AllocType allocator;

	void destruct ();

public:
	vector (const AllocType &alloc = AllocType ()) :
		sz (0),
		cap (DEFAULT_SIZE),
		data (traits::allocate (alloc, DEFAULT_SIZE)),
		allocator (alloc)
	{}
	
	vector (size_t sz, const ValueType &value = ValueType (), const AllocType &alloc = AllocType ());


	vector (const vector &other);
	vector (vector &&other);
	
	~vector () { destruct (); }
	
	vector &operator= (const vector &other) &;
	vector &operator= (vector &&other) &;


	void push_back (const ValueType & value);
	void pop_back  ();
	void resize    (size_t count);
	void reserve   (size_t count);


	size_t size () const { return sz; }

	size_t capacity () const { return cap; }

	bool empty () const { return sz == 0; }

	ValueType &operator[] (size_t index) { return data[index]; }
	const ValueType &operator[] (size_t index) const { return data[index]; }

	ValueType &at (size_t index);
	const ValueType &at (size_t index) const;

	ValueType &front () { return data[0]; }
	const ValueType &front () const { return data[0]; }

	ValueType &back () { return data[sz - 1]; }
	const ValueType &back () const { return data[sz - 1]; }

	//ValueType *data () noexcept { return datal; }
	//const ValueType *data () const noexcept { return datal; }
};



template <typename ValueType, typename AllocType>
void vector<ValueType, AllocType>::destruct ()
{
	for (size_t i = 0; i < sz; ++i)
		traits::destroy (allocator, data + i);
	traits::deallocate (allocator, data, cap);
}



template <typename ValueType, typename AllocType>
vector<ValueType, AllocType>::vector (size_t _sz, const ValueType &value, const AllocType &alloc) : 
	sz (_sz),
	cap (_sz),
	allocator (alloc),
	data (traits::allocate (allocator, _sz))
{
	for (size_t i = 0; i < _sz; ++i)
		traits::construct (allocator, data + i, value);
}



template <typename ValueType, typename AllocType>
vector<ValueType, AllocType>::vector (const vector &other) :
	sz (other.sz),
	cap (other.sz),
	data (traits::allocate (allocator, other.sz)),
	allocator (traits::select_on_container_copy_construction (other.allocator))
{
	for (size_t i = 0; i < sz; ++i)
		traits::construct (allocator, data + i, other.data[i]);
}



template <typename ValueType, typename AllocType>
vector<ValueType, AllocType>::vector (vector &&other) :
	sz (other.sz),
	cap (other.cap),
	data (other.data),
	allocator (other.allocator)
{
	other.sz = 0;
	other.cap = 0;
	other.data = nullptr;
}



template <typename ValueType, typename AllocType>
vector<ValueType, AllocType> &vector<ValueType, AllocType>::operator= (const vector &other) &
{
	if (this == &other)
		return *this;

	for (size_t i = 0; i < sz; ++i)
		traits::destroy (allocator, data + i);

	bool alloc_copy_required = traits::propagate_on_container_copy_assignment::value;
	bool realloc_required = (allocator != other.allocator && alloc_copy_required) || cap < other.sz;

	if (realloc_required)
		traits:: deallocate (allocator, data, cap);

	if (alloc_copy_required)
		allocator = other.allocator;

	if (realloc_required)
	{
		cap = other.sz;
		data = traits::allocate (allocator, cap);
	}

	sz = other.sz;

	for (size_t i = 0; i < sz; ++i)
		traits::construct (allocator, data + i, other.data[i]);

	return *this;
}



template <typename ValueType, typename AllocType>
vector<ValueType, AllocType> &vector<ValueType, AllocType>::operator= (vector &&other) &
{
	if (this == &other)
		return *this;

	if (allocator != other.allocator && !traits::propagate_on_container_move_assignment::value)
	{
		for (size_t i = 0; i < sz; ++i)
			traits::destroy (allocator, data + i);

		if (cap < other.sz)
		{
			traits::deallocate (allocator, data, cap);
			data = traits::allocate (allocator, other.sz);
			cap = other.sz;
		}

		sz = other.sz;

		for (size_t i = 0; i < sz; ++i)
			traits::construct (allocator, data + i, std::move (other.data[i]));

		other.destruct ();
	}
	else
	{
		destruct ();

		if (traits::propagate_on_container_move_assignment::value)
			allocator = std::move (other.allocator);

		data = other.data;
		sz = other.sz;
		cap = other.cap;
		other.data = nullptr;
		other.sz = 0;
		other.cap = 0;
	}

	return *this;
}



template <typename ValueType, typename AllocType>
void vector<ValueType, AllocType>::push_back (const ValueType &value)
{
	if (sz < cap)
	{
		traits::construct (allocator, data + sz, value);
		++sz;
	}
	else if (sz == cap)
	{
		size_t new_cap = cap * CAPACITY_RESIZE_COEFF;

		ValueType *new_data = traits::allocate (allocator, new_cap);

		traits::construct (allocator, new_data + sz, value);

		for (size_t i = 0; i < sz; ++i)
			traits::construct (allocator, new_data + i, std::move_if_noexcept (data[i]));

		destruct ();

		data = new_data;
		cap = new_cap;
		++sz;
	}
}



template <typename ValueType, typename AllocType>
void vector<ValueType, AllocType>::pop_back ()
{
	traits::destroy (allocator, data + sz - 1);
	--sz;
}



template <typename ValueType, typename AllocType>
void vector<ValueType, AllocType>::resize (size_t count)
{
	for (size_t i = count; i < sz; ++i)
		traits::destroy (allocator, data + i);

	for (size_t i = sz; i < count; ++i)
		push_back (ValueType ());

	sz = count;
}




template <typename ValueType, typename AllocType>
void vector<ValueType, AllocType>::reserve (size_t count)
{
	if (count < cap)
		return;

	ValueType *new_data = traits::allocate (allocator, count);

	for (size_t i = 0; i < sz; ++i)
		traits::construct (allocator, new_data + i, std::move_if_noexcept (data[i]));
	
	destruct ();

	data = new_data;
	cap = count;
}




template <typename ValueType, typename AllocType>
ValueType &vector<ValueType, AllocType>::at (size_t index)
{
	if (index >= sz)
		throw std::out_of_range ("Index is out of range!");
	return operator[](index);
}



template <typename ValueType, typename AllocType>
const ValueType &vector<ValueType, AllocType>::at (size_t index) const
{
	if (index >= sz)
		throw std::out_of_range ("Index is out of range!");
	return operator[](index);
}