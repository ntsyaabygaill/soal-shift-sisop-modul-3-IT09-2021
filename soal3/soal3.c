#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <dirent.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <pthread.h>
#include <ctype.h>

char buf[PATH_MAX+1];
char path[PATH_MAX+1], *p;
char *nama_file;
char *alamat_file;
char destpath[1024];
void *cek_file(void *arg);
int index_file = 0;
pthread_mutex_t lock;
pthread_t tid;

int is_regular_file(const char *path)
{
  struct stat path_stat;
  stat(path, &path_stat);
  return S_ISREG(path_stat.st_mode);
} 

// fungsi buat mencari path dari file c
void path_c(char *str)
{
  FILE *fp;
  char buf[4096], *p;

  *str = '\0';
  if(!(fp = fopen("/proc/self/maps", "r"))) return;

  fgets(buf, sizeof(buf), fp);
  fclose(fp);

  *(p = strchr(buf, '\n')) = '\0';
  
  while(*p != ' ') p--;

  strcpy(str, p+1);
  str[PATH_MAX] = '\0';
}

// list semua file yang ada di direktori file c dan dimasukkan di file "list_file.txt"
void list_file(char *path)
{
  FILE *f = fopen("list_file.txt", "w");
  if (f == NULL)
  {
    puts("Error dalam membuka file");
    exit(1);
  }

  DIR *d;
  struct dirent *dir;

  d = opendir(path);
  if (d)
  {
    while ((dir = readdir(d)) != NULL)
    {
      if (dir->d_type == DT_REG)
      {
        fprintf(f, "%s%s\n", path, dir->d_name);
        index_file++;
      }
    }
    closedir(d);
    fclose(f);
  }
}

void read_path(char *arg)
{
  FILE* filePointer;
  int bufferLength = 255;
  char buffer[bufferLength];

  // Variabel temp buat nyimpan argumen
  char *temp;
  temp = strrchr(arg, '/') + 1;
  strcat(temp, "\n");

  filePointer = fopen("list_file.txt", "r");

  // printf("JUMLAH FILES: %d\n", index_file);

  // Error handling mutex
  if (pthread_mutex_init(&lock, NULL) != 0)
  {
    puts("Gagal buat mutex");
    exit(EXIT_FAILURE);
  }

  // Buat thread
  while(fgets(buffer, bufferLength, filePointer))
  {
    nama_file = strrchr(buffer, '/') + 1;

    // Skip file txt dan file program
    if (strcmp(nama_file, "list_file.txt\n") == 0 || strcmp(nama_file, temp) == 0)
    {
      printf("%s skipped\n", nama_file);
      continue;
    }
    else{ 
      // WAKTU NYA MEMBUAT THREAD :)
      buffer[strcspn(buffer, "\r\n")] = 0;  // buat hapus enter di buffer

      pthread_create(&(tid), NULL, cek_file, (void *)buffer);

      pthread_join(tid, NULL);
    }
  }
  fclose(filePointer);

  // Hapus file "list_file.txt"
  if (remove("list_file.txt") == 0) puts("Direktori sukses disimpan!");
  else
    puts("Yah, gagal disimpan :(");
;
}

char *cari_ekstensi(char *filename)
{
  char *temp = filename;

  char *extension = strrchr(temp, '.');

  if(!extension || extension == temp) return 0;
  
  int len = 0;
  char tipe[100];

  extension = extension+1;
  strcpy(tipe, extension);

  if((extension[strlen(extension)-1] >= 'a' && extension[strlen(extension)-1] <= 'z') || (extension[strlen(extension)-1] >= 'A' && extension[strlen(extension)-1] <= 'Z'))
  {
    for(int i = 0; tipe[i]; i++)
    {
      tipe[i] = tolower(tipe[i]);
      len++;
    }
  }

  extension = tipe;

  return extension;
}

void* cek_folder(char *foldername)
{
  int len = 0;
  char tipe[100];

  strcpy(tipe, foldername);

  if(!strcmp(foldername, "Unknown"))
  {

  }
  else if((foldername[strlen(foldername)-1] >= 'a' && foldername[strlen(foldername)-1] <= 'z') || (foldername[strlen(foldername)-1] >= 'A' && foldername[strlen(foldername)-1] <= 'Z'))
  {
    for(int i = 0; tipe[i]; i++)
    {
      tipe[i] = tolower(tipe[i]);
      len++;
    }
  }

  foldername = tipe;
  int exist = 0;

  DIR *d;
  struct dirent *dir;
  d = opendir(".");

  while((dir = readdir(d)) != NULL) //smpe gada file lagi di dir
  {
    if(strcmp(dir->d_name,".") == 0 || strcmp(dir->d_name, "..") == 0) continue;

    //bukan file = dir
    if(!is_regular_file(dir->d_name))
    {
      if(!strcmp(foldername, dir->d_name))
      {
        exist = 1;
      }
    }
  }
  closedir(d);

  if (!exist)
  {
    mkdir(foldername, 0700);
  }
  else
  {
    // directory ada
  }
}

void* move_file(char *pathc, char *ekstensi, char *nama_file, char *alamat_asal)
{
  sprintf(destpath, "%s%s/%s", pathc, ekstensi, nama_file);


  if (rename (alamat_asal, destpath))
  {
    // something went wrong
    if (errno == EXDEV) {
        // copy data and meta data 
    } else { printf("%s : Sad, gagal :(\n", nama_file); };
  } 
  else { printf("%s : Berhasil Dikategorikan\n\n", nama_file);// the rename succeeded
  }
}

void* move_file2(char *pathc, char *ekstensi, char *nama_file, char *alamat_asal)
{
  sprintf(destpath, "%s%s/%s", pathc, ekstensi, nama_file);


  if (rename (alamat_asal, destpath))
  {
    // something went wrong
    if (errno == EXDEV) {
        // copy data and meta data 
    } else {};
  } 
  else {
  }
}


void *cek_file(void *arg)
{
  // Lock mutex
  pthread_mutex_lock(&lock);

  nama_file = strrchr((char *)arg, '/') + 1;
  alamat_file = (char *)arg;

  if(cari_ekstensi(nama_file))
  { 
    cek_folder(cari_ekstensi(nama_file));
    move_file2(path, cari_ekstensi(nama_file), nama_file, alamat_file);
  }
  else
  { 
    cek_folder("Unknown");
    move_file2(path, "Unknown", nama_file, alamat_file);
  }

  // Unlock mutex
  pthread_mutex_unlock(&lock);
  return NULL;
}

int main(int argc, char **argv)
{
  path_c(buf);

  strcpy(path, buf);
  if((p = strrchr(path, '/')))
    *(p+1) = '\0';
  
  int i = 2;
  if (argc == 0)
  {
    puts("Mohon masukkan argumen pada program (-f, *, atau -d)");
    exit(EXIT_FAILURE);
  }
  
  // Error handling mutex
  if (pthread_mutex_init(&lock, NULL) != 0)
  {
    puts("Gagal buat mutex");
    return 1;
  }
  
  if(strcmp(argv[1], "-f") == 0)
  {
    // masuk ke mode -f
    
    while (i < argc)
    {
      if(!is_regular_file(argv[i]))
      {
        puts("EXIT not a file");
        exit(EXIT_FAILURE);
      }

      pthread_create(&(tid), NULL, cek_file, (void *)argv[i]);
      pthread_join(tid, NULL);
      i++;
    }
  }
  else if(strcmp(argv[1], "*") == 0)
  {
    // masuk ke mode *

    if (argc > 2)
    {
      puts("Mohon tidak memasukkan argumen lain ketika menggunakan mode *");
      exit(EXIT_FAILURE);
    }
    
    printf("path = ");
    puts(path);
    list_file(path);

    read_path(argv[0]);
  }
  else if(strcmp(argv[1], "-d") == 0)
  {
    // masuk ke mode -d

    if (argc > 3)
    {
      puts("Mohon hanya memasukkan satu path directory!");
      exit(EXIT_FAILURE);
    }
    
    list_file(argv[2]);
    read_path(argv[0]);

  }

  return 0;
}
