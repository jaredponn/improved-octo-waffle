#include <iostream>
#include "packedvector.h"

int main(void)
{
	PackedVector<int> a(121);
	a.add_element_at_sparse_vector(1, 23);
	a.delete_element_at_sparse_vector(1);


	std::cout << "hellow";
	return 0;
}
