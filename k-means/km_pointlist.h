//
//  km_pointlist.h
//  k-means
//
//  Created by Jamie Bullock on 29/08/2014.
//  Copyright (c) 2014 Jamie Bullock. All rights reserved.
//

#ifndef __k_means__km_pointlist__
#define __k_means__km_pointlist__

#include "km_error.h"
#include "km_point.h"
#include "km_textfile.h"

#include <stdint.h>

#ifdef __cplusplus
extern “C” {
#endif

typedef struct km_pointlist_ * km_pointlist;
typedef uint64_t km_pointlist_index;

km_pointlist km_pointlist_new(uint64_t num_points);
void km_pointlist_delete(km_pointlist pointlist);
km_error km_pointlist_fill(km_pointlist pointlist, km_textfile textfile);
uint64_t km_pointlist_num_points(km_pointlist pointlist);
km_error km_pointlist_update(km_pointlist pointlist, uint64_t index, uint32_t id, float x, float y);
km_point km_pointlist_point_at_index(km_pointlist pointlist, km_pointlist_index index);
km_point km_pointlist_point_with_id(km_pointlist pointlist, km_point_id id);
void km_pointlist_randomise(km_pointlist pointlist);
void km_pointlist_print_points(km_pointlist pointlist);


#ifdef __cplusplus
}
#endif
    
#endif /* defined(__k_means__km_pointlist__) */
