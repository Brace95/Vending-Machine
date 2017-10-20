#include "vm_options.h"

/**
* vm_options.c this is where you need to implement the system handling
* functions (e.g., init, free, load, save) and the main options for
* your program. You may however have some of the actual work done
* in functions defined elsewhere.
**/

/**
* Initialise the system to a known safe state. Look at the structure
* defined in vm_system.h.
**/
Boolean systemInit(VmSystem * system)
{
  createList(system);
  return TRUE;
}

/**
* Free all memory that has been allocated. If you are struggling to
* find all your memory leaks, compile your program with the -g flag
* and run it through valgrind.
**/
void systemFree(VmSystem * system)
{
  freeList(system);
}

/**
* Loads the stock and coin data into the system. You will also need to assign
* the char pointers to the stock and coin file names in the system here so
* that the same files will be used for saving. A key part of this function is
* validation. A substantial number of marks are allocated to this function.
**/
Boolean loadData(
  VmSystem * system, const char * stockFileName, const char * coinsFileName)
  {
    printf("\t Loading Stock...\n");
    if(!loadStock(system, stockFileName))
    return FALSE;

    printf("\t Loading Coins...\n");
    if(!loadCoins(system, coinsFileName))
    return FALSE;

    return TRUE;
  }

  /**
  * Loads the stock file data into the system.
  **/
  Boolean loadStock(VmSystem * system, const char * fileName)
  {
    FILE * fp;
    Node * newNode;
    Stock * newStock;
    char buff[STOCK_MAX_LINE];

    system->stockFileName = fileName;

    /* Open file */
    fp = fopen(fileName, "r");

    if(fp == NULL)
      return FALSE;

    while(fgets(buff, STOCK_MAX_LINE, fp))
    {
      /* Remove extra chars */
      if(buff[0] == '\n')
        continue;
        
      buff[strlen(buff)-1] = '\0';

      if(!checkLineStock(buff))
      {
        fclose(fp);
        return FALSE;
      }

      newStock = createStock(buff);
      newNode = createNode(newStock);
      insertNode(system->itemList, newNode);

    }
    fclose(fp);
    return TRUE;
  }

  /**
  * Loads the coin file data into the system.
  **/
  Boolean loadCoins(VmSystem * system, const char * fileName)
  {
    FILE * fp;
    char buff[COIN_MAX_LINE];

    system->coinFileName = fileName;

    /* Open file */
    fp = fopen(fileName, "r");

    if(fp == NULL)
      return FALSE;

    while(fgets(buff, COIN_MAX_LINE, fp))
    {
      if(buff[0] == '\n')
        continue;

      /* Remove extra chars */
      buff[strlen(buff)-1] = '\0';

      if(!checkLineCoin(buff))
      {
        fclose(fp);
        return FALSE;
      }

      parseCoinLine(system, buff);

    }

    fclose(fp);
    return TRUE;
  }

  /**
  * Saves all the stock back to the stock file.
  **/
  Boolean saveStock(VmSystem * system)
  {
    FILE * fp;
    Node * curr;
    Stock * stock;

    fp = fopen(system->stockFileName, "w");

    if(fp == NULL)
      return FALSE;

    curr = system->itemList->head;
    while(curr != NULL)
    {
      stock = curr->data;
      fprintf(fp, "%s|%s|%s|%u.%02u|%u\n",
      stock->id, stock->name, stock->desc,
      stock->price.dollars, stock->price.cents, stock->onHand);
      curr = curr->next;
    }

    fclose(fp);
    return TRUE;
  }

  /**
  * Saves all the coins back to the coins file.
  **/
  Boolean saveCoins(VmSystem * system)
  {
    FILE * fp;
    Denomination deno;

    fp = fopen(system->coinFileName, "w");

    if(fp == NULL)
      return FALSE;

    for(deno = FIVE_CENTS; deno <= TEN_DOLLARS; deno++)
      fprintf(fp, "%i,%i\n", denotoint(deno), system->cashRegister[deno].count);

    fclose(fp);
    return TRUE;
  }

  /**
  * This option allows the user to display the items in the system.
  * This is the data loaded into the linked list in the requirement 2.
  **/
  void displayItems(VmSystem * system)
  {
    Node * curr;
    Stock * data;
    int i;

    printf("\nItem Menu\n\n");
    printf("%-6s| %-40s| %-10s| %-7s\n", "ID", "Name", "Available", "Price");
    for(i = 0; i < MAX_WIDTH; i++)
    printf("-");
    printf("\n");

    curr = system->itemList->head;
    while(curr != NULL)
    {
      data = curr->data;
      printf("%-6s| %-40s| %-10u| $%3u.%02u\n",
      data->id, data->name, data->onHand,
      data->price.dollars, data->price.cents);
      curr = curr->next;
    }

  }

  /**
  * This option allows the user to purchase an item.
  * This function implements requirement 5 of the assignment specification.
  **/
  void purchaseItem(VmSystem * system)
  {

    Stock * stock;

    printf("\nPurchase Item\n");
    printf("----------------\n");

    stock = stockInteraction(system);

    if(!stock)
      return;

    printf("You have selected %s, %s. that will be %u.%02u\n",
    stock->name, stock->desc, stock->price.dollars, stock->price.cents);

    printf("Please hand over the money");
    printf("- type in the value of each note/coin in cents.\n");
    printf("Press enter on a new and empty line to cancel purchase:\n");

    if(processPayment(system, stock))
      stock->onHand--;

    printf("Please come back soon.\n");


  }

  /**
  * You must save all data to the data files that were provided on the command
  * line when the program loaded up, display goodbye and free the system.
  * This function implements requirement 6 of the assignment specification.
  **/
  void saveAndExit(VmSystem * system)
  {
    printf("\nSaving and Exiting\n");
    printf("----------------\n");

    printf("\t Saving Stock...\n");
    if(saveStock(system))
      printf("\tDone!\n");
    else
      printf("\tError Could not save!\n");

    printf("\t Saving Coins...\n");
    if(saveCoins(system))
      printf("\tDone!\n");
    else
      printf("\tError Could not save!\n");

    printf("Freeing memory..\n");
    systemFree(system);

    printf("\nAll done, Goodbye!\n");

  }

  /**
  * This option adds an item to the system. This function implements
  * requirement 7 of of assignment specification.
  **/
  void addItem(VmSystem * system)
  { }

  /**
  * Remove an item from the system, including free'ing its memory.
  * This function implements requirement 8 of the assignment specification.
  **/
  void removeItem(VmSystem * system)
  {

    Stock * stock;

    printf("\nDelete Item\n");
    printf("----------------\n");

    stock = stockInteraction(system);

    printf("Removing item with id %s...", stock->id);
    removeStock(system->itemList, stock);
    printf("Deleted!\n");

  }

  /**
  * This option will require you to display the coins from lowest to highest
  * value and the counts of coins should be correctly aligned.
  * This function implements part 4 of requirement 18 in the assignment
  * specifications.
  **/
  void displayCoins(VmSystem * system)
  {
    Denomination deno;
    int i;

    printf("\nDenomination | Count\n");
    for(i = 0; i < 20; i++)
      printf("-");
    printf("\n");

    for(deno = FIVE_CENTS; deno <= TEN_DOLLARS; deno++)
    {
      if(deno >= FIVE_CENTS && deno < ONE_DOLLAR)
        printf("%2i %-9s | %i\n",
        denotoint(deno), "Cents", system->cashRegister[deno].count);
      else
      printf("%2i %-9s | %i\n",
      denotoint(deno)/100, "Dollars", system->cashRegister[deno].count);
    }

  }

  /**
  * This option will require you to iterate over every stock in the
  * list and set its onHand count to the default value specified in
  * the startup code.
  * This function implements requirement 9 of the assignment specification.
  **/
  void resetStock(VmSystem * system)
  {
    printf("\nResetting Stock Counts...\n");
    defaultStock(system->itemList);
    printf("Done!\n");
  }

  /**
  * This option will require you to iterate over every coin in the coin
  * list and set its 'count' to the default value specified in the
  * startup code.
  * This requirement implements part 3 of requirement 18 in the
  * assignment specifications.
  **/
  void resetCoins(VmSystem * system)
  {
    printf("\nResetting Coin Counts...\n");
    defaultCoin(system);
    printf("Done!\n");
  }

  /**
  * This option will require you to display goodbye and free the system.
  * This function implements requirement 10 of the assignment specification.
  **/
  void abortProgram(VmSystem * system)
  {
    printf("\nABORTING!\n");
    freeList(system);
  }
