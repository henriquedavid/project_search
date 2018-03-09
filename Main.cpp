#include <iostream>
#include <chrono>
#include <algorithm>
#include <iterator>

/*
 *	X LINEAR INTERATIVA
 *	X BINÁRIA INTERATIVA 
 *	X BINÁRIA RECURSIVA
 *	X TERNÁRIA INTERATIVA
 *	X TERNÁRIA RECURSIVA
 *	- JUMP SEARCH
 *	- FIBONACCI
*/

int * linearSearch( int *first , int *last , int value ){

	for( auto i(first); i < last ; i++ ){
		if( value == *i )
			return i;

		return last;
	}

	return last;
}

int * binarySearch( int *first , int *last , int value ){
	
	auto back( last );

	while( first <= last ){
		int middle = ( last - first ) / 2;

		if(	*( first + middle ) == value ){
		
			return first+middle;
		}

		if( *( first + middle ) < value){
			first = first + middle + 1;
		}
		else{
			last = last - middle - 1;
		}
	}
	
	return back;

}

int * ternSearch( int *first, int *last, int value, int *default_last){

	while(first <= last){
		int middle1 = (last - first) / 3;
		int middle2 = 2 * middle1;


		if( *(first + middle1) == value)
			return first + middle1;

		if( *(first + middle2) == value)
			return first + middle2;

		if( value < *(first+middle1)){
			last = first + middle1-1;
		}
		else if(*(first+middle1) < value && value < *(first+middle2)){
			first = first+middle1+1;
			last = first+middle2-1;
		}
		else if (value > *(first+middle2)){
			first = first+middle2+1;
		}
		else{
			std::cout << "Algo não saiu correto !!!\nNunca deveria entrar aqui!" << std::endl;
		}
	}

	return default_last;
}

int * tern_rec( int *first, int *last, int value, int *default_last){


	if(first <= last){
		int middle1 = (last - first) / 3;
		int middle2 = 2 * middle1;

		if( *(first + middle1) == value)
			return first + middle1;

		if( *(first + middle2) == value)
			return first + middle2;

		if( value < *(first+middle1)){
			return tern_rec(first, first + middle1 - 1, value, default_last);
		}
		else if(*(first+middle1) < value && value < *(first+middle2)){
			return tern_rec(first+middle1+1, first+middle2-1, value, default_last);
		}
		else if (value > *(first+middle2)){
			return tern_rec(first+middle2+1, last, value, default_last);
		}
		else{
			std::cout << "Algo não saiu correto !!!\nNunca deveria entrar aqui!" << std::endl;
		}


	}

	return default_last;
}

int * binary_rec( int *first , int *last , int value , int *default_last){

	if(first <= last){

		int middle = (last - first) / 2;

		if( *( first + middle ) == value ){
			return first + middle;
		}

		else if( *(first + middle ) < value ){
			auto new_first = first + middle + 1;
			return binary_rec(new_first, last, value, default_last);
			
		}
		else{
			auto new_last = last - middle - 1;
			return binary_rec(first, new_last, value, default_last);
		}
	}

	return default_last;

}


int main(int argc, char* argv[]){

	int A[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
	// Data container.
	int targets[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9,-4, 20 };
	// Target values for testing.
	// Prints out the original data container.
	std::cout << "Array: [ ";
	std::copy( std::begin(A), std::end(A), std::ostream_iterator<int>( std::cout , " " ) );
	std::cout << "]\n";
	// Executes several searchs in the data container.
	for( const auto & e : targets )     {
	    // Look for target in the entire range.
	    auto result = tern_rec( std::begin(A), std::end(A), e , std::end(A));         
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