#include <iostream>

#include "logger.h"

template <class T>
void Logger<T>::print(T a)
{
	std::cout << a << std::endl;
}
