#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#define MAX_DATA 512
#define MAX_ROWS 100

//initialize the first struct
struct Address {
	int id;
	int set;
	char name[MAX_DATA];
	char email[MAX_DATA];
};

struct Database {
	//create an array of rows 
	struct Address rows[MAX_ROWS];
};

struct Connection {
	//make a file named file
	FILE *file;
	//create a new Database struct named db (within a struct)
	struct Database *db;
};

//function that aborts the program whence an error occurs
void die(const char *message)
{
	if(errno) {
		perror(message);
	} else {
		printf("ERROR: %s\n", message);
	}

	//exit with a status of 1
	exit(1);
}

void Address_print(struct Address *addr) {
	printf("%d %s %s\n",addr->id, addr->name, addr->email);
}

//function when command is given to load database
void Database_load(struct Connection *conn)
{
	//opens file 
	int rc = fread(conn->db, sizeof(struct Database), 1, conn->file);
	//check to see if it opened properly
	if(rc != 1) die("Failed to load database.");
}

//function that returns a struct, opens the file to be manipulated 
struct Connection *Database_open(const char *filename, char mode)
{
	//make struct within struct and allocate size
	struct Connection *conn = malloc(sizeof(struct Connection));
	//error handling
	if(!conn) die("Memory Error");
	
	//allocate size for db within conn
	conn->db = malloc(sizeof(struct Database));
	//error handling
	if(!conn->db) die("Memory Error");

	//if running in create mode give write privledges
	if (mode == 'c') {
		conn->file = fopen(filename, "w");
	} else {
	//otherwise give read privledges
		conn->file = fopen(filename, "r+");

		//if file exists within conn load database
		if(conn->file) {
			Database_load(conn);
		}
	}
	//if it didnt, then kill
	if(!conn->file) die("Failed to open the file");

	//return the struct
	return conn;
}

//function to clean the allocated memory space of db it is handed
void Database_close(struct Connection *conn)
{
	//if exists
	if(conn) {
		if(conn->file) fclose(conn->file);
		if(conn->db) free(conn->db);
		free(conn);
	}
}

void Database_write(struct Connection *conn)
{
	//sets file position to the beginning of the given stream
	rewind(conn->file);

	//int to hold return value
	//write to db within conn 
	int rc = fwrite(conn->db, sizeof(struct Database), 1, conn->file);
	//if successful fwrite returns the number of elements
	//sucessfully written
	if(rc != 1) die("FAILED to write database");
	
	rc = fflush(conn->file);
	if(rc == -1) die("Cannot flush database.");
}
void Database_create(struct Connection *conn)
{
	int i = 0;

	for(i=0;i< MAX_ROWS; i++) {
		//make a prototype to initialize it
		struct Address addr = {.id = i, .set = 0};
		//then just assign it
		conn->db->rows[i] = addr;
	}
}
void Database_set(struct Connection *conn, int id, const char *name, const char *email)
{
	struct Address *addr = &conn->db->rows[id];
	if(addr->set) die("already set, delete it first");
	
	addr->set = 1;
	//WARNING
	char *res = strncpy(addr->name, name, MAX_DATA);
	//demonstrate bug
	if(!res) die("Name copy failed");

	res = strncpy(addr->email, email, MAX_DATA);
	if(!res) die("Email copy failed");
}

void Database_get(struct Connection *conn, int id)
{
	struct Address *addr = &conn->db->rows[id];

	if(addr->set) {
		Address_print(addr);
	} else {
		die("ID is not set");
	}
}

void Database_delete(struct Connection *conn, int id)
{
	struct Address addr = {.id = id, .set = 0};
	conn->db->rows[id] = addr;
}

void Database_list(struct Connection *conn)
{
	int i=0;
	struct Database *db = conn->db;
	
	for(i=0;i<MAX_ROWS;i++) {
		struct Address *cur = &db->rows[i];

		if(cur->set) {
			Address_print(cur);
		}
	}
}

int main(int argc, char *argv[])
{
	if(argc < 3) die("USAGE: ex17 <dbfile> <action> [action params]");
	
	char *filename = argv[1];
	char action = argv[2][0];
	struct Connection *conn = Database_open(filename, action);
	int id = 0;

	if(argc > 3) id = atoi(argv[3]);
	if(id>=MAX_ROWS) die("There's not that many records.");

	switch(action) {
		case 'c':
			Database_create(conn);
			Database_write(conn);
			break;

		case 'g':
			if(argc != 4) die("need an id to get");
			Database_get(conn,id);
			break;

		case 's':
			if(argc != 6) die("need id, name, email to set");
			Database_set(conn, id, argv[4], argv[5]);
			Database_write(conn);
			break;

		case 'd':
			if(argc != 4) die("need id to delete");
			Database_delete(conn,id);
			Database_write(conn);
			break;

		case 'l':
			Database_list(conn);
			break;
		default:
			die("Invalid action, only: c=create, g=get, s=set, d=del, l=list");
	}
	
	Database_close(conn);
	
	return 0;
}



