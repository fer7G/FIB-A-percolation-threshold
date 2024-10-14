#include "graph.cpp"
#include <random>
using namespace std;

vector <float> calcularprobvertex(const Graph& a){
    vector <float> ProbVertex (a.numNodes);
    random_device generador0;
    mt19937 generador(generador0());
    uniform_real_distribution<> distribucion(0.0,1.0);
    for(int i=0;i<a.numNodes;i++) {
        ProbVertex[i]=distribucion(generador);

    }
     return ProbVertex;
}

int percolaciovertex(vector<int> ProbVertex,const Graph& a, float p){
     vector <bool> nodosrestantes(a.numNodes,false);
     int n=a.numNodes;
     int nf=n;
    for(int i=0; i<n; ++i) {
        if(ProbVertex[i]<p){
            nodosrestantes[i]=false;
            nf--;

        }

    }

    vector<int> nodosfinales(n,-1);
    int temp=nf-1;
    for(int i=n-1;i>=0;--i){
        if(nodosrestantes[i]){
            nodosfinales[i]=temp;
            --temp;
        }
    }
    Graph inducido;
    inducido.numNodes=nf;
   // Matrix adjPercv;

    for(int i=0; i<n; ++i) {
        if(nodosrestantes[i]){
            int n2=a.adjList[i].size();
            for(int j=0; j<n2 ; ++j){
                int conexion=a.adjList[i][j];
                if( nodosrestantes[conexion] and i<j) {
                    inducido.adjList[nodosfinales[i]].push_back(nodosfinales[conexion]);
                  //  cout<<nodosfinales[i]<<" "<<nodosfinales[conexion]<<endl;
                }

            }
        }

    }
    return inducido.connected_components();


    }
