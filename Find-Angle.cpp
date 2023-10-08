#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

double M=0.7, I=49.61, D=3.45, P = 1e-10, G=9.81;  // Mass, Total Impulse, Thrust Duration, Output Precision (up to 1e-12)
double target, peak;

double f(double x){
    return I*I*sin(x)*cos(x)/G*2/M/M - 2*D*I*cos(x)/M;
}

double h(double a){
    double t = I*sin(a)/M-G*D;
    return t*t/2/G;
}

bool fp(){
    peak = asin((2*D*I/M+sqrt(4*D*D*I*I/M/M + 8*I*I*I*I/G/G*4/M/M/M/M))/(4*I*I/G*2/M/M));
    
    return (target<=f(peak));
}

double e(double x){
    return target - f(x);
}

double left(){
    double lb = 0, rb = peak;
    while(rb-lb > P){
        double mid = rb/2+lb/2;
        if(e(mid)>0){
            lb=mid;
        } else if (e(mid)<0){
            rb=mid;
        } else {
            return mid;
        }
    }
    return lb;
}

double right(){
    double lb = peak, rb = M_PI/2;
    while(rb-lb > P){
        double mid = rb/2+lb/2;
        if(e(mid)<0){
            lb=mid;
        } else if (e(mid)>0){
            rb=mid;
        } else {
            return mid;
        }
    }
    return lb;
}

int main(){
    cin >> target;
    
    if(!fp()) {cout << "Too Far!"; return 0;}
    
    double l = left(), r = right();
    cout << setprecision(10);
    cout << "Smaller Angle: " << l*180/M_PI << "°; Max Height: " << h(l) << "m" << endl;
    cout << "Larger Angle: " << r*180/M_PI << "°; Max Height: " << h(r) << "m" << endl;
}
