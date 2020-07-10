#include <bits/stdc++.h>
using namespace std;

#define fr(i,n) for(int i = 0; i<n; i++)
#define sz(v) (int)(v.size())
#define prin(a) cout << #a << " = " << a << endl
#define all(v) (v).begin(),(v).end()
typedef long long ll;

/*
	Arquivo para rodar outro programa varias vezes
	
	2 Usos:
	
	1)  Gerar offline
			Adicionar uma unica linha no arquivo a ser rodado varias vezes para 
			acumular (por appends) no output de cada uma das vezes que o arquivo rodou.
			Bom para programas em que quero gerar numeros offline
			
freopen("myout","a", stdout);
			
			
	
	2) 	Achar caso que quebra da ruim- ctzq(0); (assert)
	
		Quero descobrir um caso em que da erro
		Posso adicionar checkers no aquivos e fazer asserts com ctzq(x); - add funcao:
		
void ctzq(int ok){
	if(!ok){
		freopen("input_errado","a", stdout);
		cout << tam << endl; //printar input (q deve estar global no file)
		assert(0);
	}
}

*/

bool file_exists (string name) {
    ifstream f(name.c_str());
    return f.good();
}

int main(){
	//mudar nome do arquivo a ser rodado
	system("g++ -std=c++14 -O2 -w -o prog1 z.cpp"); 
	
	//resetar myout para caso va fazer appends nele em seguida
	freopen("myout","w",stdout); 
	fclose(stdout);
	
	if(file_exists("input_errado")) system("gio trash input_errado");
	
	//criar o aux.txt e rodar aquivo varias vezes com ele como input
	for(int tam = 2; tam<=7; tam++){
		//input
		freopen("aux.txt", "w", stdout);
		cout << tam << endl;
		fclose(stdout);
		
		system("./prog1 < aux.txt");
		
		if(file_exists("input_errado")){
			//usar cerr para mensagem opicional no terminal
			cerr << "Achou input_errado" << endl;
			return 0;
		}
	}	
}
