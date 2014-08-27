//
//  km_error.h
//  k-means
//
//  Created by Jamie Bullock on 24/08/2014.
//  Copyright (c) 2014 Jamie Bullock. All rights reserved.
//

#ifndef KM_ERROR_H
#define KM_ERROR_H

typedef enum km_error_
{
    km_NoError,                 // 0
    km_FileReadError,           // 1
    km_FileCloseError,          // 2
    km_FileSeekError,           // 3
    km_FileTellError,           // 4
    km_FileEndError,            // 5
    km_MemoryAllocationError,   // 6
    km_IndexOutOfBoundsError,   // 7
    km_UnspecifiedError         // 8
}
km_error;

const char *km_error_to_string(km_error error);

#endif // #ifndef KM_ERROR_H
