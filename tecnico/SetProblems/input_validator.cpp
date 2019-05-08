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
string path_with_data = "chefs/data/secret/";
string ext_input = ".in";

// ------------------------------------------------------------------------------------


bool isnum(char c){
    return '0'<=c and c<='9';
}

bool valid_number(string s){
    if(s.size()==1 and isnum(s[0])) return 1;
    if(s.size()==0) return 1;
    if(s[0]==0) return 0;
    
    fr(i,s.size()) if(!isnum(s[i])) return 0;
    
    return 1;
}   

bool read_parser(string file_name){
    FILE *pfile = fopen(file_name.c_str(),"r");
    
    vector<vector<string>> file;
    vector<string> line;
    string word;
    char c;
    
    while(fscanf(pfile,"%c", &c)!=EOF){
        if(c=='\n'){
            if(word.size()) line.eb(word);
            word.clear();
            if(line.size()) file.eb(line);
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
    if(line.size()) file.eb(line);
    line.clear();
    
    if(!file.size()) return 0;
    if(!file[0].size()==1) return 0;
    
    for(auto &v : file){
        for(auto &s : v) if(!valid_number(s)) return 0;
    }
    
    int n = stoi(file[0][0]);
    
    if(file.size()!=n+1) return 0;
    
    for(int i = 1; i<=n; i++){
        if(file[i].size()!=2) return 0;
        ll t = stoll(file[i][0]);
        ll d = stoll(file[i][1]);
        if(! (0<=t and t<=1e9)) return 0;
        if(! (1<=d and t<=1e9)) return 0;
    }
    
    return 1;
}

int main(){
    
    set<string> s_input;
    
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
	  }
	  closedir (dir);
	} else {
	  cout << "Nao foi possivel acessar arquivos" << endl;
	  exit(0);
	}
	
	cout << "Running " << s_input.size() << " files" << endl;
	
	for(auto &input_file : s_input){
	    
	    system(("./prog1 < " + path_with_data + input_file + ext_input + " > a1").c_str());
	    
	    bool ans = read_parser(path_with_data+input_file+ext_input);
	    
	    cout << "Veredict of " << input_file << ": ";
	    if(ans) cout << "OK" << endl;
	    else{
	        cout << "Wrong" << endl;
	        return 0;
	    }
	}
    
	return 0;
}

