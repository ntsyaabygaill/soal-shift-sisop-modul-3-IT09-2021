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
##### Server
##### Client
#### 1D
#### 1E
#### 1F
#### 1G
#### 1H

## Nomor 2
### Soal
(a).Membuat program perkalian matrix (4x3 dengan 3x6) dan menampilkan hasilnya. Matriks nantinya akan berisi angka 1-20 (tidak perlu dibuat filter angka). <br>
(b).Membuat program dengan menggunakan matriks output dari program sebelumnya (program soal2a.c). Kemudian matriks tersebut akan dilakukan perhitungan dengan matrix baru (input user) sebagai berikut contoh perhitungan untuk matriks yang a da. Perhitungannya adalah setiap cel yang berasal dari matriks A menjadi angka untuk faktorial, lalu cel dari matriks B menjadi batas maksimal faktorialnya matri(dari paling besar ke paling kecil). <br>
(c).Program (soal2c.c) untuk mengecek 5 proses teratas apa saja yang memakan resource komputernya <br>
### Cara Pengerjaan
#### 2A
#### 2B
#### 2C

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
