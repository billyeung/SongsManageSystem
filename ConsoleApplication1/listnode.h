#ifndef _LISTNODE_H
#define _LISTNODE_H
void namelist();
void singerlist();
void musiclist();
struct song{
	char name[40];
	char singer[30];
	struct song* prior;
	struct song* next;
};
typedef struct song song;
typedef struct song* sgptr;
struct music{
	char name[100];
	struct music* prior;
	struct music* next;
};
typedef struct music music;
typedef struct music* msptr;
typedef struct{
	sgptr head;
	sgptr tail;
}sglist;
extern sglist *nlist,*slist;
typedef struct{
	msptr head;
	msptr tail;
}mslist;
extern int on, os, num, pli;
extern mslist *mlist;
#endif