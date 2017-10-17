#include "vm.h"

int main(int argc, char ** argv)
{

    char input[INPUT_LEN + EXTRA_SPACES];

    VmSystem vm;
    MenuItem menu[MENU_SIZE];

    /* Check Arg length */
    if (argc != 3)
    {
      printf("USAGE: ./vm <stock.dat> <coin.dat>\n");
      return EXIT_FAILURE;
    }

    /* Init system */
    if(!systemInit(&vm))
    {
      printf("Cannot init system, aborting...\n");
      return EXIT_FAILURE;
    }

    if(!loadData(&vm, argv[1], argv[2]))
    {
      printf("Cannot load data, aborting...\n");
      return EXIT_FAILURE;
    }

    initMenu(menu);

    return EXIT_SUCCESS;
}
