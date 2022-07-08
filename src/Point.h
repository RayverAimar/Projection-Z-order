#ifndef POINT_INCLUDED
#define POINT_INCLUDED

#include <iostream>
#include <random>
#include <vector>
#include <algorithm>

using namespace std;

typedef unsigned __int64 ll;

template<size_t N, typename T>
struct Point{
    
    //Constructors & Destructor
    Point();
    ~Point();

    //Auxiliar Function
    void print();
    void get_z_order();
    //Operators
    Point<N,T>& operator = (Point<N,T>&);
    bool        operator ==  (const Point<N,T>&);

    T  operator []  (std::size_t) const;

    T* coords;
    int z_order;
private:
    size_t _size;
};

template<size_t N, typename T>
Point<N,T>::Point():_size(N){
    coords = new T[N];
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<>distrib(1,7);
    for(size_t i = 0; i < _size; i++){
        coords[i]=distrib(gen);
    }
    get_z_order();
}

template<size_t N, typename T>
Point<N,T>::~Point(){

}

template <size_t N, typename T>
T Point<N, T>::operator[] (size_t i) const{
    return coords[i];
}

template <size_t N, typename T>
Point<N, T>& Point<N, T>::operator=(Point<N,T>& point)
{   
    for (size_t i = 0; i < _size; i++)
    {
        coords[i] = point[i];
    }
    return *this;
}

template <size_t N, typename T>
bool Point<N, T>::Point::operator == (const Point& point) 
{
    for (int i = 0; i < _size; i++){
        if (coords[i] != point.coords[i])
        {
            return false;
        }
    }
    return true;
}

template <size_t N, typename T>
void Point<N, T>::print(){
    cout<<"(";
    for(size_t i = 0; i < _size; i++){
        cout<<coords[i];
        if (i<_size-1)
        {
            cout<<", ";
        }
    }
    cout<<")\n";
}

template <size_t N, typename T>
void Point<N, T>::get_z_order(){
    int ans = 0;
    vector<int> v;
    for(int mask = 0; mask < 3; mask++){
        int f = 1<<mask;    
        for(int i = 0; i < N; i++){
            int t = f&coords[i]?1:0;
            v.push_back(t);
        }
    }
    for(int i = 0; i < v.size();i++){
        if(!v[i]) continue;
        int t = 1<<i;
        ans+=t;
    }
    z_order=ans;
}
#endif //POINT_INCLUDED