#include "vm_stock.h"

/**
* vm_stock.c this is the file where you will implement the
* interface functions for managing the stock list.
**/

/**
* Some example functions:
* create list, free list, create node, free node, insert node, etc...
*/

Boolean createList(VmSystem * system)
{
  system->itemList = (List *)malloc(sizeof(List));

  if(system->itemList == NULL)
  return FALSE;

  system->itemList->head = NULL;
  system->itemList->size = 0;

  return TRUE;
}

void freeList(VmSystem * system)
{
  Node * prev;
  Node * curr;

  curr = system->itemList->head;

  while(curr != NULL)
  {
    prev = curr;
    curr = curr->next;
    freeStock(prev->data);
    freeNode(prev);
  }

  free(system->itemList);

}



Node * createNode(Stock * data)
{
  Node * new = (Node *)malloc(sizeof(Node));
  new->data = data;
  return new;
}

void freeNode(Node * node)
{
  free(node);
}

void insertNode(List * list, Node * new)
{
  new->next = list->head;
  list->head = new;
  list->size++;
}

void removeNode(List * list, int index)
{

  Node * prev;
  Node * curr;
  Node * next;

  curr = list->head;
  next = curr->next;

  if(index == 0)
  {
    list->head = next;
    freeNode(curr);
  }
  else
  {
    int i;
    i = 0;
    while(i != index)
    {
      prev = curr;
      curr = next;
      next = curr->next;
    }

    prev->next = next;
    freeNode(curr);
  }

}

Stock * createStock(char * stockString)
{
  char * price;
  Stock * newStock = (Stock *)malloc(sizeof(Stock));

  /* ID */
  strcpy(newStock->id, strtok(stockString, STOCK_DELIM));
  /* Name */
  strcpy(newStock->name, strtok(NULL, STOCK_DELIM));
  /* Desc */
  strcpy(newStock->desc, strtok(NULL, STOCK_DELIM));
  /* Price */
  price = strtok(NULL, STOCK_DELIM);
  /* On hand */
  newStock->onHand = atoi(strtok(NULL, STOCK_DELIM));

  newStock->price = strtoprice(price);

  return newStock;

}

void freeStock(Stock * stock)
{
  free(stock);
}

Stock * searchStock(List * list, char * id)
{
  Node * curr;

  curr = list->head;

  while(curr != NULL)
  {
    if(strcmp(curr->data->id, id) == 0)
    return curr->data;
    curr = curr->next;
  }

  return NULL;
}

Stock * getStock(VmSystem * system)
{

  char inputId[ID_LEN + EXTRA_SPACES];

  regex_t reg;
  int status;
  Boolean valid;

  Stock * stock;

  /* Get id */
  valid = FALSE;
  while(!valid)
  {
    /* Set captcha trap */
    valid = TRUE;

    /* Get user input */
    printf("Please enter the id of the item you wish to purchase:");
    fgets(inputId, ID_LEN + EXTRA_SPACES, stdin);

    /* Leave if null */
    if(inputId[0] == '\n')
    return NULL;

    /* Check if within acceptable length */
    if(inputId[strlen(inputId) -1] != '\n')
    {
      readRestOfLine();
      valid = FALSE;
      printf("\nPlease enter a valid ID\n");
    }
    else
    {

      inputId[strlen(inputId)-1] = '\0';

      /* Check if input is valid */
      status = regcomp(&reg, "I[0-9]{4}", REG_EXTENDED);
      if(status) exit(1);

      status = regexec(&reg, inputId, 0, NULL, 0);

      if(status)
      {
        printf("Invalid ID Format\n");
        valid = FALSE;
      }
      else
      {
        stock = searchStock(system->itemList, inputId);
        if(stock == NULL)
        {
          printf("No item by ID: %s\n", inputId);
          valid = FALSE;
        }
      }

      regfree(&reg);

    }

  }

  return stock;

}
