#pragma once


struct TypeDescriptor
{
	std::string m_Name;
	size_t m_Size;

	TypeDescriptor(const char* name, size_t size) : m_Size(size) {
		m_Name = name;
	}

	const std::string& GetFullName() const { return m_Name; }

	virtual void dump(const void* obj) const {}

	friend std::ostream& operator<<(std::ostream& out, const TypeDescriptor& descriptor);
};

inline std::ostream& operator<<(std::ostream& out, const TypeDescriptor& descriptor)
{
	return out << " : size = " << descriptor.m_Size ;
}

template<typename T>
TypeDescriptor* getPrimitiveDescriptor();

template<typename T>
class HasReflectionMemeber
{
	using yes = char;
	using no = long;
	template<typename U> static yes test(decltype(&U::Reflection));
	template<typename U> static no test(...);
public:
	static constexpr bool value = sizeof(test<T>(0)) == sizeof(yes);
};


struct DefaultSolver
{
	template<typename T, typename std::enable_if<HasReflectionMemeber<T>::value, long>::type = 0>
	static TypeDescriptor* get()
	{
		return &T::Reflection;
	}

	template<typename T, typename std::enable_if<!HasReflectionMemeber<T>::value, long>::type = 0>
	static TypeDescriptor* get()
	{
		return getPrimitiveDescriptor<T>();
	}
};

//public type solver
template<typename T>
struct TypeResolver
{
	static TypeDescriptor* get()
	{
		return DefaultSolver::get<T>();
	}
};

