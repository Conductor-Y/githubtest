#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

struct Address
{
	int id;
	int set;
	char gender[7];				
	char *name;
	char *email;
};

struct Database 
{
	int MAX_DATA;
	int MAX_ROWS;
	struct Address **rows;
};

struct Connection 
{
	FILE *file;
	struct Database *db;
};

void die(const char *message, struct Connection *conn)
{
	if(errno) 
	{
		perror(message);
		if(conn) 
		{
    	if(conn->file) fclose(conn->file);
    	if(conn->db) free(conn->db);
    	free(conn);
		}
	}
	else 
	{
		printf("ERROR: %s\n", message);
	}

	exit(1);
}

void Address_print(struct Address *addr)
{
	printf("%d %s %s\n", addr->id, addr->name, addr->email);
}

void Database_load(struct Connection *conn)
{
	int rc = fread(&conn->db->MAX_ROWS, sizeof(int), 1, conn->file);
	if(rc != 1) die("Failed to load MAX_ROWS.", conn);

	rc = fread(&conn->db->MAX_DATA, sizeof(int), 1, conn->file);
	if(rc != 1) die("Failed to load MAX_DATA.", conn);

	conn->db->rows = malloc(conn->db->MAX_ROWS * sizeof(struct Address*));

	for(int i = 0; i < conn->db->MAX_ROWS; i++) 
	{
		struct Address *addr = malloc(sizeof(struct Address));
		rc = fread(&(addr->id), sizeof(int), 1, conn->file);
		if(rc != 1)	die("Failed to load address->id.", conn);

		rc = fread(&(addr->set), sizeof(int), 1, conn->file);
		if(rc != 1)	die("Failed to load address->set.", conn);

		rc = fread(addr->gender, sizeof(char), 7, conn->file);
		if(rc != 7)	die("Fail to load address->gender.", conn);

		addr->name = malloc(conn->db->MAX_DATA * sizeof(char));
		addr->email= malloc(conn->db->MAX_DATA * sizeof(char));
		
		rc = fread(addr->name, sizeof(char), conn->db->MAX_DATA, conn->file);
		if(rc != conn->db->MAX_DATA) die("Failed to load address->name.", conn);

		rc = fread(addr->email, sizeof(char), conn->db->MAX_DATA, conn->file);
		if(rc != conn->db->MAX_DATA) die("Failed to load address->email.", conn);

		conn->db->rows[i] = addr;
	}


}

struct Connection *Database_open(const char *filename, char mode)
{
	struct Connection *conn = malloc(sizeof(struct Connection));
	if(!conn) die("Memory error", conn);

	conn->db = malloc(sizeof(struct Database));
	if(!conn->db) die("Memory error", conn);

	if(mode == 'c') 
	{
		conn->file = fopen(filename, "w");
	} 
	else 
	{
		conn->file = fopen(filename, "r+");

		if(conn->file) 
		{
			Database_load(conn);
		}
	}

	if(!conn->file) die("Failed to open the file", NULL);

	return conn;
}

void Database_close(struct Connection *conn)
{
	if(conn) 
	{
		if(conn->file) fclose(conn->file);
		for(int i = 0; i < conn->db->MAX_ROWS; i++)
		{
			if(conn->db->rows[i]->name) free(conn->db->rows[i]->name);
			if(conn->db->rows[i]->email) free(conn->db->rows[i]->email);
			if(conn->db->rows[i]) free(conn->db->rows[i]);
		}
		if(conn->db->rows) free(conn->db->rows);
		if(conn->db) free(conn->db);
		free(conn);
	}
}

void Database_write(struct Connection *conn)
{
	rewind(conn->file);

	int rc;
	rc = fwrite(&conn->db->MAX_ROWS, sizeof(conn->db->MAX_ROWS), 1, conn->file);
	if(rc != 1) die("Failed to write MAX_ROWS.", conn);
	rc = fwrite(&conn->db->MAX_DATA, sizeof(conn->db->MAX_DATA), 1, conn->file);
	if(rc != 1) die("Failed to write MAX_DATA.", conn);

	for(int i = 0; i < conn->db->MAX_ROWS; i++)
	{
		struct Address *address = conn->db->rows[i];

		rc = fwrite(&address->id, sizeof(address->id), 1, conn->file);
		if(rc != 1) die("Failed to write address->id.", conn);

		rc = fwrite(&address->set, sizeof(address->set), 1, conn->file);
		if(rc != 1) die("Failed to write address->set.", conn);

		rc = fwrite(address->gender, sizeof(char), 7, conn->file);
		if(rc != 7)	die("Fail to wirte address->gender.", conn);

		rc = fwrite(address->name, sizeof(char), conn->db->MAX_DATA, conn->file);
		if(rc != conn->db->MAX_DATA) die("Failed to write address->name.", conn);

		rc = fwrite(address->email, sizeof(char), conn->db->MAX_DATA, conn->file);
		if(rc != conn->db->MAX_DATA) die("Failed to write address->email.", conn);
	}	

	rc = fflush(conn->file);
	if(rc == -1) die("Cannot flush database.", conn);
}

void Database_create(struct Connection *conn, int MAX_DATA, int MAX_ROWS)
{
	int i = 0;
	conn->db->MAX_DATA = MAX_DATA;
	conn->db->MAX_ROWS = MAX_ROWS;
	conn->db->rows = (struct Address **)malloc(MAX_ROWS * sizeof(struct Address*));

	if(!(conn->db->rows))
	{
		die("ERROR:fail to assign rows.", conn);
	}	

	for(i = 0; i < MAX_ROWS; i++) 
	{
		struct Address *addr = (struct Address *)malloc(sizeof(struct Address));
		addr->name = (char *)malloc(sizeof(char) * MAX_DATA);
		addr->email = (char *)malloc(sizeof(char) * MAX_DATA);

		memset(addr->name, 0, MAX_DATA);
		memset(addr->email, 0, MAX_ROWS);

		addr->id = i;
		addr->set = 0;
		strncpy(addr->gender, "none", 7);
		strncpy(addr->name, "name", MAX_DATA);
		strncpy(addr->email, "email", MAX_DATA);
		conn->db->rows[i] = addr;
	}
}

void Database_set(struct Connection *conn, int id, const char *name, const char *email, char *gender)
{
	struct Address *addr = conn->db->rows[id];
	if(addr->set) die("Already set, delete it first", conn);

	addr->set = 1;
	
	char *res;
	
	res = strncpy(addr->gender, gender, 6);
	if(!res) die("Gender copy failer", conn);

	res = strncpy(addr->name, name, conn->db->MAX_DATA);
	if(!res) die("Name copy failed", conn);

	res = strncpy(addr->email, email, conn->db->MAX_DATA);
	if(!res) die("Email copy failed", conn);
}

void Database_get(struct Connection *conn, int id)
{
	struct Address *addr = conn->db->rows[id];

	if(addr->set) 
	{
		Address_print(addr);
	}	 
	else 
	{
		die("ID is not set", conn);
	}
}

void Database_find(struct Connection *conn, char *name)
{
	int id;
	int flag = 0;
	for(id = 0; id < conn->db->MAX_ROWS; id++)
	{
		struct Address *addr = conn->db->rows[id];
		if(strcmp(name, addr->name) == 0)
		{
			flag = 1;				//判断标志赋值
		}
	}

	if(flag)				//根据标志输出
	{
		printf("I find it.\n");
	}
	else
	{
		die("Can not find it", conn);
	}
}

void Database_delete(struct Connection *conn, int id)
{
	struct Address *addr = conn->db->rows[id];
	addr->set = 0;
}

void Database_list(struct Connection *conn)
{
	int i = 0;
	struct Database *db = conn->db;
	for(i = 0; i < db->MAX_ROWS; i++) 
	{
		struct Address *cur = db->rows[i];

		if(cur->set) 
		{
			Address_print(cur);
		}
	}
}

int main(int argc, char *argv[])
{
	if(argc < 3) die("USAGE:: ex17 <dbfile> <action> [action params] ", NULL);

	char *filename = argv[1];
	char action = argv[2][0];
	struct Connection *conn = Database_open(filename, action);
	int id = 0;
	int MAX_ROWS = 0;
	if(conn->db->MAX_ROWS) MAX_ROWS = conn->db->MAX_ROWS;
	else MAX_ROWS = atoi(argv[4]);
	if(argc > 3 && argc != 6) id = atoi(argv[3]);
	if(id >= MAX_ROWS) die("There's not that many records.", conn);

	switch(action) 
	{
		case 'c':
			Database_create(conn, atoi(argv[3]), atoi(argv[4]));
			Database_write(conn);
		break;

		case 'g':
			if(argc != 4) die("Need an id to get", NULL);
			Database_get(conn, id);
		break;

		case 's':
			if(argc != 7) die("Need id, name, email gender", NULL);
			Database_set(conn, id, argv[4], argv[5], argv[6]);
			Database_write(conn);
		break;

		case 'd':
			if(argc != 4) die("Need id to delete", NULL);
			Database_delete(conn, id);
			Database_write(conn);
		break;

		case 'l':
			Database_list(conn);
		break;

		case 'f':
			Database_find(conn, argv[3]);
		break;

		default:
		die("Invalid action, only: c=create, g=get, s=set, d=del, l=list, f=find", NULL);
	}
	

	Database_close(conn);

	return 0;
}
