#include <iostream>
#include <algorithm>
#include <interator>

int * linearSearch( int *first , int *last , int value ){

	for( auto i( first ); i < last ; i++ ){
		if( value == i )
			return i;

		return last;
	}
}