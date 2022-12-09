#include <iostream>
#include "cmath"
#include <fstream>
#include <iomanip>

using namespace std;

struct parameters
{
    double x; // pos
    double v; // velocity
    double m; // mass
    double r; // rest length of spring
    double k; // spring stiffness
    double b; // damping const
    double ts; // timestep
    double tr; // timerate
    double dx;
    double dv;
    double h;
    int precision;
    ofstream outfile;

    parameters(double x,
               double m,
               double r,
               double k,
               double b,
               double ts,
               double tr,
               double h,
               int precision)
    {
        this->x=x;
        this->m=m;
        this->r=r;
        this->k=k;
        this->b=b;
        this->ts=ts;
        this->tr=tr;
        this->h=h;
        this->precision = precision;
        CalcDx(v);
        CalcDv(x, v);
        outfile.open("out.txt");
    }

    double CalcDx(double v)
    {
        this->dx=v;
        return dx;
    }

    double CalcDv(double x, double v)
    {
        this->dv=(-this->b*v - this->k*x)/this->m;
        return dv;
    }

    void rk4()
    {
        double k1, k2, k3, k4, l1, l2, l3, l4;
        for(int i=0; i<=this->precision; ++i)
        {
            k1=CalcDx(x);
            l1=CalcDv(x, v);

            k2=CalcDx(v + l1*h/2);
            l2=CalcDv(x + k1*h/2, v + l1*h/2);

            k3=CalcDx(v + l2*h/2);
            l3=CalcDv(x + k2*h/2, v + l2*h/2);

            k4=CalcDx(v + l3*h);
            l4=CalcDv(x + k3*h, v + l3*h);
            this->x=this->x + h/6*(k1 + 2*k2 + 2*k3 + k4);
            this->v=this->v + h/6*(l1 + 2*l2 + 2*l3 + l4);
            outfile << this->x << endl;
        }
    }
};

int main()
{
    parameters *p=new parameters(
            -2.5,
            50,
            2.5,
            15,
            0.1,
            0.025,
            1,
            0.05,
            100
    );
    time_t start, end;
    time(&start);
    ios_base::sync_with_stdio(false);
    p->rk4();
    time(&end);
    double time_taken=double(end - start);
    cout << "Time taken by program is : " << fixed
         << time_taken << setprecision(5);
    cout << " sec " << endl;
}
