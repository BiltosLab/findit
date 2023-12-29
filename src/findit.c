#include "findit.h"

// #define PATH_MAX 1024 * 1024

void parsedirs(char *dirname, char *searchkey, char *ignore, bool SKIPHIDDEN)
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

            if (strcmp(stream, ".") == 0 || strcmp(stream, "..") == 0 || (SKIPHIDDEN ? strncmp(stream, ".", 1) == 0 : 0))
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
                    if (strstr(stream,ignore)!=NULL)
                    {
                        continue;
                    }
                    
                    if (strstr(stream, searchkey) != NULL)
                    {
                        printf("Found %s at \t", searchkey);
                        printf("%s\n", fullPath);
                        snprintf(Foundaddr, sizeof(Foundaddr), "%s", fullPath);
                        // printf("FOUNDADDR %s\n", Foundaddr);
                    }
                    else if (strstr(Foundaddr, fullPath) != NULL)
                    {
                        printf("Was found");
                        continue;
                    }

                    parsedirs(fullPath, searchkey, ignore, SKIPHIDDEN);
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

    if (argc == 3)
    {
        parsedirs(argv[1], argv[2], "", 1);
        return 0;
    }
    if (argc == 4)
    {
        parsedirs(argv[1], argv[2], argv[3], 1);
        return 0;
    }
    if (argc == 5 && strcmp("-sh", argv[4]) == 0)
    {
        parsedirs(argv[1], argv[2], argv[3], 0);
        return 0;
    }

    if (argc < 3 || argc > 3)
    {

        if (argc == 2 && strcmp("-version", argv[1]) == 0)
        {
            printf("%s\n", FINDITVERSION);
            return 0;
        }

        printf("Usage findit <PATH> <KEYWORD> <Ignore DIR/FILE> <-sh Search hidden by default hidden files are skipped>\nOR findit -version \nMinimum usage findit <PATH> <KEYWORD> \n");
    }

    return 0;
}
