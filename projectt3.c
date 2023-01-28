#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structs.h"
#include "commandline.h"
#include "find.h"
#include "functions.h"
#define MAX_STRING 100



int main()
{
    // user
    User *uhead = (User *)malloc(sizeof(User));
    User *logged_in_user = (User *)malloc(sizeof(User));
    uhead->name = (char *)malloc(2);
    uhead->pass = (char *)malloc(2);
    uhead->nextUser = NULL;
    strcpy(uhead->name, "p");
    strcpy(uhead->pass, "p");
    logged_in_user = NULL;
    int flag = 0;
    int user_cmd;

    while (1)
    {
        char* cmd=(char*)malloc(1); 
        cmd=input(cmd);
        int user_cmd=command(cmd);
        free(cmd);
        if (user_cmd == 0)
        {
            // signup

             char *name = (char *)malloc(100);
            name=input(name);
            char *pass = (char *)malloc(100);
            pass=input(pass);
            signup(uhead, logged_in_user, name, pass);

            // ULP head
            ULP *ULPHead = (ULP *)malloc(sizeof(ULP));
            ULPHead->likedPost = NULL;
            ULPHead->nextPost = NULL;
            findEnd(uhead)->liked_posts = ULPHead;

            // posthead
            Post *PostsHead = (Post *)malloc(sizeof(Post));
            PostsHead->text = (char *)malloc(2);
            PostsHead->likes = 0;
            PostsHead->postId = 0;
            PostsHead->nextPost = NULL;
            strcpy(PostsHead->text, "p");
            findEnd(uhead)->usersPosts = PostsHead;
            free(name);
            free(pass);
        }
        if (user_cmd == 1)
        {
            // login
            char *login_name = (char *)malloc(100);
            login_name = input(login_name);
            char *login_pass = (char *)malloc(100);
            login_pass = input(login_pass);
            login(uhead, &logged_in_user, login_name, login_pass);
            free(login_name);
            free(login_pass);
        }
        if (user_cmd == 2)
        {
            // submit post
            char* text=(char*)malloc(1);
            int i=0;
            char inp_tmp='x';
            //split inputted string
            while(1){ 
                inp_tmp=getchar();
                if(inp_tmp=='\n') break;
                *(text+i)=inp_tmp;
                i++;
               text=(char*)realloc(text,i+1);
            }
            text[i]='\0';
            submit_post(logged_in_user, text);
            free(text);
        }
        if (user_cmd == 3)
        {
            logout(&logged_in_user);
        }
        if (user_cmd == 4)
        {
            // show user's info
            show_user_info(logged_in_user);
        }
        if (user_cmd == 5)
        {
            char *username = (char *)malloc(30);
            username = input(username);
            search_user(uhead, username);
            free(username);
        }
        if (user_cmd == 6)
        {
            //delete post
            int postId;
            scanf("%d", &postId);
            removeByPostId(logged_in_user, postId);
        }
        if (user_cmd == 7)
        {
            //like post
            char *username = (char *)malloc(30);
            username = input(username);
            
            int postid;
            scanf("%d", &postid);
            likePost(uhead, logged_in_user, username, postid);
            free(username);
        }
    }
}