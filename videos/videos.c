/*
    + 1) Platform is a strcut Platform
    + 2) Creates with create function
    + 3) Destroy with destroy func, free all memory used
    + 4) Delete all viewings and videos with clear func. Also clears used memory
    + 5) Adding videos via add_video func that takes up to 100-length string title, duration in min. 
       Must return non-negative ID, -1 in case of error
    + 6) Video ID is used to add_view to add viewing for that video. Specifies number of minutes of watching.
       if number >= lenght of video, then viewing is full. Return 1 if success, 0 on errror (if ID doesn't exist)
    7) 

*/

#include "videos.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct video{
    unsigned int ID; // will be an address in the memory, since it is unique
    char title[100];
    unsigned int duration;

} VIDEO;

typedef struct platform {
    VIDEO ** videos;
    int count;
    int full_views;
    int view_minites;
} PLATFORM;


struct platform * create (){
    PLATFORM * temp = malloc(sizeof(PLATFORM));
    temp->videos = malloc(0 * sizeof(VIDEO));
    temp->count = 0;
    temp->full_views = 0;
    temp->view_minites = 0;
    return temp;
}

void destroy (struct platform * p){

    if(p == NULL){
        return;
    }

    free(p->videos);
    free(p);
}

void clear (struct platform * p){
    if(p == NULL){
        return;
    }

    size_t new_length = 0;
    VIDEO ** temp = realloc(p->videos, 0);
    if(temp == -1){
        return;
    }

    p->full_views = 0;
    p->view_minites = 0;
    p->videos = temp;
    p->count = 0;
}

int add_video (struct platform * p, const char * title, int minutes){

    VIDEO * new_video = malloc(sizeof(VIDEO));

    if(new_video == NULL){
        return -1;
    }

    new_video->ID = p->count;
    strcpy(new_video->title, title);
    new_video->duration = minutes;

    size_t new_length = p->count + 1;
    VIDEO ** temp = realloc(p->videos, new_length * sizeof(VIDEO*));

    if(temp == -1){
        return -1;
    }

    temp[new_length - 1] = new_video;
    p->videos = temp;
    p->count = new_length;

    return new_video->ID;
}

int add_view (struct platform * p, int video_id, int minutes){
    for(int i = 0; i < p->count; i++){
        if(p->videos[i]->ID == video_id){
            p->view_minites += minutes;
            if(p->videos[i]->duration <= minutes){
                p->full_views++;
            }
            return 1;
        }
    }

    return 0;
}

int total_view_minutes (struct platform * p){
    if(p == NULL){
        return -1;
    } else{
        return p->view_minites;
    }
    return 0;
}

int total_full_views (struct platform * p){
    if(p == NULL){
        return -1;
    } else{
        return p->full_views;
    }
    return 0;
}

int video_by_title (struct platform * p, const char * title){
    for(int i = 0; i < p->count; i++){
        if(strcmp(p->videos[i]->title, title) == 0){
            return p->videos[i]->ID;
        }
    }

    return -1;
}