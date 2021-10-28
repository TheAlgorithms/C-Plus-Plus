#include <ncurses.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <locale.h>
#include <pthread.h>
#include <semaphore.h>
#include <bits/stdc++.h>

// Map size
#define WIDHT 30
#define HEIGHT 15

// Initial enemies
#define N_ENEMIES 4

// Directions
#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3

// Colors
#define WALL_COLOR 1
#define ENEMY_COLOR 2
#define PLAYER_COLOR 3
#define TIMER_COLOR 4
#define INIT_COLOR 5

using namespace std;

int ch, op = 0;
int directions[4] = {0,1,2,3};
int stop = 1;										// stops=0 stops the threads
pair<int,int> p_coord;					//player position
vector<pair<int,int>> e_coord;	//enemies position
int points = 0;

sem_t screen;

// print game over screen
bool game_over(){
	char pressed_key;
	clear();
	move(0,0);
	printw("\n\t GAME OVER\n\n");
	printw("  PRESS ENTER TO RESTART\n");
	printw("\n\tPOINTS: %d\n      TOTAL ENEMIES: %d", (points*(int)e_coord.size()), (int)e_coord.size());
	printw("\n\n\tESC TO QUIT\n\n");
	refresh();
	pressed_key = getch();

	if (pressed_key == 27){
		return false;
	}

	return true;
}

//generate random changed directions
void rand_dir(){
	int values[4] = {0};
	int aux = rand()%4;
	//the fist rand
	values[aux] = 1;
	directions[0] = aux;
	//the two next
	for(int i=1; i<3; i++){
		while(values[aux] == 1){
			aux = rand()%4;
		}
		values[aux] = 1;
		directions[i] = aux;
	}
	//the last one
	for(int i=0; i<4; i++){
		if(values[i] == 0){
			values[i] = 1;
			directions[3] = i;
		}
	}
	return;
}

//Print one arrow
void print_arrow(int x, int y, int dir){
	if(dir == UP){
		mvaddstr(x, y, "↑");
	}else if(dir == DOWN){
		mvaddstr(x, y, "↓");
	}else if(dir == LEFT){
		mvaddstr(x, y, "←");
	}else{
		mvaddstr(x, y, "→");
	}
}

//print the arrows around the player
void print_dir(int x, int y){
	int flags[4] = {0};
	for(int i=0; i<(int)e_coord.size(); i++){
		if(e_coord[i].first == y){
			if(e_coord[i].second == (x-1)) flags[0] = 1;
			if(e_coord[i].second == (x+1)) flags[1] = 1;
		}
		if(e_coord[i].first == x){
			if(e_coord[i].second == (y-1)) flags[2] = 1;
			if(e_coord[i].second == (y+1)) flags[3] = 1;
		}
	}

	//up side
	if((x-1) > 0 && flags[0] == 0){
		print_arrow((x-1), y, directions[0]);
	}
	//down side
	if((x+1) <= HEIGHT && flags[1] == 0){
		print_arrow((x+1), y, directions[1]);
	}
	//up left
	if((y-1) > 0 && flags[2] == 0){
		print_arrow(x, (y-1), directions[2]);
	}
	//down side
	if((y+1) <= WIDHT && flags[3] == 0){
		print_arrow(x, (y+1), directions[3]);
	}
}

//delete arrows around the player
void delete_dir(int x, int y){
	//up side
	if((x-1) > 0){
		mvaddch((x-1), y, ' ');
	}
	//down side
	if((x+1) <= HEIGHT){
		mvaddch((x+1), y, ' ');
	}
	//up left
	if((y-1) > 0){
		mvaddch(x, (y-1), ' ');
	}
	//down side
	if((y+1) <= WIDHT){
		mvaddch(x, (y+1), ' ');
	}
}

//print map
void print_map(){
	clear();
	move(0,0);
	attron(COLOR_PAIR(WALL_COLOR));
	for(int i = 0; i < WIDHT+2; i++) addch('#');

	for(int i = 1; i <= HEIGHT; i++){
		mvaddch(i, 0, '#');
		mvaddch(i, WIDHT+1, '#');
	}

	move(HEIGHT+1, 0);

	for(int i = 0; i < WIDHT+2; i++) addch('#');
	attroff(COLOR_PAIR(WALL_COLOR));
	refresh();
	return;
}

//move player
void mov_player(int dir) {

	pair<int,int> past_coord;
	past_coord.first = p_coord.first;past_coord.second=p_coord.second;

	if(dir == directions[0]){//DOWN
		if (p_coord.second > 1)
			p_coord.second--;
	}else if(dir == directions[1]){//UP
		if(p_coord.second < HEIGHT)
			p_coord.second++;
	}else if(dir == directions[2]){//LEFT
		if(p_coord.first > 1)
			p_coord.first--;
	}else if(dir == directions[3]){//RIGHT
		if(p_coord.first < WIDHT)
			p_coord.first++;
	}

	for (int i = 0; i < (int)e_coord.size(); ++i){
		if (p_coord.first == e_coord[i].first && p_coord.second == e_coord[i].second){
			stop = 0;
			move(7,5);
			printw("**YOU WERE INFECTED**");
			move(8,2);
			printw("press any key to play again");
			refresh();
		}
	}
	//☬◈☫

	sem_wait(&screen);

	delete_dir(past_coord.second, past_coord.first);
	mvaddch(past_coord.second, past_coord.first, ' '); //erase last position;

	attron(COLOR_PAIR(PLAYER_COLOR));
	mvaddstr(p_coord.second, p_coord.first, "◈");
	attroff(COLOR_PAIR(PLAYER_COLOR));
	rand_dir();
	print_dir(p_coord.second, p_coord.first);
	refresh();

	sem_post(&screen);

	return;
}

//Move enemies
void mov_enemy(){

	srand(time(NULL));
	int dir_e = 0;

	for (int i = 0; i < (int)e_coord.size(); ++i){
		dir_e = rand()%2;
		sem_wait(&screen);
		mvaddch(e_coord[i].second, e_coord[i].first, ' '); //erase last position;

		if (dir_e==i){
			if (p_coord.second < e_coord[i].second) {
				e_coord[i].second--;
			}else{
				e_coord[i].second++;
			}
		}else{
			if (p_coord.first < e_coord[i].first) {
				e_coord[i].first--;
			}else{
				e_coord[i].first++;
			}
		}

		attron(COLOR_PAIR(ENEMY_COLOR));
		mvaddstr(e_coord[i].second, e_coord[i].first, "☫");
		attroff(COLOR_PAIR(ENEMY_COLOR));
		refresh();

		sem_post(&screen);
	}

	for (int i = 0; i < (int)e_coord.size(); ++i){
		if (p_coord.first == e_coord[i].first && p_coord.second == e_coord[i].second){
			stop = 0;
			move(7,5);
			printw("**YOU WERE INFECTED**");
			move(8,2);
			printw("press any key to play again");
			refresh();
		}
	}

}

/*
	Thread that controls player
*/
void* player_thread(void* var){

	while(op == 0 && stop != 0) {
		ch = getch();

		switch(ch) {
			case KEY_UP:
				mov_player(UP);
				break;

			case KEY_DOWN:
				mov_player(DOWN);
				break;

			case KEY_RIGHT:
				mov_player(RIGHT);
				break;

			case KEY_LEFT:
				mov_player(LEFT);
				break;

			case 27:
				op = 1;
				break;
			default:
				break;
		}
	}
	stop = 0;
	pthread_exit(NULL);
}

/*
	Timer thread
*/
void* timer_thread(void* var){
	int sec = 0, min = 0;
	while(stop){
		//bloco atomico
		sem_wait(&screen);
		attron(COLOR_PAIR(TIMER_COLOR));
		move(0, 3);
		printw("TIME - %02d:%02d", min, sec);
		refresh();
		attroff(COLOR_PAIR(TIMER_COLOR));
		sem_post(&screen);
		//fim do bloco
		sec++;
		points++;
		if(sec == 60){
			sec = 0;
			min++;
		}
		sleep(1);
	}
	pthread_exit(NULL);
}

/*
	Thread that controls enemies number, velocity and moviment
*/
void* enemy_thread(void* var){
	pair<int,int> ep;
	for (int i=0; i < N_ENEMIES; ++i){
		ep.first = rand()%(WIDHT-1)+1;
		ep.second = rand()%(HEIGHT-1)+1;
		if(ep.first == p_coord.first && ep.second == p_coord.second)
			i--;
		else
			e_coord.push_back(ep);
	}
	int cont = 0, velocidade = 1300000, p_flag=1;
	while(stop){
		if(cont%15 == 0){
			if (cont%30 == 0){
				while(p_flag){
					ep.first = rand()%(WIDHT-1)+1;
					ep.second = rand()%(HEIGHT-1)+1;
					if(ep.first != p_coord.first && ep.second != p_coord.second){
						e_coord.push_back(ep);
						p_flag = 0;
					}
				}
				p_flag = 1;
			}else{
				velocidade -= 100000;
			}
		}
		mov_enemy();
		usleep(velocidade);
		cont++;
	}pthread_exit(NULL);
}

int main (void) {

	//creates a semafor
	/*
	This semafor is used to garantee that only one thread will
	change the screen in the same time space preventing screen
	overlay bugs
	*/
	sem_init(&screen,0,1);

	//setlocale(LC_CTYPE,"C-UTF-8");
	setlocale (LC_ALL, "");
	//RANDOM SEED
	srand(time(NULL));

	initscr();   /* Start curses mode     */

	//Colors
	start_color();
	//        id            font color   bg color
	init_pair(WALL_COLOR, COLOR_YELLOW, COLOR_YELLOW);// Wall
	init_pair(ENEMY_COLOR, COLOR_RED, COLOR_BLACK);		// Enemies
	init_pair(PLAYER_COLOR, COLOR_GREEN, COLOR_BLACK);// Player
	init_pair(TIMER_COLOR, COLOR_WHITE, COLOR_BLACK);	// Timer
	init_pair(INIT_COLOR, COLOR_YELLOW, COLOR_BLACK);	// Message

	// Stops buffer
	cbreak();

	//initial message
	attron(COLOR_PAIR(INIT_COLOR));
	printw("           The real direction is what you see!\n");
	printw("         Don't trust in what you previously know!\n");
	printw(" Avoid the red enemies to make through the other side!\n\n");
	printw("           Press any key to open the gates...\n"); /* Print init message   */
	attroff(COLOR_PAIR(INIT_COLOR));
	refresh();

	//wait strart signal
	getch();
	curs_set(0);
	noecho();

	//activate key code
	keypad(stdscr, TRUE);

	//thread vars
	pthread_t timer;
	pthread_t player_t;
	pthread_t enemy_t;
	void *status_timer;
	void *status_player;
	void *status_enemy;

	// game loop
	do{
		// Starts game
		p_coord.first = 15;
		p_coord.second = 7;
		e_coord.clear();
		print_map();
		mov_player(-1);

		// Starts threads
		pthread_create(&timer, NULL, timer_thread, NULL);
		pthread_create(&player_t, NULL, player_thread, NULL);
		pthread_create(&enemy_t, NULL, enemy_thread, NULL);
		pthread_join(timer, &status_timer);
		pthread_join(enemy_t, &status_enemy);
		pthread_join(player_t, &status_player);

		stop = 1;
	}while(game_over());

	endwin();   					//End curses mode
	sem_destroy(&screen); // destroy semafor
	pthread_exit(NULL);		// exit threads
	return 0;
}
