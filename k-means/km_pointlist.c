//
//  km_pointlist.c
//  k-means
//
//  Created by Jamie Bullock on 29/08/2014.
//  Copyright (c) 2014 Jamie Bullock. All rights reserved.
//

#include "km_pointlist.h"
#include "km_point.h"

#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

#ifdef _WIN32
#include "gettimeofday.c"
#else
#include <sys/time.h>
#endif

struct km_pointlist_
{
    uint32_t seed;
    struct km_point_ *points;
    km_pointlist_index num_points;
};

/* API implementation */

km_pointlist km_pointlist_new(uint64_t num_points)
{
    struct timeval time;
    gettimeofday(&time, NULL);
    
    km_pointlist pointlist = malloc(sizeof(struct km_pointlist_));
    pointlist->seed = (time.tv_sec + time.tv_usec) % UINT_MAX;
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
    
    while ((error = km_textfile_read_line(textfile, &line)) == km_NoError)
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

km_point km_pointlist_point_with_id(km_pointlist pointlist, km_point_id id)
{
    for (km_pointlist_index index = 0; index < pointlist->num_points; ++index)
    {
        if (pointlist->points[index].id == id)
        {
            return &pointlist->points[index];
        }
    }
    return NULL;
}

void km_pointlist_randomise(km_pointlist pointlist)
{
    for (uint8_t cluster_index = 0; cluster_index < pointlist->num_points; ++cluster_index)
    {
        float x = rand_r(&pointlist->seed) / (float)RAND_MAX * 10 - 5;
        float y = rand_r(&pointlist->seed) / (float)RAND_MAX * 10 - 5;
        km_pointlist_update(pointlist, cluster_index, cluster_index, x, y);
    }
    km_pointlist_print_points(pointlist);
}

void km_pointlist_print_points(km_pointlist pointlist)
{
    for (uint32_t point_num = 0; point_num < pointlist->num_points; ++point_num)
    {
        km_point point = &pointlist->points[point_num];
        printf("%d\t%u\t%f\t%f\t%f\n", point_num, point->id, point->x, point->y, point->distance);
    }
}
