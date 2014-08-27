//
//  k-means.c
//  k-means
//
//  Created by Jamie Bullock on 24/08/2014.
//  Copyright (c) 2014 Jamie Bullock. All rights reserved.
//

#include "km.h"

#include <stdio.h>
#include <stdlib.h>


struct km_pointlist_
{
    struct km_point_ *points;
    km_pointlist_index num_points;
};

km_error km_point_init(km_point point, uint32_t id, float x, float y, float distance)
{
    point->id = id;
    point->x = x;
    point->y = y;
    point->distance = distance;
    
    return km_NoError;
}


km_pointlist km_pointlist_new(uint64_t num_points)
{
    km_pointlist pointlist = malloc(sizeof(struct km_pointlist_));
    pointlist->num_points = num_points;
    pointlist->points = malloc(num_points * sizeof(struct km_point_));
    return pointlist;
}

void km_pointlist_delete(km_pointlist pointlist)
{
    free(pointlist->points);
    free(pointlist);
}

km_error km_pointlist_fill(km_pointlist pointlist, km_textfile textfile)
{
    float x = 0.f;
    float y = 0.f;
    
    char *line = NULL;
    km_error error = km_NoError;
    uint64_t count = 0L;
    
    while ((error = km_textfile_next_line(textfile, &line)) == km_NoError)
    {
        sscanf(line, "%g,%g", &x, &y);
        free(line);
        km_point_init(&pointlist->points[count++], 0, x, y, 0);
        line = NULL;
    }
    
    if (error == km_FileEndError) // Don't propogate km_FileEndError as we expect it
    {
        return km_NoError;
    }
    
    return error;
}

uint64_t km_pointlist_num_points(km_pointlist pointlist)
{
    return pointlist->num_points;
}

km_error km_pointlist_update(km_pointlist pointlist, uint64_t index, uint32_t id, float x, float y)
{
    if (index >= pointlist->num_points)
    {
        return km_IndexOutOfBoundsError;
    }
    pointlist->points[index].id = id;
    pointlist->points[index].x = x;
    pointlist->points[index].y = y;
    
    return km_NoError;
}

km_point km_pointlist_point_at_index(km_pointlist pointlist, km_pointlist_index index)
{
    return &pointlist->points[index];
}

