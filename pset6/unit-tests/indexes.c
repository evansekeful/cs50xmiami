/**
 * indexes.c
 *
 * Computer Science 50
 * Problem Set 6
 *
 * Tests functionality of lookup function for indexes.c
 * 
 * argv1 = path
 * 
 * Test input:
 * 
 * ~/workspace/pset6/public/test/
 * ~/workspace/pset6/unit-tests/other-dir/
 */
 
 // feature test macro requirements
#define _GNU_SOURCE
#define _XOPEN_SOURCE 700
#define _XOPEN_SOURCE_EXTENDED

// limits on an HTTP request's size, based on Apache's
// http://httpd.apache.org/docs/2.2/mod/core.html
#define LimitRequestFields 50
#define LimitRequestFieldSize 4094
#define LimitRequestLine 8190

// number of bytes for buffers
#define BYTES 512

// header files
#include <arpa/inet.h>
#include <dirent.h>
#include <errno.h>
#include <limits.h>
#include <math.h>
#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <ctype.h>

// types
typedef char BYTE;

// prototypes
void freedir(struct dirent** namelist, int n);
char* indexes(const char* path);

int main(int argc, char* argv[])
{
	char* path = argv[1];
	char* index = indexes(path);
	
	if (index == NULL)
	{
		printf("NULL\n");
	}
	else
	{
		printf("%s\n", index);
	}
}

char* indexes(const char* path)
{
    // initiate index path variable
    char* index_path = NULL;
    
    // ensure path is readable and executable
    if (access(path, R_OK | X_OK) == -1)
    {
        // error(403);
        return NULL;
    }

    // open directory
    DIR* dir = opendir(path);
    if (dir == NULL)
    {
        return NULL;
    }
    
    // iterate over directory namelist
    struct dirent** namelist = NULL;
    int n = scandir(path, &namelist, NULL, alphasort);
    for (int i = 0; i < n; i++)
    {
        char* name = namelist[i]->d_name;
        
        if(strcasecmp(name, "index.php") == 0)
		{
			index_path = malloc(strlen(path) + 10);
			if(index_path == NULL)
			{	
				free(index_path);
				freedir(namelist, n);
				// error(500);
				return NULL;
			}
			strcpy(index_path, path);
			strncat(index_path, name, 9);
			freedir(namelist, n);
			closedir(dir);
			return index_path;
		}
		
		if(strcasecmp(name, "index.html") == 0)
		{
			index_path = malloc(strlen(path) + 11);
			if(index_path == NULL)
			{	
				free(index_path);
				freedir(namelist, n);
				// error(500);
				return NULL;
			}
			strcpy(index_path, path);
			strncat(index_path, name, 10);
			freedir(namelist, n);
			closedir(dir);
			return index_path;
		}
    }
    
    // free memory allocated by scandir
    freedir(namelist, n);
    
    // close directory
    closedir(dir);
    
    return NULL;
}   
    
 /**
 * Frees memory allocated by scandir.
 */
void freedir(struct dirent** namelist, int n)
{
    if (namelist != NULL)
    {
        for (int i = 0; i < n; i++)
        {
            free(namelist[i]);
        }
        free(namelist);
    }
}