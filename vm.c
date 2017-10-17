#include "vm.h"

int main(int argc, char ** argv)
{
    VmSystem vm;
    MenuItem menu[MENU_SIZE];
    MenuFunction func;

    /* Check Arg length */
    if (argc != 3)
    {
      printf("USAGE: ./vm <stock.dat> <coin.dat>\n");
      return EXIT_FAILURE;
    }

    /* Init system */
    printf("Initialising System...\n");
    if(!systemInit(&vm))
    {
      printf("Cannot init system, aborting...\n");
      return EXIT_FAILURE;
    }

    printf("Loading Data...\n");
    if(!loadData(&vm, argv[1], argv[2]))
    {
      printf("Cannot load data, aborting...\n");
      return EXIT_FAILURE;
    }

    printf("Initialising Menu...\n");
    initMenu(menu);

    printf("----- Done -----\n");

    while(vm.itemList != NULL)
    {
      displayMenu(menu);
      func = getMenuChoice(menu);

      if(func != NULL)
        func(&vm);
      else
        printf("!!Invalid Options!!\n");
    }

    return EXIT_SUCCESS;
}
