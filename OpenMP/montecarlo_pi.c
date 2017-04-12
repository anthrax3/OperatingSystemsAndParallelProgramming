//OpenMP ile Pi Sayısı Hesaplama
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <Windows.h>
#define iterasyon 100000000
#define chunksize 100
int main()
{
	double PI25DT = 3.141592653589793238462643;
	long  sayac = 0, i;
	long sayac2 = 0, j;
	int chunk = chunksize;
	double seri_toplam_sure, paralel_toplam_sure;
	double baslangic_z, bitis_z;
	printf("SERi HESAPLAMA\n");
	baslangic_z = omp_get_wtime();
	for (j = 0; j < iterasyon; j++)
	{
		double x = (double)rand() / RAND_MAX;
		double y = (double)rand() / RAND_MAX;
		if (x * x + y * y <= 1)
			sayac2++;
	}
	double PI = 4.0 * sayac2 / iterasyon;
	printf("PI sayisi = %lf\n", PI);
	bitis_z = omp_get_wtime();
	seri_toplam_sure = bitis_z - baslangic_z;
	printf("sure:%f(sn)\n\n", seri_toplam_sure);



	baslangic_z = omp_get_wtime();

	printf("PARALEL HESAPLAMA");

#pragma omp parallel shared(chunk,sayac) private(i)
	{
#pragma omp for schedule(dynamic,chunk) reduction(+:sayac)
		for (i = 0; i < iterasyon; i++)
		{
			double x = (double)rand() / RAND_MAX;
			double y = (double)rand() / RAND_MAX;
			if (x * x + y * y <= 1)
				sayac++;
		}
	}
	bitis_z = omp_get_wtime();
	paralel_toplam_sure = bitis_z - baslangic_z;
	printf("sure:%f(sn)\n\n", paralel_toplam_sure);
	double PI2 = 4.0 * sayac / iterasyon;
	printf("PI sayisi = %lf\n", PI2);
	printf("Hata degeri= %lf\n", PI25DT- PI2);
	printf("Hizlanma orani:%f(%%%.1f)\n", seri_toplam_sure / paralel_toplam_sure, (seri_toplam_sure * 100 / paralel_toplam_sure));
	system("pause");

}
