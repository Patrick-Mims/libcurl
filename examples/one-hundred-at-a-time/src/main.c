#include <curl/curl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 50
#define NUM_URLS

#define INTERFACE(x) ((x) == (0) ? CURL : CURLM)

struct node
{
  char url[SIZE];
  struct node *next;
};

struct queue
{
  CURL *curl_obj;
  char url[SIZE];
  int count;
  struct queue *next;
};

void curl_multi(CURL *single_http, CURLM *multi_http, CURLMcode mc, struct node *list)
{
  FILE *file_error = fopen("DumpItOut", "wb");
  int running = 1;
  struct node *m = NULL;

  m = list;
  m = m->next;

  printf("TOP OF THE STACK: %s\n", m->url);

  curl_easy_setopt(single_http, CURLOPT_URL, m->url); // pass the struct->url
  curl_easy_setopt(single_http, CURLOPT_STDERR, file_error);
  curl_easy_setopt(single_http, CURLOPT_VERBOSE, 1L);
  curl_easy_setopt(single_http, CURLOPT_HEADER, 1L);
  curl_easy_setopt(single_http, CURLOPT_FOLLOWLOCATION, m->url);
  // curl_easy_setopt(single_http, CURLOPT_WRITEFUNCTION, write_callback);

  // curl_easy_perform(single_http);

  /* add individual transfers */
  curl_multi_add_handle(multi_http, single_http);

  /*
   * Do work here
   * */
  do
  {
    mc = curl_multi_perform(multi_http, &running);
  } while (running);

  /* cleanup */
  curl_multi_remove_handle(multi_http, single_http);

  curl_easy_cleanup(single_http);
  curl_multi_cleanup(multi_http);
  curl_global_cleanup();

  printf("BOTTOM OF THE STACK: %s\n", m->url);

  /*
  int i = 1; // this is temporary, fix buffer overflow later :(

  for(m = list; i < 2; m = m->next)
  {
    printf("going here->%d. %s\n",i, m->url);

       curl_easy_setopt(single_http, CURLOPT_VERBOSE, 1L);
       curl_easy_setopt(single_http, CURLOPT_HEADER, 1L);
       curl_easy_setopt(single_http, CURLOPT_FOLLOWLOCATION, m->url);
       curl_easy_setopt(single_http, CURLOPT_WRITEFUNCTION, write_callback);

       curl_easy_perform(single_http);
    i = i + 1;
  }
  */
}

void curl_easy(CURL *easy, const char *str)
{
  char buffer[1024];
  if (easy == NULL)
  {
    printf("something is wrong with curl_easy()\n");
    exit(EXIT_FAILURE);
  }

  printf("URL: %s\n", str);

  curl_easy_setopt(easy, CURLOPT_URL, str);
  curl_easy_setopt(easy, CURLOPT_FOLLOWLOCATION, 1L);

  if ((curl_easy_perform(easy)) == CURLE_OK)
  {
    size_t len = strlen(buffer);

    if (len)
      fprintf(stderr, "%s%s", buffer, ((buffer[len - 1] != '\n') ? "\n" : ""));

    printf("SUCCESS!\n");
  }

  curl_easy_cleanup(easy);
}

void insert_node(struct node **list, char *item)
{
  /* create a new node */
  struct node *new_node = NULL;

  /* allocate memory for the new node. */
  if ((new_node = malloc(sizeof(struct node))) == NULL)
    exit(EXIT_FAILURE);

  /* store data in the node. */
  strncpy(new_node->url, item, sizeof(new_node->url) - 1);

  /* insert node into the list. */
  new_node->next = *list;
  *list = new_node;
}

void insert_curl_handle(struct queue **curl_list, CURL *handle, char *company)
{
  static curl_count = 0;
  struct queue *c = NULL;

  if ((c = malloc(sizeof(struct queue))) == NULL)
  {
    exit(EXIT_FAILURE);
  }

  strcpy((*c).url, company);
  (*c).count = curl_count;

  printf("curl_count -> %d -> %s\n", (*c).count, (*c).url);

  curl_count = curl_count + 1;

  c->curl_obj = handle;
  c->next = *curl_list;
  *curl_list = c;
}

/* Create a new curl object and pass it to curl_multi() */
CURL *create_curl_handle()
{
  CURL *new_handle = NULL;
  new_handle = curl_easy_init();

  return new_handle;
}

void display_curl_queue(struct queue *curl_list)
{
  struct queue *c = NULL;
  c = curl_list;
  printf("Total Number of Nodes: %d\n", c->count);
}

int main(int argc, char **argv)
{
  CURL *curl_handle = create_curl_handle();
  CURLM *multi_handle;
  CURLMcode multi_code = 0;
  // CURLcode *multi_clean;

  curl_global_init(CURL_GLOBAL_DEFAULT);

  // curl = curl_easy_init();
  /* this call must have a matching call to curl_multi_clean() */

  /* create a easy handle */
  // single_handle = curl_easy_init();

  /* init a multi stack */
  multi_handle = curl_multi_init();

  int count = 0;
  char item[SIZE];
  char url[SIZE];
  FILE *fp = NULL;

  strcpy(url, "https://");

  /* set head to point to the beginning of the list */
  struct node *head = NULL;
  struct queue *curl_head = NULL;

  /* initialize to the size of the (struct node) */
  if ((head = malloc(sizeof(struct node))) == NULL)
  {
    exit(EXIT_FAILURE);
  }

  if ((curl_head = malloc(sizeof(struct queue))) == NULL)
  {
    exit(EXIT_FAILURE);
  }

  if ((fp = fopen("companies.txt", "r")) == NULL)
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

  // display(head);

  printf("count: %d\n", count);

  /*
     curl_multi(single_handle, multi_handle, multi_code, head);
     curl_multi(insert_curl_node, multi_handle, multi_code, head);
  */

  /* insert new node into curl_queue */
  insert_curl_handle(&curl_head, curl_handle, "Apple");
  insert_curl_handle(&curl_head, curl_handle, "Cisco");
  insert_curl_handle(&curl_head, curl_handle, "Facebook");
  insert_curl_handle(&curl_head, curl_handle, "Google");
  insert_curl_handle(&curl_head, curl_handle, "Microsoft");

  display_curl_queue(curl_head);

  curl_multi_cleanup(multi_handle);

  return 0;
}

// gcc -Wall -o build/main7 src/main.c -lcurl -I~/source-code/curl/include
