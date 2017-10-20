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

Boolean processPayment(VmSystem * system, Stock * item);
Boolean processChange(VmSystem * system, int due);

Boolean denocmpint (int value);
int denotoint(Denomination dom);
Denomination inttodeno(int value);
Boolean isCoin(int value);

void parseCoinLine(VmSystem * system, char * line);
Price strtoprice (char * str);
void initCoin(Coin * coin);
void addCoins(VmSystem * system, Coin * given);

#endif
