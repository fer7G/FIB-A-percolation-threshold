#include <iostream>
#include <random>
#include <vector>
using namespace std;

int main(){
    int n,m;
    cin>>n>>m;
    int m2=m;
    vector < vector < int > > aristas(n);
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
        int j=0;
        while(j<aristas[i].size()) {
            if(distribucion(generador)){
                aristas[i].erase(aristas[i].begin()+j);
                m2--;
            }
            else j++;
        }
    }
    cout<<n<<" "<<m2<<endl;
    for(int i=0; i<n; ++i) {
        int n2=aristas[i].size();
        for(int j=0; j<n2 ; ++j) cout<<i<<" "<<aristas[i][j]<<endl;

    }

}
