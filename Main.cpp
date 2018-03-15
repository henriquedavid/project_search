/*
 * Programa que possibilita testar 7 algoritmos
 * de busca (linear, binaria interativa
 * e recursiva, ternária interativa e
 * recursiva, jump search e fibonacci search).
 * 
*/

#include <iostream>		// std::cout, std::endl, std::cerr, std::cin
#include <chrono>		// std::chrono, std::chrono::system_clock, std::chrono::duration_cast
#include <algorithm>	// .count(),
#include <iterator>		// std::ostream_iterator<int>
#include <cmath>		// std::sqrt
#include <string>		// std::string
#include <sstream>		// std::istringstream
#include <fstream>		// .open(), .close(), .fail()
#include <vector>		// std::vector<std::string>
#include <iomanip>		// std::setw(), std::setprecision()

// Transforma uma string em um inteiro.
/*
 * \param recebe valor em string.
 * \return retorna valor em inteiro.
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

/* 
 * Padrão para as buscas Linear, Binária Interativa, Binária Recursiva, Ternária Interativa,
 * Jump Search e Fibonacci Search.
 * 
 * \param ponteiro first aponta para o primeiro elemento do vetor.
 * \param ponteiro last aponta para após o último elemento do array.
 * \param value - valor desejado que deseja buscar.
 * \param ponteiro default_last aponta para após o último elemento do array.
 * \return ponteiro para o valor desejado; ou para após o último elemento do array.
 */

long int * linearSearch( long int *first , long int *last , int value , long  int *default_last){

	for( auto i( first ); i < last ; i++ ){
		
		if( value == *i )
			return i;


	}

	return default_last;
}

long int * binarySearch( long int *first , long int *last , int value , long int *default_last){
	
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

long int * binary_rec( long int *first , long int *last , int value , long int *default_last){

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


long int * ternSearch( long int *first , long int *last , int value , long int *default_last ){

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

long int * tern_rec( long int *first , long int *last , int value , long int *default_last ){


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

long int * jump_search(long int *first, long int *last, int value, long int *default_last){

	int aux = std::sqrt( ( last - first ) );
	
	long int* new_first = first;
	long int* new_last = first+aux;


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

// Retorna o menor valor entre dois.
/*
 * \param recebe inteiro.
 * \param recebe inteiro.
 * \return retorna qual é o menor valor entre dois.
 */

int menorValor(	int x , int y ){
	if( x < y ) return x;
	return y;
}

long int * fibonacci_search( long int *first , long int *last , int value , long int *default_last ){

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

	long int quant_Element = 0; // acompanha a variação da quantidade de elementos.

	/*
	* tipo_busca informa qual o tipo de busca desejada e o padrão
	* caso não seja informado o tipo de busca.
	*/
	std::string tipo_busca = "LN";
	int valor;

	/*
	* quant_max é a quantidade máxima de um vetor (varia de computador em computador).
	*/
	long int quant_max_Element = 1026991; 
	int amostras = 0; // Verifica a quantidade de amostras desejadas.

	std::ofstream FILE;
	std::vector<std::string> cabecalho = {"Quantidade de Elementos","TEMPO(ns)"};

	if(argc < 3){
		// Apresenta erro caso o usuário não tenha executado corretamente o executável.
		std::cout << "Há informações faltando\n ./EXECUTAVEL QUANTIDADE_AMOSTRAS NOME_DA_BUSCA" << std::endl;
	} else{

		// Transforma o valor da quantidade de amostras.
		amostras = getInteger(argv[1]);
		// Recebe o tipo de busca.
		tipo_busca = argv[2];

		// Cria arquivo com o nome do tipo de busca em formato csv para gerar os gráficos.
		FILE.open("results_" + tipo_busca + ".csv");

		// Verifica se foi possível abrir o arquivo, caso contrário apresenta erro e encerra o programa.
		if(FILE.fail()){
			std::cout << "Erro ao abrir o arquivo!" << std::endl;
			return -1;
		}

		// Insere o padrão do cabeçalho no arquivo de saída.
		FILE << "TIPO DE BUSCA: " << tipo_busca << ", Quantidade de amostras analisadas:" << amostras << std::endl << std::endl;
		FILE << cabecalho[0] << "  ";
		FILE << ",  " << cabecalho[1] << "  ";
		FILE << std::endl;		

		// Inicia a quantidade de elementos no vetor.

		int media_inicial = quant_max_Element / amostras;
		quant_Element = media_inicial;

		// Executa séries de repetições de amostras.
		for( auto rep(1); rep <= amostras; rep++){
			
			// Reinicia a média em cada repetição.
			int media = 0;

			// Previne caso a quantidade de elementos for maior do que suportado.
			if(quant_Element > quant_max_Element)
				quant_Element = quant_max_Element;

			// Cria um vetor para armazenar elementos.
			long int A[quant_Element];
		
			// Insere elementos no vetor.
			for( auto i(0); i < quant_Element; i++){
				A[i] = i;
			}

			// Torna a variável valor não seja um elemento do vetor.
			valor = quant_max_Element+1;

			// Realiza séries de testes dos tempos da busca escolhida.

			for( auto t(0); t < 100; t++){

				auto start = std::chrono::system_clock::now();

				// Realiza a busca desejada.
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

			//Insere os dados no arquivo.

			FILE << std::fixed << std::setprecision(cabecalho[0].size()) << std::setw(cabecalho[0].size()) << quant_Element << ",  ";
			FILE << "  " << std::fixed << std::setprecision(cabecalho[1].size()) << std::setw(cabecalho[1].size()) << media << "  ";
			FILE << std::endl;
		
			// Adiciona mais elementos no vetor.
			quant_Element += media_inicial;

		}

		FILE.close();
	}

	return 0;
}