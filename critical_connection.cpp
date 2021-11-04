class Solution {
public:
    std::map<int, std::vector<int> > lista;
    std::vector< std::vector<int> > muchii;
    std::vector<int> viz;
    std::vector<int> low;
    std::vector<int> tata;
    
    void dfs(int nod){
    static int cnt = 0;
    viz[nod] = cnt;
    low[nod] = cnt++;

    for( auto i = lista[nod].begin(); i != lista[nod].end(); i++) {
        if (viz[*i] == -1) {
            tata[*i] = nod;
            dfs(*i);
            low[nod] = fmin(low[nod], low[*i]);
        }

        if(low[*i] > viz[nod]){
            muchii.push_back(std::vector<int>({nod, *i}));
        }
        else if(*i!= tata[nod]){
            low[nod] = fmin(low[nod], viz[*i]);
        }
    }
    }


    
    vector<vector<int>> criticalConnections(int n, vector<vector<int>>& connections) {
    for(auto i = 0 ; i<=n ; i++){
        viz.push_back(-1);
        low.push_back(-1);
        tata.push_back(-1);
    }
        
    
    for(int i=0 ; i<connections.size() ; i++){
        lista[connections[i][0]].push_back(connections[i][1]);
        lista[connections[i][1]].push_back(connections[i][0]);
    }

    for(int i = 0 ; i< n ; i++){
        if(viz[i] == -1) dfs(i);
    }


   /* for(int i= 0 ; i<muchii.size() ; i++){
       std::cout<<muchii[i][0]<<" "<<muchii[i][1]<<"\n";
    }*/
    return muchii;
    }
};
