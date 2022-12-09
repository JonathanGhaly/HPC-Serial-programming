#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>
#include <iomanip>

using namespace std;
const double PI=3.141592653589793;

struct parameters
{
    double L, D, t_in, t_sur, delta_x, delta_t;
    int numSpacePoint, numTimePoint;

    parameters(double L, double D, double t_in, double t_sur, double delta_x, double delta_t, double timeLimit)
    {
        this->L=L;
        this->D=D;
        this->t_in=t_in;
        this->t_sur=t_sur;
        this->delta_x=delta_x;
        this->delta_t=delta_t;
        numTimePoint=(int) (timeLimit/delta_t);
        numSpacePoint=(int) (L/delta_x);
    }
};

double getValue(parameters p, double x, double t, int precision)
{
    double sum=0.0;
    for(int m=1; m<precision; m++)
    {
        sum+=exp(-p.D*t*pow(PI*m/p.L, 2))*((1 - pow(-1, m))/(m*PI))*sin(m*PI*x/p.L);
    }
    return p.t_sur + 2*(p.t_in - p.t_sur)*sum;
}

double getNextStep(parameters p, int x, int t)
{
    return getValue(p, x*p.delta_x, t*p.delta_t, 1000);
}

vector<vector<double>> solve(parameters p)
{
    vector<vector<double>> table(p.numTimePoint, vector<double>(p.numSpacePoint));

    for(int t=0; t<p.numTimePoint; t++)
    {
        for(int x=0; x<p.numSpacePoint; x++)
        {
            table[t][x]=getNextStep(p, x, t);
        }
    }
    return table;
}

int main()
{
//    parameters p(0.3048, 0.00929, 37.8, 148.9, 0.05, 0.01, 0.5);
//    parameters p(1, 0.1, 100, 300, 0.05, 0.01, 1);
    parameters p(10, 0.1, 100, 300, 0.05, 0.01, 60);
    time_t start, end;
    time(&start);
    ios_base::sync_with_stdio(false);
    vector<vector<double>> table=solve(p);
    time(&end);
    double time_taken=double(end - start);
    cout << "Time taken by program is : " << fixed
         << time_taken << setprecision(5);
    cout << " sec " << endl;
    ofstream myfile;
    myfile.open("output.txt");
    for(int t=0; t<p.numTimePoint; t++)
    {
        for(int x=0; x<p.numSpacePoint; x++)
        {
            myfile << table[t][x] << " ";
        }
        myfile << endl;
    }
    char *pythonCode="python3 plot.py";

    system(pythonCode);

    return 0;
}
