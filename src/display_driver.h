#ifndef DISPLAY_DRIVER_HEADER
#define DISPLAY_DRIVER_HEADER
#include <stddef.h>
#define DEFAULT_DRAWSTACK_CAP 8
#include <raylib.h>

typedef struct Position{
  int x;
  int y;
} position_t;

typedef struct DDDrawRect{
  position_t start_pos;
  unsigned int width;
  unsigned int height;
  struct Color color;
} draw_rect_t;

typedef struct DDDrawLine{
  position_t start_pos;
  position_t end_pos;
  struct Color color;
} draw_line_t;

typedef enum DrawType{
  RECT,
  LINE
} draw_type_t;


typedef union Drawable{
  draw_rect_t v_rect;
  draw_line_t v_line;
} drawable_t;

typedef struct DrawStack{
  int count;
  size_t cap;
  drawable_t* data;
  draw_type_t* type;
} draw_stack_t;

typedef struct DisplayDriver{
  draw_stack_t* stack;
} display_driver_t;


display_driver_t* NewDisplayDriver();
void FreeDisplayDriver(display_driver_t* display);
void* FlushDrawStack(display_driver_t* display);
void* PushToStack(display_driver_t* display, drawable_t* entity, draw_type_t type);
void* DrawObject(drawable_t* data, draw_type_t type);

#endif /* ifndef DISPLAY_DRIVER_HEADER */
