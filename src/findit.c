#include <stdio.h>
#include "findit.h"
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <unistd.h>
// #define PATH_MAX 1024 * 1024

void parsedirs(char *dirname, char *searchkey)
{
    DIR *d;
    struct dirent *dir;
    struct stat fileInfo;

    d = opendir(dirname);
    if (d)
    {
        while ((dir = readdir(d)) != NULL)
        {
            char Foundaddr[PATH_MAX];
            char fullPath[PATH_MAX];
            char resolvedPath[PATH_MAX];
            char *stream = dir->d_name;
            snprintf(fullPath, sizeof(fullPath), "%s/%s", dirname, stream);
            realpath(fullPath, resolvedPath); // Use realpath to handle symbolic links
            



            if (strcmp(stream, ".") == 0 || strcmp(stream, "..") == 0 || strncmp(stream, ".", 1) == 0 )
            {
                continue;
            }

            if (stat(resolvedPath, &fileInfo) == 0)
            {
                if (S_ISLNK(fileInfo.st_mode))
                {
                    
                    printf("ENOUGHHHH!");
                    continue;
                }
                if (S_ISDIR(fileInfo.st_mode))
                {
                    if (strstr(stream, searchkey) != NULL)
                    {
                        printf("Found %s at \t", searchkey);
                        printf("%s\n", fullPath);
                        snprintf(Foundaddr, sizeof(Foundaddr), "%s", fullPath);
                        //printf("FOUNDADDR %s\n", Foundaddr);
                    }
                    else if (strstr(Foundaddr, fullPath) != NULL)
                    {
                        printf("Was found");
                        continue;
                    }

                    parsedirs(fullPath, searchkey);
                }
                else if (S_ISREG(fileInfo.st_mode))
                {

                    if (strstr(stream, searchkey) != NULL)
                    {
                        printf("Found %s at \t", searchkey);
                        printf("%s\n", fullPath);
                        snprintf(Foundaddr, sizeof(Foundaddr), "%s", fullPath);
                      //  printf("FOUNDADDR %s\n", Foundaddr);
                    }
                    else if (strstr(Foundaddr, fullPath) != NULL)
                    {
                        printf("Was found");
                        continue;
                    }
                }
                else
                {
                    if (strstr(stream, searchkey) != NULL)
                    {
                        printf("Found %s at \t\n But this(%s)is neither a directory nor a regular file.\n", searchkey, stream);
                        printf("%s\n", fullPath);
                    }
                }
            }
            else
            {
                perror("Error getting file status\n");
            }
        }
        closedir(d);
    }
}

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        printf("Usage findit <PATH> <KEYWORD>\n ");
        printf("Provide both args!!\n ");
        return 0;
    }
    parsedirs(argv[1], argv[2]);

    return 0;
}
