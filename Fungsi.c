#include<stdio.h>
#include<windows.h>
#include<string.h>
#include<time.h>
#include<conio.h>
#define failfail -1000000
#define SIZE_CONT 10000
#define MAX 256
#define ESC 27
#define BACKSPACE 8
#define ENTER 13
#define TAMBAHAN_GOJEK 4000
#define jumlah_kursi 6

char menu[MAX][MAX];
int harga[MAX],menu_len,qty[MAX],kursi[jumlah_kursi]={0};

int menu_init(){
	FILE *fp=fopen("menu.csv","r");
	int temp,i=0;
	while(fscanf(fp,"%[^;];%d\n",&menu[i],&harga[i])!=-1) i++;
	fclose(fp);
	return i;
}

void banner(){
	printf("     |                                                        ) ))\n");
	printf("     |  /       ==========================================   ( ((  /)\n");
	printf("     | /        |               Welcome                  |   ,-===-//\n");
	printf(" .~^(,&|/o.     |                 to                     |  |`-===-'|\n");
	printf(" |`-------^|    |        Bakmi Ayam Special Pedas        |  '       '\n");
	printf(" \\         /    |              Bukit Dago                |   \\_____/\n");
	printf("  `======='     ==========================================\n");
	return;
}

void gambar_denah(){
	printf ("|------------------------------------------------------------------------------|\n");
	printf ("|                                                                              |\n");
	printf ("|                                                                              |\n");
	printf ("|          ________               Outdoor            ________                  |\n");
	printf ("|         |   1    |                                |   2    |                 |\n");
	printf ("|         |________|                                |________|                 |\n");
	printf ("|                                                                              |\n");
	printf ("|------------------------------------------------------------------------------|\n");
	printf ("|______________________________________________________________________________|\n");
	printf ("|______________________________________________________________________________|\n");
	printf ("|                                   indoor                                     |\n");
	printf ("| ______________               ____________                            _______ |\n");
	printf ("||  Gerobak     |             |      3     |                          |       ||\n");
	printf ("||______________|             |____________|        __________        |       ||\n");
	printf ("|           | K |                                  |          |       |   5   ||\n");
	printf ("|           | a |                                  |    6     |       |       ||\n");
	printf ("|           | s |              ____________        |__________|       |       ||\n");
	printf ("|           | i |             |      4     |                          |_______||\n");
	printf ("|           | r |             |____________|                                   |\n");
	printf ("|           |___|                                                              |\n");
	printf ("|______________________________________________________________________________|\n");
}

void print_salah(){
	printf("(Masukkan Anda salah, silahkan dicoba lagi...)\n");
	return;
}

int pkt(int n,int x){
	if(x==0) return 1;
	return n*pkt(n,x-1);
}

int digit(int n){
	int sum=0;
	while(n>0){
		n/=10;
		sum++;
	}
	return sum;
}

struct tm curr_dt(){
	time_t sys_dt;
	time(&sys_dt);
	struct tm *_dt,dt;
	_dt=localtime(&sys_dt);
	dt=*_dt;
	return dt;
}

char *month_word(int month){
	char *name_of_month[12]={
		"Januari","Februari","Maret","April","Mei","Juni",
		"Juli","Agustus","September","Oktober","November","Desember"
	};
	return name_of_month[month];
}

void print_ts(FILE *fp){
	void leading_zero(int x){
		if(x<10) fprintf(fp,"0");
		return;
	}
	struct tm ts=curr_dt();
	fprintf(
		fp,"%d %s %d %d:",
		ts.tm_mday,
		month_word(ts.tm_mon),
		(ts.tm_year)+1900,
		ts.tm_hour
	);
	leading_zero(ts.tm_min);
	fprintf(fp,"%d:",ts.tm_min);
	leading_zero(ts.tm_sec);
	fprintf(fp,"%d\n",ts.tm_sec);
	return;
}

int between(int num,int lower,int upper){
	if(num>=lower&&num<=upper) return 1;
	return 0;
}

int isDigit(int x){
	if(between(x,0,9)) return 1;
	return 0;
}
int parseInt(int arr[],int amnt){
	int temp=0;
	for(int i=0;i<amnt;i++) temp+=arr[i]*pkt(10,amnt-(i+1));
	return temp;
}

int print_scan(int arr[],int length){
	for(int i=0;i<length;i++) printf("%d",arr[i]);
	return getch();
}
