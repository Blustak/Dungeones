#ifndef DISPLAY_DRIVER_HEADER
#define DISPLAY_DRIVER_HEADER
#define DEFAULT_DRAWSTACK_CAP 8
#include <raylib.h>

typedef struct Position{
  int x;
  int y;
} position_t;

typedef struct EntityRectangle{
  position_t pos;
  struct Color color;
} entity_rectangle;

typedef enum DrawType{
  RECT
} draw_type_t;


typedef union Drawable{
  entity_rectangle v_rect;
} drawable_t;

typedef struct DrawStack{
  unsigned int count;
  unsigned int cap;
  drawable_t* data;
} draw_stack_t;

typedef struct DisplayDriver{
  draw_stack_t* stack;
} display_driver_t;


display_driver_t* NewDisplayDriver();
void FreeDisplayDriver(display_driver_t* display);
void* FlushDrawStack(display_driver_t* display);
void* PushToStack(display_driver_t* display, drawable_t* entity);
void* DrawEntity(drawable_t* data, draw_type_t type);

#endif /* ifndef DISPLAY_DRIVER_HEADER */
