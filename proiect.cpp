#include <bits/stdc++.h>
#include<fstream>
#include<vector>
#include<map>
#include<queue>
std::ifstream f("date.in");
std::ofstream fg("date.out");
int n, m, a, b,c;

class graf{
public:
    int n, m;

    graf(int n, int m);

    //std::vector< bool> viz;
    std::vector< std::vector<int> > mat;
    std::vector<std::vector<int> > lista;
    std::vector<std::vector< std::pair<int, int>> > lista_cost;
    std::vector< std::pair<int, int> > muchii;

    void new_mat( int nod1, int nod2);
    void new_lista( int nod1, int nod2);
    void new_lista_cost( int nod1, int nod2, int cost);
    void new_muchii( int nod1, int nod2);

    void afisare_mat();
    void afisare_lista();
    void afisare_lista_cost();
    void afisare_muchii();

    void sortare_lista();

    void dfs(int nod, std::vector<bool> &viz);
    int DFS_componente_conexe();

    void bfs(int nod);

    void dfs_sortare_topologica(int nod, std::deque<int> &coada, std::vector<int> &viz);
    void sortare_topologica();

    bool havel_hakimi_verificare(std::vector<int> &secv);
    void havel_hakimi();

    void dfs_comp_conex(int nod, int &nr_comp_conex, std::vector<int> &low, std::vector<int> &membru, std::vector<int> &viz,
                        std::vector<std::vector<int> > &componente, std::deque<int> &st);
    void comp_conex();

    void biconex();
    void dfs_biconex(int nod, int &nr_comp_biconex, std::vector<int> &viz, std::vector<int> &low, std::vector<int> &tata,
                     std::deque<int> &st, std::deque<std::pair<int, int>> &perechi,
                     std::vector<std::set<int>> &componente);

    void disjoint();
    int find_set(int nod, std::vector<int> &tata);
    void union_set(int nod1, int nod2, std::vector<int> &tata, std::vector<int> adancime);

    void dijkstra();
    void bellmanford();



};

graf::graf(int n, int m) {
    this->n = n;
    this->m = m;

    std::vector<int> v;
    std::vector< std::pair<int, int>> p;

    for(auto i = 0; i<n ; i++){
        lista.push_back(v);
        mat.push_back(v);
        lista_cost.push_back(p);
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
}

void graf::new_lista_cost(int nod1, int nod2, int cost) {
    lista_cost[nod1].push_back(std::make_pair(nod2, cost));
    //lista_cost[nod2].push_back(std::make_pair(nod1, cost));
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

void graf::afisare_lista_cost() {
    for(auto i=0 ; i<n ; i++){
        std::cout<<i<<" - ";
        for( auto j = lista_cost[i].begin() ; j != lista_cost[i].end(); j++){
            std::cout<<" ( "<< j->first<<" , "<<j->second<<" ) ";
        }
        std::cout<<"\n";
    }

    std::cout<<"\n";
}

void graf::afisare_muchii(){
    for(auto i=0 ; i<muchii.size(); i++)
        std::cout<<muchii[i].first<<" "<<muchii[i].second<<"\n";
    std::cout<<"\n";
}


void graf::dfs(int nod, std::vector<bool> &viz){
    viz[nod] = true;
    //std::cout<<nod<<" ";

    for( auto i = lista[nod].begin(); i != lista[nod].end(); i++)
        if(!viz[*i]) dfs(*i, viz);
}

int graf::DFS_componente_conexe() {
    std::vector< bool> viz;

    for(auto i = 0 ; i<=n ; i++) {
        viz.push_back(false);
    }

    int cnt = 0;
    for(auto i = 0 ; i<n ; i++ )
        if( !viz[i] ){
            cnt++;
            dfs(i, viz);
        }

    return cnt;
}

void graf::bfs(int nod){
    std::queue<int> coada;
    std::vector< bool> viz;
    std::vector<int> dist;

    for(auto i = 0 ; i<=n ; i++) {
        viz.push_back(false);
        dist.push_back(-1);
    }

    viz[nod] = true;
    dist[nod] = 0;
    coada.push(nod);

    while(!coada.empty()){
        int vecin = coada.front();
        //std::cout<<vecin<<" ";
        coada.pop();

        for( auto i = lista[vecin].begin() ; i != lista[vecin].end(); i++){
            if( !viz[*i] ){
                viz[*i] = true;
                coada.push(*i);
                dist[*i] = dist[vecin] + 1;
            }
        }
    }

    //std::cout<<"\n";
    for(int i = 1; i <= n; i++)
        fg<<dist[i]<<" ";

}

void graf::dfs_sortare_topologica(int nod, std::deque<int> &coada, std::vector<int> &viz){
    static int cnt = 0;
    viz[nod] = ++cnt;

    for( auto i = lista[nod].begin(); i != lista[nod].end(); i++) {
        if (viz[*i] == -1) dfs_sortare_topologica(*i, coada, viz);
    }

    coada.push_back(nod);
}

void graf::sortare_topologica(){
    std::vector<int> viz;
    std::deque<int> coada;

    for(auto i = 0 ; i<=n ; i++){
        viz.push_back(-1);
    }


    for(auto i = 0 ; i<=n ; i++){
        viz.push_back(-1);
    }

    for(int i = 0 ; i< n ; i++){
        if(viz[i] == -1) dfs_sortare_topologica(i, coada, viz);
    }

    /*for(int i=0 ; i<n ; i++)
        std::cout<<viz[i]<<" ";*/

    while(!coada.empty()){
        int aux = coada.back();
        fg<<aux + 1<<" ";
        coada.pop_back();
    }
}

bool graf::havel_hakimi_verificare(std::vector<int> &secv){
    int sum= 0, ok=1, nr;
    for( auto i = secv.begin() ; i!=secv.end() ; i++){
        sum += *i;
        if(*i >= n) ok = 0;
    }

    if(sum%2 != 0 || ok ==0) return false;

    while(ok){
        sort(secv.begin(), secv.end(), std::greater<>());

        if(secv[0] == 0) return true; //toate elementele sunt 0 daca cel mai mare e 0

        int cnt = secv[0];
        secv.erase(secv.begin()); //sterg primul elem

        if( cnt  > secv.size()) return false; //verific ca nu ies din secventa

        for(int i= 0; i< cnt ; i++){
            secv[i]--;

            if(secv[nr] < 0) return false;

        }

        for( auto i = secv.begin() ; i!=secv.end() ; i++)
            std::cout<<*i<<" ";
        std::cout<<"\n";

    }

}

void graf::havel_hakimi(){
    std::vector<int> secv;
    f>>n;
    for(int i = 0 ; i<n ; i++){
        f>>a;
        secv.push_back(a);
    }

    if(havel_hakimi_verificare(secv)) std::cout << "DA";
    else std::cout<<"NU";

}

void graf::dfs_comp_conex(int nod, int &nr_comp_conex, std::vector<int> &low, std::vector<int> &membru, std::vector<int> &viz,
                          std::vector<std::vector<int> > &componente, std::deque<int> &st){
    static int cnt = 0;
    viz[nod] = ++cnt;
    low[nod] = cnt;
    st.push_back(nod);
    membru[nod] = 1;

    for( auto i = lista[nod].begin(); i != lista[nod].end(); i++) {
        if (viz[*i] == -1) {
            dfs_comp_conex(*i, nr_comp_conex, low, membru, viz, componente, st);
            low[nod] = fmin(low[nod], low[*i]);
        } else if (membru[*i] == 1) {
            low[nod] = fmin(low[nod], viz[*i]);
        }
    }

    int aux = 0;
    if(low[nod] == viz[nod]){

        std::vector<int>v;
        componente.push_back(v);

        while(st.back() != nod){
            aux = st.back();
            //std::cout<< aux<<" ";

            componente[nr_comp_conex].push_back(aux);
            membru[aux] = 0;
            st.pop_back();
        }

        aux = st.back();
        //std::cout<< aux<<"\n ";
        componente[nr_comp_conex].push_back(aux);
        membru[aux] = 0;
        st.pop_back();

        ++nr_comp_conex;
    }

}

void graf::comp_conex(){
    std::vector<int> viz;
    std::vector<int> low;
    std::vector<int> membru;
    std::deque<int> st;
    std::vector< std::vector<int> > componente;

    int nr_comp_conex = 0;

    std::vector<int> v;
    for(auto i = 0 ; i<=n ; i++){
        viz.push_back(-1);
        low.push_back(-1);
        membru.push_back(0);
    }

    for(int i = 0 ; i< n ; i++){
        if(viz[i] == -1) dfs_comp_conex(i, nr_comp_conex, low, membru, viz, componente, st);
    }

    fg<<nr_comp_conex<<"\n";

    for(int i= 0 ; i<nr_comp_conex ; i++){
        for(auto j= componente[i].begin(); j!=componente[i].end(); j++)
            fg<<*j + 1<<" ";
        fg<<"\n";
    }

}

void graf::dfs_biconex(int nod, int &nr_comp_biconex, std::vector<int> &viz, std::vector<int> &low, std::vector<int> &tata,
                       std::deque<int> &st, std::deque<std::pair<int, int>> &perechi,
                       std::vector<std::set<int>> &componente ){
    static int cnt = 0;
    std::set<int> s;
    viz[nod] = ++cnt;
    low[nod] = cnt;
    st.push_back(nod);
    int nr_copii = 0;

    for( auto i = lista[nod].begin(); i != lista[nod].end(); i++) {
        if (viz[*i] == -1) {
            tata[*i] = nod;
            nr_copii++;
            perechi.push_back(std::make_pair(nod, *i));

            dfs_biconex(*i, nr_comp_biconex, viz, low, tata, st, perechi, componente );

            low[nod] = fmin(low[nod], low[*i]);
            //  std::cout <<nod<<" si "<<*i<< "\n";
            //  std::cout <<viz[nod]<<" si "<<low[*i]<< "\n";

            if ( low[*i] >= viz[nod]) { //e punct de articulatie
                componente.push_back(s);

                while (perechi.back().first != nod || perechi.back().second != *i) {
                    componente[nr_comp_biconex].insert(perechi.back().first);
                    componente[nr_comp_biconex].insert(perechi.back().second);
                    //std::cout << perechi.back().first << " " << perechi.back().second << " ";
                    perechi.pop_back();
                }
                componente[nr_comp_biconex].insert(perechi.back().first);
                componente[nr_comp_biconex].insert(perechi.back().second);
                //std::cout << perechi.back().first << " " << perechi.back().second << " ";
                perechi.pop_back();

                ++nr_comp_biconex;

                //std::cout << "\n";
            }

        } else if (*i != tata[nod]) {
            low[nod] = fmin(low[nod], viz[*i]);
        }
    }

}

void graf::biconex(){
    std::vector<std::set<int>> componente;
    std::vector<int> viz;
    std::vector<int> low;
    std::vector<int> tata;
    std::deque<int> st;
    std::deque<std::pair<int, int>> perechi;
    int nr_comp_biconex = 0;

    for(auto i = 0 ; i<=n ; i++) {
        viz.push_back(-1);
        low.push_back(-1);
        tata.push_back(-1);
    }

    for(int i = 0 ; i< n ; i++){
        if(viz[i] == -1) dfs_biconex(i, nr_comp_biconex, viz, low, tata, st, perechi, componente );
    }

    fg<<nr_comp_biconex<<"\n";

    for(int i = 0 ; i<nr_comp_biconex ; i++){
        for(auto j = componente[i].begin() ; j != componente[i].end() ; j++)
            fg<< *j + 1<<" ";
        fg<<"\n";
    }

}

int graf::find_set(int nod, std::vector<int> &tata) {
    if( nod == tata[nod])  return nod;
    return tata[nod] =  find_set(tata[nod], tata);
}

void graf::union_set(int nod1, int nod2, std::vector<int> &tata, std::vector<int> adancime){
    nod1 = find_set(nod1, tata);
    nod2 = find_set(nod2, tata);

    if(nod1 != nod2) {
        if( adancime[nod1] < adancime[nod2]) std::swap( nod1, nod2);

        tata[nod2] = nod1;

        if(adancime[nod1] == adancime[nod2]) adancime[nod1]++;
    }

    nod1 = find_set(nod1, tata);
    nod2 = find_set(nod2, tata);
}

void graf::disjoint(){
    std::vector<int> tata;
    std::vector<int> adancime;
    int op;

    for(auto i = 0 ; i<=n ; i++){
        tata.push_back(i);
        adancime.push_back(0);
    }

    for(int i=0 ; i<m ; i++){
        f>>op>>a>>b;

        if(op == 1){
            union_set(a, b, tata, adancime);
        }

        if(op == 2){
            a = find_set(a, tata);
            b = find_set(b, tata);

            if(a!=b) fg<<"NU\n";
            else fg<<"DA\n";
        }
    }

}

void graf::bellmanford(){
    std::vector<int> dist;
    std::queue<int> coada;
    std::vector<bool> viz;
    std::vector<int> ord;


    for( int i=0 ; i<n ; i++)
    {
        dist.push_back(INT_MAX);
        viz.push_back(false);
        ord.push_back(0);
    }

    bool neg = false;
    dist[0] = 0;
    coada.push(0);
    viz[0] = true;

    while(!coada.empty() && !neg) {
        int nod = coada.front();
        coada.pop();
        viz[nod] = false;

        for (auto i = lista_cost[nod].begin(); i != lista_cost[nod].end(); i++) {

            if (dist[nod] < INT_MAX) {


                int vecin = i->first;
                int cost = i->second;

                if (dist[vecin] > dist[nod] + cost) {
                    dist[vecin] = dist[nod] + cost;

                    if (!viz[vecin]) {
                        if( ord[vecin] > n) neg = true;
                        else{
                            coada.push(vecin);
                            viz[vecin] = true;
                            ord[vecin]++;
                        }
                    }
                }

            }
        }

    }

    if(neg) fg<<"Ciclu negativ!";
    else
    {
        for(auto i=1 ; i<n ; i++) {
            fg<<dist[i]<<" ";
        }
    }

}

void graf::dijkstra(){
    std::vector<int> tata;
    std::vector<int> dist;
    std::vector<bool> viz;

    for( int i=0 ; i<n ; i++)
    {
        dist.push_back(INT_MAX);
        viz.push_back(false);
        tata.push_back(-1);
    }

    dist[0] = 0;

    std::set<std::pair<int, int>> s;

    s.insert( std::make_pair(0, 0));

    while(!s.empty()){
        int nod = s.begin()->second;

        s.erase(s.begin());

        for(auto i = lista_cost[nod].begin() ; i != lista_cost[nod].end(); i++){
            int vecin = i->first;
            int cost = i->second;

            if(dist[vecin] > dist[nod] + cost){
                s.erase(std::make_pair(dist[vecin], vecin));
                dist[vecin] = cost + dist[nod];
                tata[vecin] = nod;
                s.insert(std::make_pair(dist[vecin], vecin));
            }
        }
    }

    for(int i = 1; i<n ; i++)
    {
        if(dist[i] == INT_MAX) fg<<"0 ";
        else fg<<dist[i]<<" ";
    }


}

int main() {
    f>>n>>m;

    graf g(n, m);
    for(int i=0 ; i<m ; i++){
        f>>a>>b;
        g.new_lista(a-1,b-1);
        // g.new_mat(a, b);
       // g.new_muchii(a, b);


        /*f>>a>>b>>c;
        g.new_lista_cost(a-1, b-1, c); */

    }
 /*
    std::cout<<"Lista de adiacenta:\n";
    g.afisare_lista();
    std::cout<<"Matricea de adiacenta:\n";
    g.afisare_mat();
    std::cout<<"Lista de muchii:\n";
    g.afisare_muchii();*/

    //fg<<g.DFS_componente_conexe();
    //g.bfs();

    //g.comp_conex();
    //g.sortare_topologica();
    //g.biconex();

    //g.disjoint();
    //g.bellmanford();
    //g.dijkstra();

    return 0;
}
