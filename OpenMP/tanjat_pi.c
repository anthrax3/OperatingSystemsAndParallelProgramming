# include<omp.h>
#include<stdio.h>
#include<stdlib.h>
#define adim_sayisi 10000000
#define thread_sayi 10
int main()
{
	double x, toplam_s = 0.0, toplam_p = 0.0;
	double adim_miktari = 1.0 / adim_sayisi;
	double pi_s, pi_p;
	int i;
	omp_set_num_threads(thread_sayi);
	double baslangic_z, bitis_z;
	double seri_toplam_sure, paralel_toplam_sure;
	// seri olarak pi hesaplama
	baslangic_z = omp_get_wtime();
	for (i = 0; i<adim_sayisi; i++)
	{
		x = (i + 0.5)*adim_miktari;
		toplam_s += 4.0 / (1.0 + x*x);
	}
	pi_s = toplam_s*adim_miktari;
	bitis_z = omp_get_wtime();
	seri_toplam_sure = bitis_z - baslangic_z;
	//seri sonuçlar
	printf("pi seri yontemle hesaplaniyor\n");
	printf("-------------------------------\n");
	printf("iterasyon sayisi:%d\n", adim_sayisi);
	printf("cekirdek sayisi:%d\n", omp_get_num_procs());
	printf("kosulan thread sayisi:%d\n", omp_get_num_threads());
	printf("hesaplanan pi degeri:%50.49f\n", pi_s);
	printf("sure:%f(sn)\n\n", seri_toplam_sure);
	//openmp ile paralel yöntemle pi sayısını hesaplama
	baslangic_z = omp_get_wtime();
#pragma omp parallel reduction(+:toplam_p) // uygulama yapılacak alan oluşturuldu
	{
#pragma omp for schedule(static)  // her iş parcacıgına eşit dagılım yapılır
		for (i = 0; i<adim_sayisi; i++)
		{
			x = (i + 0.5)*adim_miktari;
			toplam_p += 4.0 / (1.0 + x*x);
		}
	}
	pi_p = toplam_p*adim_miktari;
	bitis_z = omp_get_wtime();
	paralel_toplam_sure = bitis_z - baslangic_z;
	//paralel sonuçlar//
	printf("paralel yontem\n");
	printf("-------------------------------\n");
	printf("iterasyon sayisi:%d\n", adim_sayisi);
	printf("cekirdek sayisi:%d\n", omp_get_num_procs());
	printf("kosulan thread sayisi:%d\n", omp_get_max_threads());
	printf("hesaplanan pi degeri:%50.49f\n", pi_p);
	printf("sure:%f(sn)\n\n", paralel_toplam_sure);
	printf("Hizlanma orani:%f(%%%.1f)\n", seri_toplam_sure / paralel_toplam_sure, (seri_toplam_sure * 100 / paralel_toplam_sure));
	char ch = getchar();
	return 0;
}

