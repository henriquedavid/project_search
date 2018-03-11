#include <iostream>		// std::cout
#include <chrono>
#include <algorithm>
#include <iterator>		// std::ostream_iterator<int>
#include <cmath>		// std::sqrt
#include <string>		// std::string
#include <sstream>
#include <fstream>
#include <vector>
#include <iomanip>

/*
 * Programa que possibilita testar 7 algoritmos de busca (linear, binaria interativa
 * e recursiva, ternária interativa e recursiva, jump search e fibonacci search).
 * 
*/

int getInteger(std::string value){
	int ver = 0;
	int valor;

	while(ver == 0){

		std::istringstream iss(value);

		iss >> valor >> std::ws;

		if(iss.fail() or !iss.eof()){
			std::cerr << "Erro ao converter!\nInsira novamente: \n" << std::endl;
			std::cin >> value;
		} else
			ver = 1;
	}

	return valor;
}

int * linearSearch( int *first , int *last , int value ,  int *default_last){

	for( auto i( first ); i < last ; i++ ){
		if( value == *i )
			return i;
	}

	return default_last;
}

int * binarySearch( int *first , int *last , int value , int *default_last){
	
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

	long int quant_Element = 0;
	std::string tipo_busca = "LN";
	long int quant_max_Element = 1809983;
	int valor = quant_max_Element+1;
	int amostras = 0;
	int media = 0;

	std::ofstream FILE;
	std::vector<std::string> cabecalho = {"Quantidade de Elementos","TEMPO(ns)"};

	

	if(argc < 3){
		std::cout << "Há informações faltando\n ./EXECUTAVEL QUANTIDADE_AMOSTRAS NOME_DA_BUSCA" << std::endl;
	} else{

		amostras = getInteger(argv[1]);
		tipo_busca = argv[2];

		FILE.open("results_" + tipo_busca + ".csv");

		if(FILE.fail()){
			std::cout << "Erro ao abrir o arquivo!" << std::endl;
			return -1;
		}


		FILE << "TIPO DE BUSCA: " << tipo_busca << ", Quantidade de amostras analisadas:" << amostras << std::endl << std::endl;
		FILE << cabecalho[0] << "  ";
		FILE << ",  " << cabecalho[1] << "  ";
		FILE << std::endl;		

		quant_Element = 100000;

		for( auto rep(1); rep <= amostras; rep++){
			

			if(quant_Element > quant_max_Element)
				quant_Element = quant_max_Element;

			int A[quant_Element];
		
			for( auto i(0); i < quant_Element; i++){
				A[i] = i;
			}

			valor = quant_Element+1;


			// Target values for testing.
			// Prints out the original data container.
			/*std::cout << "Array: [ ";
			for( auto i(0); i < quant_Element; i++){
				std::cout << A[i] << " ";
			}
			std::cout << "]\n\n\n";*/
			// Executes several searchs in the data container.

			// Look for target in the entire range.

			for( auto t(0); t <= 100; t++){

				auto start = std::chrono::system_clock::now();

				if(tipo_busca == "FS")
					auto result = fibonacci_search( A, A+quant_Element, valor, A+quant_Element );
				else if(tipo_busca == "BI")
					auto result = binarySearch( A, A+quant_Element, valor, A+quant_Element );
				else if(tipo_busca == "BR")
					auto result = binary_rec( A, A+quant_Element, valor, A+quant_Element );
				else if(tipo_busca == "TI")
					auto result = ternSearch( A, A+quant_Element, valor, A+quant_Element );
				else if(tipo_busca == "TR")
					auto result = tern_rec( A, A+quant_Element, valor, A+quant_Element );
				else if(tipo_busca == "JS")
					auto result = jump_search( A, A+quant_Element, valor, A+quant_Element );
				else
					auto result = linearSearch( A, A+quant_Element, valor, A+quant_Element );
		
				auto end = std::chrono::system_clock::now();

				int waste_time = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

				media += (waste_time - media) / rep; 

			}

			FILE << std::fixed << std::setprecision(cabecalho[0].size()) << std::setw(cabecalho[0].size()) << quant_Element << ",  ";
			FILE << "  " << std::fixed << std::setprecision(cabecalho[1].size()) << std::setw(cabecalho[1].size()) << media << "  ";
			FILE << std::endl;
		
			quant_Element += 34199;

		}

		FILE.close();
	}

	return 0;
}