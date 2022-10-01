#include <stdio.h>
#include "twitter_create.h"
#include "functionality.h"
#include "printing.h"

int main() {

    twitter twitter_system;
    create_twitter_system(&twitter_system);
     
    if(twitter_system.users !=NULL){
        printUsers(&twitter_system);
        menu(&twitter_system);
    }

    return 0;

}
