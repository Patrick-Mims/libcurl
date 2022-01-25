#include <curl/curl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 50
#define NUM_URLS

struct node
{
  char url[SIZE];
  struct node *next;
};

/*
   static size_t callback(char *data, size_t n, size_t l, void *userp)
   {

   }
   */

/*
   void display(struct node *list)
   {
   struct node *p = NULL;

   for (p = list; p != NULL; p = p->next)
   {
   printf("%s\n", p->url);
   }
   }

   d display(struct node *list)
   {
   struct node *s = NULL;

   for(s = list; s != NULL; s = s->next)
   {
   printf("%s\n", s->url);
   }
   }
   */

void curl_multi(CURLM *multi, char *str)
{

}

void curl_easy(CURL *easy, const char *str)
{
  char buffer[1024];
  if(easy == NULL)
  {
    printf("something is wrong with curl_easy()\n");
    exit(EXIT_FAILURE);
  }

  printf("URL: %s\n", str);

  curl_easy_setopt(easy, CURLOPT_URL, str);
  curl_easy_setopt(easy, CURLOPT_FOLLOWLOCATION, 1L);

  if((curl_easy_perform(easy)) == CURLE_OK)
  {
    size_t len = strlen(buffer);

    if(len)
      fprintf(stderr, "%s%s", buffer, ((buffer[len -1] != '\n') ? "\n" : ""));

    printf("SUCCESS!\n");
  }

  curl_easy_cleanup(curl);
}

void insert_node(struct node **list, char *item)
{
  struct node *new_node = NULL;

  if((new_node = malloc(sizeof(struct node))) == NULL)
    exit(EXIT_FAILURE);

  strcpy(new_node->url, item);

  new_node->next = *list;
  *list = new_node;
}

int main(int argc, char **argv)
{
  CURL *curl;

  curl = curl_easy_init();

  int count = 0;
  char item[SIZE];
  char url[SIZE];
  FILE *fp = NULL;

  strcpy(url,"https://");
  struct node *head = NULL;

  if((head = malloc(sizeof(struct node))) == NULL)
  {
    exit(EXIT_FAILURE);
  }

  fp = fopen("companies.txt", "r");

  if(fp == NULL)
  {
    printf("Error!\n");
    exit(1);
  }

  while (fscanf(fp, "%s", item) != EOF)
  {
    insert_node(&head, item);
    count = count + 1;

    if(count == 1)
    {
      strcat(url, item);
      curl_easy(curl, url);
    }
    printf("->%s\n", url);
  }

  fclose(fp);

  //display(head);

  printf("count: %d\n", count);

  curl_easy(curl, "https://www.microsoft.com");

  return 0;
}

//gcc -Wall -o build/main7 src/main.c -lcurl -I~/source-code/curl/include
