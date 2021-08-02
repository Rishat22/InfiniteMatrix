#ifndef MATRIX_H
#define MATRIX_H
#include <vector>
#include <map>
#include <memory>
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
		, m_InternalMatrix(new Matrix<T, DEFAULT_VALUE, DIMENSIONS - 1>(m_Storage))
	{

	}
	Matrix(std::shared_ptr<Storage> storage,
		   std::vector<int> position)
		: m_Storage(storage)
		, m_InternalMatrix(new Matrix<T, DEFAULT_VALUE, DIMENSIONS - 1>(m_Storage))
	{}
	~Matrix()
	{
		clear();
	}
	void setPosition()
	{
		m_Storage.clear();
	}
	void clear()
	{
		m_Storage.clear();
	}
	const Matrix<T, DEFAULT_VALUE>& operator[](const size_t index) const
	{
		std::vector<size_t> child_position;
		std::copy(m_Position.begin(),m_Position.end(), std::back_inserter(child_position));
		child_position.push_back(index);
//		return *(new Matrix(m_Storage, child_position));
		return *m_InternalMatrix;
	}
	Matrix<T, DEFAULT_VALUE>& operator[](const size_t index)
	{
		std::vector<size_t> child_position;
		std::copy(m_Position.begin(),m_Position.end(), std::back_inserter(child_position));
		child_position.push_back(index);
		return *m_InternalMatrix;
	}
	size_t Size() const
	{
		return m_Storage.size();
	}
	bool Empty() const
	{
		return m_Storage.empty();
	}

private:
	std::shared_ptr<Matrix> m_InternalMatrix;
	std::shared_ptr<Storage> m_Storage;
	std::vector<size_t> m_Position;
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
			m_Storage.get()[m_Position] = value;
		return *this;
	};
	bool operator==(const T& value) const
	{
		if (m_Storage->find(m_Position) == m_Storage->end())
		{
			return DEFAULT_VALUE == value;
		}
		return m_Storage(m_Position) == value;
	}
	explicit operator T() const
	{
		if (m_Storage->find(m_Position) == m_Storage->end())
		{
			return DEFAULT_VALUE;
		}
		return m_Storage(m_Position);
	}
	friend std::ostream& operator<< (std::ostream& out,
									const Matrix<T, DEFAULT_VALUE, 0>& matrix)
	{
	  return out << matrix();
	}
private:
	std::shared_ptr<Storage> m_Storage;
	std::vector<size_t> m_Position;
};


#endif // MATRIX_H
