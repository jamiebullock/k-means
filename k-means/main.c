//
//  main.c
//  k-means
//
//  Created by Jamie Bullock on 24/08/2014.
//  Copyright (c) 2014 Jamie Bullock. All rights reserved.
//

#include "km.h"

#include <stdio.h>

enum cluster_id {
    Adam,
    Bob,
    Charley,
    David,
    Edward,
    km_num_cluster_ids_
};

void set_initial_cluster_centroids(km_pointlist pointlist)
{
    km_pointlist_update(pointlist, 0, Adam, -0.357, -0.253);
    km_pointlist_update(pointlist, 1, Bob, -0.055, 4.392);
    km_pointlist_update(pointlist, 2, Charley, 2.674, -0.001);
    km_pointlist_update(pointlist, 3, David, 1.044, -1.251);
    km_pointlist_update(pointlist, 3, Edward, -1.495, -0.090);
}

int main(int argc, const char * argv[])
{

    km_textfile textfile = km_textfile_new();
    
    RETURN_ON_ERROR(km_textfile_init(textfile));
    RETURN_ON_ERROR(km_textfile_read(textfile, "input-2.csv"));
    
    km_pointlist pointlist = km_pointlist_new(km_textfile_num_lines(textfile));
    km_pointlist centroids = km_pointlist_new(km_num_cluster_ids_);
    
    RETURN_ON_ERROR(km_pointlist_fill(pointlist, textfile));
    
    set_initial_cluster_centroids(centroids);
        
    km_pointlist_delete(pointlist);
    km_textfile_delete(textfile);
        
    return 0;
}
