#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <mpi.h>
#include <limits.h>
#define INFINITE INT_MAX
using namespace std;

struct floatMem
{
    float *arr;
    int length;
    float max;
    float min;
    void push(float data)
    {
        max = data > max ? data : max;
        min = data > min ? min : data;

        arr[length++] =data;
    }
    float get(int index) const
    {
        return arr[index];
    }
};

/*****************************************************************************/
floatMem* create_small_buckests(int nbuckets,int bucketCount);

float* create_big_bucket(int nbuckets, int bucketCount);

float *distribute_water_to_processor(int ndata,float max, float min, int nbuckets,int bucketCount,floatMem *buckets);

// Routines used in the sequential implementation of the bucket sort
void bucket_sort(int nbuckets,floatMem *buckets);


int check(float *data,int nitems);

int compare(const void* x1, const void* x2);

float *full_into_big_bucket(int nbuckets, int bucketCount,floatMem* buckets);

void distribute_water(float *data,int ndata,float min,int bucketCount,floatMem *buckets);
//send

void send_signal_sca(void *sendCounts,void *recvCounts, int rank,int num);
void send_signal_gather(int sendCounts,int *recvCounts);

float* receive_send_data_scav(float *sendData,int *sendCounts,int *recvCounts,int nbuckets);
float* receive_send_data_gatherv(float *sendData,int sendCounts,int *recvCounts,int nbuckets);
/*****************************************************************************/
int main(int argc,char *argv[]) {
  // Specify here the full range that the data numbers can cover. We
  // may assume that all the numbers are positive definite
     clock_t t_start, t_finish;
    
    int k;
    MPI_Init(NULL, NULL);
    // Get the number of processes
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    k=world_size;
    
    // Get the rank of the process
    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
    
    cout<<k<<endl;
    if(world_size<4)
    {
        cout<<"processor is not enough" <<endl;
        return 0;
    }
    t_start = clock();
    
   float xmin = 10.0;
   float xmax = 250000;

  //多少（分桶）
  int nbuckets=1000/k;
   //动态分配float数组内存根据用户输入的大小  (master)
  int nitems=3200000;
    
    
    float *data=NULL;
    float *water=NULL;

    int *sendCounts = new int[k];
    int *recvCounts = new int[k]; // for ata
    int recvSingalCount; // for scatter

    
    if(world_rank==0)
    {
        // 每个桶的范围=(max-min)/空桶数量+1 。
        float bucketCount = ((xmax - xmin) / k)+1;
        
        floatMem* buckets = create_small_buckests(k,nitems/2);
        data = distribute_water_to_processor(nitems,xmax ,xmin, k, bucketCount, buckets);

        
        for (int i=0,total=0; i<k; total+=buckets[i].length,i++) {
            sendCounts[i] = buckets[i].length;
            copy(buckets[i].arr,buckets[i].arr+buckets[i].length,data+total);
        }
        
        delete[] buckets;
    }
    
    //提前通知一下节点，各个节点要准备接收多少数
    send_signal_sca(sendCounts,&recvSingalCount,world_rank,1);
    water=receive_send_data_scav(data, sendCounts, &recvSingalCount,k);
    
    xmax = water[recvSingalCount-1];
    xmin = water[recvSingalCount-2];
    
    //for each process
    float bucketCount = ((xmax - xmin) / k)+1;;

    floatMem* buckets = create_small_buckests(nbuckets,nitems*10);

    distribute_water(water, recvSingalCount-2, xmin, bucketCount, buckets);
    delete[] water;

    //排序
    bucket_sort(nbuckets,buckets);

    float *bucket=full_into_big_bucket(nbuckets,recvSingalCount-2,buckets);

    send_signal_gather(recvSingalCount-2,recvCounts);
    data = receive_send_data_gatherv(bucket,recvSingalCount-2,recvCounts,k);
    
    if(world_rank==0)
    {
        t_finish = clock();
        double t_duration = (double)(t_finish - t_start) / CLOCKS_PER_SEC;
        printf("%f seconds\n", t_duration);
        
        check(data, nitems);
    }
    
    delete[] data;
   
    MPI_Finalize();
    return 0;
}
void distribute_water(float *data,int ndata,float min,int bucketCount,floatMem *buckets)
{
    for (int i =0; i<ndata; i++)
    {
        // 桶索引值 = 计算公式为floor(([] – min) / 20.8)
        int bktno = (int)floor((data[i] - min) / bucketCount);
        buckets[bktno].push(data[i]);
    }

}

float *full_into_big_bucket(int nbuckets, int bucketCount,floatMem* buckets)
{
    float *bucket=create_big_bucket(nbuckets,bucketCount);
    
    for (int i=0,total=0; i<nbuckets; total+=buckets[i].length,i++)
    {
        copy(buckets[i].arr,buckets[i].arr+buckets[i].length,bucket+total);
        delete[] buckets[i].arr;
    }
    delete[] buckets;
    return bucket;
}


void send_signal_sca(void *sendCounts,void *recvCounts, int rank,int num)
{
    MPI_Scatter(sendCounts, num, MPI_INT, recvCounts, num, MPI_INT, 0, MPI_COMM_WORLD);
    cout<<"myid is "<<rank<<" receive count is "<<*(int*)recvCounts<<endl;
}

void send_signal_gather(int sendCounts,int *recvCounts)
{
    MPI_Gather(&sendCounts,1,MPI_INT,recvCounts,1,MPI_INT,0,MPI_COMM_WORLD);
}

float* receive_send_data_gatherv(float *sendData,int sendCounts,int *recvCounts,int nbuckets)
{
    int *roffset = new int[nbuckets];
    int sum = 0;
    for (int i=0; i<nbuckets; i++)
    {
        roffset[i]=sum;
        sum +=recvCounts[i];
    }

    float *final_bucket= create_big_bucket(nbuckets,sendCounts);
    
    MPI_Gatherv(sendData, sendCounts, MPI_FLOAT, final_bucket, recvCounts, roffset, MPI_FLOAT, 0, MPI_COMM_WORLD);
    delete[] roffset;
    return final_bucket;
}


float* receive_send_data_scav(float *sendData,int *sendCounts,int *recvCounts,int nbuckets)
{
    int *soffset = new int[nbuckets];
    int sum = 0;
    for (int i=0; i<nbuckets; i++)
    {
        soffset[i]=sum;
        sum +=sendCounts[i];
    }

    float *recvData=new float[*recvCounts];
    
    MPI_Scatterv(sendData, sendCounts, soffset, MPI_FLOAT, recvData, *recvCounts, MPI_FLOAT, 0, MPI_COMM_WORLD);  // 分发数据
    delete[] soffset;
    return recvData;
}



float *distribute_water_to_processor(int ndata,float max, float min, int nbuckets,int bucketCount,floatMem *buckets)
{
    //drand48 返回服从均匀分布的·[0.0, 1.0) 之间的 double 型随机数。
    //设置100000个随机值在[10,250000]范围内 (master)
    float *data=new float[ndata+(2*nbuckets)];
    for(int i=0;i<ndata;i++)
    {
        data[i]=drand48()*(max-min-1)+min;
        int bktno = (int)floor((data[i] - min) / bucketCount);
        buckets[bktno].push(data[i]);
    }
    for(int i=0;i<nbuckets;i++)
    {
        buckets[i].push(buckets[i].min);
        buckets[i].push(buckets[i].max);
    }
    return data;
}


////检测是否已经被排序了
int check(float * data,int nitems) {
  double sum=0;
  int sorted=1;

  for(int i=0;i<nitems;i++)
  {
     sum+=data[i];
     //如果 前面比后面大，就代表没排序好 ， sorted =0
     if(i && data[i]<data[i-1])
         sorted=0;
  }
    printf("sum=%f, sorted=%d\n",sum,sorted);
  return sorted;
}
/*****************************************************************************/

// Sequential implementation of the bucket sort routine. The full
// range x1 to x2 will be divided into a number of equally spaced
// subranges according to the number of buckets. All the buckets are
// contained in the single one dimensional array "bucket".
void bucket_sort(int nbuckets,floatMem *buckets)
{
  // Toss the data items into the correct bucket
    for (int i = 0; i < nbuckets; i++) {
        qsort(&buckets[i].arr[0],buckets[i].length, sizeof(float), compare);
    }
}

floatMem* create_small_buckests(int nbuckets,int bucketCount)
{
    floatMem* buckets;
       if((buckets = new floatMem[nbuckets])==NULL)
       {
           goto out;
       }
       for (int j=0; j<nbuckets; j++)
       {
           if((buckets[j].arr = new float[bucketCount])==NULL)
           {
               goto out;
           }
           for (int i=0; i<bucketCount; i++)
           {
               buckets[j].arr[i] = INFINITE;
           }
           buckets[j].min = INFINITE;
           buckets[j].max = 0;
           buckets[j].length=0;
       }
       return buckets;
       
       out:
       printf("failed apply the memory");
       return NULL;
}

float* create_big_bucket(int nbuckets, int bucketCount)
{
 int ntotal = nbuckets * bucketCount;

  // Pointer to an array of more pointers to each bucket
   float *aa = new float[ntotal];
  // return the address of the array of pointers to float arrays
  return aa;
}

/*****************************************************************************/

// The comparison function to use with the library qsort
// function. This will tell qsort to sort the numbers in ascending
// order.
int compare(const void* a, const void* b) {

    if ( *(float*)a <  *(float*)b )
        return -1;
    if ( *(float*)a == *(float*)b )
        return 0;
    return 1;
}
