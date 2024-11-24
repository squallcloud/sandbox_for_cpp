export module ex;

#define DEFINE_EXPORT_EX(_name_) export namespace _name_ { void Exec(); }
#include "ex.h"
#undef DEFINE_EXPORT_EX