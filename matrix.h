#ifndef MATRIX_H
#define MATRIX_H
#include <vector>
#include <map>
#include <memory>
#include <fstream>
#include "vecIterator.h"

template <typename T, T DEFAULT_VALUE, size_t DIMENSIONS = 2>
class Matrix
{
	using iterator = VecIterator<T>;
	using const_iterator = VecIterator<const T>;
	using reverse_iterator =  VecIterator<T>;
	using const_reverse_iterator =  VecIterator<const T>;

	using Storage = std::map<std::vector<size_t>, T>;
public:
	Matrix()
		: m_Storage(std::make_shared<Storage>())
		, m_InternalMatrix(std::make_shared<Matrix<T, DEFAULT_VALUE, DIMENSIONS - 1>>(m_Storage, m_Position))
	{

	}
	Matrix(std::shared_ptr<Storage> storage,
		   std::vector<size_t> position)
		: m_Storage(storage)
		, m_Position(std::move(position))
		, m_InternalMatrix(std::make_shared<Matrix<T, DEFAULT_VALUE, DIMENSIONS - 1>>(m_Storage, m_Position))
	{}
	~Matrix()
	{
		clear();
	}
	void clear()
	{
		m_Storage->clear();
		m_Position.clear();
		m_InternalMatrix->clear();
	}
	const Matrix<T, DEFAULT_VALUE, DIMENSIONS - 1>& operator[](const size_t index) const
	{
		std::vector<size_t> internal_position = m_Position;
		internal_position.push_back(index);
		return *(new Matrix<T, DEFAULT_VALUE, DIMENSIONS - 1>(m_Storage, internal_position));
	}
	Matrix<T, DEFAULT_VALUE, DIMENSIONS - 1>& operator[](const size_t index)
	{
		std::vector<size_t> internal_position = m_Position;
		internal_position.push_back(index);
		return *(new Matrix<T, DEFAULT_VALUE, DIMENSIONS - 1>(m_Storage, internal_position));
	}
	size_t size() const
	{
		return m_Storage->size();
	}
	bool empty() const
	{
		return m_Storage->empty();
	}

private:
	std::shared_ptr<Storage> m_Storage;
	std::vector<size_t> m_Position;
	std::shared_ptr<Matrix<T, DEFAULT_VALUE, DIMENSIONS - 1>> m_InternalMatrix;
};

template <typename T, T DEFAULT_VALUE>
class Matrix<T, DEFAULT_VALUE, 0>
{
	using Storage = std::map<std::vector<size_t>, T>;
public:
	Matrix(std::shared_ptr<Storage> storage,
		   std::vector<size_t> position)
		: m_Storage(storage), m_Position(std::move(position))
	{}
	Matrix<T, DEFAULT_VALUE, 0>& operator= (const T &value)
	{
		if (value == DEFAULT_VALUE)
			m_Storage->erase(m_Position);
		else
			(*m_Storage)[m_Position] = value;
		return *this;
	};
	bool operator==(const T& value) const
	{
		if (m_Storage->find(m_Position) == m_Storage->end())
		{
			return DEFAULT_VALUE == value;
		}
		return m_Storage->at(m_Position) == value;
	}
	T operator() () const
	{
		if (m_Storage->find(m_Position) == m_Storage->end())
		{
			return DEFAULT_VALUE;
		}
		return m_Storage->at(m_Position);
	}
	friend std::ostream& operator<< (std::ostream& out,
									const Matrix<T, DEFAULT_VALUE, 0>& matrix)
	{
	  return out << matrix();
	}
	void clear()
	{
		m_Storage->clear();
		m_Position.clear();
	}
private:
	std::shared_ptr<Storage> m_Storage;
	std::vector<size_t> m_Position;
};


#endif // MATRIX_H
