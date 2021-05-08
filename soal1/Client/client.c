#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#define PORT 8080

#define SIZE 3000

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

int main(int argc, char const *argv[]) {
    struct sockaddr_in address, new_addr;
    socklen_t addr_size;
    int sock = 0, valread;
    int pil;
    int id;
    char *login = "2";
    char *regist = "1";
    char *add = "add";
    char *see = "see";
    char *find = "find";
    char *del = "delete";
    char *down = "down";
    char isi[1000]={0};
    char pass[100];
    char idc[3]={0};
    char kirim[200]={0};
    struct sockaddr_in serv_addr;
    FILE* fp;
    char filename[200]={0};
    char publisher[200]={0};
    char tahun[200]={0};
    char cari[200]={0};
    char delete[200]={0};
    char download[200]={0};
    
    char buffer[1024] = {0};
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\n Socket creation error \n");
        return -1;
    }
  
    memset(&serv_addr, '0', sizeof(serv_addr));
  
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
      
    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0) {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }
  
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        printf("\nConnection Failed \n");
        return -1;
    }

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
        if (strcmp(buffer,"login")==0){
            printf("login berhasil\n");
            //while(1){
                char cmd[100]={0};
                printf("masukkan command : ");
                scanf("%s",cmd);
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
                else if(strcmp(cmd,"see")==0){
                    send(sock , see , strlen(see) , 0 );
                    memset(buffer,0,sizeof(buffer));
                    valread = read( sock , buffer, 1024);
                    strcat(isi,buffer);
                    printf("\n%s",isi);
                }
                else if(strcmp(cmd,"find")==0){
                    send(sock , find , strlen(find) , 0 );
                    printf("Masukkan judul: ");
                    scanf("%s",cari);
                    send(sock , cari , strlen(cari) , 0 );
                    //printf("%s\n%s",cmd,cari);
                    // memset(buffer,0,sizeof(buffer));
                    // valread = read( sock , buffer, 1024);
                    // strcat(isi,buffer);
                    // printf("\n%s",isi);
                }
                else if(strcmp(cmd,"delete")==0){
                    send(sock , del , strlen(del) , 0 ); //pesan
                    printf("Masukkan judul: ");
                    scanf("%s",delete);
                    send(sock , delete , strlen(delete) , 0 );
                }
                else if(strcmp(cmd,"download")==0){
                    send(sock , down , strlen(down) , 0 );
                    printf("Masukkan judul: ");
                    scanf("%s",download);
                    send(sock , download , strlen(download) , 0 );
                    addr_size = sizeof(new_addr);
                    write_file(sock,download);
                }
            //}
            
        }
        else if (strcmp(buffer,"registered")==0){
            printf("registered\n");
        }
        else{
            printf("gagal login\n");
        }
    }
    else {
        printf("gagal");
    }
    // send(sock , hello , strlen(hello) , 0 );
    // printf("Hello message sent\n");
    // valread = read( sock , buffer, 1024);
    // printf("%s\n",buffer );
    return 0;
}
