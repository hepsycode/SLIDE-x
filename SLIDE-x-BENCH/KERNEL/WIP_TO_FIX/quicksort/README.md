Questa versione del quicksort ha problemi durante l'esecuzione con l'8051. 
Per farla funzionare bisogna abbassare la size (ssize) dello stack interno:

enum{ssize = 15};
TARGET_INDEX stack[ssize];
