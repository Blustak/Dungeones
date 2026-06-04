#include "display_driver.h"
#include <stdlib.h>
#include <string.h>

draw_stack_t* newDrawStack(unsigned int capacity);
draw_stack_t* extendDrawStack(draw_stack_t* stack);
void freeDrawStack(draw_stack_t* stack);

// allocate new display driver
display_driver_t* NewDisplayDriver() {
  display_driver_t* retVal = (display_driver_t*)malloc(sizeof(display_driver_t));
  if (retVal == NULL){
    return NULL;
  }
  draw_stack_t* stack = newDrawStack(DEFAULT_DRAWSTACK_CAP);
  if (stack == NULL) {
    free((void*) retVal);
    return NULL;
  }
  retVal->stack = stack;
  return retVal;
}

void FreeDisplayDriver(display_driver_t *display){
  freeDrawStack(display->stack);
  free(display);
}

void* DrawEntity(drawable_t* data, draw_type_t type) {
  drawable_t ent;
  drawable_t* entAddr = &ent;
  switch (type) {
    case RECT:
      *entAddr = (drawable_t){.v_rect = data->v_rect};

  }
}

void* FlushDrawStack(display_driver_t* display) {
  return NULL; //TODO Implement
}

void* PushToStack(display_driver_t* display, drawable_t* entity) {
  if (display->stack->count >= display->stack->cap) {
    draw_stack_t* extendedStack = extendDrawStack(display->stack);
    if (extendedStack == NULL) {
      return NULL;
    }

    freeDrawStack(display->stack);
    display->stack = extendedStack;
  }
  *(display->stack->data + display->stack->count) = *entity;
  display->stack->count += 1;
  return (void*)display;
}

// allocate new drawStack
draw_stack_t* newDrawStack(unsigned int capacity){
  draw_stack_t* stack = (draw_stack_t*)malloc(sizeof(draw_stack_t));
  if (stack == NULL) {
    return NULL;
  }

  stack->count = 0;
  stack->cap = capacity ? capacity > 0 : DEFAULT_DRAWSTACK_CAP;

  drawable_t* data = (drawable_t*)malloc(sizeof(drawable_t) * capacity);

  if (data == NULL) {
    free((void*)stack);
    return NULL;
  }

  return stack;
}

// doubles stack capacity; returns NULL on failure.
draw_stack_t* extendDrawStack(draw_stack_t* stack) {
  if (stack == NULL) {
    return NULL;
  }
  unsigned int newCap = stack->cap * 2 ? stack->cap * 2 > 0 : 2;
  drawable_t* newData = (drawable_t*)malloc(sizeof(drawable_t) * newCap);
  if (newData == NULL) {
    return NULL; // Don't modify stack
  }

  memcpy((void*)newData, (void*)stack->data, stack->count); // TODO check if null?
  stack->cap = newCap;
  stack->data = newData;
  return stack;
}

void freeDrawStack(draw_stack_t* stack) {
  free((void*) stack->data);
  free((void*)stack);
}
