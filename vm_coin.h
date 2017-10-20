#ifndef VM_COIN_H
#define VM_COIN_H

#include "vm_system.h"

/**
 * The default coin level used when resetting values.
 **/
#define DEFAULT_COIN_COUNT 20
#define INT_PRICE_LEN 4

#define COIN_DELIM ","
#define PRICE_DELIM "."

void processPayment(VmSystem * system, Stock * item);
void processChange(VmSystem * system, int due);

Boolean denocmpint (int value);
int denotoint(Denomination dom);
Denomination inttodeno(int value);

void parseCoinLine(VmSystem * system, char * line);
Price strtoprice (char * str);

#endif
