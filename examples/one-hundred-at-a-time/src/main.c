#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 30

struct node
{
  char url[SIZE];
  struct node *next;
};

static void display(struct node *list)
{
  struct node *s = NULL;

  for(s = list; s != NULL; s = s->next)
  {
    printf("%s\n", s->url);
  }

}

struct node insert_node(struct node **list, char *item)
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
  }

  fclose(fp);

  display(head);

  return 0;
}
