#include <bits/stdc++.h>
#include <unistd.h>
#include <dirent.h>
using namespace std;

#define fr(i,n) for(int i=0;i<n;i++)
#define all(a) a.begin(),a.end() 
#define prin(a) cout << #a << " = " << (a) << endl

typedef long long ll;

// ------------------------------------------------------------------------------------

string file_program_to_check = "2crt.cpp";
string path_with_data = "inputf/";
string ext_input = ".in", ext_output = ".out";

/*
To add extension to all files in a repository, use following script:
	for f in * ; do 
	  mv "$f" "$f.in"
	done
*/

// ------------------------------------------------------------------------------------

FILE *pfile;

vector<vector<string>> read_parser(string file_name){
    pfile = fopen(file_name.c_str(),"r");
    
    vector<vector<string>> ans;
    vector<string> line;
    string word;
    char c;
    
    while(fscanf(pfile,"%c", &c)!=EOF){
        if(c=='\n'){
            if(word.size()) line.emplace_back(word);
            word.clear();
            if(line.size()) ans.emplace_back(line);
            line.clear();
        } else if(isspace(c)){
            if(word.size()) line.emplace_back(word);
            word.clear();
        } else{
            word += c;
        }
    }
    if(word.size()) line.emplace_back(word);
    word.clear();
    if(line.size()) ans.emplace_back(line);
    line.clear();
    
    return ans;
}

clock_t ts;

double get_time(){
	return (double)(clock()-ts)/CLOCKS_PER_SEC;
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
	
	system(("g++ -std=c++14 -O2 -o prog1 " + file_program_to_check).c_str());
	
	cout << "Running " << s_input.size() << " files" << endl;
	
	double max_time = 0;
	
	for(auto &input_file : s_input){
	    if(!s_output.count(input_file)){
	        cout << "Input extension contains: " << input_file << endl;
	        cout << "But output extension does not contain it" << endl;
	        return 0;
	    }
	    
	    ts = clock();
	    system(("./prog1 < " + path_with_data + input_file + ext_input + " > a1").c_str());
	    max_time = max(max_time,get_time());
	    
	    vector<vector<string>> ans1 = read_parser("a1"), ans2 = read_parser(path_with_data+input_file+ext_output);
	    
	    cout << "Veredict of " << input_file << ": ";
	    if(ans1==ans2) cout << "OK" << endl;
	    else{
	        cout << "Wrong" << endl;
	        return 0;
	    }
	}
	prin(max_time);
    
	return 0;
}

