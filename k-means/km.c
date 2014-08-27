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

struct km_point_
{
    uint32_t id;
    float x;
    float y;
};

// 1. Read the data from file into N km_point structs
// 2. Compute the distance of each point from each of M cluster centres
// 3. Re-compute cluster centres
// 4. Repeat 2–3 until the total error is minimised
// 5. Write output points to file

km_point km_point_new(void)
{
    return malloc(sizeof(struct km_point_));
}


void km_point_delete(km_point point)
{
    free(point);
}

km_error km_point_init(km_point point, uint32_t id, float x, float y)
{
    point->id = id;
    point->x = x;
    point->y = y;
    
    return km_NoError;
}


km_pointlist km_pointlist_new(uint64_t num_points)
{
    return malloc(num_points * sizeof(struct km_point_ *));
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
        km_point point = km_point_new();
        km_point_init(point, 0, x, y);
        pointlist[count++] = point;
        line = NULL;
    }
    
    for (int i = 0; i < km_textfile_num_lines(textfile); ++i )
    {
        printf("%f, %f\n", pointlist->points[i].x, pointlist->points[i].y);
    }

    return error;
}

uint64_t km_pointlist_num_points(km_pointlist pointlist)
{
    return pointlist->num_points;
}

