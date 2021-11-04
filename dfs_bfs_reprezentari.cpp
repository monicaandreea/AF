#include <bits/stdc++.h>
#include<fstream>
#include<vector>
#include<map>
#include<queue>
std::ifstream f("date.in");
std::ofstream fg("date.out");
int n, m, a, b;

class graf{
public:
    int n, m;

    graf(int n, int m);

    std::vector< bool> viz;
    std::vector< std::vector<int> > mat;
    std::vector<std::vector<int> > lista;
    std::vector< std::pair<int, int> > muchii;

    void new_mat( int nod1, int nod2);
    void new_lista( int nod1, int nod2);
    void new_muchii( int nod1, int nod2);
    void afisare_mat();
    void afisare_lista();
    void afisare_muchii();

    void sortare_lista();

    void dfs(int nod);
    void bfs(int nod);

    int componente_conexe();
};

graf::graf(int n, int m) {
    this->n = n;
    this->m = m;

    std::vector<int> v;
    for(auto i = 0; i<n ; i++){
        viz.push_back(false);
        lista.push_back(v);
        mat.push_back(v);
        for(auto j = 0; j<n ; j++){
            mat.at(i).push_back(0);
        }
    }

}

void graf::new_mat(int nod1, int nod2) {
    mat[nod1-1][nod2-1] = 1;
    mat[nod2-1][nod1-1] = 1;
}

void graf::new_lista(int nod1, int nod2){
    lista[nod1].push_back(nod2);
    lista[nod2].push_back(nod1);
    this->sortare_lista();
}

void graf::new_muchii( int nod1, int nod2) {
    muchii.push_back( std::make_pair(nod1, nod2) );
}

void graf::sortare_lista() {
    for(auto i=1 ; i<n+1 ; i++)
        std::sort(lista[i].begin(), lista[i].end());
}

void graf::afisare_mat() {
    for(auto i=0; i<n; i++){
        for(auto j=0 ; j<n; j++){
            std::cout<<mat[i][j]<<" ";
        }
        std::cout<<"\n";
    }

    std::cout<<"\n";
}

void graf::afisare_lista() {
    for(auto i=1 ; i<n+1 ; i++){
        std::cout<<i<<" : ";
        for(auto j=0 ; j<lista[i].size(); j++)
            std::cout<<lista[i][j]<<" ";
        std::cout<<"\n";
    }

    std::cout<<"\n";
}

void graf::afisare_muchii(){
    for(auto i=0 ; i<muchii.size(); i++)
        std::cout<<muchii[i].first<<" "<<muchii[i].second<<"\n";
    std::cout<<"\n";
}

void graf::dfs(int nod){
    viz[nod] = true;
    std::cout<<nod<<" ";

    for( auto i = lista[nod].begin(); i != lista[nod].end(); i++)
        if(!viz[*i]) dfs(*i);
}

void graf::bfs(int nod){
    for(auto i = 0 ; i<=n ; i++)
        viz[i] = false;

    std::queue<int> coada;

    viz[nod] = true;
    coada.push(nod);

    while(!coada.empty()){
        int vecin = coada.front();
        std::cout<<vecin<<" ";
        coada.pop();

        for( auto i = lista[vecin].begin() ; i != lista[vecin].end(); i++){
            if( !viz[*i] ){
                viz[*i] = true;
                coada.push(*i);
            }
        }
    }

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
        g.new_mat(a, b);
        g.new_muchii(a, b);

    }

    std::cout<<"Lista de adiacenta:\n";
    g.afisare_lista();
    std::cout<<"Matricea de adiacenta:\n";
    g.afisare_mat();
    std::cout<<"Lista de muchii:\n";
    g.afisare_muchii();

    std::cout<<"DFS : "; g.dfs(1);
    std::cout<<"\nBFS : "; g.bfs(1);
    for(auto i = 0 ; i<=n ; i++)
        g.viz[i] = false;
    //std::cout<<"\nNumar de componente conexe: "<< g.componente_conexe();

    return 0;
}
