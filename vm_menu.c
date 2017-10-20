#include "vm_menu.h"

/**
 * vm_menu.c handles the initialisation and management of the menu array.
 **/

/**
 * In this function you need to initialise the array of menu items
 * according to the text to be displayed for the menu. This array is
 * an array of MenuItem with text and a pointer to the function
 * that will be called.
 **/
void initMenu(MenuItem * menu)
{

  strcpy(menu[0].text, "Display Item");
  menu[0].function = &displayItems;

  strcpy(menu[1].text, "Purchase Item");
  menu[1].function = &purchaseItem;

  strcpy(menu[2].text, "Save and Exit");
  menu[2].function = &saveAndExit;

  strcpy(menu[3].text, "Add Item");
  menu[3].function = &addItem;

  strcpy(menu[4].text, "Remove Item");
  menu[4].function = &removeItem;

  strcpy(menu[5].text, "Display Coins");
  menu[5].function = &displayCoins;

  strcpy(menu[6].text, "Reset Stock");
  menu[6].function = &resetStock;

  strcpy(menu[7].text, "Reset Coins");
  menu[7].function = &resetCoins;

  strcpy(menu[8].text, "Abort Program");
  menu[8].function = &abortProgram;

}

/**
 * Gets input from the user and returns a pointer to the MenuFunction
 * that defines how to perform the user's selection. NULL is returned
 * if an invalid option is entered.
 **/
MenuFunction getMenuChoice(MenuItem * menu)
{
    char input[OPT_LEN + EXTRA_SPACES];
    int opt;

    fgets(input, OPT_LEN + EXTRA_SPACES, stdin);

    if(input[strlen(input)-1] != '\n')
    {
      readRestOfLine();
      return NULL;
    }

    if(isdigit(input[0]))
    {
      opt = atoi(input);
      if (opt > 0 && opt <= MENU_SIZE)
      {
        return menu[opt - 1].function;
      }

    }
    return NULL;
}

void displayMenu(MenuItem * menu)
{
  int i;

  printf("\n\nMain Menu:\n");
  for(i = 0; i < MAIN_LEN; i++)
    printf("%i. %s\n", i+1, menu[i].text);

  printf("Administrator-Only Menu:\n");
  for(i = ADMIN_START; i < MENU_SIZE; i++)
    printf("%i. %s\n", i+1, menu[i].text);

  printf("Select your option (1-9): ");
}
