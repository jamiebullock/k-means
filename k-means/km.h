//
//  k-means.h
//  k-means
//
//  Created by Jamie Bullock on 24/08/2014.
//  Copyright (c) 2014 Jamie Bullock. All rights reserved.
//

#include "km_textfile.h"

#include <stdint.h>

typedef struct km_point_ *km_point;
typedef struct km_point_ **km_pointlist;

km_pointlist km_pointlist_new(uint64_t num_points);
km_error km_pointlist_fill(km_pointlist pointlist, km_textfile textfile);



