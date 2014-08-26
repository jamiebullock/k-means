//
//  main.c
//  k-means
//
//  Created by Jamie Bullock on 24/08/2014.
//  Copyright (c) 2014 Jamie Bullock. All rights reserved.
//

#include "km.h"

#include <stdio.h>

#define RETURN_ON_ERROR(func) if ((func) != km_NoError) return 1;

int main(int argc, const char * argv[])
{

    km_textfile textfile = km_textfile_new();
    
    RETURN_ON_ERROR(km_textfile_init(textfile));
    RETURN_ON_ERROR(km_textfile_read(textfile, "input-2.csv"));
    
    km_pointlist pointlist = km_pointlist_new(km_textfile_num_lines(textfile));
    
    RETURN_ON_ERROR(km_pointlist_fill(pointlist, textfile));

        
    km_textfile_delete(textfile);
    
    
    return 0;
}
