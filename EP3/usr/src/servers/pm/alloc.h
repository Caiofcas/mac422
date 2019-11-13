#define FIRST_FIT 1
#define WORST_FIT 0

typedef unsigned int phys_clicks;

extern phys_clicks alloc_mem_worst_fit(int clicks);
extern phys_clicks alloc_mem(int clicks);