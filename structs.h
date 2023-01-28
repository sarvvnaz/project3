#ifndef STRUCTS
#define STRUCTS

typedef struct User
{
    char *name;
    char *pass;
    struct Post *usersPosts;
    struct User *nextUser;
    struct ULP *liked_posts;
} User;

typedef struct Post
{
    User *user;
    int postId;
    int likes;
    char *text;
    struct Post *nextPost;
} Post;

typedef struct ULP
{
    Post *likedPost;
    struct ULP *nextPost;
} ULP;

#endif