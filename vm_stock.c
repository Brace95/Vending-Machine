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
  /* LATER!!! */
  price = strtok(NULL, STOCK_DELIM);
  /* On hand */
  newStock->onHand = atoi(strtok(NULL, STOCK_DELIM));

  return newStock;

}

void freeStock(Stock * stock)
{
  free(stock);
}
