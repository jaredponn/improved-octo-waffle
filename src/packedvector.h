#pragma once

#include <vector>


template <class T>
class PackedVector
{
    private:
	std::vector<size_t> m_sparse_vector;
	std::vector<size_t> m_packed_indicies;
	std::vector<T> m_data;

	size_t m_next_free_index;


    public:
	PackedVector(size_t capacity);

	void add_element_at_sparse_vector(const size_t index, const T &val);
	void delete_element_at_sparse_vector(const size_t index);

	/* Getters */
	const std::vector<size_t> &get_sparse_vector();
	const std::vector<size_t> &get_packed_indicies();
	const std::vector<T> &get_data();

	~PackedVector();
};
