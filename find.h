#ifndef FIND
#define FIND

User *find(User *head, char *name)
{
    //finds user by username
    User *curr = head;
    while (curr != NULL)
    {
        if (strcmp(curr->name, name) == 0)
        {
            return curr;
        }
        curr = curr->nextUser;
    }
    return NULL;
}

User *findEnd(User *usersHead)
{
    //finds the end of user linkedlist
    User *curr = usersHead;
    while (curr->nextUser != NULL)
    {
        curr = curr->nextUser;
    }
    return curr;
}

Post *findPostEnd(Post *posthead)
{
    //finds the end of post linkedlist
    Post *curr = posthead;
    while (curr->nextPost != NULL)
    {
        curr = curr->nextPost;
    }
    return curr;
}

Post *findPost(Post *head, int postId)
{
    //finds post by postid
    Post *curr = head->nextPost;
    while (curr != NULL)
    {
        if (curr->postId == postId)
            return curr;
        curr = curr->nextPost;
    }
    printf("\npost not found\n");
    return NULL;
}
// signup func
// check if the username exists before

int postLen(Post *head)
{
    Post *curr = head;
    int len = 0;
    while (curr->nextPost != NULL)
    {
        len++;
        curr = curr->nextPost;
    }
    return len;
}

Post *findLP(User *head, char *username, int postid)
{
    //finds the post user wants to like
    if (find(head, username) != NULL)
    {
        User *user = find(head, username);
        if (findPost(user->usersPosts, postid) != NULL)
        {
            return findPost(user->usersPosts, postid);
        }
        else
        {
            printf("post not found.\n");
            return NULL;
        }
    }
    else
    {
        printf("username doesn't exist.\n");
        return NULL;
    }
}
#endif