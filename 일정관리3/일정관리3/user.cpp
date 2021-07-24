#include <stdio.h>

#define MAX_GROUP 100
#define MAX_ID 1000
#define MAX_USER 100
#define MAX_DIF_NAME 200
#define MAX_SAME_NAME 5
#define MAX_NAME 15

#define rint register int

void mstrcpy(char dst[], const char src[]) {
	int c = 0;
	while ((dst[c] = src[c]) != 0) ++c;
}

int mstrcmp(const char str1[], const char str2[]) {
	int c = 0;
	while (str1[c] != 0 && str1[c] == str2[c]) ++c;
	return str1[c] - str2[c];
}

struct EVENT
{
	char ename[MAX_NAME];
	int n;
	int slave[MAX_SAME_NAME];
} group[MAX_GROUP][MAX_DIF_NAME];

int group_cnt[MAX_GROUP];

struct NODE
{
	char ename[MAX_NAME];
	int groupID;
	EVENT* g;
} user[MAX_ID][MAX_USER];
int user_cnt[MAX_ID];

void init()
{
	for (int i = 0; i < MAX_GROUP; i++)
	{
		for (int j = 0; j < MAX_DIF_NAME; j++)
		{
			group[i][j].n = 0;
		}
		group_cnt[i] = 0;
	}
	for (int i = 0; i < MAX_ID; i++)
	{
		user_cnt[i] = 0;
	}
}

void addEvent(int uid, char ename[], int groupid)
{
	mstrcpy(user[uid][user_cnt[uid]].ename, ename);
	user[uid][user_cnt[uid]].groupID = groupid;


	int flag = 0;
	for (rint i = 0; i < group_cnt[groupid]; i++)
	{
		if (!mstrcmp(group[groupid][i].ename, ename))
		{
			group[groupid][i].slave[group[groupid][i].n++] = uid;
			user[uid][user_cnt[uid]].g = &group[groupid][i];
			flag = 1;
			break;
		}
	}
	if (flag == 0)
	{
		mstrcpy(group[groupid][group_cnt[groupid]].ename, ename);
		group[groupid][group_cnt[groupid]].slave[0] = uid;
		group[groupid][group_cnt[groupid]].n = 1;
		user[uid][user_cnt[uid]].g = &group[groupid][group_cnt[groupid]];
		group_cnt[groupid]++;
	}
	user_cnt[uid]++;
}

void swap_user(int uid, int i, int j)
{
	user[uid][i] = user[uid][j];
}

void swap_group(int groupid, EVENT* p)
{	
	*p = group[groupid][--group_cnt[groupid]];
}

int deleteEvent(int uid, char ename[])
{
	for (rint i = 0; i < user_cnt[uid]; i++)
	{
		if (!mstrcmp(user[uid][i].ename, ename))
		{
			if (user[uid][i].g->slave[0] == uid)
			{
				int temp = user[uid][i].g->n;
				int groupid = user[uid][i].groupID;

				swap_group(groupid, user[uid][i].g);
				swap_user(uid, i, --user_cnt[uid]);
				return temp;
			}
			else
			{
				for (rint j = 1; j < user[uid][i].g->n; j++)
				{
					if (user[uid][i].g->slave[j] == uid)
					{
						user[uid][i].g->n--;
						user[uid][i].g->slave[j] = user[uid][j].g->slave[user[uid][i].g->n];

						swap_user(uid, i, user_cnt[uid]--);
						return 1;
					}
				}
			}
		}
	}
	return 0;
}

int changeEvent(int uid, char ename[], char cname[])
{
	int cnt = 1;
	int groupid = 0;
	for (int i = 0; i < user_cnt[uid]; i++)
	{
		if (!mstrcmp(user[uid][i].ename, ename))
		{
			if (user[uid][i].g->slave[0] == uid)
			{
				int temp = user[uid][i].g->n;
				mstrcpy(user[uid][i].g->ename, cname);
				mstrcpy(user[uid][i].ename, cname);
				return temp;
			}
		}
		else
		{
			for (rint j = 1; j < user[uid][i].g->n; j++)
			{
				if (user[uid][i].g->slave[j] == uid)
				{
					mstrcpy(user[uid][i].ename, cname);
					groupid = user[uid][i].groupID;
					user[uid][i].g->n--;
					user[uid][i].g->slave[j] = user[uid][j].g->slave[user[uid][i].g->n];

					///////
					for (int k = 0; k < group_cnt[groupid]; k++)
					{
						if (!mstrcmp(group[groupid][k].ename, cname))
						{
							user[uid][i].g = &group[groupid][k];
							group[groupid][k].slave[group[groupid][k].n++] = group[groupid][k].slave[0];
							group[groupid][k].slave[0] = uid;
							return 1;
						}
					}
					mstrcpy(group[groupid][group_cnt[groupid]].ename, cname);
					group[groupid][group_cnt[groupid]].slave[0] = uid;
					group[groupid][group_cnt[groupid]].n = 1;
					user[uid][i].g = &group[groupid][group_cnt[groupid]];
					group_cnt[groupid]++;

					return 1;
				}
			}
		}
	}

	return cnt;
}

int getCount(int uid)
{
	return user_cnt[uid];
}