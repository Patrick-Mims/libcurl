#include <curl/curl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

const char *urls[] = {
  "microsoft",
  "oracle"
};

static void addTransfer(CURLM *m, int i)
{
    printf("Transfer: %d\n", i);
}

int main(void)
{
  int transfer = 0;
  CURLM *curl_multi;
  CURLMsg *message;

  curl_global_init(CURL_GLOBAL_ALL);
  message = curl_multi_init();

  /* limit the amount of simultaneous connections curl should allow */
  curl_multi_setopt(message, CURLMOPT_MAXCONNECTS, 10L);

  for(transfer; transfer < 10; ++transfer) {
    addTransfer(message, transfer);
  }

  return 0;
}
