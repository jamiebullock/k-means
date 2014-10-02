//
//  km_local.c
//  k-means
//
//  Created by Jamie Bullock on 29/08/2014.
//  Copyright (c) 2014 Jamie Bullock. All rights reserved.
//

#include "km_local.h"
#include "km_pointlist.h"
#include "km_error.h"
#include "km_textfile.h"
#include "km_point.h"

#include <string.h>
#include <stdio.h>
#include <stdint.h>

/* Utility functions */
uint32_t count_digits(uint32_t num)
{
    uint32_t digits = 1;
    
    while (num > 9)
    {
        num /= 10;
        digits++;
    }
    return digits;
}


km_error km_textfile_write_cluster_names(km_textfile outfile, km_pointlist pointlist)
{
    for (km_pointlist_index index = 0; index < km_pointlist_num_points(pointlist); ++index)
    {
        km_point point = km_pointlist_point_at_index(pointlist, index);
        size_t id_buffer_size = count_digits(point->id) + 1;
        char id_buffer[id_buffer_size];
        snprintf(id_buffer, id_buffer_size, "%u", point->id);
        
        RETURN_ON_ERROR(km_textfile_write_line(outfile, id_buffer, id_buffer_size));
    }
    return km_NoError;
}


