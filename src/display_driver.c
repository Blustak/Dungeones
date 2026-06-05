#include "display_driver.h"
#include <raylib.h>
#include <stdlib.h>
#include <string.h>

draw_stack_t *newDrawStack(size_t capacity);
draw_stack_t *extendDrawStack(draw_stack_t *stack);
void freeDrawStack(draw_stack_t *stack);

void drawRect(draw_rect_t rect) {
  DrawRectangle(rect.start_pos.x, rect.start_pos.y, rect.width, rect.height,
                rect.color);
}

void drawLine(draw_line_t line) {
  DrawLine(line.start_pos.x, line.start_pos.y, line.end_pos.x, line.end_pos.y,
           line.color);
}

// allocate new display driver
display_driver_t *NewDisplayDriver() {
  display_driver_t *retVal =
      (display_driver_t *)malloc(sizeof(display_driver_t));
  if (retVal == NULL) {
    return NULL;
  }
  draw_stack_t *stack = newDrawStack((size_t)DEFAULT_DRAWSTACK_CAP);
  if (stack == NULL) {
    free((void *)retVal);
    return NULL;
  }
  retVal->stack = stack;
  return retVal;
}

void FreeDisplayDriver(display_driver_t *display) {
  freeDrawStack(display->stack);
  free(display);
}

// Draws the given object
void *DrawObject(drawable_t *obj, draw_type_t type) {
  switch (type) {
  case RECT:
    drawRect(obj->v_rect);
    break;
  case LINE:
    drawLine(obj->v_line);
    break;
  }
  return NULL;
}

void *FlushDrawStack(display_driver_t *display) {
  drawable_t* obj;
  draw_type_t type;
  void* err = NULL;
  if (display == NULL) {
    return NULL;
  }
  while (display->stack->count >= 0) {
    obj = (display->stack->data + display->stack->count);
    type = display->stack->type[display->stack->count];

    err = DrawObject(obj,type);

    if (err != NULL) {
      break; // Something wrong with draw loop; breakpoint
    }
    display->stack->count -= 1;
  }
  return NULL; // TODO Implement
}

void *PushToStack(display_driver_t *display, drawable_t *restrict entity,
                  draw_type_t type) {
  if (display->stack->count >= display->stack->cap) {
    draw_stack_t *extendedStack = extendDrawStack(display->stack);
    if (extendedStack == NULL) {
      return NULL;
    }

    freeDrawStack(display->stack);
    display->stack = extendedStack;
  }
  *(display->stack->data + display->stack->count) = *entity;
  *(display->stack->type + display->stack->count) = type;
  display->stack->count += 1;
  return (void *)display;
}

// allocate new drawStack
draw_stack_t *newDrawStack(size_t capacity) {
  draw_stack_t *stack = (draw_stack_t *)malloc(sizeof(draw_stack_t));
  if (stack == NULL) {
    return NULL;
  }

  stack->count = 0;
  stack->cap = capacity ? capacity > 0 : DEFAULT_DRAWSTACK_CAP;

  drawable_t *data = (drawable_t *)malloc(sizeof(drawable_t) * capacity);

  if (data == NULL) {
    free((void *)stack);
    return NULL;
  }

  draw_type_t *types = (draw_type_t *)malloc(sizeof(draw_type_t) * capacity);

  if (types == NULL) {
    free((void *)data);
    free((void *)stack);
    return NULL;
  }

  stack->data = data;
  stack->type = types;

  return stack;
}

// doubles stack capacity; returns NULL on failure.
draw_stack_t *extendDrawStack(draw_stack_t *stack) {
  if (stack == NULL) {
    return NULL;
  }
  unsigned int newCap = stack->cap * 2 ? stack->cap * 2 > 0 : 2;
  drawable_t *newData = (drawable_t *)malloc(sizeof(drawable_t) * newCap);
  if (newData == NULL) {
    return NULL; // Don't modify stack
  }
  draw_type_t *newType = (draw_type_t *)malloc(sizeof(draw_type_t) * newCap);
  if (newType == NULL) {
    free(newData);
    return NULL;
  }

  memcpy((void *)newData, (void *)stack->data,
         stack->count); // TODO check if null?
  memcpy((void *)newType, (void *)stack->type,
         stack->count); // TODO check if null?
  stack->cap = newCap;
  stack->data = newData;
  stack->type = newType;
  return stack;
}

void freeDrawStack(draw_stack_t *stack) {
  free((void *)stack->data);
  free((void *)stack->type);
  free((void *)stack);
}
