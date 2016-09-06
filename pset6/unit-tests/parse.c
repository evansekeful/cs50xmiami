/**
 * parse.c
 *
 * Computer Science 50
 * Problem Set 6
 *
 * Tests functionality of parse function for server.c
 * 
 * ! abs_path MUST be null-terminated
 * 
 * Test input:
 * 
 * GET /hello.php HTTP/1.1
 * GET /hello.html HTTP/1.1
 * GET /hello.php?name=ellie HTTP/1.1
 * GET /cat.jpg HTTP/1.1
 * GET /cat2.HTML HTTP/1.1
 * GET /cat3.HtMl HTTP/1.1
 * GET /test.css HTTP/1.1
 * GET /test.js HTTP/1.1
 * GET /favicon.ico HTTP/1.1
 * GET /hello.php? HTTP/1.1
 * * remember to use "" to indicate a single string argument
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
 
 
// limits on an HTTP request's size, based on Apache's
// http://httpd.apache.org/docs/2.2/mod/core.html
#define LimitRequestFields 50
#define LimitRequestFieldSize 4094
#define LimitRequestLine 8190

// prototypes
bool parse(const char* line, char* abs_path, char* query);
 
 int main(int argc, char* argv[])
 {
    //copies argv1 to line for test
    char line[strlen(argv[1])];
    for (int t = 0, n = strlen(argv[1]); t < n; t++)
    {
        line[t] = argv[1][t]; 
    }
    
    char abs_path[LimitRequestLine + 1];
    char query[LimitRequestLine + 1];
    
    if (parse(line, abs_path, query) == true)
    {
        printf("true\n");
    }
    else
    {
        printf("false\n");
    }
    printf("%s\n", abs_path);
    printf("%s\n", query);
 }
    
    /**
     * Function starts here
     **/
     
bool parse(const char* line, char* abs_path, char* query)
{
 // check request-line is appropriately formatted
    if (strstr(line, "GET") == NULL)
    {
        printf("error(405);\n");
        return false;
    }
    else if(line[0] != 'G' || line[3] != ' ')
    {
        printf("error(405);\n");
        return false;
    }
    else if(line[4] != '/')
    {
       printf("error(501);\n");
       return false;
    }
    else if (strstr(line, "HTTP/1.1") == NULL)
    {
        printf("error(505);\n");
        return false;
    }
    else if (strstr(line, "\"") != NULL)
    {
        printf("error(400);\n");
        return false;
    }
    
    // define abs_path
    const char* ap_start = strchr(line, 32) + 1;
    const char* ap_end = strrchr(line, 32);
    
    if (ap_start == NULL)
    {
        printf("error(501);\n");
        return false;
    }
    else if (ap_end != NULL)
    {
        strncpy(abs_path, ap_start, (ap_end - ap_start));
        abs_path[ap_end - ap_start] = '\0';
        
        // check if path starts with '/'
        if (abs_path[0] != '/')
        {
            printf("error(501);\n");
            return false;
        }
        
        // check for and store query
        const char* q_start = strchr(abs_path, '?');
        if (q_start != NULL)
        {
            // create query
            const char* q_end = strchr(abs_path, '\0');
            strncpy(query, q_start + 1, q_end - q_start);
            query[strlen(query)] = '\0';
            
            // edit abs_path
            abs_path[strlen(abs_path) - strlen(query) - 1] = '\0';
            
            return true;
        }
        
    }
    
    return true;
}

    
    /**
     * Function ends here
     **/