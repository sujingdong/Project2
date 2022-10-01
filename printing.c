#include <stdio.h>
#include <string.h>
#include "twitter_create.h"
#include "functionality.h"
#include "printing.h"
#include <stdbool.h>
// function to display all user created
void printUsers(twitter * twitter_system){
    user *currentPtr = twitter_system->users;
    printf("Here is a list of users created:\n");
    printf("\n");
    while(currentPtr!=NULL){
        printf("Username: %s\n",currentPtr->username);
        printf("Number of followings: %d\n", currentPtr->num_following);
        printf("Number of followers: %d\n",currentPtr->num_followers);
        printf("\n");
        currentPtr = currentPtr->next_user;
    }
}

// function to display most recent 10 tweets posted by current user and users they follow
void getNewsfeed (user *currUser, twitter *twitter_system)
{
    tweet *startTweetPtr = twitter_system->tweets; // points to head node of tweet
    tweet *currentTweetPtr = startTweetPtr; // points to the start
    int limit = 10; // max length of recent tweet to be printed
    printf("Here is your 10 most recent feeds:\n");
    printf("\n");
    
    // if current user has not following anyone, only prints current user's tweets
    if(currUser->num_following == 0){
        while(currentTweetPtr!=NULL){
            if(strcmp(currUser->username,currentTweetPtr->user)==0){
                printf("ID: %d \n",currentTweetPtr->id);
                printf("User: %s\n", currentTweetPtr->user);
                printf("Tweet: %s\n",currentTweetPtr->msg);
                printf("\n");
            }
            currentTweetPtr = currentTweetPtr->next_tweet;
        }
    }
    // else iterate through tweets linked list, print most recent 10 tweets posted by current user and their followees
    else {
        int i = 0; // count how many tweets have been printed
        currentTweetPtr = startTweetPtr;
        while(currentTweetPtr!=NULL && i<limit){
            if(strcmp(currUser->username,currentTweetPtr->user)==0 || checkFollowingTweet(currUser,currentTweetPtr)==true){
                printf("ID: %d\n",currentTweetPtr->id);
                printf("User: %s\n", currentTweetPtr->user);
                printf("Tweet: %s\n",currentTweetPtr->msg);
                printf("\n");
                i++;
            }
            currentTweetPtr = currentTweetPtr->next_tweet;
        }
    }
}

// display instructions to user
void instructions(){
    printf("Please select from one of the following options:\n");
    printf("--------------------------------------------------------\n");
    printf("|  0: End Twitter System(Exit the program)             |\n");
    printf("|  1: Post Tweet                                       |\n");
    printf("|  2: Get Newest Feeds                                 |\n");
    printf("|  3: Follow a user                                    |\n");
    printf("|  4: Unfollow a user                                  |\n");
    printf("|  5: Delete your account                              |\n");
    printf("|  6: End Turn(move on to next user)                   |\n");
    printf("--------------------------------------------------------\n");
}