
template <typename ValType, size_t Nm>
struct array_traits
{
	typedef ValType ArrType[Nm];

	static constexpr ValType &get_reference (const ArrType &arr, size_t n) noexcept
	{
		return const_cast<ValType &> (arr[n]);
	}

	static constexpr ValType *get_pointer (const ArrType *arr) noexcept
	{
		return const_cast<ValType *> (arr);
	}
};



template <typename ValType>
struct array_traits<ValType, 0>
{
	struct ArrType {};

	static constexpr ValType &get_reference (const ArrType &arr, size_t n) noexcept
	{
		return const_cast<ValType &> (nullptr);
	}

	static constexpr ValType *get_pointer (const ArrType *arr) noexcept
	{
		return nullptr;
	}
};



template <typename ValType, size_t Nm>
class array
{
private:

	typedef typename array_traits<ValType, Nm>::ArrType ArrType;

	ArrType arr;


public:

	constexpr ValType &at (size_t index)
	{
		if (index >= Nm)
			throw std::runtime_error ("Index above size in at() function");
		return operator[] (index);
	}

	constexpr const ValType &at (size_t index) const
	{
		if (index >= Nm)
			throw std::runtime_error ("Index above size in at() function");
		return operator[] (index);
	}


	constexpr ValType &operator[] (size_t index)
	{
		return array_traits<ValType, Nm>::get_reference (arr, index);
	}

	constexpr const ValType &operator[] (size_t index) const
	{
		return array_traits<ValType, Nm>::get_reference (arr, index);
	}


	constexpr ValType &front ()
	{
		return array_traits<ValType, Nm>::get_reference (arr, 0);
	}

	constexpr const ValType &front () const
	{
		return array_traits<ValType, Nm>::get_reference (arr, 0);
	}


	constexpr ValType &back ()
	{
		return array_traits<ValType, Nm>::get_reference (arr, Nm - 1);
	}

	constexpr const ValType &back () const
	{
		return array_traits<ValType, Nm>::get_reference (arr, Nm - 1);
	}


	constexpr ValType *data () noexcept
	{
		return array_traits<ValType, Nm>::get_pointer (arr);
	}

	constexpr const ValType *data () const noexcept
	{
		return array_traits<ValType, Nm>::get_pointer (arr);
	}


	constexpr bool empty () const noexcept
	{
		return Nm == 0;
	}


	constexpr size_t size () const noexcept
	{
		return Nm;
	}


	void fill (const ValType &val)
	{
		for (size_t i = 0; i < Nm; ++i)
			array_traits<ValType, Nm>::get_reference (arr, i) = val;
	}


	constexpr void swap (const ValType &val) noexcept(std::is_nothrow_swappable<ValType>())
	{
		for (size_t i = 0; i < Nm; ++i)
			std::swap (array_traits<ValType, Nm>::get_reference (arr, i), array_traits<ValType, Nm>::get_reference (other.arr, i));
	}
};