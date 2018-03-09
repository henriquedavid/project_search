#include <iostream>
#include <chrono>
#include <algorithm>
#include <iterator>
#include <cmath>

/*
 * Programa que possibilita testar 7 algoritmos de busca (linear, binaria interativa
 * e recursiva, ternária interativa e recursiva, jump search e fibonacci search).
 * 
*/

int * linearSearch( int *first , int *last , int value , int *default_last){

	for( auto i(first); i < last ; i++ ){
		if( value == *i )
			return i;
	}

	return default_last;
}

int * binarySearch( int *first , int *last , int value ){
	
	auto back( last );

	while( first <= last ){
		int middle = ( last - first ) / 2;

		if(	*( first + middle ) == value ){
		
			return first + middle;
		}

		if( *( first + middle ) < value ){
			first = first + middle + 1;
		}
		else{
			last = last - middle - 1;
		}
	}
	
	return back;

}

int * binary_rec( int *first , int *last , int value , int *default_last){

	if( first <= last ){

		int middle = ( last - first ) / 2;

		if( *( first + middle ) == value ){
			return first + middle;
		}

		else if( *( first + middle ) < value ){
			auto new_first = first + middle + 1;
			return binary_rec( new_first , last , value , default_last );
			
		}
		else{
			auto new_last = last - middle - 1;
			return binary_rec( first , new_last , value , default_last );
		}
	}

	return default_last;

}


int * ternSearch( int *first , int *last , int value , int *default_last ){

	while( first <= last ){
		int middle1 = ( last - first) / 3;
		int middle2 = 2 * middle1;


		if( *( first + middle1 ) == value )
			return first + middle1;

		if( *( first + middle2 ) == value )
			return first + middle2;

		if( value < *( first + middle1 ) ){
			last = first + middle1 - 1;
		}
		else if( *( first + middle1 ) < value && value < *( first + middle2 ) ){
			first = first + middle1 + 1;
			last = first + middle2 - 1;
		}
		else if (value > *( first + middle2 ) ){
			first = first + middle2 + 1;
		}
		else{
			return default_last;
		}
	}

	return default_last;
}

int * tern_rec( int *first , int *last , int value , int *default_last ){


	if( first <= last ){
		int middle1 = ( last - first ) / 3;
		int middle2 = 2 * middle1;

		if( *( first + middle1 ) == value )
			return first + middle1;

		if( *( first + middle2 ) == value )
			return first + middle2;

		if( value < *( first + middle1 ) ){
			return tern_rec( first , first + middle1 - 1 , value , default_last );
		}
		else if( *( first + middle1 ) < value && value < *( first + middle2 ) ){
			return tern_rec( first + middle1 + 1 , first + middle2 - 1 , value , default_last );
		}
		else if ( value > *( first + middle2 ) ){
			return tern_rec( first + middle2 + 1 , last , value , default_last );
		}
		else{
			return default_last;
		}
	}

	return default_last;
}

int * jump_search( int *first, int *last, int value, int *default_last){

	int aux = std::sqrt( ( last - first ) );
	
	int* new_first = first;
	int* new_last = first+aux;


	while( first <= last && new_last <= default_last ){

		if( value == *new_first )
			return new_first;

		if( value == *new_last )
			return new_last;

		if( value > *new_first && value < *new_last )
			return linearSearch( new_first , new_last , value , default_last );
		else{
			new_first += aux;
			new_last += aux;
		}
	}
	
	return default_last;

}

int fibonacci_number( int numero ){
	int a = 0, b = 1, number;
	
	for( auto i(0) ; i <= numero ; i++ ){
		number = a + b;
		a = b;
		b = number;

		if( number > numero )
			return b;
	}

	return -1;
}

int menorValor(	int x , int y ){
	if( x < y ) return x;
	return y;
}

int * fibonacci_search( int *first , int *last , int value , int *default_last ){

	int fib_m2 = 0;
	int fib_m1 = 1;

	int fib = fib_m2 + fib_m1;
	int menor = 0 , aux = -1;

	while( fib <= *( last - 1 ) ){
		fib_m2 = fib_m1;
		fib_m1 = fib;
		fib = fib_m2 + fib_m1;
	}

	while( fib > 1 ){

		menor = menorValor( fib_m2 + aux , *( last - 2 ) );

		if( *( first + menor ) < value ){
			fib = fib_m1;
			fib_m1 = fib_m2;
			fib_m2 = fib - fib_m1;
			aux = menor;

		} else if( *( first + menor ) > value ){
			fib = fib_m2;
			fib_m1 = fib_m1 - fib_m2;
			fib_m2 = fib - fib_m1;

		} else{
			return first + menor;
		}

	}

	return default_last;
}

int main(int argc, char* argv[]){

	int A[] = { 0, 1, 2, 3, 4, 6,7, 8, 9, 10};
	// Data container.
	int targets[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 20, 21};
	// Target values for testing.
	// Prints out the original data container.
	std::cout << "Array: [ ";
	std::copy( std::begin(A), std::end(A), std::ostream_iterator<int>( std::cout , " " ) );
	std::cout << "]\n";
	// Executes several searchs in the data container.
	for( const auto & e : targets )     {
	    // Look for target in the entire range.
	    auto result = fibonacci_search( std::begin(A), std::end(A), e , std::end(A));         
	    // Process the result         
	     
	    if ( result != std::end(A))         
	    {             
	      	std::cout << ">>> Found \"" << e << "\" at position "                       
	     				<< std::distance(std::begin(A),result) << ".\n";         
	    }         
	    else
	   	{             
       		std::cout << ">>> Value \"" << e << "\" not found in array!\n";
	    }
	}

	return 0;
}