






#include <bits/stdc++.h>

using namespace std;

template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os << '(' << p.first << ", " << p.second << ')'; }
template<typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type> ostream& operator<<(ostream &os, const T_container &v) { os << '{'; string sep; for (const T &x : v) os << sep << x, sep = ", "; return os << '}'; }
void dbg_out() { cerr << endl; }
template<typename Head, typename... Tail> void dbg_out(Head H, Tail... T) { cerr << ' ' << H; dbg_out(T...); }
#ifdef LOCAL
#define dbg(...) cerr << "(" << #__VA_ARGS__ << "):", dbg_out(__VA_ARGS__)
#else
#define dbg(...)
#endif

#define ar array
#define vi vector<int>
#define pii pair<int,int>
 #define vii vector<pii> 
#define ll long long
#define ld long double
#define sza(x) ((int)x.size())
#define all(a) (a).begin(), (a).end()

 void printVector(vector<int>arr)
{
for (int i = 0; i < arr.size(); i++)
 {cout<<arr[i];}cout<<endl;}
const int MAX_N = 1e5 + 5;
const ll MOD = 1e9 + 7;
const ll INF = 1e9;
const ld EPS = 1e-9;



void solve(float p11, float p22, float p33) {

//calculating survival when two players left 

float arr[6][3] = {0};
//  arr[3][2] = 7.22;

float p1 = p11/100;
float p2 = p22/100;
float p3 = p33/100;

// cout<<endl<<p1<<endl<<p2<<endl<<p3<<endl;



//arr[][0] = survival chance A ,  arr[][1] : survival chance B , arr[][2]:C
//P(S,XYZ) for the probability that S survives
// when the current shooting order is XYZ.

//shooting order : AB  ---------------------------------------

//P(A,AB)
 arr[0][0] = p1;

 //P(B,AB)
 arr[0][1] = 1 - p1;

 //P(C,AB) 
 arr[0][2] = 1- p1;


 //shooting order : AC  -----------------------------------------

 //P(A,AC)
 arr[1][0] = p1 ;

 //P(B,AC)
 arr[1][1] = 1 - p1 ;

 //P(C,AC) 
 arr[1][2] = 1- p1 ;

 //shooting order : BA  -----------------------------------------

 //P(A,BA)  = P(B misses) × P(A,AB) 
 arr[2][0] = (1-p2)*arr[0][0];

 //P(B,BA) = P(B hits) + P(B misses) × P(B,AB)
 arr[2][1] = p2 + (1-p2)*arr[0][1];

 //P(C,BA) 
 arr[2][2] = 1- p1;


 //shooting order : BC  -----------------------------------------

 //P(A,BC)
 arr[3][0] = 1-p1 ;

 //P(B,BC) = P(B hits) + P(B misses) × P(C misses) × P(B,BC) 
 arr[3][1] = (p2)/(1-(1-p2)*(1-p3)) ;

 //P(C,BC) = P(B misses) × P(C hits) + P(B misses) × P(C misses) × P(C,BC) 
 arr[3][2] = ((1-p2)*(p3))/(1- (1-p2)*(1-p3)) ;

 
//shooting order : CA  -----------------------------------------

 //P(A,CA) = P(C misses)
 arr[4][0] = 1-p3 ;

 //P(B,CA)
 arr[4][1] = 1 - p1 ;

 //P(C,CA) 
 arr[4][2] = p3 ;

//shooting order : CB  -----------------------------------------

 //P(A,CB) 
 arr[5][0] = 1-p1 ;

 //P(B,CB) = P(C misses) × P(B hits) + P(C misses) × P(B misses) × P(B,CB
 arr[5][1] = ((1-p3)*(p2))/(1-(1-p3)*(1-p2)) ;

 //P(C,CB) 
 arr[5][2] = ((p3))/(1-(1-p3)*(1-p2)) ;



   





















   for (int i = 0; i < 6; i++)
   {
       cout<<arr[i][0]<<" "<<arr[i][1]<<" "<<arr[i][2]<<endl;
   }
   
}



int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
       
       cout<<"Truel"<<endl;
    
    float p1,p2,p3; 
     cout<<"Enter hitting probability percentage (out of 100): "<<endl;
     cout<<"Player 1: 100 ( Assumed ) ";
     p1= 100;
      cout<<"Player 2: ";
     cin>>p2;

      cout<<"Player 3: ";
     cin>>p3;

cout<< endl;
     solve(p1,p2,p3);



   
    
}