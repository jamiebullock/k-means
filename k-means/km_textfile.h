//
//  km_textfile.h
//  k-means
//
//  Created by Jamie Bullock on 24/08/2014.
//  Copyright (c) 2014 Jamie Bullock. All rights reserved.
//

#ifndef KM_TEXTFILE_H
#define KM_TEXTFILE_H

#include "km_error.h"

#include <stdint.h>

typedef struct km_textfile_ * km_textfile;

km_textfile km_textfile_new(void);
void km_textfile_delete(km_textfile textfile);
km_error km_textfile_init(km_textfile textfile);
km_error km_textfile_read(km_textfile textfile, const char *path);
km_error km_textfile_next_line(km_textfile textfile, char **line); // Advance to next file and return a pointer to it via return parameter, caller must free()
uint64_t km_textfile_num_lines(km_textfile textfile);

#endif // #ifndef KM_TEXTFILE_H
