#include <stdio.h>
#include "litt.h"
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>

void parsedirs(char* dirname)
{
   // printf("Init func call\n");
    char ignorefileinput[] = ".git"; // this is a placeholder (later on we gonna parse a file then add it to this char array to skip certain files/folders but for now this will do)
    DIR *d;
    struct dirent *dir;
    struct stat fileInfo;
    
    
    d = opendir(dirname);
    if (d)
    {
        while ((dir = readdir(d)) != NULL)
{
    char* stream = dir->d_name;
    if (strcmp(stream,".") == 0 || strcmp(stream,"..") == 0 /*|| strcmp(stream,ignorefileinput) == 0 */ )
    {
       // printf("SKIP WORKING\n");
        continue;
    }

    char fullPath[1024];
    snprintf(fullPath, sizeof(fullPath), "%s/%s", dirname, stream);

    if (stat(fullPath, &fileInfo) == 0)
    {
        if (S_ISDIR(fileInfo.st_mode))
        {
           /* DIR *directory;
            struct dirent *direct;
            struct stat fileInf;
            directory = opendir(fullPath);*/
            printf("%s is a directory.\n", stream);
            parsedirs(fullPath);
        }
        else if (S_ISREG(fileInfo.st_mode))
        {
            printf("%s is a regular file.\n", stream);
        }
        else
        {
            printf("%s is neither a directory nor a regular file.\n", stream);
        }
    }
    else
    {
        perror("Error getting file status");
    }
}
        closedir(d);
    }

}

int main(int argc, char *argv[])
{
    //we gonna wanna implement a gitignore type of thing so we can parse it and add it to the first if 
    // that skips the . and .. paths :D
    
    parsedirs(".");
    // printf("X value %d\n",argc);
    //  parse args
    if (argc < 2)
    {
        printf("Usage litt [-v {to print version}] [-h {for help}]\n ");
        return 0;
    }
    for (int i = 0; i < argc; i++)
    {

        // printf(argv[i]);
        if (strcmp(argv[i], "init") == 0)
        {
            printf("initalizing repository\n");
            
        }
    }

    return 0;
}
