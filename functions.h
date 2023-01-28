#ifndef FUNCS
#define FUNCS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structs.h"
#include "commandline.h"
#include "find.h"
#define MAX_STRING 100

int signup(User *usersHead, User *logged_in_user, char *name, char *pass)
{
    if (find(usersHead, name) != NULL)
    {
        printf("entered username exists.");
        return 1;
    }
    User *newUser = (User *)malloc(sizeof(User));
    newUser->name = (char *)malloc(MAX_STRING);
    newUser->pass = (char *)malloc(MAX_STRING);
    newUser->nextUser = NULL;
    User *curr = findEnd(usersHead);
    strcpy(newUser->name, name);
    strcpy(newUser->pass, pass);
    curr->nextUser = newUser;
    printf("user %s %s created\n", newUser->name, newUser->pass);
    return 0;

    printf("sb else is already logged in.\n");
    return 1;
}

// login
// check if the info is correct
// check if anyone is logged in
// change value of loggedin user

void login(User *usersHead, User **logged_in_user, char *name, char *pass)
{
    if (*logged_in_user == NULL)
    {
        if (find(usersHead, name) != NULL)
        {
            if (strcmp(find(usersHead, name)->pass, pass) == 0)
            {
                *logged_in_user = find(usersHead, name);
                printf("login successful\n");
            }
            else
                printf("wrong password\n");
        }
        else
            printf("wrong username\n");
    }
    else
        printf("another user is logged in.\n");
}

int submit_post(User *logged_in_user, char* text)
{ // check if any user is logged in
    if (logged_in_user != NULL)
    {
        Post *newpost = (Post *)malloc(sizeof(Post));
        newpost->text = (char *)malloc(MAX_STRING);

        strcpy(newpost->text, text);
        newpost->likes = 0;
        // ask if it works
        newpost->postId = (findPostEnd(logged_in_user->usersPosts)->postId) + 1;
        findPostEnd(logged_in_user->usersPosts)->nextPost = newpost;

        printf("new post created with postid %d.\n", newpost->postId);
        return 0;
    }
    printf("noone is logged in.\n");
    return 1;
}

// logout
// check if any user is logged in
void logout(User **logged_in_user)
{
    if (*logged_in_user != NULL)
    {
        *logged_in_user = NULL;
        printf("logged out successfully.\n");
        return;
    }
    printf("no one logged in. \n");
}

// check user info
// check if anyone is loggedin
// print user info
void show_user_info(User *logged_in_user)
{
    if (logged_in_user != NULL)
    {
        printf("user name: %s\n", logged_in_user->name);
        printf("user password: %s\n", logged_in_user->pass);
        // check if any post exists
        if (logged_in_user->usersPosts != NULL)
        {
            Post *head = logged_in_user->usersPosts;
            Post *curr = head->nextPost;
            while (curr != NULL)
            {
                printf("post ID:%d\n", curr->postId);
                printf("post text:%s\n", curr->text);
                printf("post likes:%d\n", curr->likes);
                curr = curr->nextPost;
            }
        }
        else
            printf("no posts yet.\n");
    }
}
void search_user(User *user, char *username)
{

    User *searched_user = find(user, username);

    if (searched_user != NULL)
    {
        if (searched_user->usersPosts != NULL)
        {
            Post *curr = searched_user->usersPosts->nextPost;
            while (curr != NULL)
            {

                printf("post ID:%d\n", curr->postId);
                printf("post text:%s\n", curr->text);
                printf("post likes:%d\n", curr->likes);
                curr = curr->nextPost;
            }
        }
        else
            printf("no posts yet.\n");
    }
    else
        printf("user doesnt exist\n");
}
void likePost(User *head, User *logged_in_user, char *username, int postId)
{
    // check if the user has logged in
    if (logged_in_user != NULL)
    {

        Post *likedpost = findLP(head, username, postId);
        ULP *curr = logged_in_user->liked_posts;
        ULP *hold;
        // check if user has already liked this post.
        while (curr != NULL)
        {
            hold = curr;
            if (curr->likedPost == likedpost)
            {
                printf("uve already liked this post!\n");
                return;
            }
            curr = curr->nextPost;
        }
        ULP *newLP = (ULP *)malloc(sizeof(ULP));
        newLP->nextPost = NULL;
        newLP->likedPost = likedpost;
        hold->nextPost = newLP;    
        // increase likes of the post
        (likedpost->likes)++;
        printf("post liked!\n");
    }
    else
        printf("u should login first.\n");
    
}


void removeByPostId(User *logged_in_user, int postid)
{
    if (logged_in_user != NULL)
    {
        Post *postHead = logged_in_user->usersPosts;
        Post *curr = postHead;
        Post *hold = postHead;
        while (curr != NULL)
        {
            if (curr->postId == postid)
            {
                hold->nextPost = curr->nextPost;
                free(curr);
                printf("deleted succsesfully\n");
                return;
            }
            hold = curr;
            curr = curr->nextPost;
        }
        printf("post not found\n");
    }
    else
        printf("u should login first.\n");
}

#endif