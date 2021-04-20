#ifndef NEW_H
#define NEW_H


#include <stdint.h>

#include <stddef.h>

#include <stdbool.h>

#include "cg.h"



#ifdef __cplusplus
extern "C" {
#endif

typedef void ((*(runner_executeTypedef))(void *,myDataType ,myDataType *));
typedef void ((*(runner_updateTypedef))(void *,myDataType ));

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif
