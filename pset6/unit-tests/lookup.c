/**
 * lookup.c
 *
 * Computer Science 50
 * Problem Set 6
 *
 * Tests functionality of lookup function for server.c
 * 
 * Test input:
 * 
 * /index.php
 * /pure-html.html
 * /kitten-little.jpg
 * /cat.jpg
 * /cat2.HTML
 * /cat3.HtMl
 * /favicon.ico
 * /test.css
 * /test.js
 * /hello.php?name=Alice
 * /hello.php?
 */
 
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

// prototype
const char* lookup(const char* path);
 
 int main(int argc, char* argv[])
 {
    //copies argv1 to path for test
    char path[strlen(argv[1])];
    for (int t = 0, n = strlen(argv[1]); t < n; t++)
    {
        path[t] = argv[1][t]; 
    }
    
    path[strlen(argv[1])] = '\0'; //null terminate path string
    
    const char* rtn_value = lookup(path);
    
    if (rtn_value != NULL)
    {
        printf("%s %s\n", path, rtn_value);
    }
    else
    {
        printf("NULL\n");
    }
 }
    
    /**
     * Function starts here
     **/
    
const char* lookup(const char* path)
{
    // iterate over path to find "."
    int i = 0;
    
    do
    {
        i++;
    }
    while (path[i] != 46);
    
    // write extension to new string
    char ext[5]; 
    int j = 0;
    
    while (isalpha(path[i+1]))
    {
        ext[j] = path[i+1];
        i++;
        j++;
    }
    
    ext[j] = '\0';
    
    printf("%s\n", ext); // for testing purposes
    
    // test extension
    if (strcasecmp("css", ext) == 0)
    {
        return "text/css";
    }
    else if (strcasecmp("html", ext) == 0)
    {
        return "text/html";
    }
    else if (strcasecmp("gif", ext) == 0)
    {
        return "image/gif";
    }
    else if (strcasecmp("ico", ext) == 0)
    {
        return "image/x-icon";
    }
    else if (strcasecmp("jpg", ext) == 0)
    {
        return "image/jpeg";
    }
    else if (strcasecmp("js", ext) == 0)
    {
            return "text/javascript";
    }
    else if (strcasecmp("php", ext) == 0)
    {
        return "text/x-php";
    }
    else if (strcasecmp("png", ext) == 0)
    {
        return "image/png";
    }

    return NULL;
}
