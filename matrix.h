#ifndef MATRIX_H
#define MATRIX_H
#include <vector>
#include <map>
#include <memory>
#include <fstream>

template <typename T, T DEFAULT_VALUE, size_t DIMENSIONS = 2>
class Matrix
{
	using Storage = std::map<std::vector<size_t>, T>;
public:
	Matrix()
		: m_Storage(std::make_shared<Storage>())
		, m_InternalMatrix(std::make_unique<Matrix<T, DEFAULT_VALUE, DIMENSIONS - 1>>(m_Storage, m_Position))
	{

	}
	Matrix(std::shared_ptr<Storage> storage,
		   std::vector<size_t> position)
		: m_Storage(storage)
		, m_Position(std::move(position))
		, m_InternalMatrix(std::make_unique<Matrix<T, DEFAULT_VALUE, DIMENSIONS - 1>>(m_Storage, m_Position))
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
	Matrix<T, DEFAULT_VALUE, DIMENSIONS - 1>& operator[](const size_t index)
	{
		m_InternalMatrix->m_Storage = m_Storage;
		std::vector<size_t> internal_position = m_Position;
		internal_position.push_back(index);
		m_InternalMatrix->m_Position = internal_position;
		return *m_InternalMatrix;
	}
	size_t size() const
	{
		return m_Storage->size();
	}
	bool empty() const
	{
		return m_Storage->empty();
	}
	/* Iterators */
	auto begin() const { return m_Storage->begin(); }
	auto end() const { return m_Storage->end(); }
	auto cbegin() const { return m_Storage->cbegin();}
	auto cend() const { return m_Storage->cend();}

	friend class Matrix<T, DEFAULT_VALUE, DIMENSIONS + 1>;
private:
	std::shared_ptr<Storage> m_Storage;
	std::vector<size_t> m_Position;
	std::unique_ptr<Matrix<T, DEFAULT_VALUE, DIMENSIONS - 1>> m_InternalMatrix;
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
		return this->operator()() == value;
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

	friend class Matrix<T, DEFAULT_VALUE, 1>;
private:
	std::shared_ptr<Storage> m_Storage;
	std::vector<size_t> m_Position;
};


#endif // MATRIX_H
