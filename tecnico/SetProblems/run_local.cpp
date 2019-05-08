#include <bits/stdc++.h>
#include <unistd.h>
#include <dirent.h>
using namespace std;

#define FILE_IN freopen("kotlin.in", "r", stdin);
#define FILE_OUT freopen("kotlin.out", "w", stdout);

#define fr(i,n) for(int i=0;i<n;i++)
#define frr(i,a,b) for(int i =a;i<=b;i++)

typedef long long ll;
typedef long double ld;

#define eb emplace_back

#define all(a) a.begin(),a.end() 

bool debug = 1;
#define prin(a) if(debug) cout << #a << " = " << (a) << endl

// ------------------------------------------------------------------------------------

string file_program_to_check = "chefs/submissions/accepted/sol_ponctualcheffs.cpp";
string path_with_data = "chefs/data/sample/";
string ext_input = ".in", ext_output = ".ans";

// ------------------------------------------------------------------------------------

const int N = 1e6+10;
ll t[N], d[N];
FILE *pfile;

ll n, k;

vector<vector<string>> read_parser(string file_name){
    pfile = fopen(file_name.c_str(),"r");
    
    vector<vector<string>> ans;
    vector<string> line;
    string word;
    char c;
    
    while(fscanf(pfile,"%c", &c)!=EOF){
        if(c=='\n'){
            if(word.size()) line.eb(word);
            word.clear();
            if(line.size()) ans.eb(line);
            line.clear();
        } else if(isspace(c)){
            if(word.size()) line.eb(word);
            word.clear();
        } else{
            word += c;
        }
    }
    if(word.size()) line.eb(word);
    word.clear();
    if(line.size()) ans.eb(line);
    line.clear();
    
    return ans;
}

int main(){
    
    
    set<string> s_input, s_output;
    
	DIR *dir;
	struct dirent *ent;
	if ((dir = opendir (path_with_data.c_str())) != NULL) {
	  while ((ent = readdir (dir)) != NULL) {
	  	string complete_file_name = string(ent->d_name);
	  	string file_name;
	  	string ext;
	  	int i = 0;
	  	while(i<complete_file_name.size() and complete_file_name[i]!='.') file_name += complete_file_name[i++];
	  	if(i==complete_file_name.size()) continue;
	  	while(i<complete_file_name.size()) ext += complete_file_name[i++];
	  	if(ext==ext_input) s_input.emplace(file_name);
	  	if(ext==ext_output) s_output.emplace(file_name);
	  }
	  closedir (dir);
	} else {
	  cout << "Nao foi possivel acessar arquivos" << endl;
	  exit(0);
	}
	
	if(s_input.size()!=s_output.size()){
	    cout << "Error! Diferent number of input and output files" << endl;
	    cout << "Number of input files: " << s_input.size() << endl;
	    cout << "Number of output files: " << s_output.size() << endl;
	    return 0;
	}   
	
	system(("g++ -std=c++14 -Wshadow -fsanitize=address -D_GLIBCXX_DEBUG -o prog1 " + file_program_to_check).c_str());
	
	cout << "Running " << s_input.size() << " files" << endl;
	
	for(auto &input_file : s_input){
	    if(!s_output.count(input_file)){
	        cout << "Input extension contains: " << input_file << endl;
	        cout << "But output extension does not contain it" << endl;
	        return 0;
	    }
	    
	    system(("./prog1 < " + path_with_data + input_file + ext_input + " > a1").c_str());
	    
	    vector<vector<string>> ans1 = read_parser("a1"), ans2 = read_parser(path_with_data+input_file+ext_output);
	    
	    cout << "Veredict of " << input_file << ": ";
	    if(ans1==ans2) cout << "OK" << endl;
	    else{
	        cout << "Wrong" << endl;
	        return 0;
	    }
	}
    
	return 0;
}

