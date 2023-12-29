#include <stdio.h>
#include "findit.h"
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>

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
            char *stream = dir->d_name;
            if (strcmp(stream, ".") == 0 || strcmp(stream, "..") == 0)
            {
                continue;
            }

            char fullPath[10240];
            snprintf(fullPath, sizeof(fullPath), "%s/%s", dirname, stream);

            if (stat(fullPath, &fileInfo) == 0)
            {
                if (S_ISDIR(fileInfo.st_mode))
                {
                    if (strstr(stream, searchkey)!=NULL)
                    {
                        printf("Found %s at \t", searchkey);
                        printf("%s\n", fullPath);
                    }
                    parsedirs(fullPath, searchkey);
                }
                else if (S_ISREG(fileInfo.st_mode))
                {

                    if (strstr(stream, searchkey)!=NULL)
                    {
                        printf("Found %s at \t", searchkey);
                        printf("%s\n", fullPath);
                    }
                }
                else
                {
                    if (strstr(stream, searchkey)!=NULL)
                    {
                        printf("Found %s at \t\n But this(%s)is neither a directory nor a regular file.\n", searchkey,stream);
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
