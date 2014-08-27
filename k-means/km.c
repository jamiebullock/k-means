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

struct km_pointlist_
{
    struct km_point_ *points;
    uint64_t num_points;
};

// 1. Read the data from file into N km_point structs
// 2. Compute the distance of each point from each of M cluster centres
// 3. Re-compute cluster centres
// 4. Repeat 2–3 until the total error is minimised
// 5. Write output points to file

km_error km_point_init(km_point point, uint32_t id, float x, float y)
{
    point->id = id;
    point->x = x;
    point->y = y;
    
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
        km_point_init(&pointlist->points[count++], 0, x, y);
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

