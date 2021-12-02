#include <bits/stdc++.h>
#include<fstream>
#include<vector>
#include<map>
#include<queue>

int n, m, a, b,c, s;

class graf{
public:
    std::vector< std::vector<int> > mat;
    std::vector< std::vector<int> > lista;
    std::vector< std::vector< std::pair<int, int>> > lista_cost;
    std::vector< std::pair<int, int> > muchii;

    void solve_DFS_componente_conexe();
    void solve_bfs();
    void solve_sortare_topologica();
    void solve_havel_hakimi();
    void solve_comp_conex();
    void solve_biconex();
    void solve_disjoint();
    void solve_kruskal();
    void solve_dijkstra();
    void solve_bellmanford();
    void solve_royfloyd();
    void solve_darb();
    void solve_maxflow();

private:
    void new_mat( int nod1, int nod2);
    void new_lista( int nod1, int nod2);
    void new_lista_orientat(int nod1, int nod2);
    void new_lista_cost( int nod1, int nod2, int cost);
    void new_lista_cost_neorientat(int nod1, int nod2, int cost);
    void new_muchii( int nod1, int nod2);

    void afisare_mat(std::ostream &fg);
    void afisare_lista();
    void afisare_lista_cost();
    void afisare_muchii();
    void sortare_lista();

    void dfs(int nod, std::vector<bool> &viz);

    void bfs(int nod, std::vector<bool> &viz, std::vector<int> &dist);

    void dfs_sortare_topologica(int nod, std::deque<int> &coada, std::vector<int> &viz);

    bool havel_hakimi_verificare(std::vector<int> &secv);


    void dfs_comp_conex(int nod, int &nr_comp_conex, std::vector<int> &low, std::vector<int> &membru, std::vector<int> &viz,
                        std::vector<std::vector<int> > &componente, std::deque<int> &st);

    void dfs_biconex(int nod, int &nr_comp_biconex, std::vector<int> &viz, std::vector<int> &low, std::vector<int> &tata,
                     std::deque<int> &st, std::deque<std::pair<int, int>> &perechi,
                     std::vector<std::set<int>> &componente);


    int find_set(int nod, std::vector<int> &tata);
    void union_set(int nod1, int nod2, std::vector<int> &tata, std::vector<int> adancime);

    void royfloyd();

    std::pair<int, int> BFS_darb(int start);

    int BFS_maxflow(int start, int dest, std::vector<int> &tata, std::vector<std::vector<int>> &cap);

    void dijkstra(int start, std::vector<int> &dist);

    void bellmanford(int start, std::vector<int> &dist, bool neg);


    void
    kruskal(std::vector<std::pair<int, std::pair<int, int>>> &apm,
            std::vector<std::pair<int, std::pair<int, int>>> &muchii,
            int &sum);

};

void graf::new_mat(int nod1, int nod2) {
    mat[nod1-1][nod2-1] = 1;
    mat[nod2-1][nod1-1] = 1;
}

void graf::new_lista(int nod1, int nod2){
    lista[nod1].push_back(nod2);
    lista[nod2].push_back(nod1);
}

void graf::new_lista_orientat(int nod1, int nod2){
    lista[nod1].push_back(nod2);
}

void graf::new_lista_cost(int nod1, int nod2, int cost) {
    lista_cost[nod1].push_back(std::make_pair(nod2, cost));
}

void graf::new_lista_cost_neorientat(int nod1, int nod2, int cost) {
    lista_cost[nod1].push_back(std::make_pair(nod2, cost));
    lista_cost[nod2].push_back(std::make_pair(nod1, cost));
}

void graf::new_muchii( int nod1, int nod2) {
    muchii.push_back( std::make_pair(nod1, nod2) );
}

void graf::sortare_lista() {
    for(auto i=1 ; i<n+1 ; i++)
        std::sort(lista[i].begin(), lista[i].end());
}

void graf::afisare_mat(std::ostream& fg) {
    for(auto i=0; i<n; i++){
        for(auto j=0 ; j<n; j++){
            fg<<mat[i][j]<<" ";
        }
        fg<<"\n";
    }
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

void graf::solve_DFS_componente_conexe() {
    std::ifstream f("dfs.in");
    std::ofstream fg("dfs.out");

    std::vector< bool> viz;
    std::vector<int> v;

    f>>n>>m;

    for(auto i = 0 ; i<=n ; i++) {
        viz.push_back(false);
        lista.push_back(v);
    }

    for(int i=0 ; i<m ; i++){
        f>>a>>b;
        new_lista(a,b);
    }

    int cnt = 0;
    for(auto i = 0 ; i<n ; i++ )
        if( !viz[i] ){
            cnt++;
            dfs(i, viz);
        }

    fg<< cnt;
}

void graf::bfs(int nod, std::vector< bool> &viz, std::vector< int> &dist){
    std::queue<int> coada;
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
}

void graf::solve_bfs(){
    std::ifstream f("bfs.in");
    std::ofstream fg("bfs.out");

    std::vector< bool> viz;
    std::vector<int> dist;
    std::vector<int> v;

    f>>n>>m>>s;

    for(auto i = 0 ; i<=n ; i++) {
        viz.push_back(false);
        dist.push_back(-1);
        lista.push_back(v);
    }

    for(int i=0 ; i<m ; i++){
        f>>a>>b;
        new_lista_orientat(a,b);
    }

    bfs(s, viz, dist);

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

void graf::solve_sortare_topologica(){
    std::ifstream f("sortaret.in");
    std::ofstream fg("sortaret.out");

    std::vector<int> viz;
    std::deque<int> coada;
    std::vector<int> v;

    f>>n>>m;

    for(auto i = 0 ; i<=n ; i++){
        viz.push_back(-1);
        lista.push_back(v);
    }

    for(int i=0 ; i<m ; i++){
        f>>a>>b;
        new_lista(a-1,b-1);
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

            if(secv[i] < 0) return false;

        }

        for( auto i = secv.begin() ; i!=secv.end() ; i++)
            std::cout<<*i<<" ";
        std::cout<<"\n";

    }
return true;
}

void graf::solve_havel_hakimi(){
    std::ifstream f("hh.in");
    std::ofstream fg("hh.out");
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

void graf::solve_comp_conex(){
    std::ifstream f("ctc.in");
    std::ofstream fg("ctc.out");

    std::vector<int> viz;
    std::vector<int> low;
    std::vector<int> membru;
    std::deque<int> st;
    std::vector< std::vector<int> > componente;

    int nr_comp_conex = 0;

    f>>n>>m;

    std::vector<int> v;
    for(auto i = 0 ; i<=n ; i++){
        viz.push_back(-1);
        low.push_back(-1);
        membru.push_back(0);
        lista.push_back(v);
    }

    for(int i=0 ; i<m ; i++){
        f>>a>>b;
        new_lista_orientat(a-1,b-1);
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

void graf::solve_biconex(){
    std::ifstream f("biconex.in");
    std::ofstream fg("biconex.out");

    std::vector<std::set<int>> componente;
    std::vector<int> viz;
    std::vector<int> low;
    std::vector<int> tata;
    std::deque<int> st;
    std::deque<std::pair<int, int>> perechi;
    std::vector<int> v;
    int nr_comp_biconex = 0;

    f>>n>>m;

    for(auto i = 0 ; i<=n ; i++) {
        viz.push_back(-1);
        low.push_back(-1);
        tata.push_back(-1);
        lista.push_back(v);
    }

    for(int i=0 ; i<m ; i++){
        f>>a>>b;
        new_lista(a-1,b-1);
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
}

void graf::solve_disjoint(){
    std::ifstream f("disjoint.in");
    std::ofstream fg("disjoint.out");

    std::vector<int> tata;
    std::vector<int> adancime;
    int op;

    f>>n>>m;

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

void graf::kruskal(std::vector< std::pair< int, std::pair<int, int>> > &apm, std::vector< std::pair< int, std::pair<int, int>> > &muchii, int &sum){
    std::vector<int> id;

    for(auto i=0 ; i<n ; i++){
        for( auto j = lista_cost[i].begin() ; j != lista_cost[i].end(); j++){
            muchii.push_back( std::make_pair( j->second, std::make_pair(i, j->first)) );
        }

        id.push_back(i);
    }

    std::sort(muchii.begin() , muchii.end());

    for(auto i = muchii.begin() ; i!= muchii.end() ; i++){
        if( id[i->second.first] != id[i->second.second] ){
            sum = sum + i->first;
            apm.push_back( *i );

            int id_vechi = id[i->second.first];
            int id_nou = id[i->second.second];

            for(int i = 0 ; i<n ; i++){
                if( id[i] == id_vechi ) id[i] = id_nou;
            }
        }
    }
}

void graf::solve_kruskal() {
    std::ifstream f("apm.in");
    std::ofstream fg("apm.out");

    std::vector< std::pair< int, std::pair<int, int>> > muchii;
    std::vector< std::pair< int, std::pair<int, int>> > apm;
    std::vector< std::pair<int, int>> p;
    int sum = 0;

    f>>n>>m;

    for( int i=0 ; i<n ; i++){
        lista_cost.push_back(p);
    }

    for(int i=0 ; i<m ; i++){
        f>>a>>b>>c;
        new_lista_cost_neorientat(a-1, b-1, c);
    }

    kruskal(apm,muchii, sum);

    fg<<sum<<"\n"<<apm.size()<<"\n";

    for(auto i = apm.begin() ; i!= apm.end() ; i++) {
        fg<<i->second.first + 1<<" "<<i->second.second + 1<<"\n";
    }


}

void graf::bellmanford(int start, std::vector<int> &dist, bool neg){
    std::vector<bool> viz;
    std::vector<int> ord;
    std::queue<int> coada;

    for( int i=0 ; i<n ; i++)
    {
        viz.push_back(false);
        ord.push_back(0);
    }

    dist[start] = 0;
    coada.push(start);
    viz[start] = true;

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
}

void graf::solve_bellmanford(){
    std::ifstream f("bellmanford.in");
    std::ofstream fg("bellmanford.out");

    std::vector<int> dist;
    std::vector< std::pair<int, int>> p;
    bool neg = false;

    f>>n>>m;

    for( int i=0 ; i<n ; i++)
    {
        dist.push_back(INT_MAX);
        lista_cost.push_back(p);
    }

    for(int i=0 ; i<m ; i++){
        f>>a>>b>>c;
        new_lista_cost(a-1, b-1, c);
    }

    bellmanford(0, dist, neg);

    if(neg) fg<<"Ciclu negativ!";
    else
    {
        for(auto i=1 ; i<n ; i++) {
            fg<<dist[i]<<" ";
        }
    }

}

void graf::dijkstra(int start, std::vector<int> &dist){
    dist[start] = 0;

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
                s.insert(std::make_pair(dist[vecin], vecin));
            }
        }
    }
}

void graf::solve_dijkstra(){
    std::ifstream f("dijkstra.in");
    std::ofstream fg("dijkstra.out");

    f>>n>>m;

    std::vector<int> tata;
    std::vector<int> dist;
    std::vector<bool> viz;
    std::vector< std::pair<int, int>> p;

    for( int i=0 ; i<n ; i++)
    {
        dist.push_back(INT_MAX);
        viz.push_back(false);
        tata.push_back(-1);
        lista_cost.push_back(p);
    }

    for(int i=0 ; i<m ; i++){
        f>>a>>b>>c;
        new_lista_cost(a-1, b-1, c);
    }

    dijkstra(0, dist);

    for(int i = 1; i<n ; i++)
    {
        if(dist[i] == INT_MAX) fg<<"0 ";
        else fg<<dist[i]<<" ";
    }

}

void graf::royfloyd(){
    for(int i=0 ; i<n; i++)
        for(int j=0 ; j<n; j++)
            for(int k=0 ; k<n; k++)
                if(mat[j][i] && mat[i][k] && (mat[j][k] > mat[j][i] + mat[i][k] || !mat[j][k]) && j!=k)
                    mat[j][k] = mat[j][i] + mat[i][k];
}

void graf::solve_royfloyd() {
    std::ifstream f("royfloyd.in");
    std::ofstream fg("royfloyd.out");

    f>>n;

    std::vector<int> v(n,0);

    for(auto i = 0; i<n ; i++){
        mat.push_back(v);
    }

    for( int i=0 ; i<n ; i++){
        for( int j=0 ; j<n ; j++){
            f>>a;
            mat[i][j] = a;
        }
    }

    royfloyd();

    afisare_mat( fg);

}

std::pair<int, int> graf::BFS_darb(int start){
    std::vector<int> v;
    std::vector<int> viz;
    std::vector<int> dist;
    std::queue<int> coada;
    int diametru;
    int dest;

    for(int i = 0; i<n ; i++){
        viz.push_back(-1);
        dist.push_back(0);
    }

    viz[start] = 1;
    coada.push(start);
    dist[start] = 1;

    while( !coada.empty()){
        int nod = coada.front();
        coada.pop();

        for(auto vecin = lista[nod].begin() ; vecin != lista[nod].end(); vecin++){
            if(viz[*vecin] == -1){
                coada.push(*vecin);
                viz[*vecin] = 1;
                dist[*vecin] = dist[nod] + 1;

                diametru = dist[*vecin];
                dest = *vecin;
            }
        }
    }

    return std::make_pair(diametru, dest);
}

void graf::solve_darb() {
    std::ifstream f("darb.in");
    std::ofstream fg("darb.out");

    f>>n;

    std::vector<int> v;
    int diametru, dest ;
    std::pair<int, int> s;

    for(int i = 0; i<n ; i++){
        lista.push_back(v);
    }

    for( int i=0 ; i<n-1 ; i++){
        f>>a>>b;
        lista[a-1].push_back(b-1);
        lista[b-1].push_back(a-1);
    }

    s = BFS_darb(0);
    dest = s.second;
    s = BFS_darb(dest);
    diametru = s.first;
    fg<<diametru;

}

int graf::BFS_maxflow(int start, int dest, std::vector<int> &tata, std::vector<std::vector<int>> &cap){
    std::queue<std::pair<int, int>> coada;
    for(int i=0 ; i<n ; i++){
        tata[i] = -1;
    }

    tata[start] = -2;

    coada.push(std::make_pair(start, INT_MAX));

    while(!coada.empty()){

        int nod = coada.front().first;
        int flux = coada.front().second;
        coada.pop();

        for(auto vecin = lista[nod].begin(); vecin != lista[nod].end(); vecin++){
            //std::cout<<nod<<" "<<*vecin<<" "<<cap[nod][*vecin]<<"\n";
            if( tata[*vecin] == -1 && cap[nod][*vecin] >0){
                tata[*vecin] = nod;

                int flux_nou = std::min(flux, cap[nod][*vecin]);

                if( *vecin == dest) return flux_nou;

                coada.push(std::make_pair(*vecin, flux_nou));
            }
        }
    }
    return 0;
}

void graf::solve_maxflow() {
    std::ifstream f("maxflow.in");
    std::ofstream fg("maxflow.out");

    f>>n>>m;

    std::vector<std::vector<int> > cap;
    std::vector<int> tata(n,0);
    std::vector<int> v(n,0);
    std::vector<int> l;
    int start=0;
    int dest=n-1;

    for(auto i = 0; i<n ; i++){
        lista.push_back(l);
        cap.push_back(v);
    }

    for( int i=0 ; i<m ; i++){
        f>>a>>b>>c;
        lista[a-1].push_back(b-1);
        cap[a-1][b-1] = c;
    }

    int flux = 0;

    int flux_nou = BFS_maxflow(start, dest, tata, cap);
    while(flux_nou){

        flux += flux_nou;
        int nod = dest;

        while(nod != start){
            int t = tata[nod];
            cap[t][nod] -= flux_nou; //actualizezi flowul gasit  + muchiile de intoarcere
            cap[nod][t] += flux_nou;
            nod = t;
        }


        flux_nou = BFS_maxflow(start, dest, tata, cap);
    }

    fg<<flux;

}

int main() {
    graf g;

    g.solve_bfs();

    return 0;
}
