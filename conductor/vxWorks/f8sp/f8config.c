#include     <precomp.h>
#include     <stdio.h>      
#include     <stdlib.h>     
#include     <unistd.h>     
#include     <sys/types.h>  
#include     <sys/stat.h>   
#include     <fcntl.h>      
#include     <errno.h>      
#include     <math.h>

#define PORT "/tyCo/0"
#define CLRSCREEN "\f\f"
#define HSB_DIS 1
#define HSB_EN 2

static int port_fd;
static char password[16]="123456";

typedef struct{
	int sn;
	int hs;
}config_t;
config_t cfg_cur,cfg_old;

static void send_line(int fd, char *line)
{
	write(fd, line, strlen(line));
}

static void perr(char *line)
{
	send_line(port_fd,line);
}

static int read_line(int fd, char* data, int data_len, int pwd)
{
	int i;

	memset(data, 0, data_len);
	i=0;
	while(i<data_len){
		read(fd, &data[i], data_len-i);
		if(data[i]=='\r' || data[i]=='\n'){
			data[i]=0;
			write(fd,"\r\n",2);
			break;
		}
		if(pwd){
			write(fd,"*",1);
		}else{
			write(fd,&data[i],1);
		}
		i++;
	}

	return i;
}

static void load_password()
{
	FILE *fd;
	fd = fopen("/c/wordpass", "r");

	memset(password,0,sizeof(password));
	if(fd!=NULL){
		fread(password,sizeof(password)-1,1,fd);
		fclose(fd);
	}
}

static void save_password()
{
	FILE *fd;
	fd = fopen("/c/wordpass", "w");
	if(fd!=NULL){
		fwrite(password,sizeof(password)-1,1,fd);
		fclose(fd);
	}
}

#define NWORD 80
#define NLINE 80
static int get_word(char *line, char *word, int *cursor)
{
	char * pl, * pw;
	int i;

	pw = word;
	pl = line + *cursor;
	while((*pl == ' ' || *pl == '\t' || *pl == '"' || *pl == '.') && *pl != 0){
		pl++;
		*cursor += 1;
	}
	i = 0;
	while((*pl != '\0' && *pl != ' ' && *pl != '\t' && *pl != '"' && *pl != '.') && *pl != 0 && i < NWORD - 1){
		*pw = *pl;
		pw++;
		pl++;
		*cursor += 1;
		i++;
	}
	*pw = 0;
	return i;
}
static int get_line(char *buf, char *line, int *cursor)
{
	char *pb, *pl;
	int i;

	pl = line;
	pb = buf+*cursor;
	while(*pb=='\n' && *pb!=0){
		pb++;
		*cursor+=1;
	}
	i=0;
	while(*pb!='\n' && *pb!=0 && i<NLINE-1){
		*pl=*pb;
		pl++;
		pb++;
		*cursor+=1;
		i++;
	}
	*pl=0;
	return i;
}

static void load_cfg()
{
	FILE *fd;
	char buffer[1024];
	char line[NLINE];
	char word[NWORD];
	int csrline, csrword;
	int flag;
	
	fd = fopen("/c/startup.sh","r");
	if(fd==NULL){
		return;		
	}

	fread(buffer,1024,1,fd);
	fclose(fd);

	csrline=0;
	while(get_line(buffer, line, &csrline)!=0){
		csrword=0;
		get_word(line,word,&csrword);
		if(strcmp(word,"initInterface")==0){
			get_word(line,word,&csrword);
			get_word(line,word,&csrword);
			get_word(line,word,&csrword);
			get_word(line,word,&csrword);
			get_word(line,word,&csrword);
			get_word(line,word,&csrword);
			cfg_old.sn=strtol(word,0,0);		
		}

		if(strcmp(word,"ex_main_z")==0){
			get_word(line,word,&csrword);
			flag=strtol(word,0,0);
			if(flag & 4){
				cfg_old.hs=HSB_EN;
			}else{
				cfg_old.hs=HSB_DIS;
			}
		}		
	}
}

static void save_cfg()
{
	FILE *fd;
	char line[80];
	
	fd = fopen("/c/startup.sh", "w");
	if(fd==NULL){
		return;
	}
	fprintf(fd, "shellInitHook\n");
	fprintf(fd, "initInterface \"rtl 0 192.168.0.%d f8 0xffffff00\"\n", cfg_cur.sn);
	fprintf(fd, "initInterface \"rtl 1 192.168.1.%d f8 0xffffff00\"\n", cfg_cur.sn);
	fprintf(fd, "localexec \"/d/f8kernel.out\",\"\"\n");
	if(cfg_cur.hs==HSB_EN){
		fprintf(fd, "ex_main_z 0x3f\n");
	}else{
		fprintf(fd, "ex_main_z 0x3b\n");
	}
	fprintf(fd, "taskDelay 5000\n");
	fprintf(fd, "localexec \"/d/dbsync.o\",\"\"\n");
	fprintf(fd, "gmem_start_ex 125, 0\n");
	fprintf(fd, "localexec \"/c/f8config.o\",\"cfg_start\"");
	fclose(fd);
	//printf("save complete\n");
}

static void load_config()
{
	load_cfg();
	memcpy(&cfg_cur, &cfg_old, sizeof(config_t));
	//printf("old sn:%d, hs:%d\n", cfg_old.sn, cfg_old.hs);
	//printf("cur sn:%d, hs:%d\n", cfg_cur.sn, cfg_cur.hs);
}

static void reset_config()
{
	memcpy(&cfg_cur, &cfg_old, sizeof(config_t));
}

static void save_config()
{
	memcpy(&cfg_old, &cfg_cur, sizeof(config_t));
	save_cfg();	
}

static int open_port (char* port)
{
	int fd;
	if((fd = open(port, O_RDWR, 0)) == -1){
		//perror("Cannot open the desired port\n");
		return -1;
	}
	return fd;
}

static int close_port (int fd)
{
	close(fd);
}

static void check_password()
{
	char pwd[16];

	memset(pwd, 0, sizeof(pwd));		
	while(strcmp(pwd, password) != 0){
		send_line(port_fd, CLRSCREEN);
		send_line(port_fd, "password:\r\n");	
		send_line(port_fd, ">");
		read_line(port_fd, pwd, sizeof(pwd)-1, 1);
	}
	send_line(port_fd, CLRSCREEN);
}

static void menu()
{
	send_line(port_fd, "cpu config menu\r\n");
	send_line(port_fd, "    1 -> station number\r\n");
	send_line(port_fd, "    2 -> hotstandby\r\n");
	send_line(port_fd, "    3 -> show\r\n");
	send_line(port_fd, "    4 -> change password\r\n");
	send_line(port_fd, "    5 -> save current setting\r\n");
	send_line(port_fd, "    6 -> quit\r\n");
}

static void set_station()
{
	char line[80];
	int sn;
	
	sprintf(line,"current station number: %d\r\n", cfg_cur.sn);
	send_line(port_fd, line);
	send_line(port_fd, "enter new station number:\r\n");
	send_line(port_fd, ">");

	memset(line,0,sizeof(line));
	read_line(port_fd, line, 4, 0);
	sn=strtol(line,0,0);
	if(sn>=1 && sn<=254){
		cfg_cur.sn=sn;
	}
	send_line(port_fd, "\r\n");
}

static void set_state()
{
	char line[80];
	int hs;

	if(cfg_cur.hs==HSB_EN){
		send_line(port_fd, "hot standby state: enable\r\n");
	}else{
		send_line(port_fd, "hot standby state: disable\r\n");
	}

	send_line(port_fd, "set new state:\r\n");
	send_line(port_fd, "    1 -> disable\r\n");
	send_line(port_fd, "    2 -> enable\r\n");
	send_line(port_fd, ">");

	memset(line, 0, sizeof(line));
	read_line(port_fd, line, 2, 0);
	hs=strtol(line,0,0);

	if(hs==1){
		cfg_cur.hs=HSB_DIS;
	}else if(hs==2){
		cfg_cur.hs=HSB_EN;
	}

	send_line(port_fd, "\r\n");
}

static void show()
{
	char line[80];
 
	sprintf(line,"current config:\r\n");
	sprintf(line,"    station number: %d\r\n", cfg_cur.sn);
	send_line(port_fd, line);
	if(cfg_cur.hs==HSB_EN){
		send_line(port_fd, "    hot standby state: enable\r\n");
	}else{
		send_line(port_fd, "    hot standby state: disable\r\n");
	}
	send_line(port_fd, "\r\n");
}

static void save()
{
	save_config();
}

static void change_pwd()
{
	char line[16];
	char line1[16];
	
	memset(line, 0, sizeof(line));
	memset(line1, 0, sizeof(line1));

	send_line(port_fd, "enter new password: \r\n>");
	read_line(port_fd, line, sizeof(line)-1, 1);
	send_line(port_fd, "enter new password again: \r\n>");
	read_line(port_fd, line1, sizeof(line1)-1, 1);
	if(strcmp(line, line1) != 0){
		send_line(port_fd, "two passwords you entered is not same\r\n");
		send_line(port_fd, "\r\n");
		return;
	}
	
	memcpy(password, line, 16);	
	save_password();
	
	send_line(port_fd, "password has been changed successfully\r\n");
	send_line(port_fd, "\r\n");
}

static void quit()
{
	reset_config();
}

static void config()
{
	char sel[16];
	int s;
	
	s = 0;
	menu();
	send_line(port_fd, ">>");
	while(s != 6){
		read_line(port_fd, sel, sizeof(sel)-1, 0);
		send_line(port_fd, "\r\n");
		s = strtol(sel,0,0);
		switch(s){
			case 1:
				set_station();			
				break;
			case 2:
				set_state();		
				break;
			case 3:
				show();			
				break;
			case 4:
				change_pwd();			
				break;
			case 5:
				save();			
				break;
			case 6:
				quit();
				break;
			default:
				menu();
				s=0;
		}
		send_line(port_fd, ">>");
	}
}
 
static int cfg_main()
{
	port_fd = open_port(PORT);
	if(port_fd == -1){
		printf("Open port Error\n");		
		return -1;
	}
	send_line(port_fd, "config start!\n");	

	load_password();
	load_config();

	while(1){
		check_password();
		config();
	}

	close_port(port_fd);
	
	return 0;
}

int cfg_start()
{
	int id;
	id = taskSpawn(
		"cfg_main",	/* name */
		255,			/* priority */
		VX_FP_TASK,		/* options */
		8*1024,		/* stack size */
		cfg_main,	/* entry point */
		0,
		0,0,0,0,0,0,0,0,0	/* arg 2 ~ 10 */
		);

	return 0;
}
