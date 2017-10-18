#include "vm_coin.h"

/**
 * Implement functions here for managing coins and the
 * "cash register" contained in the VmSystem struct.
 **/

/**
 * Some example functions:
 * init coins array, insert coin, change coin count for Denomination,
 * convert Denomination to coin value, deducting coins from register, etc...
 */












 Price strtoprice (char * str)
 {
   char * tok;
   Price new;

   tok = strtok(str, PRICE_DELIM);
   new.dollars = atoi(tok);

   tok = strtok(NULL, PRICE_DELIM);
   new.cents = atoi(tok);

   return new;
 }
