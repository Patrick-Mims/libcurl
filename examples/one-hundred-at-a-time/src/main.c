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

void curl_easy(CURL *curl, char *str)
{

  if(curl == NULL)
  {
    printf("something is wrong with curl_easy()\n");
    exit(EXIT_FAILURE);
  }

  printf("URL: %s\n", str);

  curl_easy_setopt(curl, CURLOPT_URL, str);
  curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

  if((curl_easy_perform(curl)) == CURLE_OK)
  {
    printf("SUCCESS!\n");
  }

}

void insert_node(struct node **list, char *item)
{
  struct node *new_node = NULL;

  if((new_node = malloc(sizeof(struct node))) == NULL)
    exit(EXIT_FAILURE);

  printf("Pushing -> %s\n", item);
  strcpy(new_node->url, item);

  new_node->next = *list;
  *list = new_node;
}

int main(int argc, char **argv)
{
  CURL *curl;
  //CURLcode ret;
  //CURLMsg *multi_message;

  curl = curl_easy_init();
  //curl_global_init(CURL_GLOBAL_DEFAULT);

  int count = 0;
  char item[SIZE];
  FILE *fp = NULL;

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
  }

  fclose(fp);

  //display(head);
  //gcc -Wall -o build/main7 src/main.c -lcurl -I~/source-code/curl/include

  printf("count: %d\n", count);

  curl_easy(curl, "https://www.microsoft.com");

  return 0;
}
