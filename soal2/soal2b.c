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
