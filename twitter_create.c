#include <stdio.h>
#include <string.h>
#include "twitter_create.h"
#include <stdlib.h>

// function to create a Twitter system, creat users and initialise users and tweets
void create_twitter_system(twitter * twitter_system){
    int num;
    twitter_system->users = NULL; // user pointer points to null at the start
    twitter_system ->count_user =0; // assume that there's no user in the system
    printf("Welcome to Twitter\n");
    printf("How many users do you want to create: ");
    scanf("%d", &num);
    while(num <=0 || num>MAX_USERS){
        scanf("%d",&num);
    }
    getchar(); // to store enter key pressed
    
    // for loop to create a specific number of users
    for (int i =0; i < num; i++){
    user *newuser = malloc(sizeof(user)); // malloc allocates memory for new user pointer
    if(newuser!=NULL){
        printf( "Enter your username: \n" );
        char name[USR_LENGHT];
        gets(name);
        // avoid user input empty string
        if(strlen(name)==0){
            printf("Invalid username.\n");
            printf("Please re-enter:\n");
            gets(name);
        }
        strcpy(newuser->username,name);
        newuser->num_followers=0; // assume user doesn't have any followers at the start
        newuser->num_following=0; // assume user doesn't follow any other users at the start
        twitter_system ->count_user +=1; // increment number of users in the system
        newuser->next_user = twitter_system->users; // insert the new user to the start of the linked list, so it is pointing to the previous user created
        twitter_system->users = newuser; // update the user pointer in the system to always point to the newuser created
        twitter_system->count_tweet = 0; // assume that there's no tweets in the system at the start
        twitter_system->tweets = NULL; // assume the tweet's pointer points to null at the start
    }
    else{
        printf("No more memory available.\n");
        return;
    }

    }

}

