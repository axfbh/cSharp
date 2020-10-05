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

const int k = 4;
const long a = 1664525;
const long m = pow(2,32);
const long c = 1013904223;
long n_prev =12345;

int main()
{
    MPI_Init(NULL, NULL);
    
    // Get the number of processes
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    // Get the rank of the process
    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
    
    if(world_size<4)
    {
        cout<<"processor is not enough" <<endl;
        return 0;
    }
    
    long long A = calcA(a, k, m);
    long long C = calcC(a, c, k, m);
    
    long long n_next;
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
    
    cout<<"start:"<<(double)n_next/(double)m<<endl;
    for (int i=0; i<3; i++) {
        long long xik = (A * n_next +C) %m;
        cout<<"jump:"<<(double)xik/(double)m <<endl;
        n_next = xik;
    }
    MPI_Finalize();
    return 0;
}

long long Rand(long &n_prev)
{
    
    return n_prev=(a*n_prev+c) %m;
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
