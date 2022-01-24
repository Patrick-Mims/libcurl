#include <stdio.h>
#include <curl/curl.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 30
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

static void display(struct node *list)
{
  struct node *s = NULL;

  for(s = list; s != NULL; s = s->next)
  {
    printf("%s\n", s->url);
  }
}

static struct node insert_node(struct node **list, char *item)
{
  struct node *new_node = NULL;

  if((new_node = malloc(sizeof(struct node))) == NULL)
  {
    exit(EXIT_FAILURE);
  }

  strcpy(new_node->url, item);

  new_node->next = *list;
  *list = new_node;
}

int main(int argc, char **argv)
{
  CURLM *multi_curl;
  CURLMsg *multi_message;

  curl_global_init(CURL_GLOBAL_DEFAULT);

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

  display(head);

  printf("count: %d\n", count);

  return 0;
}
