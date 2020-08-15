#ifndef RANDOM_ACCESS_ITERATOR_INCLUDED
#define RANDOM_ACCESS_ITERATOR_INCLUDED
template <typename ValueType>
class random_access_iterator: public std::iterator_traits<ValueType>
{
private:
	ValueType *ptr;

public:
	explicit random_access_iterator (ValueType *pointer) : ptr (pointer) {}

	ValueType &operator* () const noexcept
	{ return *ptr; }

	ValueType *operator-> () const noexcept
	{ return ptr; }

	random_access_iterator operator++ () noexcept
	{
		++ptr;
		return *this;
	}

	random_access_iterator operator++ (int) noexcept
	{ return random_access_iterator (ptr++); }

	random_access_iterator operator-- () noexcept
	{
		--ptr;
		return *this;
	}

	random_access_iterator operator-- (int) noexcept
	{ return random_access_iterator (ptr--); }	
};


#endif // RANDOM_ACCESS_ITERATOR_INCLUDED