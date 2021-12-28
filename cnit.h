#ifndef CNIT_H
#define CNIT_H

void cnit_trigger_breakpoint();

#define CNIT_ASSERT(x) do { if (!(x)) { cnit_trigger_breakpoint(); return __LINE__; } } while (0)

#endif //CNIT_H
