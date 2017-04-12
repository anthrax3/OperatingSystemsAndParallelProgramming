#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"
double calculatePi (double b, double s, double N);

void master(int);//main process
void slave(int); //child process

int main(int argc, char *argv[]){
	int np,rank;
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&np);
	if(rank==0)
		master(np-1); //main starting process
	else
		slave(rank);
	MPI_Finalize();
}
double calculatePi(double b,double s,double N){
	double sonuc = 0;
	for (int i = b; i <=s; i++){
		double x = ((double) i-0.5*(1/N));
		sonuc +=4/(1+(x*x));
	}
	sonuc=sonuc*(1/N);
	return sonuc;
}
void master(int worker){
	double is=0,toplam=0,gelen=0;
	int baslik=1;
	int tasks=5;
	MPI_Status stat;
	for (int i = 0; i < worker; i++)
	{
		//MPI_SEND(&buffer,count,datatype,dest,tag,comm) 
		MPI_Send(&is,1,	MPI_DOUBLE,	i+1,baslik,MPI_COMM_WORLD);
		is++;
	}
	while(is <=tasks){
		//MPI_RECV(&buffer,count,datatype,source,tag,comm,status) 
		MPI_Recv(&gelen,1,MPI_DOUBLE,MPI_ANY_SOURCE,baslik,MPI_COMM_WORLD,&stat);
		toplam+=gelen;
		MPI_Send(&is,1,	MPI_DOUBLE,stat.MPI_SOURCE,baslik,MPI_COMM_WORLD);
		is++;
	}
	printf("\nPi Sayisi :%.10g\n",toplam);
}
void slave(int sira){
	double bas,son,hesaplanan;
	double gelen=0,area=0;
	int tasks=5;
	int interveal=10000;
	
	int baslik=1;
	MPI_Status stat;
	while(gelen < tasks){
		area = interveal/tasks;
		MPI_Recv(&gelen,1,MPI_DOUBLE,0,baslik,MPI_COMM_WORLD,&stat);
		bas = gelen*area;
		son=bas + area -1;
		hesaplanan = calculatePi(bas,son,interveal);
		MPI_Send(&hesaplanan,1,MPI_DOUBLE,0,baslik,MPI_COMM_WORLD);
	}
}