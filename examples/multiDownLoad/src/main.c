#include <curl/curl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define SIZE 5

static size_t callback()
{
}

static void transfer(CURLM *msg, const char **l)
{
  CURL *eh = curl_easy_init();
  int count = 0;

  /*
  l[0] = "https://www.microsoft.com";
  l[1] = "https://www.apple.com";
  l[2] = "https://www.oracle.com";
  l[3] = "https://www.amazon.com";
  l[4] = "https://www.cisco.com";
  */

  //for (count; count <= SIZE; count++)
  //{
  // curl_easy_setopt(eh, CURLOPT_VERBOSE, 1);
  //curl_easy_setopt(eh, CURLOPT_WRITEFUNCTION, callback);
  //curl_easy_setopt(eh, CURLOPT_URL, *(l + count));
  //curl_easy_setopt(eh, CURLOPT_URL, *(l + count));
  //printf("=>%s\n", *(l + count));
  //curl_easy_setopt(eh, CURLOPT_URL, l[count]);
  /*
    curl_easy_setopt(eh, CURLOPT_WRITEFUNCTION, write_cb);
    curl_easy_setopt(eh, CURLOPT_PRIVATE, l[count]);
    */
  //curl_multi_add_handle(msg, eh);
  // }

  printf("Transfer...\n");
}

int main(void)
{
  CURLM *curl_multi;
  CURLMsg *message;

  const char *list[SIZE];

  curl_global_init(CURL_GLOBAL_ALL);
  message = curl_multi_init();

  /* limit the amount of simultaneous connections curl should allow */
  curl_multi_setopt(message, CURLMOPT_MAXCONNECTS, 10L);

  transfer(message, list);

  return 0;
}