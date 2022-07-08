#include <iostream>
#include <vector>
#include <cmath>
#include <utility>
#include "Point.h"

using namespace std;
typedef Point<10,int> PointNDim;
const int N = 5000;
int KNN[] = {5,10,15,20};
PointNDim myPoints[N];
vector<pair<double, PointNDim*>> KNN_ED;
vector<pair<double, PointNDim*>> KNN_Z;


double Distance(const PointNDim& one, const PointNDim& two) {
    double result = 0.0;
    for (size_t i = 0; i < 10; ++i)
        result += (one.coords[i] - two.coords[i]) * (one.coords[i] - two.coords[i]);
    return sqrt(result);
}

void K_Nearest_Neighbors_EDistance(){
    for(int i = 1; i < N; i++){
        KNN_ED.emplace_back(Distance(myPoints[0], myPoints[i]), &myPoints[i]);
    }
    sort(KNN_ED.begin(), KNN_ED.end());
}

void K_Nearest_Neighbors_Z_order(){
    for(int i = 1; i < N; i++){
        double temp = abs(myPoints[0].z_order - myPoints[i].z_order);
        KNN_Z.emplace_back(temp, &myPoints[i]);
    }
    sort(KNN_Z.begin(), KNN_Z.end());
}

void match_KNN(int k_nn){
    double matched = 0;
    for(int j = 0; j < k_nn; j++){
        bool found = false;
        for(int k = 0; k < k_nn; k++){
            if(KNN_ED[j].second == KNN_Z[k].second) {
                matched++;
                found = true;
                break;
            }
        }
        if(found) break;
    }
    double rate = matched/(double)k_nn;
    cout<<rate<<endl;
}

void __init__(){
    cout<<"\nChosen Point -> ";
    myPoints[0].print();
    cout<<"Z_Order -> "<<myPoints[0].z_order<<"\n\n";
}

int main(){
    __init__();
    K_Nearest_Neighbors_EDistance();
    K_Nearest_Neighbors_Z_order();
    for (int i = 0; i < 4; i++){
        cout<<"For "<<KNN[i]<<" Nearest Neighbors, rate: ";
        match_KNN(KNN[i]);
    }
    
    cout<<"\n20 Nearest Neighbors - Euclidean Distance"<<endl;
    for(int i = 0; i < 20; i++){
        cout<<KNN_ED[i].first<<" "; //Distance between chosen Point and KNNs using Euclidean Distance
        KNN_ED[i].second->print();
    }
    cout<<"\n20 Nearest Neighbors - Z Order (Printing Z-Order-Distance between Points)"<<endl;
    for(int i = 0; i < 20;i++){
        cout<<abs(myPoints[0].z_order - KNN_Z[i].second->z_order)<<" "; //Distance between chosen Point and KNNs using Z-Order
        KNN_Z[i].second->print();
    }
}