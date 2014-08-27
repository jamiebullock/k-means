//
//  km_error.c
//  k-means
//
//  Created by Jamie Bullock on 26/08/2014.
//  Copyright (c) 2014 Jamie Bullock. All rights reserved.
//

#include "km_error.h"

#include <stdio.h>
#include <stdlib.h>

const char *km_error_to_string(km_error error)
{
    switch (error)
    {
        case km_NoError:
            return "no error";
        case km_FileReadError:
            return "file read error";
        case km_FileCloseError:
            return "file close error";
        case km_FileSeekError:
            return "file seek error";
        case km_FileTellError:
            return "file tell error";
        case km_FileEndError:
            return "file end error";
        case km_UnspecifiedError:
            return "unspecified error";
        case km_MemoryAllocationError:
            return "memory allocation error";
        case km_IndexOutOfBoundsError:
            return "index out of bounds error";
        default:
            fprintf(stderr, "an unhandled error was generated");
            abort();
    }
    return "";
}