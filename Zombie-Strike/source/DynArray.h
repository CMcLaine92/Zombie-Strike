#pragma once

template <class Type>
class DynArray
{
	unsigned int m_size, m_capacity;
	Type* m_arr;

public:
	DynArray() : m_size(0), m_capacity(0), m_arr(nullptr) {}
	~DynArray();
	DynArray(const DynArray<Type>& that);
	DynArray<Type>& operator=(const DynArray<Type>& that);


	//Accessors
	unsigned int size() const { return m_size; }
	unsigned int capacity() const { return m_capacity; }

	//Mutators
	Type& operator[](const unsigned int index);
	const Type& operator[](const unsigned int index) const;
	void append(const Type& item);
	void reserve(const unsigned int & newCap = 0);
	void clear();
};

template <typename Type>
DynArray<Type>::~DynArray()
{
	clear();
}

template <typename Type>
DynArray<Type>::DynArray(const DynArray<Type>& that)
{
	m_capacity = that.capacity();
	m_arr = new Type[m_capacity];
	m_size = that.size();
	for (size_t i = 0; i < m_size; i++)
	{
		m_arr[i] = that.m_arr[i];
	}
}

template <typename Type>
DynArray<Type>& DynArray<Type>::operator=(const DynArray<Type>& that)
{
	if (this != &that)
	{
		clear();
		m_capacity = that.capacity();
		m_arr = new Type[m_capacity];
		m_size = that.size();
		for (size_t i = 0; i < m_size; i++)
		{
			m_arr[i] = that.m_arr[i];
		}
	}
	return *this;
}

//Mutators
template <typename Type>
Type& DynArray<Type>::operator[](const unsigned int index)
{
	return m_arr[index];
}

template <typename Type>
const Type& DynArray<Type>::operator[](const unsigned int index) const
{
	return m_arr[index];
}

template <typename Type>
void DynArray<Type>::append(const Type& item)
{
	if (m_size == m_capacity)
	{
		if (m_capacity == 0)
			m_capacity++;
		else
			m_capacity *= 2;

		Type* temp = new Type[m_capacity];

		for (size_t i = 0; i < m_size; i++)
		{
			temp[i] = m_arr[i];
		}
		
		delete[] m_arr;
		m_arr = temp;
	}
	m_arr[m_size] = item;
	m_size++;
}

template <typename Type>
void DynArray<Type>::reserve(const unsigned int & newCap = 0)
{
	if (!newCap)
	{
		if (!m_capacity)
			m_capacity = 1;
		else
			m_capacity *= 2;
	}
	else if (newCap <= m_capacity)
		return;
	else
		m_capacity = newCap;

	Type* temp = new Type[m_capacity];
	for (size_t i = 0; i < m_size; i++)
	{
		temp[i] = m_arr[i];
	}
	delete[] m_arr;

	m_arr = temp;
}

template <typename Type>
void DynArray<Type>::clear()
{
	delete[] m_arr;
	m_arr = NULL;
	m_capacity = 0;
	m_size = 0;
}

