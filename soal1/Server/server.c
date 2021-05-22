#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <dirent.h>
#define PORT 8080

#define SIZE 3000

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

int main(int argc, char const *argv[]) {
    int server_fd, new_socket, valread, new_sock;
    struct sockaddr_in address, new_addr;
    socklen_t addr_size;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};
    char *hello = "Hello from server";
    char *sukses = "sukses";
    char *login = "login";
    char *gagal = "gagal";
    char *registered = "registered";
    FILE * fp;
    FILE * down;
    char namafile[200]={0};
    char publish[200]={0};
    char tahun[200]={0};
    char file_del[200]={0};
    char tulis[1000]={0};
    char t_log[1000]={0};
    char file_down[1000]={0};
    char cari[200]={"\0"};
    char hasil_cari[200]={0};

    /* open the file for writing*/
    fp = fopen ("akun.txt","a+");
    
    char isi[1024]={0};
    char *ptr;
    char *ret;

    FILE * tsv;
    /* open the file for writing*/
    tsv = fopen ("files.tsv","a+");

    FILE * log;
    /* open the file for writing*/
    log = fopen ("running.log","a+");
      
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
      
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( PORT );
      
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address))<0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0) {
        perror("accept");
        exit(EXIT_FAILURE);
    }

    valread = read(new_socket , buffer, 1024);
    //printf("%s\n",buffer );
    if (strcmp(buffer,"2")==0){
        send(new_socket , sukses , strlen(sukses) , 0 );
        memset(buffer,0,sizeof(buffer));
        char * buff = 0;
        long length;
        FILE * f = fopen ("akun.txt", "rb");

        if (f)
        {
            fseek (f, 0, SEEK_END);
            length = ftell (f);
            fseek (f, 0, SEEK_SET);
            buff = malloc (length);
        if (buff)
        {
            fread (buff, 1, length, f);
        }
        fclose (f);
        }

        if (buff)
        {
            //printf("%s",buff);
            valread = read(new_socket , buffer, 1024);
            strcat(isi,buffer);
            ret = strstr(buff, isi);
            if (ret){
                send(new_socket , login , strlen(login) , 0 );
                memset(buffer,0,sizeof(buffer));
                // while (1)
                // {
                    valread = read(new_socket , buffer, 1024);
                    //printf("%s",buffer);
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

                    
                //}
                
                
                //printf("[+]Data written in the text file ");
            }
            else
            send(new_socket , gagal , strlen(gagal) , 0 );
        }
    }

    else if (strcmp(buffer,"1")==0){
        send(new_socket , sukses , strlen(sukses) , 0 );
        memset(buffer,0,sizeof(buffer));
        valread = read(new_socket , buffer, 1024);
        //printf("%s\n",buffer );
        strcat(isi,buffer);
        strcat(isi,"\n");
        if(fp){
            fputs(isi,fp);
        }
        fclose (fp);
        send(new_socket , registered , strlen(registered) , 0 );
    }
    

    // valread = read( new_socket , buffer, 1024);
    // printf("%s\n",buffer );
    // send(new_socket , hello , strlen(hello) , 0 );
    // printf("Hello message sent\n");
    return 0;
}
