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


	random_access_iterator &operator++ () noexcept
	{
		++ptr;
		return *this;
	}

	random_access_iterator operator++ (int) noexcept
	{ return random_access_iterator (ptr++); }

	random_access_iterator &operator-- () noexcept
	{
		--ptr;
		return *this;
	}

	random_access_iterator operator-- (int) noexcept
	{ return random_access_iterator (ptr--); }


	ValueType &operator[] (size_t index) const noexcept
	{ return ptr[index]; }


	random_access_iterator &operator+= (int value) noexcept
	{
		ptr += value;
		return *this;
	}

	random_access_iterator &operator-= (int value) noexcept
	{
		ptr -= value;
		return *this;
	}


	random_access_iterator operator+ (int value) const noexcept
	{ return random_access_iterator (ptr + value); }

	random_access_iterator operator- (int value) const noexcept
	{ return random_access_iterator (ptr - value); }


	const ValueType *base () const noexcept
	{ return ptr; }
};



template <typename ValueType>
inline bool operator== (const random_access_iterator<ValueType> &left, const random_access_iterator<ValueType> &right) noexcept
{ return left.base() == right.base (); }

template <typename ValueType>
inline bool operator!= (const random_access_iterator<ValueType> &left, const random_access_iterator<ValueType> &right) noexcept
{ return left.base() != right.base (); }

template <typename ValueType>
inline bool operator< (const random_access_iterator<ValueType> &left, const random_access_iterator<ValueType> &right) noexcept
{ return left.base() < right.base (); }

template <typename ValueType>
inline bool operator> (const random_access_iterator<ValueType> &left, const random_access_iterator<ValueType> &right) noexcept
{ return left.base() > right.base (); }

template <typename ValueType>
inline bool operator<= (const random_access_iterator<ValueType> &left, const random_access_iterator<ValueType> &right) noexcept
{ return left.base() <= right.base (); }

template <typename ValueType>
inline bool operator>= (const random_access_iterator<ValueType> &left, const random_access_iterator<ValueType> &right) noexcept
{ return left.base() >= right.base (); }



template <typename ValueType>
inline int operator- (const random_access_iterator<ValueType> &left, const random_access_iterator<ValueType> &right) noexcept
{ return left.base() - right.base (); }

template <typename ValueType>
inline random_access_iterator<ValueType> operator+ (int left, const random_access_iterator<ValueType> &right) noexcept
{ return random_access_iterator<ValueType> (right.base () + left); }


#endif // RANDOM_ACCESS_ITERATOR_INCLUDED