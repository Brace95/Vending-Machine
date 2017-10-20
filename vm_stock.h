#ifndef VM_STOCK_H
#define VM_STOCK_H

#include "vm_coin.h"

/**
 * The default stock level that all new stock should start with and the value
 * to use when restting stock.
 **/
#define DEFAULT_STOCK_LEVEL 20

#define STOCK_DELIM "|"

Boolean createList(VmSystem * system);
void freeList(VmSystem * system);

Node * createNode(Stock * data);
void freeNode(Node * node);
void insertNode(List * list, Node * new);

Stock * createStock(char * stockString);
void removeStock(List * list, Stock * stock);
void freeStock(Stock * stock);
Stock * searchStock(List * list, char * id);
Stock * stockInteraction(VmSystem * system);
void defaultStock(List * list);

#endif
