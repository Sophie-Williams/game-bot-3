#include <StandardCplusplus.h>
#include <functional-vlpp.h>
#include <functional-bot.h>
#include "build.gamefabricator.h"


uint16_t freeMemory();


static EventLoop eventloop;


static void buildMachine(GameFabricator &fabricator)
{
    fabricator.build4ButtonPanel();
    // fabricator.buildMockButtonPanel();
    // fabricator.buildPanelButtons();
    // fabricator.build4ButtonPanelViewer();
    fabricator.buildDisplayFreeMemory();
    // fabricator.buildDisplayAnimator();
}


void setup(void)
{
    Serial.begin(9600);

    GameFabricator fabricator;
    buildMachine(fabricator);
    eventloop = fabricator.getEventLoop();

    Serial.print("Free memory: ");
    Serial.println(freeMemory());

    Serial.println("Setup complete");
}


void loop(void)
{
    eventloop();
}














extern unsigned int __heap_start;
extern void *__brkval;

/*
 * The free list structure as maintained by the 
 * avr-libc memory allocation routines.
 */
struct __freelist {
  size_t sz;
  struct __freelist *nx;
};

/* The head of the free list structure */
extern struct __freelist *__flp;

/* Calculates the size of the free list */
uint16_t freeListSize() {
  struct __freelist* current;
  uint16_t total = 0;
  for (current = __flp; current; current = current->nx) {
    total += 2; /* Add two bytes for the memory block's header  */
    total += (uint16_t) current->sz;
  }
  return total;
}

uint16_t freeMemory() {
  uint16_t free_memory;
  if ((uint16_t)__brkval == 0) {
    free_memory = ((uint16_t)&free_memory) - ((uint16_t)&__heap_start);
  } else {
    free_memory = ((uint16_t)&free_memory) - ((uint16_t)__brkval);
    free_memory += freeListSize();
  }
  return free_memory;
}



// int freeListSize() {
//   struct __freelist* current;
//   int total = 0;
//   for (current = __flp; current; current = current->nx) {
//     total += 2; /* Add two bytes for the memory block's header  */
//     total += (int) current->sz;
//   }
//   return total;
// }

// uint16_t freeMemory() {
//   int free_memory;
//   if ((int)__brkval == 0) {
//     free_memory = ((int)&free_memory) - ((int)&__heap_start);
//   } else {
//     free_memory = ((int)&free_memory) - ((int)__brkval);
//     free_memory += freeListSize();
//   }
//   return free_memory;
// }
