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

void processPayment(VmSystem * system, Stock * item)
{
  int start;
  int owing;
  int value;

  char amountInput[INT_PRICE_LEN + EXTRA_SPACES];
  regex_t reg;
  int status;


  start = item->price.dollars * 100 + item->price.cents;
  owing = start;

  while(owing > 0)
  {
    printf("You still need to give us $%0.02f:", owing / 100.0);
    fgets(amountInput, INT_PRICE_LEN + EXTRA_SPACES, stdin);

    if(amountInput[strlen(amountInput) -1] != '\n')
    {
      readRestOfLine();
      printf("Please enter a valid input\n");
    }
    else
    {
      if(amountInput[0] == '\n')
      break;
      /* Check if input is valid */
      status = regcomp(&reg, "[0-9]{1,4}", REG_EXTENDED);
      if(status) exit(1);

      status = regexec(&reg, amountInput, 0, NULL, 0);

      if(status)
      printf("Invalid coin format\n");
      else
      {
        value = (int)atoi(amountInput);
        if((value))
        owing -= value;
        else
        printf("Invalid Denomination\n");
      }

    }

  }

  if(owing < 0)
  {
    printf("Change:\n");
    processChange(system, -owing);
  }
  else if (owing > 0)
  {
    printf("Refunding:\n");
    processChange(system, start-owing);
  }
  else
  printf("Thank you, here is you %s\n", item->name);
}

void processChange(VmSystem * system, int due)
{

  Denomination coin;
  int value;

  for(coin = TEN_DOLLARS; coin >= FIVE_CENTS; coin--)
  {
    value = denotoint(coin);
    if(due - value >= 0)
    {
      due -= value;
      coin++;
      printf("\t%0.02f\n", value / 100.0);
    }

    if(coin == FIVE_CENTS)
    break;
  }

}

Boolean denocmpint (int value)
{
  Denomination dom;
  int i;

  dom = FIVE_CENTS;

  for(i = 0; i < NUM_DENOMS; i++)
  {
    if(value == denotoint(dom))
    return TRUE;
    dom++;
  }
  return FALSE;
}

int denotoint(Denomination dom)
{
  switch(dom)
  {
    case FIVE_CENTS:
    return 5;
    case TEN_CENTS:
    return 10;
    case TWENTY_CENTS:
    return 20;
    case FIFTY_CENTS:
    return 50;
    case ONE_DOLLAR:
    return 100;
    case TWO_DOLLARS:
    return 200;
    case FIVE_DOLLARS:
    return 500;
    case TEN_DOLLARS:
    return 1000;
    default:
    return -1;
  }
}

Denomination inttodeno(int value)
{
  switch(value)
  {
    case 5:
    return FIVE_CENTS;
    case 10:
    return TEN_CENTS;
    case 20:
    return TWENTY_CENTS;
    case 50:
    return FIFTY_CENTS;
    case 100:
    return ONE_DOLLAR;
    case 200:
    return TWO_DOLLARS;
    case 500:
    return FIVE_DOLLARS;
    default:
    return TEN_DOLLARS;
  }
}

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

void parseCoinLine(VmSystem * system, char * line)
{
  Denomination deno;
  deno = inttodeno(atoi(strtok(line, COIN_DELIM)));
  system->cashRegister[deno].denom = deno;
  system->cashRegister[deno].count = atoi(strtok(NULL, COIN_DELIM));

}
