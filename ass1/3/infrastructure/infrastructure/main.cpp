#include <stdio.h>
#include <vector>
#include <mpi.h>
#include <cmath>
#include <iostream>

using namespace std;
long long calcA(const long a,const int count,const long m);
long long calcC(const long a,const long c,const int count,const long m);
long long Associativity(const long a ,const long b,const long m);
long long Distributivity(const long a ,const long b,const long m);
long long Rand(long &n_prev);
long long Srand(long long &n_next);
double calculate_pi(int step);

int k;
const long a = 1664525;
const long m = pow(2,32);
const long c = 1013904223;
long n_prev =12345;
long long A;
long long C;
long long n_next;

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
    
    t_start = clock();
    int partner_rank =1;
    if(world_rank==0)
    {
        n_next = Rand(n_prev);
        MPI_Send(&n_prev, 1, MPI_LONG_LONG, partner_rank, 0,MPI_COMM_WORLD);
        printf("%d sent and incremented n_next ""%lld to %d\n", world_rank, n_prev,partner_rank);
    }
    else
    {
        partner_rank=(world_rank+3)%4;
        MPI_Recv(&n_prev, 1, MPI_LONG_LONG, partner_rank, 0, MPI_COMM_WORLD,MPI_STATUS_IGNORE);
        printf("%d received n_next %lld from %d\n",world_rank, n_prev, partner_rank);
        n_next = Rand(n_prev);
        
        partner_rank=world_rank+1;
        if(partner_rank!=4)
        {
            MPI_Send(&n_prev, 1, MPI_LONG_LONG, partner_rank, 0,MPI_COMM_WORLD);
            printf("%d sent and incremented n_next ""%lld to %d\n", world_rank, n_prev,partner_rank);
        }
    }
    
    int N = 1024 * 1024 * 64;
    int step = (int)(N/world_size);
    double value = calculate_pi(step);
    double result = 0.0;
    int count = 0;
    if (world_rank == 0) {
        count += value;
        for(int i = 1; i < world_size; i++) {
            MPI_Recv(&value, 1, MPI_DOUBLE, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            count += value;
        }
        result = 4.0 * ((double)count / (double)N);
        t_finish = clock();
        double t_duration = (double)(t_finish - t_start) / CLOCKS_PER_SEC;
        printf("pi is : %0.15f\n",result);
        printf( "%f seconds\n", t_duration );
    }
    else
    {
           MPI_Send(&value, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
    }
    MPI_Finalize();
    return 0;
}

long long Rand(long &n_prev)
{
    return n_prev=(a*n_prev+c) %m;
}
long long Srand(long long &n_next)
{
    return  n_next=(A * n_next +C) %m;
}
long long calcA(const long a,const int count,const long m)
{
    long long A = 1;
    for (int i=0; i<count; i++) {
        A = Associativity(A, a, m);
    }
    return A;
}

long long calcC(const long a,const long c,const int count,const long m)
{
    vector<long long> storePow;
    long long C =0;
    for (int i=count-1; i>=0; i--) {
        long long times = 1;
        for (int j =0; j<i; j++) {
            times = Associativity(times, a, m);
        }
        times = Associativity(times, c, m);
        storePow.push_back(times);
    }
    for (int i=0; i<storePow.size(); i++) {
        C = Distributivity(C, storePow[i], m);
    }
    return C;
}

long long Associativity(const long a ,const long b,const long m)
{
    long long tmp =(a*(b%m)) %m;
    return tmp;
}

long long Distributivity(const long a ,const long b,const long m)
{
    long long tmp =( (a%m) + (b%m) ) %m;
    return tmp;
}
double rangeRandom(long long range)
{
    return (double)range/(double)m;
}

double calculate_pi(int step)
{
    int count = 0;
    for(int i = 0; i < step; i++) {
        long long xr = Srand(n_next);
        long long xy = Srand(n_next);
        
        double x = rangeRandom(xr);
        double y = rangeRandom(xy);

        double r = x*x+y*y;
        if(r<=1.0)
            count++;
    }
    cout<<"end"<<endl;
    return count;
}

