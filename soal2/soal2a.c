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
