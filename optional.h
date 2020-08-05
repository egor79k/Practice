template <typename T>
class optional
{
private:
	T value;
	bool is_correct = false;

public:
	constexpr optional () noexcept {}

	constexpr optional (std::nullopt) noexcept
	{
		is_correct = false;
	}

	constexpr optional (const optional &other)
	{
		if (other.is_correct) value = other.value;
		is_correct = other.is_correct;
	}

	constexpr optional &operator= (std::nullopt) noexcept
	{
		is_correct = false;
	}

	constexpr optional &operator= (const optional &other)
	{
		if (other.is_correct) value = other.value;
		is_correct = other.is_correct;
	}
};