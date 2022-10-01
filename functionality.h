#ifndef PROJECT2_FUNCTIONALITY_H
#define PROJECT2_FUNCTIONALITY_H

#endif //PROJECT2_FUNCTIONALITY_H
#include <stdbool.h>

user *findUser(twitter *twitter_system, char name[USR_LENGHT]);
void follow(user *currUser, twitter *twitter_system);
void unfollow(user * userPtr,twitter *twitter_system);
void delete (user * currUser, twitter *twitter_system);
void postTweet (user*currUser,twitter *twitter_system);
bool checkFollowingTweet(user *currUser, tweet * tweetPtr);
void endTwitter (twitter *twitter_system);
void endTurn(twitter *twitter_system);
void menu(twitter *twitter_system);