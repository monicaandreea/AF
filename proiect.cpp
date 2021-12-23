#include <bits/stdc++.h>
#include<fstream>
#include<vector>
#include<map>
#include<queue>
std::ifstream f("dfs.in");
std::ofstream fg("dfs.out");
int n, m, a, b;

class graf{
public:
    int n, m;

    graf(int n, int m);

    std::vector< bool> viz;
    std::vector<std::vector<int> > lista;

    void new_lista( int nod1, int nod2);
    void dfs(int nod);

    int componente_conexe();
};

graf::graf(int n, int m) {
    this->n = n;
    this->m = m;

    std::vector<int> v;
    for(auto i = 0 ; i<=n ; i++){
        viz.push_back(false);
        lista.push_back(v);
    }

}

void graf::new_lista(int nod1, int nod2){
    lista[nod1].push_back(nod2);
    lista[nod2].push_back(nod1);
}

void graf::dfs(int nod){
    viz[nod] = true;
    //std::cout<<nod<<" ";

    for( auto i = lista[nod].begin(); i != lista[nod].end(); i++)
        if(!viz[*i]) dfs(*i);
}

int graf::componente_conexe() {
    int cnt = 0;
    for(auto i = 1 ; i<=n ; i++ )
        if( !viz[i] ){
            cnt++;
            dfs(i);
        }

    return cnt;
}


int main() {
    f>>n>>m;

    graf g(n, m);
    for(int i=0 ; i<m ; i++){
        f>>a>>b;
        g.new_lista(a,b);
    }

    fg<<g.componente_conexe();

    return 0;
}
