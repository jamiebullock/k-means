//
//  km.h
//  km
//
//  Created by Jamie Bullock on 24/08/2014.
//  Copyright (c) 2014 Jamie Bullock. All rights reserved.
//

#ifndef KM_H
#define KM_H

#include "km_textfile.h"
#include "km_error.h"

#include <stdint.h>

#define RETURN_ON_ERROR(func) { km_error error__ = (func); if (error__ != km_NoError) return error__; }

typedef struct km_point_ * km_point;
typedef struct km_pointlist_ * km_pointlist;

km_pointlist km_pointlist_new(uint64_t num_points);
void km_pointlist_delete(km_pointlist pointlist);
km_error km_pointlist_fill(km_pointlist pointlist, km_textfile textfile);
uint64_t km_pointlist_num_points(km_pointlist pointlist);
km_error km_pointlist_update(km_pointlist pointlist, uint64_t index, uint32_t id, float x, float y);

#endif // #ifndef KM_H
