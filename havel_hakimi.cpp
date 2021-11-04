#include <bits/stdc++.h>
#include <vector>
std::ifstream f("date.in");

int n, x, nr;
std::vector<int> secv;

bool havel_hakimi(std::vector<int> &secv){
    int sum= 0, ok=1;
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


return true;
}

int main() {
    f>>n;
    for(int i = 0 ; i<n ; i++){
        f>>x;
        secv.push_back(x);
    }

    if(havel_hakimi(secv) == true) std::cout<<"DA";
    else std::cout<<"NU";

    return 0;
}
