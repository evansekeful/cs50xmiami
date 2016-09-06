/**
 * load.c
 *
 * Computer Science 50
 * Problem Set 6
 *
 * Tests functionality of parse function for load.c
 * 
 * argv1 - test file; argv2 - output name
 * 
 * Test input:
 * 
 * index.html response.html
 * 
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

// prototypes
bool load(FILE* file, BYTE** content, size_t* length);
const char* reason(unsigned short code);
 
 int main(int argc, char* argv[])
 {
    // remember filenames
    char* infile = argv[1];
    char* outfile = argv[2];
    
    // open input file 
    FILE* file = fopen(infile, "r");
    
    // load content
    char* content;
    size_t length;
    if (load(file, &content, &length) == false)
    {
        printf("error(500)");
    }
    
    // write content to output file
    FILE* outptr = fopen(outfile, "w");
    fwrite(content, sizeof(content), 1, outptr);

    // prepare response
    int code = 200;
    const char* phrase = reason(code);
    printf("HTTP/1.1 %i %s\r\n", code, phrase);

    // close file
    fclose(file);
    fclose(outptr);    
}

    
    /**
     * Function starts here
     **/
 bool load(FILE* file, BYTE** content, size_t* length)
 {
    // checks if file is present
    if (file == NULL)
    {
        return false;
    }
    
    // initialize pointers
    *content = NULL;
    *length = 0;
    
    // initialize buffer
    BYTE buffer[BYTES];
    
    while(1)
    {
        // read a buffer's worth of bytes
        size_t bytes = fread(buffer, sizeof(BYTE), BYTES, file);
        
        // error check
        if (ferror(file) != 0)
        {
            if (*content != NULL)
            {
                free(*content);
                *content = NULL;
                *length = 0;
            }
            
            return false;
        }
        
        // if bytes read, append to content
        if (bytes > 0)
        {
            *content = realloc(*content, *length + bytes + 1);
            
            if (*content == NULL)
            {
                *length = 0;
                return false;
            }
            
            // write file to content
            memcpy(*content + *length, buffer, bytes);
            *length += bytes;
        }
        
        // check for EOF
        if (feof(file) != 0)
        {
                break;
        }
    }
        
    *(*content + *length) = '\0';
    return true;
 }

     /**
     * Function ends here
     **/
     
/**
 * Returns status code's reason phrase.
 *
 * http://www.w3.org/Protocols/rfc2616/rfc2616-sec6.html#sec6
 * https://tools.ietf.org/html/rfc2324
 */
const char* reason(unsigned short code)
{
    switch (code)
    {
        case 200: return "OK";
        case 301: return "Moved Permanently";
        case 400: return "Bad Request";
        case 403: return "Forbidden";
        case 404: return "Not Found";
        case 405: return "Method Not Allowed";
        case 414: return "Request-URI Too Long";
        case 418: return "I'm a teapot";
        case 500: return "Internal Server Error";
        case 501: return "Not Implemented";
        case 505: return "HTTP Version Not Supported";
        default: return NULL;
    }
}