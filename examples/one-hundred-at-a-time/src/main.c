#include <curl/curl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 50
#define NUM_URLS

/*
#define CURLM *cm
#define CURL *curl
*/

#define INTERFACE(x) ((x) == (0) ? CURL : CURLM)

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

void curl_multi(CURLM *multi, struct node *list)
{
    int cnt = 1; // this is temporary, fix buffer overflow later :(
    struct node *m = NULL;

    m = list;

    do
    {
      m = m->next;
      printf("-> %s\n", m->url);
      cnt = cnt + 1;
    } while(cnt < 44);

    /*
    int i = 1;
    for(m = list; m != NULL; m = m->next)
    {
      printf("going here->%d. %s\n",i, m->url);
      i = i + 1;
    }
    */
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

  curl_easy_cleanup(easy);
}

void insert_node(struct node **list, char *item)
{
  /* create a new node */
  struct node *new_node = NULL;

  /* allocate memory for the new node. */
  if((new_node = malloc(sizeof(struct node))) == NULL)
    exit(EXIT_FAILURE);

  /* store data in the node. */
  strncpy(new_node->url, item, sizeof(new_node->url) - 1);

  /* insert node into the list. */
  new_node->next = *list;
  *list = new_node;
}

int main(int argc, char **argv)
{
  //CURL *curl;
  CURLM *cm;

  //curl = curl_easy_init();
  cm = curl_multi_init();

  int count = 0;
  char item[SIZE];
  char url[SIZE];
  FILE *fp = NULL;

  strcpy(url,"https://");

  /* set head to point to the beginning of the list */
  struct node *head = NULL;

  /* initialize to the size of the (struct node) */
  if((head = malloc(sizeof(struct node))) == NULL)
  {
    exit(EXIT_FAILURE);
  }

  if((fp = fopen("companies.txt", "r")) == NULL)
  {
    printf("Error!\n");
    exit(1);
  }

  while (fscanf(fp, "%s", item) != EOF)
  {
    insert_node(&head, item);
    count = count + 1;

    /*
    if(count == 1)
    {
      strcat(url, item);
      curl_easy(curl, url);
    }
    */
  }

  fclose(fp);

  //display(head);

  printf("count: %d\n", count);

//  curl_easy(curl, "https://www.microsoft.com");
  curl_multi(cm, head);

  return 0;
}

//gcc -Wall -o build/main7 src/main.c -lcurl -I~/source-code/curl/include
