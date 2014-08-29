//
//  km_error.h
//  k-means
//
//  Created by Jamie Bullock on 24/08/2014.
//  Copyright (c) 2014 Jamie Bullock. All rights reserved.
//

#ifndef __k_means__km_error__
#define __k_means__km_error__

#define RETURN_ON_ERROR(func) { km_error error__ = (func); if (error__ != km_NoError) return error__; }

#ifdef __cplusplus
extern “C” {
#endif
    
typedef enum km_error_
{
    km_NoError,                 // 0
    km_FileReadError,           // 1
    km_FileCloseError,          // 2
    km_FileSeekError,           // 3
    km_FileTellError,           // 4
    km_FileEndError,            // 5
    km_FileWriteError,          // 6
    km_MemoryAllocationError,   // 7
    km_IndexOutOfBoundsError,   // 8
    km_UnspecifiedError         // 9
}
km_error;

const char *km_error_to_string(km_error error);

#ifdef __cplusplus
}
#endif

#endif /* defined(__k_means__km_error__) */
