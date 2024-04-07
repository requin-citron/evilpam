#ifndef HTTPSEXFIL_H
#define HTTPSEXFIL_H

#include <curl/curl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define USERAGENT "VICTIME1"
#define FILNAL_URL_LEN 1000

#define URL "http://127.0.0.1:8000/index.php"

int https_exfil(const char *, const char *);

#endif