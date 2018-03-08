#include <iostream>
#include <algorithm>
#include <interator>

int * binarySearch( int *first , int *last , int value ){

	auto result(last);
	int distance;

	for( auto i(first) ; i < last ; i++ ){

		distance = (last - first) / 2;

		if( value == *i ) return i;
		else if( value < *i ) last = &distance;
		else
			first = &distance;

		return result;
	}

}