#include <stdio.h>
#include <string.h>
#include "twitter_create.h"
#include "printing.h"
#include "functionality.h"
#include <stdlib.h>
#include <stdbool.h>

// function to determine whether a user exists in the system or not
user *findUser(twitter *twitter_system, char name[USR_LENGHT]){
    user *currentPtr = twitter_system->users; // pointer points to the start of user linked list
    // loop through the linked list, if the username passed in is found, return the pointer pointing to that user struct
    while(currentPtr!=NULL){
        if(strcmp(currentPtr->username,name)==0){
            return currentPtr;
        }
        currentPtr = currentPtr->next_user;
    }

    return NULL; // return null if username was not found 
}

// function to avoid printing out username of users which current use is following
bool check (user* checkUser, user *currentUser){
    for(int i=0; i<currentUser->num_following; i++){
        if(strcmp(checkUser->username,currentUser->following[i])==0){
            return true;
        }
    }
    return false;

}

// function allows user to follow another existing user in the system, start with printing usernames that current user can follow
void follow(user *currUser, twitter *twitter_system)
{
    char followeeName[USR_LENGHT];
    bool userfollow = false; // to determine if a user has been followed by current user

    user* userPtr = twitter_system ->users;  // points to the start of the user linked list

    // every user begins with no followers. print all users except current user
    if (currUser->num_following ==0){
        printf("\nWho would you like to follow?\n");
        while(userPtr!= NULL)
        {  
            if (userPtr != currUser)
            {
                printf("%s\n", userPtr ->username);
            }
            userPtr = userPtr->next_user;
        }
    }
    
    // if current user has already followed all users except current user, return to the menu
    else if (currUser->num_following == twitter_system->count_user -1)
    {
        printf("All users followed.\n");
        return;
    }
    else {
        printf("\nWho would you like to follow?\n");
        //loop through following array, print users the user currently does not follow
        while(userPtr!=NULL)
        {
            if(strcmp(currUser->username,userPtr->username)!=0 && check(userPtr,currUser)==false){
                printf("%s\n",userPtr->username);
            }
            userPtr = userPtr->next_user;
        }
    }

    printf("\nPlease enter the username to follow the user:\n");
    gets(followeeName);

    //check if current user currently follows chosen followee
    if (currUser->num_following > 0){
        for (int j =0; j < currUser->num_following; j++)
        {
            if (strcmp (followeeName, currUser->following[j]) ==0 )
            {
                printf("Already followed user\n");
                userfollow = true;      
            }
        }
    }
     
    //only follow if user exists and is not being followed by current user
    if (userfollow == false)
    {
        user* followee = findUser(twitter_system, followeeName); // return a pointer to followee if it exists
        // if followee doesn't exist, return to menu
        if (followee == NULL)
        {
            printf("User not found\n");
            printf("Kindly select another menu option\n");
            return;   
        }
        // avoid current user following themselves
        else if (strcmp(followee->username, currUser->username)==0)
        {
            printf("You can not follow yourself.\n ");
            return;
        }
        // store username of followee to following array, increase  number of followers of followee and current user's number of following by 1
        else{
            followee ->num_followers +=1;
            strcpy(followee->followers[(followee->num_followers)-1], currUser ->username);
            currUser-> num_following += 1;
            strcpy(currUser->following[(currUser-> num_following)-1], followee -> username);
            printf("successfully followed");
            printf("\n");
            printf("My following list:\n");
            for(int i=0; i<currUser->num_following; i++)
            {
                printf("%s\n",currUser->following[i]);
            }
        }
    }
}

// function that allows user to unfollow a user from their following list
void unfollow(user * currUserPtr,twitter *twitter_system){

    char followeeName [USR_LENGHT];
    int index = -1;
    
    // check if current user's following list is empty
    if(currUserPtr->num_following == 0){
        printf("You have not followed anyone yet.\n");
        return;
    }

    printf("\nWhich user do you want to unfollow?\n");
    // print out current user's following list
    for(int i=0; i<currUserPtr->num_following; i++){
        printf("%s\n",currUserPtr->following[i]);
    }
    
    printf("\nPlease enter the person's username:\n");
    gets(followeeName);
    if(strlen(followeeName)==0){
        printf("You have not entered anything.\n");
        printf("Kindly select another menu option\n");
        return;
    }
    else{

    if(strcmp(followeeName,currUserPtr->username)==0){
        printf("You can not unfollow yourself.\n");
        printf("Kindly select another menu option\n");
        return;
    }
    // loop thorugh the following array, find the index of username of followee of which the current user wish to unfollow
    for(int i=0; i<currUserPtr->num_following; i++){
        if(strcmp(followeeName,currUserPtr->following[i])==0){
            index = i; // update the index value to the nth row where username of followee is found

            //remove username of followee from the array, update following array by moving all the usernames after this followee one position to the left
            for(int j=index; j<currUserPtr->num_following; j++){
                strcpy(currUserPtr->following[j],currUserPtr->following[j+1]);
            }
            currUserPtr->num_following --; // decrement current user's number of followings by 1
        }
    }
    // check if current user has followed this user 
    if(index == -1){
        printf("You have not followed this user yet.\n");
        return;
    }

    user *followeePtr = findUser(twitter_system,followeeName); // return a pointer points to the user which the current user wish to unfollow

    // loop through followers array of this followee, delete current user's username from the array
    for(int k=0; k<followeePtr->num_followers; k++){
        if(strcmp(currUserPtr->username,followeePtr->followers[k])==0){
            index = k;
            for(int j=index; j<followeePtr->num_followers; j++){
                strcpy(followeePtr->followers[j],followeePtr->followers[j+1]);
            }
            followeePtr->num_followers --; // decrement the number of followers of this followee by 1
        }
    }
    printf("unfollowed successfully.\n");
    }

}


//function allow user to delete their account, it takes a pointer to current user and deletes all information regarding user 
void delete (user * currUser, twitter *twitter_system)
{
    void menu(twitter *twitter_system);

    //loop through list of current users following 
    for(int i=0; i<currUser->num_following; i++){
        user *followeePtr = findUser(twitter_system,currUser->following[i]); // return a pointer to current user's followee
        
        // remove current user from follower array of current followee
        for(int k=0; k<followeePtr->num_followers; k++){
            if(strcmp(currUser->username,followeePtr->followers[k])==0){
                int index = k;
                for(int j=index; j<followeePtr->num_followers; j++){
                    strcpy(followeePtr->followers[j],followeePtr->followers[j+1]);
                }
                followeePtr->num_followers --; // decrement the number of followers of current followee by 1
            }    
        }
    }
    
    // loop through current user's followers array
    for(int i=0; i<currUser->num_followers; i++){
        user *followerPtr = findUser(twitter_system,currUser->followers[i]); // return a pointer points to current user's follower

        // loop through this follower's following array and remove current user
        for(int k=0; k<followerPtr->num_following; k++){
            if(strcmp(currUser->username,followerPtr->following[k])==0){
                int index = k;
                for(int j=index; j<followerPtr->num_following; j++){
                    strcpy(followerPtr->following[j],followerPtr->following[j+1]);
                }
                followerPtr->num_following --; // decrement the number of followings of current followee by 1
            }
        }
    }

    tweet *head = twitter_system->tweets; //place pointer at the beginning of tweet stack 
    tweet *temptweetPtr = NULL; // store node to be removed
    // if curr user to be deleted is at the beginning of the tweet stack remove stack head, keep updating the head node until its not current user's tweet
    while(head!=NULL && strcmp(head->user,currUser->username)==0){
        temptweetPtr = head;
        head = head->next_tweet;
        free(temptweetPtr); // release memory
    }

    tweet *prevTweetPtr = NULL;
    tweet *currTweetPtr = head;
    // while loop to remove all tweets of current user
    while(currTweetPtr!=NULL ){

        // loop through stack and get previous node pointer
        while(currTweetPtr!=NULL && strcmp(currTweetPtr->user, currUser ->username)!=0)
        {
            prevTweetPtr = currTweetPtr;
            currTweetPtr = currTweetPtr->next_tweet;
        }
        // when a current user's tweet is found, remove from the list and free the memory
        if(currTweetPtr != NULL)
        {
            temptweetPtr = currTweetPtr;
            prevTweetPtr->next_tweet = currTweetPtr->next_tweet; // let previous tweet's next pointer points to removed tweet's next tweet
            free(temptweetPtr); // free memory
        }
        currTweetPtr = prevTweetPtr->next_tweet; // update current tweet pointer for next iteration
    }
    twitter_system->tweets = head; // update tweets head node

    //check if user to be deleted is at the begining of the list 
    if (currUser == twitter_system ->users)
    {
        user *tempPtr = currUser; //store value of node to be deleted 
        twitter_system ->users = (*currUser).next_user;
        free (tempPtr); // release memory  
        twitter_system->count_user--;
        return;
    }
    else
    {
        user *userPrevPtr = twitter_system ->users;
        user *usercurrentPtr = twitter_system->users -> next_user;

        //loop through list to get user node before current node of user to be deleted 
        while (usercurrentPtr != NULL && usercurrentPtr != currUser)
        {
            userPrevPtr = usercurrentPtr; //update pointers with each iteration 
            usercurrentPtr = usercurrentPtr ->next_user;
        }

        //delete node when curr user has been found
        if (usercurrentPtr != NULL)
        {
            user *tempPtr = currUser;
            userPrevPtr->next_user = currUser->next_user; // let previous user's next user points to removed user's next user
            free(tempPtr); // release memory
            twitter_system->count_user--; // reduce number of users by 1
            printf("User successfully deleted \n");
        }
    }
    
    menu(twitter_system); // call menu function after successfully deleting user

}


// function allow user to post tweet
void postTweet (user*currUser,twitter *twitter_system)
{
    if(twitter_system->count_tweet == MAX_TWEETS){
        printf("No more tweets can be posted.\n");
    }
    else{
        twitter_system ->count_tweet ++;
        // creates pointer to new node 
        tweet* newTweetPtr =  malloc(sizeof(tweet)); // allocate memory for newTweetPtr
        if(newTweetPtr!=NULL){
            newTweetPtr->id = twitter_system->count_tweet; // timestamp of new tweet
            printf("tweet ?\n");
            gets(newTweetPtr->msg);
            // check if current user entered empty string
            if(strlen(newTweetPtr->msg)==0){
                printf("You have not entered anything yet.\n");
                printf("Please re-enter:\n");
                fgets(newTweetPtr->msg, TWEET_LENGTH, stdin); 
            }
            strcpy(newTweetPtr ->user, currUser ->username);
            //update head to newnode
            newTweetPtr->next_tweet = twitter_system->tweets;  
            twitter_system->tweets = newTweetPtr; 
            printf("New tweet posted.\n");
        }
        else{
            printf("No more memory available.\n");
        }
    }

}

// function to exit the program
void endTwitter (twitter *twitter_system)
{
    user *p, *q; // pointer to user node
    tweet *a, *b; // pointer to tweet node
    p = twitter_system->users; // points to head of users linked list

    // release the memory of all users
    while(p){
        q = p->next_user;
        free(p);
        p = q;
    }
    twitter_system->users = NULL;

    a = twitter_system->tweets; // points to head of tweets linked list

    // release the memory of all tweets
    while(a){
        b = a->next_tweet;
        free(a);
        a = b;
    }
    twitter_system->tweets = NULL;

    free (twitter_system); // release memory 
    twitter_system = NULL;

    printf("Twitter successfully terminated\n");
}

// function allow the program to proceed to the next user
void endTurn(twitter *twitter_system){
    void menu(twitter *twitter_system);
    menu(twitter_system);
}

// function to check whether current tweet's user is current user's followees
bool checkFollowingTweet(user *currUser, tweet * tweetPtr){
    for(int i=0; i<currUser->num_following; i++){
        if(strcmp(tweetPtr->user,currUser->following[i])==0){
            return true;
        }
    }
    return false;

}

// function to allow user to choose listed functions
void menu(twitter *twitter_system){
    printf("please enter your username to continue with more functions:\n");
    char name[USR_LENGHT];
    gets(name);
    // check if user exists in the system
    if(findUser(twitter_system,name)==NULL){
        printf("User doesn't exit, please enter a valid username.\n");
        menu(twitter_system);
    }
    user * current_user = findUser(twitter_system,name); // return a pointer points to current user
    tweet *currentTweet = NULL;
    printf("Number of followings: %d\n",current_user->num_following); // print number of followings of current user
    printf("Number of followers: %d\n",current_user->num_followers); // print number of followers of current user
    printf("\n Hello %s \n",current_user->username);
    instructions(); // display instructions
    int option;
    scanf("%d",&option);
    getchar(); // to store enter key pressed
    if(option == 0){
        endTwitter(twitter_system);
        exit(0);
    }
    
    // allow user to continue choosing functions
    while(option!=0){
        if(option == 1) {
            postTweet(current_user, twitter_system);
        }
        else if(option == 2) {
            getNewsfeed(current_user, twitter_system);
        }
        else if(option == 3) {
            follow(current_user, twitter_system);
        }
        else if(option == 4) {
            unfollow(current_user, twitter_system);
        }
        else if(option == 5) {
            delete(current_user, twitter_system);
        }
        else if(option == 6) {
            endTurn(twitter_system);
        }
        else{
            printf("Please enter a valid option(between 0 and 6):\n");
        }
        instructions();
        scanf("%d",&option);
        getchar(); // to store enter key pressed
        if(option == 0){
            endTwitter(twitter_system);
            exit(0);
        }
    }
}