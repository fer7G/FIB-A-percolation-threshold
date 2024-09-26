#include <iostream>
#include <vector>
using namespace std;

void DFS(int n,vector < vector < int > > &aristas, int i, vector<bool>& visitados){
    visitados[i]=true;
    int m2=aristas[i].size();
    for(int j=0; j<m2; ++j){
        int nodo=aristas[i][j];
        if(not visitados[nodo]) DFS(n,aristas,nodo,visitados);
    }
}

int main(){
    int n,m;
    cin>>n>>m;
     vector < vector < int > > aristas(n);
     for(int i =0; i<m; i++){
        int a,b;
        cin>>a>>b;
        aristas[a].push_back(b);
    }

    vector <bool> visitados (n,false);
    int componentesc=0;

    for(int i=0; i<n; ++i){
        if(not visitados [i]){
            DFS(n,aristas,i,visitados);
            ++componentesc;
        }


    }

    cout<<componentesc<<endl;


}
