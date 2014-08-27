//
//  km_textfile.c
//  k-means
//
//  Created by Jamie Bullock on 24/08/2014.
//  Copyright (c) 2014 Jamie Bullock. All rights reserved.
//

#include "km_textfile.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <sys/stat.h>

struct km_textfile_
{
    FILE *fp;
    uint64_t num_lines;
    uint64_t num_bytes;
};

km_error km_textfile_seek_(km_textfile textfile, int64_t offset)
{
    if (offset > textfile->num_bytes)
    {
        return km_FileSeekError;
    }
    
    clearerr(textfile->fp);
    int error = 0;
    
#ifdef _WIN32
    error = _fseeki64(textfile->fp, offset, SEEK_SET);
#else
    error = fseeko(textfile->fp, offset, SEEK_SET);
#endif
    
    if (error != 0)
    {
        perror("error");
        return km_FileSeekError;
    }

    return km_NoError;
}

km_error km_textfile_tell_(km_textfile textfile, uint64_t *offset)
{
    int64_t offset_ = 0L;
    
#ifdef _WIN32
    offset_ = _ftelli64(textfile->fp);
#else
    offset_ = ftello(textfile->fp);
#endif
    
    if (offset_ == -1)
    {
        perror("error");
        return km_FileTellError;
    }
    
    *offset = offset_;
    return km_NoError;
}

km_textfile km_textfile_new(void)
{
    return malloc(sizeof(struct km_textfile_));
}

void km_textfile_delete(km_textfile textfile)
{
    km_error error = km_NoError;
    
    if (textfile->fp != NULL)
    {
        if (fclose(textfile->fp) != 0)
        {
            perror("error");
            error = km_FileCloseError;
        }
    }
    free(textfile);
}

km_error km_textfile_init(km_textfile textfile)
{
    textfile->fp = NULL;
    textfile->num_lines = 0L;
    textfile->num_bytes = 0L;
    return km_NoError;
}

km_error km_textfile_read(km_textfile textfile, const char *path)
{
    textfile->fp = fopen(path, "r");
    
    if (textfile->fp == NULL)
    {
        perror("error");
        return km_FileReadError;
    }
    
    int fd = fileno(textfile->fp); // According to the man page this "shouldn't fail"
    struct stat data;
    int rv = fstat(fd, &data);
    
    if (rv != 0) {
        perror("error");
        return km_FileReadError;
    }
    
    textfile->num_bytes = data.st_size;
    
    char c = 0;
    
    do
    {
        c = getc(textfile->fp);
        if(c == '\n')
        {
            ++textfile->num_lines;
        }
    }
    while (c != EOF);
    
    km_textfile_seek_(textfile, 0);
    
    return km_NoError;
}

km_error km_textfile_next_line(km_textfile textfile, char **line)
{
    uint64_t initial_offset = 0;
    km_error error = km_textfile_tell_(textfile, &initial_offset);
    
    if (error != km_NoError)
    {
        return error;
    }
    
    if (feof(textfile->fp) || getc(textfile->fp) == EOF)
    {
        return km_FileEndError;
    }
    
    error = km_textfile_seek_(textfile, initial_offset); // reset after initial getc() call
    
    if (error != km_NoError)
    {
        return error;
    }
   
    int c = 0;
    
    do
    {
        c = getc(textfile->fp);
    }
    while (c != '\n' && c != EOF);
    
    uint64_t new_offset = 0;
    error = km_textfile_tell_(textfile, &new_offset);
    
    if (error != km_NoError)
    {
        return error;
    }
    
    uint64_t line_length = new_offset - initial_offset; // includes '\n' or EOF
    
    if (line_length != (int32_t)line_length)
    {
        fprintf(stderr, "error: line length was %llu, which is too long to read\n", line_length);
        return km_UnspecifiedError;
    }
    
    error = km_textfile_seek_(textfile, initial_offset);
    
    if (error != km_NoError)
    {
        return error;
    }
    
    ++line_length; // add 1 char for '\0'
    *line = malloc(line_length);
    char *line_ = *line;
    
    if (line_ == NULL)
    {
        perror("error");
        return km_MemoryAllocationError;
    }
    
    char *rv = fgets(line_, (int32_t)line_length, textfile->fp); // leave line_length as is because fgets() reads "at most one less than the number of characters specified by size"
    line_[strcspn(line_, "\n")] = '\0'; // Replace newline with '\0'
    
    if (rv == NULL)
    {
        if (ferror(textfile->fp))
        {
            line_ = NULL; // "If an error occurs, they return NULL and the buffer contents are indeterminate" so we don't free *line
            return km_FileReadError;
        }
        assert(!feof(textfile->fp)); // The way this function is designed reading past EOF should be impossible
    }
    
    return km_NoError;
}

uint64_t km_textfile_num_lines(km_textfile textfile)
{
    return textfile->num_lines;
}

