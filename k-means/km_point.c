//
//  km_point.c
//  k-means
//
//  Created by Jamie Bullock on 29/08/2014.
//  Copyright (c) 2014 Jamie Bullock. All rights reserved.
//

#include "km_point.h"
#include "km_error.h"

km_error km_point_init(km_point point, uint32_t id, float x, float y, float distance)
{
    point->id = id;
    point->x = x;
    point->y = y;
    point->distance = distance;
    
    return km_NoError;
}

