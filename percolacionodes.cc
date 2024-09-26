#include <iostream>
#include <random>
#include <vector>
using namespace std;

int main(){
    int n,m;
    cin>>n>>m;
    int nf=n;
    vector < vector < int > > aristas(n);
    vector <bool> nodosrestantes (n,true);
    for(int i =0; i<m; i++){
        int a,b;
        cin>>a>>b;
        aristas[a].push_back(b);
    }
    float q;
    cin>>q;
    random_device generador0;
    mt19937 generador{generador0()};
    bernoulli_distribution distribucion(1-q);
    for(int i=0; i<n; ++i) {
        if(distribucion(generador)){
            nodosrestantes[i]=false;
            nf--;

        }

    }

    vector<int> nodosfinales(nf);
    int temp=nf-1;
    for(int i=n-1;i>=0;--i){
        if(nodosrestantes[i]){
            nodosfinales[i]=temp;
            --temp;
        }
    }
    m=0;
    for(int i=0; i<n; ++i) {
        if(nodosrestantes[i]){
            int n2=aristas[i].size();
            for(int j=0; j<n2 ; ++j){
                int conexion=aristas[i][j];
                if( nodosrestantes[conexion]) m++;

            }
        }

    }

    cout<<nf<<" "<<m<<endl;
    for(int i=0; i<n; ++i) {
        if(nodosrestantes[i]){
            int n2=aristas[i].size();
            for(int j=0; j<n2 ; ++j){
                int conexion=aristas[i][j];
                if(nodosrestantes[conexion]){
                    cout<<nodosfinales[i]<<" "<<nodosfinales[conexion]<<endl;
                }

            }
        }

    }

}
