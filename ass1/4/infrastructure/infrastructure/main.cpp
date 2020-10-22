#include <stdio.h>
#include <vector>
#include <mpi.h>
#include <cmath>
#include <iostream>


using namespace std;

typedef unsigned long ULONG;
ULONG calcA(const long a,const int count,const long m);
ULONG calcC(const long a,const long c,const int count,const long m);
ULONG Associativity(const long a ,const long b,const long m);
ULONG Distributivity(const long a ,const long b,const long m);
ULONG Rand(ULONG &n_prev);
ULONG Srand(ULONG &n_next);
double rescale(ULONG N, ULONG n, double x1, double x2);
double calculate_pi(int step);

int k;
const long a = 1664525;
const long m = pow(2,32);
const long c = 1013904223;
ULONG n_prev =12345;
ULONG A;
ULONG C;
ULONG n_next;

const ULONG sidelen = sqrt(m);

int main()
{
    
    clock_t t_start, t_finish;
    MPI_Init(NULL, NULL);
    
    // Get the number of processes
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    k=world_size;
    
    // Get the rank of the process
    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
    
    A = calcA(a, k, m);
    C = calcC(a, c, k, m);
    
    if(world_size<4)
    {
        cout<<"processor is not enough" <<endl;
        return 0;
    }
    
    
    //partiton
    {
        int i =0;
        do
        {
            i++;
            n_next = Rand(n_prev);
        }while(i<world_rank);
    }

    long N = pow(2, 32);
    int step = (int)(N/world_size);
    t_start = clock();
    double value = calculate_pi(step);
    
    double result = 0.0;
    double count = 0;
    
    if (world_rank == 0) {
        count += value;
        clock_t c_start = clock();
        for(int i = 1; i < world_size; i++) {
            MPI_Recv(&value, 1, MPI_DOUBLE, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            count += value;
        }
        clock_t c_end = clock();
        double t_duration = (double)(c_end - c_start) / CLOCKS_PER_SEC;
        result = 4.0 * (count / (double)N);
        t_finish = clock();
        printf("%.15lf communication seconds\n", t_duration);
        t_duration = (double)(t_finish - t_start) / CLOCKS_PER_SEC;
        printf("pi is : %0.15f\n",result);
        printf("%f seconds\n", t_duration);
    }
    else
    {
           MPI_Send(&value, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
    }
    
    MPI_Finalize();
    return 0;
}

ULONG Rand(ULONG &n_prev)
{
    return n_prev=(a*n_prev+c) %m;
}
ULONG Srand(ULONG &n_next)
{
    return  n_next=(A * n_next +C) %m;
}
ULONG calcA(const long a,const int count,const long m)
{
    ULONG A = 1;
    for (int i=0; i<count; i++) {
        A = Associativity(A, a, m);
    }
    return A;
}

ULONG calcC(const long a,const long c,const int count,const long m)
{
    ULONG C =0;
    for (int i=count-1; i>=0; i--) {
        ULONG times = 1;
        for (int j =0; j<i; j++) {
            times = Associativity(times, a, m);
        }
        times = Associativity(times, c, m);
        C = Distributivity(C, times, m);
    }
    return C;
}

ULONG Associativity(const long a ,const long b,const long m)
{
    ULONG tmp =(a*(b%m)) %m;
    return tmp;
}

ULONG Distributivity(const long a ,const long b,const long m)
{
    ULONG tmp =( (a%m) + (b%m) ) %m;
    return tmp;
}

double rescale(ULONG N, ULONG n, double x1, double x2)
{
    double f = static_cast<double>(n) / static_cast<double>(N);
    return x1 + f * (x2 - x1);
}
double calculate_pi(int step)
{
    
    double count = 0;
    for(int i = 0; i < step; i++) {
        
        ULONG i_random = Srand(n_next);
        
        ULONG ix = i_random % sidelen;
        ULONG iy = i_random / sidelen;
        
        double x = rescale(sidelen, ix, -1, 1);
        double y = rescale(sidelen, iy, -1, 1);

        double r = x*x+y*y;
        if(r<=1.0)
            count++;
    }
    cout<<"end"<<endl;
    return count;
}

