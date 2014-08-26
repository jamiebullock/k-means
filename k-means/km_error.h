//
//  km_error.h
//  k-means
//
//  Created by Jamie Bullock on 24/08/2014.
//  Copyright (c) 2014 Jamie Bullock. All rights reserved.
//

typedef enum km_error_
{
    km_NoError,
    km_FileReadError,
    km_FileCloseError,
    km_FileSeekError,
    km_FileTellError,
    km_FileEndError,
    km_MemoryAllocationError,
    km_UnspecifiedError
}
km_error;

const char *km_error_to_string(km_error error);