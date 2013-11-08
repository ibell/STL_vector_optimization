
#include <vector>
#include <iostream>
#include "time.h"
#include "math.h"

struct cont
{
    double A,B,C,D;
};

class wrapper
{
public:
    std::vector<double> A, B, C, D;
    std::vector<cont> CCCC;

    double summer1(double tau, double delta)
    {
        double summer = 0;
        for (unsigned int i = 0; i < A.size(); ++i)
        {
            summer += A[i]*B[i]*log(tau) + C[i]*D[i]*log(delta);
        }
        return summer;
    }

    double summer2(double tau, double delta)
    {
        double summer = 0;
        for(unsigned int i = 0; i < CCCC.size(); ++i)
        {
            //summer += CCCC[i].A*CCCC[i].B*log(tau) + CCCC[i].C*CCCC[i].D*log(delta);
            
            cont c = CCCC[i];
            summer += c.A*c.B*log(tau) + c.C*c.D*log(delta);
        }
        return summer;
    }
    
    double summer3(double tau, double delta)
    {
        double summer = 0;
        for(std::vector<cont>::const_iterator it = CCCC.begin(); it != CCCC.end(); ++it)
        {
            summer += (*it).A*(*it).B*log(tau) + (*it).C*(*it).D*log(delta);
        }
        return summer;
    }
};

int main()
{
    wrapper w = wrapper();
    
    clock_t t1, t2;
    
    unsigned long N = 10;
    
    w.A = std::vector<double>(N,0.3);
    w.B = w.A;
    w.C = w.A;
    w.D = w.A;
    
    unsigned long Ntries = 100000000;
    
    t1 = clock(); 
    double s1 = 0;
    for (int i = 0; i < Ntries; i++) { s1 += w.summer1(1.3+i*1e-16,1.1); }
    t2 = clock();
    std::cout << "Time summer 1: " << (double)(t2-t1)/(double)CLOCKS_PER_SEC/Ntries*1e6 << std::endl;
    
    w.CCCC.resize(N);
    for(unsigned int i = 0; i < w.CCCC.size(); ++i)
    {
        w.CCCC[i].A = w.A[i];
        w.CCCC[i].B = w.B[i];
        w.CCCC[i].C = w.C[i];
        w.CCCC[i].D = w.D[i];
    }
    
    t1 = clock(); 
    double s2 = 0;
    for (int i = 0; i < Ntries; i++) { s2 += w.summer2(1.3+i*1e-16,1.1); }
    t2 = clock();
    std::cout << "Time summer 2: " << (double)(t2-t1)/(double)CLOCKS_PER_SEC/Ntries*1e6 << std::endl;
    
    t1 = clock(); 
    double s3 = 0;
    for (int i = 0; i < Ntries; i++) { s3 += w.summer3(1.3+i*1e-16,1.1); }
    t2 = clock();
    std::cout << "Time summer 3: " << (double)(t2-t1)/(double)CLOCKS_PER_SEC/Ntries*1e6 << std::endl;
    
    std::cout << "Values: " << s1 << " & " << s2 << " & " << s3 << std::endl;
    
    return 0;
}