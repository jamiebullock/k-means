//
//  km_point.h
//  k-means
//
//  Created by Jamie Bullock on 29/08/2014.
//  Copyright (c) 2014 Jamie Bullock. All rights reserved.
//

#ifndef __k_means__km_point__
#define __k_means__km_point__

#include "km_error.h"

#include <stdint.h>

#ifdef __cplusplus
extern “C” {
#endif

typedef uint32_t km_point_id;

typedef struct km_point_
{
    km_point_id id;
    float distance;
    float x;
    float y;
}
* km_point;
    
km_error km_point_init(km_point point, uint32_t id, float x, float y, float distance);

#ifdef __cplusplus
}
#endif

#endif /* defined(__k_means__km_point__) */
