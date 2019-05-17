#include "Fungsi.c"

int struk_pembukuan(int x){
	int p,q,amnt=0,sum=0,add,cnt=1;
	void record(){
		FILE *fp=fopen("record.csv","a");
		fprintf(fp,"%d;%d;",amnt,sum);
		print_ts(fp);
		fclose(fp);
		return;
	}
	system("cls");
	for(int i=0;i<menu_len;i++){
		q=qty[i];
		if(q>0){
			amnt+=q;
			if(x==3) add=TAMBAHAN_GOJEK;
			else add=0;
			p=harga[i]+add;
			printf("|%d. %s\t%d\tx%d\t%d\t|\n",cnt,menu[i],p,q,q*p);
			cnt++;
			sum+=q*p;
		}
	}
	record();
	printf("|Total tagihan: %d\t\t\t|\n",sum);
	printf("\nTunjukkan struk ini ke kasir dalam 15 detik\n");
	Sleep(15000);
	return 1;
}

int pilih_kursi(){
	int salah=0,opt,j,pos,dig_len=digit(jumlah_kursi);
	int container[dig_len];
	int execute(){
		pos=parseInt(container,j);
		if(pos>jumlah_kursi){
			salah=2;
			return 0;
		}
		pos--;
		if(kursi[pos]==1){
			salah=1;
			return 0;
		}
		kursi[pos]=1;
		return 1;
	}
	void reset_container(){
		for(int i=0;i<dig_len;i++) container[i]='\0';
		j=0;
		return;
	}
	reset_container();
	while(1){
		system("cls");
		if(salah==1){
			printf("Kursi ini sudah terisi. Silahkan pilih yang lain ...\n");
		}
		if(salah==2) print_salah();
		salah=0;
		gambar_denah();
		printf("Silahkan pilih tempat duduk...\n");
		printf("Tekan ESC untuk kembali ke pembayaran\nRespon: ");
		opt=print_scan(container,j);
		switch(opt){
			case ESC:return 0;break;
			case BACKSPACE:
				if(j>0){
					j--;
					container[j]='\0';
				}
			break;
			case ENTER:
				if(j>0){
					if(execute()) return 1;
					reset_container();
				}
			break;
			default:
				opt-=48;
				if(isDigit(opt)){
					if(j==0&&opt==0) continue;
					container[j]=opt;
					j++;
					if(parseInt(container,j)*10>jumlah_kursi){
						if(execute()) return 1;
						reset_container();
					}
				}
				else salah=2;
			break;
		}
	}
}

int pembayaran(int x){
	int p,q,add,cnt,sum;
	while(1){
		cnt=1;
		sum=0;
		system("cls");
		printf("Berikut detail pesanan Anda:\n");
		for(int i=0;i<menu_len;i++){
			q=qty[i];
			if(x==3) add=TAMBAHAN_GOJEK;
			else add=0;
			p=harga[i]+add;
			if(q>0){
				printf("%d. %s\t%d\tx%d\t%d\n",cnt,menu[i],p,q,q*p);
				cnt++;
				sum+=q*p;
			}
		}
		printf("Total tagihan: %d\n\n",sum);
		printf("Apakah pesanan sudah benar?\n");
		printf("Jika benar, tekan enter\n");
		printf("Jika salah dan ingin mengubah pesanan, tekan apa saja\n");
		if(getch()==ENTER){
			if(x==1){
				if(!pilih_kursi()) continue;
			}
			struk_pembukuan(x);
			return 1;
		}
		return 0;
	}
}
void change_order(int ID,int n){
	qty[ID]=n;
	return;
}
int select_qty(int num){
	int n,salah=0,j=0,opt,container[SIZE_CONT],temp=0;
	for(int i=0;i<SIZE_CONT;i++) container[i]='\0';
	while(1){
		system("cls");
		if(salah) print_salah();
		salah=0;
		printf("Anda memesan %s. Masukkan jumlah pesanan...\n",menu[num]);
		printf("(Untuk membatalkan pesanan ini, tekan enter)\n");
		printf("Respon: ");
		opt=print_scan(container,j);
		switch(opt){
			case ESC:return -1;break;
			case BACKSPACE:
				if(j>0){
					j--;
					container[j]='\0';
				}
			break;
			case ENTER:return parseInt(container,j);break;
			default:
				opt-=48;
				if(isDigit(opt)){
					container[j]=opt;
					j++;
				}
				else salah=1;
			break;
		}
	}
}
int pilih_menu(int x){
	int opt,subtotal,salah=0,sudah_pesan,j,ID,ret_qty,
		dig_len=digit(menu_len),container[dig_len];
	for(int i=0;i<menu_len;i++) qty[i]=0;
	void reset_container(){
		for(int i=0;i<dig_len;i++) container[i]='\0';
		j=0;
		return;
	}
	int execute(){
		ID=parseInt(container,j);
		reset_container();
		if(ID>menu_len) return 0;
		ID--;
		ret_qty=select_qty(ID);
		if(ret_qty!=-1) change_order(ID,ret_qty);
		return 1;
	}
	reset_container();
	while(1){
		system("cls");
		if(salah) print_salah();
		salah=0;
		sudah_pesan=0;
		printf("Silahkan pilih menu:\n");
		for(int i=0;i<menu_len;i++){
			subtotal=harga[i];
			if(x==3) subtotal+=TAMBAHAN_GOJEK;
			printf("%d. %s",i+1,menu[i]);
			if(x==3) printf(" (Go-Food)");
			printf("\t%d",subtotal);
			if(qty[i]>0){
				printf("\tx%d",qty[i]);
				sudah_pesan=1;
			}
			printf("\n");
		}
		if(sudah_pesan) printf("0. Selesai, lanjut ke pembayaran\n");
		printf("Tekan ESC untuk kembali ke menu sebelumnya\nRespon: ");
		opt=print_scan(container,j);
		switch(opt){
			case ESC:return 0;break;
			case BACKSPACE:
				if(j>0){
					j--;
					container[j]='\0';
				}
			break;
			case ENTER:
				if(j>0) execute();
				else salah=1;
			break;
			default:
				opt-=48;
				if(isDigit(opt)){
					if(j==0&&opt==0){
						if(!sudah_pesan) salah=1;
						else{
							if(pembayaran(x)) return 1;
							reset_container();
						}
					}
					else{
						container[j]=opt;
						j++;
						if(parseInt(container,j)*10>menu_len){
							if(!execute()) salah=1;
						}
					}
				}
				else salah=1;
			break;
		}
	}
}
void tipe_pelanggan(){
	int salah=0,opt,num;
	while(1){
		system("cls");
		if(salah) print_salah();
		salah=0;
		printf("Apakah Anda ...\n");
		printf("1. Pelanggan biasa (makan di tempat)\n");
		printf("2. Pelanggan biasa (takeaway)\n");
		printf("3. Mitra Go-Food");
		num=getch()-48;
		opt=between(num,1,3);
		if(opt){
			if(pilih_menu(num)) return;
			continue;
		}
		salah=1;
	}
}
void selesai_makan(){
	system("cls");
	char input_pass[SIZE_CONT];
	const char pass[]={'_','_','0','_','_'};
	int no;
	const int pass_len=sizeof(pass)/sizeof(char);
	int length(){
		int i=0;
		while(input_pass[i]!='\0') i++;
		return i;
	}
	scanf("%d %s",&no,&input_pass);
	if(length()!=pass_len) return;
	for(int i=0;i<pass_len;i++){
		if(input_pass[i]!=pass[i]) return;
	}
	if(between(no,1,jumlah_kursi)) kursi[no-1]=0;
	return;
}
int main(){
	menu_len=menu_init();
	system("color 1B");
	while(1){
		system("cls");
		banner();
		printf("Tekan apa saja untuk melanjutkan ...");
		if(getch()==ESC) selesai_makan();
		else tipe_pelanggan();
	}
}
