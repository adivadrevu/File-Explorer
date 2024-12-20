#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/wait.h>
#include<string.h>
#include<fcntl.h>
#include<stdlib.h>
#include<sys/types.h>
// #include <conio.h>
#include <sys/stat.h>


char path[100]="/";

void copypaste(char * s_path, char * d_path){

    int src_fd, dst_fd, n, err;
    unsigned char buffer[4096];
    printf("s_path: %s",s_path);
    src_fd = open(s_path, O_RDONLY);
    printf("src_fd %d",src_fd);
    dst_fd = open(d_path, O_CREAT | O_WRONLY );

    while (1) {
        err = read(src_fd, buffer, 4096);
        if (err == -1) {
            printf("Error reading file.\n");
            exit(1);
        } else {
            printf("copied the file");
        }
        n = err;

        if (n == 0) break;
        printf("dst_fd %d",dst_fd);
        printf("buffer %c",buffer);
        printf("n %d",n);

        err = write(dst_fd, buffer, n);
        if (err == -1) {
            printf("Error writing to file.\n");
            exit(1);
        } else {
            printf("pasted the file");
        }
    }
    close(src_fd);
    close(dst_fd);
}

int subdirectoriesdisplay(char *p)
{
    printf("\n\nSub-directories List: \n\n");
    pid_t pid1=0;
    pid1=fork();
    if(pid1==0){
        char *str[]={"ls",p,NULL};
        int res=execvp("ls",str);
        return res;
    }else{
        wait(NULL);
    }
 return 0;
}

void createDir(char dirname[100]){
    int check;
  
    printf("in create dir");
    printf("dirname in cr dir: %s",dirname);
    check = mkdir(dirname,0777);
    printf("\ncheck: %d \n",check);
    if (!check)
        printf("Directory created\n");
    else {
        printf("Unable to create directory\n");
        exit(1);
    }
}

int filedisplay(char *p)
{
    pid_t pid1=0;
    pid1=fork();
    if(pid1==0){
        execlp("cat","cat",p,0);
        return 0;
    } else {
        wait(NULL);
    }
return 0;
}

void backfunction()
{
    for(int i=strlen(path);i>=1;i--)
    {
        if(path[i]!='/'){
            path[i]='\0';
        }else{
            path[i]='\0';
            return;
        }
    }
}

void createFile(char dirname[100]){

    FILE *fp;
    printf("createFile: %s",dirname);
    fp  = fopen (dirname, "w");
}

int main(){
        pid_t pid=0;
        pid_t pid_1=0;
        int i=0;
        char wish[50];
        char temp_path[500];
        char src_path[500];
        char dst_path[500];
        char dirname[100];
        int result;
        int opt;
        while(i>=0){
                system("clear");
                printf("\t\t\t   FILE EXPLORER APPLICATION\n\n\n");
                printf("\n Path: %s",path);
                printf("\n\n");
                int b=filedisplay(path);
                char s[50];
                int c=subdirectoriesdisplay(path);

               printf("\nChoose an option: \n");
               printf("\n enter 1 to move into a sub-directory: \n");
               printf("\n enter 2 to copy-paste a file to new file: \n");
               printf("\n enter 3 to create a new directory: \n");
               printf("\n enter 4 to create a new file: \n");
                scanf("%d",&opt);
                switch(opt) {
                    case 3 :
                        printf("\nWould you plike to create a directory?\n");
                        printf("\nenter yes or no: ");
                        scanf("%s",wish);
                        result = strcmp(wish, "yes");
                        if(result == 0){
                            printf("\n\nenter the name of new directory\n ");
                            scanf("%s",dirname);
                            printf("%s\n", dirname);
                            strcat(path,"/");
                            strcat(path,dirname);
                            createDir(path);
                        }
                        if(strcmp(s,"back")==0){
                        backfunction();
                        }else if(strcmp(s,"exit")==0){
                        exit(0);
                        }
                        
                        break;
                    case 2 :
                        printf("\nDo you wish to copy a file?\n");
                        printf("\nenter yes or no: ");
                        scanf("%s",wish);
                        result = strcmp(wish, "yes");
                        //temp_path = path;
                        strcpy(temp_path,path);
                        if(result == 0){
                            printf("\npath: %s",temp_path);
                            printf("\n\nenter path of file to be copied from: ");
                            scanf("%s",src_path);
                            strcat(temp_path,"/");
                            strcat(temp_path,src_path);
                            printf("\n\npath entered is: %s",src_path);
                            printf("\n\nenter path of file to be copied to: ");
                            scanf("%s",dst_path);
                            printf("\n\npath entered is: %s",dst_path);
                            copypaste(src_path, dst_path);
                        
                        }

                        if(strcmp(s,"back")==0){
                            backfunction();
                        }else if(strcmp(s,"exit")==0)
                        {
                            exit(0);
                        }
                        

                        break;
                    case 1 :
                        printf("\nEnter the sub-directory you wish to move into: ");
                        scanf(" %s",s);

                        if(strcmp(s,"back")==0){
                        backfunction();
                        }else if(strcmp(s,"exit")==0){
                        exit(0);
                        }else{
                            if(i!=0){ 
                                strcat(path,"/");
                            }
                        strcat(path,s);
                        }

                        break;
                    case 4 :
                        printf("\nWould you plike to create a new file?\n");
                        printf("\nenter yes or no: ");
                        scanf("%s",wish);
                        result = strcmp(wish, "yes");
                        if(result == 0){
                            printf("\n\nenter the name of new file with extension\n ");
                            scanf("%s",dirname);
                            printf("%s\n", dirname);
                            strcat(path,"/");
                            strcat(path,dirname);
                            createFile(path);
                        }
                        if(strcmp(s,"back")==0){
                            backfunction();
                        } else if(strcmp(s,"exit")==0){
                            exit(0);
                        }

                        break;
                    default :
                         printf("Invalid option\n" );
                         exit(0);
                }

                if(strcmp(s,"back")==0){
                        backfunction();
                }else if(strcmp(s,"exit")==0){
                        exit(0);
                }
                i++;
       
        }
}

