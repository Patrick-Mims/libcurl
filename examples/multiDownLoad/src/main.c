#include <curl/curl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static void addTransfer(CURLM *m, const char *u[])
{
  CURL *eh = curl_easy_init();
  int i = 0;

  u[0] = "https://www.microsoft.com";
  u[1] = "https://www.apple.com";
  u[2] = "https://www.oracle.com";
  u[3] = "https://www.amazon.com";
  u[4] = "https://www.cisco.com";
  u[5] = "https://www.ibm.com";

  for (i; i < 10; ++i)
  {
    curl_easy_setopt(eh, CURLOPT_URL, u[i]);
    curl_multi_add_handle(m, eh);
  }
}

int main(void)
{
  CURLM *curl_multi;
  CURLMsg *message;

  /* moved the array inside main */
  const char *urls[10];

  curl_global_init(CURL_GLOBAL_ALL);
  message = curl_multi_init();

  /* limit the amount of simultaneous connections curl should allow */
  curl_multi_setopt(message, CURLMOPT_MAXCONNECTS, 10L);

  addTransfer(message, urls);

  return 0;
}
