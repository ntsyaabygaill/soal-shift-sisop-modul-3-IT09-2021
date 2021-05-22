# soal-shift-sisop-modul-3-IT09-2021

Nama Anggota | NRP
------------------- | --------------		
Daniel Evan | 05311940000016
Natasya Abygail N | 05111940000020
Muhammad Naufal Imantyasto | 05111940000041

## List of Contents :
- [No 1](#Cara-Pengerjaan)
	- [1a](#1A)
	- [1b](#1B)
	- [1c](#1C)
	- [1d](#1D)
	- [1e](#1E)
	- [1f](#1F)
	- [1g](#1G)
	- [1h](#1H)
- [No 2](#Cara-Pengerjaan)
	- [2a](#2A)
	- [2b](#2B)
	- [2c](#2C)
- [No 3](#Cara-Pengerjaan)
	- [3a](#3A)
	- [3b](#3B)
	- [3c](#3C)
	- [3d](#3D)
	- [3e](#3E)

## Nomor 1
### Soal
(a).Pada saat client tersambung dengan server, terdapat dua pilihan pertama, yaitu register dan login. Jika memilih register, client akan diminta input id dan passwordnya untuk dikirimkan ke server. User juga dapat melakukan login. Login berhasil jika id dan password yang dikirim dari aplikasi client sesuai dengan list akun yang ada didalam aplikasi server. Lokasi penyimpanan berada dalam akun.txt. <br>
(b).Sistem memiliki sebuah database yang bernama files.tsv. Isi dari files.tsv ini adalah path file saat berada di server, publisher, dan tahun publikasi. Setiap penambahan dan penghapusan file pada folder file yang bernama  FILES pada server akan memengaruhi isi dari files.tsv. <br>
(c).Command "add" untuk mengupload file ke server <br>
(d).Command "download" untuk mendownload file dari server <br>
(e).Command "delete" untuk menghapus file yang berada di server <br>
(f).Command "see" untuk melihat isi file.tsv <br>
(g).Command "find" untuk menemukan file yang memiliki nama tertentu <br>
(h).running.log untuk mencatat penambahan atau pengurangan file <br>
### Cara Pengerjaan
#### Library
Berikut adalah library yang kami gunakan
``` C
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <dirent.h>
```
#### 1A
##### Client
``` C
printf("Pilih menu :\n1.Register\n2.Login\n");
    scanf("%d",&pil);
    if (pil==1){
        send(sock , regist , strlen(regist) , 0 );
    }
    else if (pil==2){
        send(sock , login , strlen(login) , 0 );
    }
    valread = read( sock , buffer, 1024);
    if (strcmp(buffer,"sukses")==0){
        memset(buffer,0,sizeof(buffer));
        printf("Masukkan id : ");
        scanf("%d",&id);
        printf("Masukkan password : ");
        scanf("%s",pass);
        sprintf(idc,"%d",id);
        strcat(kirim,idc);
        strcat(kirim,":");
        strcat(kirim,pass);
        //printf("%s",kirim);
        send(sock , kirim , strlen(kirim) , 0 );
        valread = read( sock , buffer, 1024);
```
Pada Client akan ditampilkan isian sebagai berikut :
```
Pilih menu :
1.Register
2.Login
```
Jika client memilih register mode register akan dikirimkan ke server, jika client memilih login mode login akan dikirimkan ke server. Setelah server berhasil men-set modenya ke mode login atau register, selanjutnya client akan diminta memasukkan id dan password :
```
Masukkan id :
Masukkan password :
```
Setelah itu dengan fungsi ini
```C
sprintf(idc,"%d",id);
strcat(kirim,idc);
strcat(kirim,":");
strcat(kirim,pass);
```
id dan password dibentuk dalam format ```id:password``` selanjutnya format inilah yang dikirimkan kepada server.
##### Server
jika login
```C
if (strcmp(buffer,"2")==0){
	send(new_socket , sukses , strlen(sukses) , 0 );
memset(buffer,0,sizeof(buffer));
char * buff = 0;
long length;
FILE * f = fopen ("akun.txt", "rb");
```
Server akan mengirimkan status sukses masuk ke mode login ke client dan membuka file akun.txt, selanjutnya client akan meminta id dan password dari client.
```C
valread = read(new_socket , buffer, 1024);
strcat(isi,buffer);
ret = strstr(buff, isi);
if (ret){
	send(new_socket , login , strlen(login) , 0 );
memset(buffer,0,sizeof(buffer));
```
Untuk memeriksa id dan password digunakan fungsi strstr, jika ada maka login berhasil

#### 1B
##### Server
Membuka dan membuat file tsv
```C
FILE * tsv;
/* open the file for writing*/
tsv = fopen ("files.tsv","a+");
```
kami menggunakan fopen untuk membuat dan membuka ```files.tsv```, disini juga kami menggunakan mode ```a+``` yang berfungsi untuk append sehingga data akan terus di tulis tanpa di overwrite.
```C
strcat(tulis,"Publisher: ");
strcat(tulis,publish);
strcat(tulis,"\n");
strcat(tulis,"Tahun Publikasi: ");
strcat(tulis,tahun);
strcat(tulis,"\n");
strcat(tulis,"Filepath: ");
strcat(tulis,"FILES/");
strcat(tulis,namafile);
strcat(tulis,"\r\n\n");
if(tsv){
	fputs(tulis,tsv);
}
```
Apabila ada perintah add maka program akan melakukan cat terhadap inputan hingga berbentuk seperti ini :
```
Publisher:
Tahun Publikasi:
Filepath:
```
dan memasukkannya ke dalam files.tsv
#### 1C
##### Client
Ketika client mengirim command add maka
```C
if(strcmp(cmd,"add")==0){
	send(sock , add , strlen(add) , 0 );
	printf("Publisher: ");
	scanf ("%s",publisher);
	send(sock , publisher , strlen(publisher) , 0 );
	printf("Tahun Publikasi: ");
	scanf ("%s",tahun);
	send(sock , tahun , strlen(tahun) , 0 );
	printf("Filepath: ");
	scanf ("%s",filename);
	send(sock , filename , strlen(filename) , 0 );
	fp = fopen(filename, "r");
	if(fp == NULL)
	{
		perror("[-]Error in reading file.");
		exit(1);
	}
	send_file(fp,sock);
	sleep(10);
}
```
Fungsi send_file()
```C
void send_file(FILE *fp, int sockfd)
{
    char data[SIZE] = {0};

    while(fgets(data, SIZE, fp)!=NULL)
    {
        if(send(sockfd, data, sizeof(data), 0)== -1)
        {
            perror("[-] Error in sending data");
            exit(1);
        }
        bzero(data, SIZE);
    }
}
```
##### Server
Ketika menerima command add dari client maka server akan :
```C
if (strcmp(buffer,"add")==0){
	valread = read(new_socket , buffer, 1024); //publisher
	memset(publish,0,sizeof(publish));
	strcpy(publish,buffer);
	valread = read(new_socket , buffer, 1024); //tahun
	memset(tahun,0,sizeof(tahun));
	strcpy(tahun,buffer);
	valread = read(new_socket , buffer, 1024); //nama file
	memset(namafile,0,sizeof(namafile));
	strcpy(namafile,buffer);

	strcat(tulis,"Publisher: ");
	strcat(tulis,publish);
	strcat(tulis,"\n");
	strcat(tulis,"Tahun Publikasi: ");
	strcat(tulis,tahun);
	strcat(tulis,"\n");
	strcat(tulis,"Filepath: ");
	strcat(tulis,"FILES/");
	strcat(tulis,namafile);
	strcat(tulis,"\r\n\n");
	//printf("%s",tulis);

	if(tsv){
	    fputs(tulis,tsv);
	}
	memset(tulis,0,sizeof(tulis));
	//printf("%s",namafile);
	addr_size = sizeof(new_addr);
	write_file(new_socket,namafile);
	memset(buffer,0,sizeof(buffer));


	//log
	strcat(t_log,"Tambah : ");
	strcat(t_log,namafile);
	strcat(t_log," (");
	strcat(t_log,isi);
	strcat(t_log,")\n");
	if(log){
	    fputs(t_log,log);
	}
}
```
Fungsi write file :
``` C
void write_file(int sockfd,char *file)
{
    int n; 
    FILE *fp;
    char filename[100]="FILES/";
    strcat(filename,file);
    char buffer[SIZE];

    fp = fopen(filename, "w");
    if(fp==NULL)
    {
        perror("[-]Error in creating file.");
        exit(1);
    }
    while(1)
    {
        n = recv(sockfd, buffer, SIZE, 0);
        if(n<=0)
        {
            break;
            return;
        }
        fprintf(fp, "%s", buffer);
        bzero(buffer, SIZE);
    }
    return;
    
}
```
#### 1D
##### Client
Jika menerima perintah download maka client akan :
```C
else if(strcmp(cmd,"download")==0){
    send(sock , down , strlen(down) , 0 );
    printf("Masukkan judul: ");
    scanf("%s",download);
    send(sock , download , strlen(download) , 0 );
    addr_size = sizeof(new_addr);
    write_file(sock,download);
}
```
Fungsi Write File
``` C
void write_file(int sockfd,char *file)
{
    int n; 
    FILE *fp;
    char filename[100]="download/";
    strcat(filename,file);
    char buffer[SIZE];

    fp = fopen(filename, "w");
    if(fp==NULL)
    {
        perror("[-]Error in creating file.");
        exit(1);
    }
    while(1)
    {
        n = recv(sockfd, buffer, SIZE, 0);
        if(n<=0)
        {
            break;
            return;
        }
        fprintf(fp, "%s", buffer);
        bzero(buffer, SIZE);
    }
    return;
    
}
```
##### Server
```C
else if (strcmp(buffer,"down")==0){
	memset(buffer,0,sizeof(buffer));
	valread = read(new_socket , buffer, 1024); //file'
	strcpy(file_down,"FILES/");
	strcat(file_down,buffer);
	down = fopen(file_down, "r");
	if(down == NULL)
	{
	    perror("[-]Error in reading file.");
	    exit(1);
	}
	send_file(down,new_socket);
}
```
Fungsi send_file()
```C
void send_file(FILE *fp, int sockfd)
{
    char data[SIZE] = {0};

    while(fgets(data, SIZE, fp)!=NULL)
    {
        if(send(sockfd, data, sizeof(data), 0)== -1)
        {
            perror("[-] Error in sending data");
            exit(1);
        }
        bzero(data, SIZE);
    }
}
```
#### 1E
##### Client
Ketika client memasukkan command delete maka akan dikirimkan pesan kepada server untuk memasuki mode delete, dan client meminta nama file apa yang akan dihapus dan dikirimkan ke server.
```C
else if(strcmp(cmd,"delete")==0){
    send(sock , del , strlen(del) , 0 ); //pesan
    printf("Masukkan judul: ");
    scanf("%s",delete);
    send(sock , delete , strlen(delete) , 0 );
    memset(buffer,0,sizeof(buffer));
    valread = read( sock , buffer, 1024);
    if(buffer!=NULL){
	printf("%s",buffer);
    }
}
```
Jika file tidak ada maka pesan error dari server akan ditampilkan kepada client.
##### Server
```C
else if (strcmp(buffer,"delete")==0){
memset(buffer,0,sizeof(buffer));
valread = read(new_socket , buffer, 1024); //file
strcpy(file_del,buffer);
int flag;
char new_name[200]={0};
strcat(new_name,"old-");
strcat(new_name,file_del);
chdir("FILES");
flag = rename(file_del,new_name);
if(flag == 0) {
    strcat(t_log,"Hapus : ");
    strcat(t_log,namafile);
    strcat(t_log," (");
    strcat(t_log,isi);
    strcat(t_log,")\n");
    if(log){
	fputs(t_log,log);
    }
} else {
    send(new_socket , "file tidak ada\n" , strlen("file tidak ada\n") , 0 );
}
}
```
Ketika memasuki mode delete server akan melakukan rename ke file yang bersangkutan dengan format ```old-nama.ekstensi``` setelah itu menulis di file log, jika file tidak ada maka akan dikirimkan pesan error ```"file tidak ada"```.
#### 1F
##### Client
```C
else if(strcmp(cmd,"see")==0){
    send(sock , see , strlen(see) , 0 );
    memset(buffer,0,sizeof(buffer));
    valread = read( sock , buffer, 1024);
    strcat(isi,buffer);
    printf("\n%s",isi);
}
```
##### Server
```
else if (strcmp(buffer,"see")==0){
	char * buf = 0;
	char content[1000]={0};
	long length;
	FILE * f = fopen ("files.tsv", "rb");

	if (f)
	{
		fseek (f, 0, SEEK_END);
		length = ftell (f);
		fseek (f, 0, SEEK_SET);
		buf = malloc (length);
		if (buf)
		{
		    fread (buf, 1, length, f);
		}
		fclose (f);
	}

	if (buf)
	{
	    strcpy(content,buf);
	    send(new_socket , content , strlen(content) , 0 );
	}
}
```
#### 1G
##### Client
Ketika client memasukkan command find maka program akan meminta memasukkan judul, yang selanjutnya dikirim ke server, dan di print kembali hasil yang didapat dari server.
```C
else if(strcmp(cmd,"find")==0){
    send(sock , find , strlen(find) , 0 );
    printf("Masukkan judul: ");
    scanf("%s",cari);
    send(sock , cari , strlen(cari) , 0 );
    //printf("%s\n%s",cmd,cari);
    memset(buffer,0,sizeof(buffer));
    valread = read( sock , buffer, 1024);
    strcat(isi,buffer);
    printf("\n%s",isi);
}
```
##### Server
```C
else if (strcmp(buffer,"find")==0){
memset(buffer,0,sizeof(buffer));
// printf(" %s",buffer);
valread = read(new_socket , buffer, 1024); //find nama
//printf(" %s",buffer);
strcat(cari,buffer);

int o=0, z=0;
DIR *d;
struct dirent *dir;
d = opendir("FILES");

//Determine the number of files
while((dir = readdir(d)) != NULL) {
    if ( !strcmp(dir->d_name, ".") || !strcmp(dir->d_name, "..") )
    {

    } else {
	o++;
    }
}
rewinddir(d);

char *filesList[o];

//Put file names into the array
while((dir = readdir(d)) != NULL) {
    if ( !strcmp(dir->d_name, ".") || !strcmp(dir->d_name, "..") )
    {}
    else {
	filesList[z] = (char*) malloc (strlen(dir->d_name)+1);
	//strncpy (filesList[z],dir->d_name, strlen(dir->d_name) );
	strcpy(filesList[z],dir->d_name);
	z++;
    }
}
rewinddir(d);

for(z=0; z<o; z++){
    if(strstr(filesList[z],cari)){
	//printf("%s\n", filesList[z]);
	if((strstr(filesList[z],"old-")==0)&&z>0){
	strcat(hasil_cari,filesList[z]);
	strcat(hasil_cari,"\n");}
    }
    send(new_socket , hasil_cari , strlen(hasil_cari) , 0 );
}
}
```
Server akan melakukan loop untuk menyimpan setiap nama yang ada dalam directory FILES, kemudian untuk mencocokkan nama file digunakan fungsi strstr, dan terdapat filter untuk file yang sudah dihapus (old-) dengan menggunakan strstr juga.
#### 1H
##### Penambahan File
```C
strcat(t_log,"Tambah : ");
strcat(t_log,namafile);
strcat(t_log," (");
strcat(t_log,isi);
strcat(t_log,")\n");
if(log){
	fputs(t_log,log);
}
```
##### Pengurangan File
```C
trcat(t_log,"Hapus : ");
strcat(t_log,namafile);
strcat(t_log," (");
strcat(t_log,isi);
strcat(t_log,")\n");
if(log){
	fputs(t_log,log);
}
```

## Nomor 2
### Soal
(a).Membuat program perkalian matrix (4x3 dengan 3x6) dan menampilkan hasilnya. Matriks nantinya akan berisi angka 1-20 (tidak perlu dibuat filter angka). <br>
(b).Membuat program dengan menggunakan matriks output dari program sebelumnya (program soal2a.c). Kemudian matriks tersebut akan dilakukan perhitungan dengan matrix baru (input user) sebagai berikut contoh perhitungan untuk matriks yang a da. Perhitungannya adalah setiap cel yang berasal dari matriks A menjadi angka untuk faktorial, lalu cel dari matriks B menjadi batas maksimal faktorialnya matri(dari paling besar ke paling kecil). <br>
(c).Program (soal2c.c) untuk mengecek 5 proses teratas apa saja yang memakan resource komputernya <br>
### Cara Pengerjaan
#### 2A
```C
#include <stdio.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <pthread.h>
#include <sys/ipc.h>

//deklarasi
int (*value)[10];
int hasil = 0;
int matriks_A[10][10], matriks_B[10][10], baris_A=4, kolom_A=3, baris_B=3, kolom_B=6; // deklarasi array
pthread_t thread1, thread2, thread3; // pembuatan thread

void *input_matriks_A(void *arg);
void *input_matriks_B(void *arg);

// fungsi menghitung perkalian matriks
void *perkalian_matriks(void *arg){
   for(int i=0;i<baris_A;i++){
      for(int j=0;j<kolom_B;j++){
         for(int k=0;k<kolom_A;k++){
            hasil+=matriks_A[i][k] * matriks_B[k][j]; //lakukan perhitungan perkalian matriks
         }
         value[i][j]= hasil; // menyimpanan hasil perkalian dalam var value
         hasil = 0; // nilai dikembalikan 0 agar bisa menghitung nilai ulang
      }
   }
   return NULL;
}

int main(){
   //template shared memory 
   key_t key = 1234;
   int shmid = shmget(key, sizeof(int[10][10]), IPC_CREAT | 0666); //int [10][10] membuat matriks (array multidimensi)
   value = shmat(shmid, 0, 0);

   pthread_create(&thread1, NULL, input_matriks_A, NULL); // membuat thread 1 matriks A
   pthread_join(thread1,NULL);

   pthread_create(&thread2, NULL, input_matriks_B, NULL); // membuat thread 2 matriks B
   pthread_join(thread2,NULL);

   for(int i=0;i<baris_A;i++){ // sebanyak 4 baris
      for(int j=0;j<kolom_B;j++){ // sebanyak 5 kolom
         value[i][j]=0;
      }
      pthread_create(&thread3, NULL, perkalian_matriks, NULL); // membuat thread 3 untuk hasil perkalian
      pthread_join(thread3,NULL);
   }

   //menampilkan hasil perkalian matriks
   printf("Hasil perkalian dari matriks A dan B adalah: \n");
   for(int i=0; i<baris_A; i++){ // sebanyak 4 baris
      for(int j=0;j<kolom_B;j++){  // sebanyak 5 kolom
         printf("%d\t", value[i][j]); // print per elemen diselat tab
      }
      printf("\n");
   }
}

//matriks pertama
void *input_matriks_A(void *arg) { //fungsi matriks pertama
   matriks_A[0][0]=2; //baris 1 kolom 1
   matriks_A[0][1]=1; //baris 1 kolom 2
   matriks_A[0][2]=3; //baris 1 kolom 3
   matriks_A[1][0]=4; //baris 2 kolom 1
   matriks_A[1][1]=3; //baris 2 kolom 2
   matriks_A[1][2]=1; //baris 2 kolom 3
   matriks_A[2][0]=2; //baris 3 kolom 1
   matriks_A[2][1]=1; //baris 3 kolom 2
   matriks_A[2][2]=3; //baris 3 kolom 3
   matriks_A[3][0]=4; //baris 4 kolom 1
   matriks_A[3][1]=3; //baris 4 kolom 2
   matriks_A[3][2]=2; //baris 4 kolom 2
   return NULL;
}

//matriks kedua
void *input_matriks_B(void *arg){ //fungsi matriks kedua
   matriks_B[0][0]=4; //baris 1 kolom 1
   matriks_B[0][1]=1; //baris 1 kolom 2
   matriks_B[0][2]=2; //baris 1 kolom 3
   matriks_B[0][3]=3; //baris 1 kolom 4
   matriks_B[0][4]=1; //baris 1 kolom 5
   matriks_B[0][5]=2; //baris 1 kolom 6
   matriks_B[1][0]=2; //baris 2 kolom 1
   matriks_B[1][1]=1; //baris 2 kolom 2
   matriks_B[1][2]=3; //baris 2 kolom 3
   matriks_B[1][3]=1; //baris 2 kolom 4
   matriks_B[1][4]=3; //baris 2 kolom 5
   matriks_B[1][5]=2; //baris 2 kolom 6
   matriks_B[2][0]=1; //baris 3 kolom 1
   matriks_B[2][1]=4; //baris 3 kolom 2
   matriks_B[2][2]=3; //baris 3 kolom 3
   matriks_B[2][3]=1; //baris 3 kolom 4
   matriks_B[2][4]=2; //baris 3 kolom 5
   matriks_B[2][5]=3; //baris 3 kolom 6
   return NULL;
}
```
#### 2B
```C
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <pthread.h>

//deklarasi
unsigned long long angka; // memakai unsigned long long agar banyak menampung angka 
int baris = 4, kolom = 6; //baris 4 kolom 5

unsigned long long factorial(unsigned long long a);
void *faktorial(void *arg);

int main(){
    pthread_t thread;
    //shared memory template
    key_t key = 1234;
    int (*value)[10];
    int shmid = shmget(key, sizeof(int), IPC_CREAT | 0666);
    value = shmat(shmid, 0, 0);

    printf("Hasil perkalian dari matriks A dan B adalah: \n");
    //menampilkan hasil perkalian matriks pada soal 4a
    for(int i=0;i< 4;i++){
        for(int j=0;j<6;j++){
            printf("%d\t", value[i][j]);
        }
        printf("\n");
    }
    pthread_create(&thread, NULL, faktorial, NULL); // membuat thread faktorial 
    pthread_join(thread,NULL); // join thread faktorial
}

unsigned long long factorial(unsigned long long a){  //fungsi menghitung faktorial tambah
    if(a==0 || a==1) return 1;
    else return a+ factorial(a-1); //pemanggilan fungsi factorial
}

//fungsi faktorial
void *faktorial(void *arg){
    //shared memory template 
    key_t key = 1234;
    int (*value)[10];
    int shmid = shmget(key, sizeof(int), IPC_CREAT | 0666);
    value = shmat(shmid, 0, 0);
    
    printf("Hasil faktorial pertambahan matriks ialah: \n");
    
    for(int i=0;i<baris;i++){ // perulangan untuk baris
        for(int j=0;j<kolom;j++){ // perulangan untuk kolom
            angka=value[i][j]; // faktorial dihitung per elemen matriks hasil perkalian
            printf("%llu\t", factorial(angka)); // pemanggilan fungsi factorial untuk menghitung
        }
        printf("\n");
    }
    pthread_exit(0); // keluar thread
}
```
#### 2C
```C
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<wait.h>
#include<fcntl.h>

void    loop_pipe(char ***cmd);

int main()
{
  char *ps[] = {"ps", "aux", NULL};
  char *sort[] = {"sort", "-nrk", "3,3", NULL};
  char *head[] = {"head", "-5", NULL};
  char **cmd[] = {ps, sort, head, NULL};

  loop_pipe(cmd);
  return (0);
}

void    loop_pipe(char ***cmd) 
{
  int   p[2];
  pid_t pid;
  int   fd_in = 0;

  while (*cmd != NULL)
    {
      pipe(p);
      if ((pid = fork()) == -1)
        {
          exit(EXIT_FAILURE);
        }
      else if (pid == 0)
        {
          dup2(fd_in, 0); //change the input according to the old one 
          if (*(cmd + 1) != NULL)
            dup2(p[1], 1);
          close(p[0]); //menutup input pipe
          execvp((*cmd)[0], *cmd);
          exit(EXIT_FAILURE);
        }
      else
        {
          wait(NULL);
          close(p[1]); //menutup output pipe
          fd_in = p[0]; //menyimpan input untuk loop selanjutnya
          cmd++;
        }
    }
}
```

## Nomor 3
### Soal
(a).Program menerima opsi -f seperti contoh di atas, jadi pengguna bisa menambahkan argumen file yang bisa dikategorikan sebanyak yang diinginkan oleh pengguna. <br>
(b).Program juga dapat menerima opsi -d untuk melakukan pengkategorian pada suatu directory. Namun pada opsi -d ini, user hanya bisa memasukkan input 1 directory saja, tidak seperti file yang bebas menginput file sebanyak mungkin. <br>
(c).Program menerima opsi * <br>
(d).Semua file harus berada di dalam folder, jika terdapat file yang tidak memiliki ekstensi, file disimpan dalam folder “Unknown”. Jika file hidden, masuk folder “Hidden”. <br>
(e).Setiap 1 file yang dikategorikan dioperasikan oleh 1 thread agar bisa berjalan secara paralel sehingga proses kategori bisa berjalan lebih cepat. <br>
### Cara Pengerjaan
#### 3A
#### 3B
#### 3C
#### 3D
#### 3E
