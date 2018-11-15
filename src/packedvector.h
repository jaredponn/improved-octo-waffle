#pragma once

#include <vector>
#include <cstdint>

#include "logger.h"

namespace iow
{

template <class T>
class PackedVector
{
    private:
	std::vector<size_t> m_sparse_vector;
	std::vector<size_t> m_packed_indicies;
	std::vector<T> m_packed_data;

	size_t m_next_free_index;


    public:
	inline PackedVector(size_t capacity);

	/* Functions */
	inline void add_element_at_sparse_vector(const size_t index,
						 const T &val);
	// delets the element at the sparse vector. Sets that sparse vector
	// index to SIZE_MAX and pops and swaps the corrosponding data / indices
	// vector
	inline void delete_element_at_sparse_vector(const size_t index);

	// when given the sparse_vector index, and returns the data in the
	// packed vector
	inline T get_data_from_sparse_vector(const size_t index);
	// gets the global index (sparse_vector) when given the packed index
	inline size_t get_global_index_from_packed_index(const size_t index);

	/// should only be used when yo know for certain that the entity is
	/// thing
	T operator[](size_t i) const
	{
		if (i >= m_sparse_vector.size()
		    || m_sparse_vector[i] == SIZE_MAX) {
			Logger::logMessage(
				"MAJOR ERROR in PackedVector. Invalid access, please you are inputting a valid entity index.");
		}

		return m_packed_data[m_sparse_vector[i]];
	}
	T &operator[](size_t i)
	{
		if (i >= m_sparse_vector.size()
		    || m_sparse_vector[i] == SIZE_MAX) {
			Logger::logMessage(
				"MAJOR ERROR in PackedVector. Invalid access, please you are inputting a valid entity index.");
		}
		return m_packed_data[m_sparse_vector[i]];
	}

	/* Getters */
	inline const std::vector<size_t> &get_sparse_vector() const;
	inline const std::vector<size_t> &get_packed_indicies() const;
	inline const std::vector<T> &get_packed_data() const;

	~PackedVector();
};

template <class T>
inline PackedVector<T>::PackedVector(size_t capacity)
{
	m_sparse_vector.resize(capacity, SIZE_MAX);
	m_packed_indicies.reserve(capacity);
	m_packed_data.reserve(capacity);
	m_next_free_index = 0;
}


template <class T>
inline void PackedVector<T>::add_element_at_sparse_vector(const size_t index,
							  const T &val)
{
	if (index >= m_sparse_vector.size()) {
		Logger::logMessage(
			"MAJOR ERROR in PackedVector. Too many entities exist for this engine. Increase the buffer size");

		return;
	}
	// if the index has already been added, throw an error
	if (m_sparse_vector[index] != SIZE_MAX) {
		Logger::logMessage(
			"MAJOR ERROR in PackedVector. You are using add_element_at_sparse_vector when there is already an entity at that point. Everything past here is weird UNDEFINED behaviour");
		return;
	}

	m_sparse_vector[index] = m_next_free_index;
	m_packed_indicies.push_back(index);
	m_packed_data.push_back(val);

	++m_next_free_index;
}
template <class T>
inline void PackedVector<T>::delete_element_at_sparse_vector(const size_t index)
{
	// if the index has already been added, throw an error
	if (m_sparse_vector[index] == SIZE_MAX) {
		Logger::logMessage(
			"MINOR ERROR in PackedVector with function delete_element_at. You are deleting an element that has already been deleted. The system should continue working as normally.");
		return;
	}

	size_t todeletesysindex = m_sparse_vector.at(index);
	size_t lastindexsysindexinsparsevec = m_packed_indicies.back();

	std::swap(m_sparse_vector[index],
		  m_sparse_vector[lastindexsysindexinsparsevec]);

	std::swap(m_packed_indicies[todeletesysindex],
		  m_packed_indicies.back());
	std::swap(m_packed_data[todeletesysindex], m_packed_data.back());

	m_packed_indicies.pop_back();
	m_packed_data.pop_back();

	--m_next_free_index;

	m_sparse_vector[index] = SIZE_MAX;
}

template <class T>
inline T PackedVector<T>::get_data_from_sparse_vector(const size_t index)
{
	if (m_sparse_vector[index] == SIZE_MAX) {
		Logger::logMessage(
			"MAJOR ERROR: Accessing invalid sparse vector index with get_data_from_sparse_vector function");
	}
	return m_packed_data[m_sparse_vector[index]];
}

template <class T>
inline size_t
PackedVector<T>::get_global_index_from_packed_index(const size_t index)
{
	if (index >= m_packed_indicies.size()) {
		Logger::logMessage(
			"MAJOR ERROR: Accessing index outside of the packed_indicies vector.");
	}
	return m_packed_indicies[index];
}

/* Getters */
template <class T>
inline const std::vector<size_t> &PackedVector<T>::get_sparse_vector() const
{
	return m_sparse_vector;
}
template <class T>
inline const std::vector<size_t> &PackedVector<T>::get_packed_indicies() const

{
	return m_packed_indicies;
}
template <class T>
inline const std::vector<T> &PackedVector<T>::get_packed_data() const

{
	return m_packed_data;
}

template <class T>
inline PackedVector<T>::~PackedVector()
{
}

} // namespace iow
