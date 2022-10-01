//
// Created by Lili on 30/03/2022.
//

#ifndef PROJECT2_TWITTER_CREATE_H
#define PROJECT2_TWITTER_CREATE_H

#endif //PROJECT2_TWITTER_CREATE_H

#define TWEET_LENGTH 270
#define USR_LENGHT 100
#define MAX_FOLLOWERS 30
#define MAX_FOLLOWING 30
#define MAX_TWEETS 100
#define MAX_USERS 100

typedef struct tweet{
    int id;
    char msg[TWEET_LENGTH];
    char user[USR_LENGHT];
    struct tweet *next_tweet;
}tweet;

typedef struct user{
    char username[USR_LENGHT];
    char followers[MAX_FOLLOWERS][USR_LENGHT];
    int num_followers;
    char following[MAX_FOLLOWING][USR_LENGHT];
    int num_following;
    struct user *next_user;
}user;

typedef struct twitter{
    int count_user;
    int count_tweet;
    user *users;
    tweet *tweets;
} twitter;

void create_twitter_system(twitter * twitter_system);