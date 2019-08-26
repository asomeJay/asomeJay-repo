#include "tetris.h"

#include <string.h>

static struct sigaction act, oact;

int main(){
	int exit=0;
	time_t start, stop;
	double duration;

	initscr();
	noecho();
	keypad(stdscr, TRUE);	

	srand((unsigned int)time(NULL));
	recRoot = (RecNode*)malloc(sizeof(RecNode));
	recRoot->lv = -1;
	recRoot->score = 0;
	recRoot->f = field;
	constructRecTree(recRoot);

	while(!exit){
		clear();
		switch(menu()){
		case MENU_PLAY: play(); break;
		case MENU_EXIT: exit=1; break;
		case MENU_RANK: rank(); break;
		case MENU_R_PLAY: recommendedPlay();
		default: break;
		}
	}

	endwin();
	system("clear");
	return 0;
}

void InitTetris(){
	int i,j;

	for(j=0;j<HEIGHT;j++)
		for(i=0;i<WIDTH;i++)
			field[j][i]=0;
	for(i = 0; i < VISIBLE_BLOCKS;i++){
		nextBlock[i] = rand()%7;
	}

	recommend();
	blockRotate=0;
	blockY=-1;
	blockX=WIDTH/2-2;
	score=0;	
	gameOver=0;
	timed_out=0;

	DrawOutline();
	DrawField();
	DrawBlockWithFeatures(blockY,blockX,nextBlock[0],blockRotate);
	DrawNextBlock(nextBlock);
	PrintScore(score);

}

void DrawOutline(){	
	int i,j;
	/* 블럭이 떨어지는 공간의 태두리를 그린다.*/
	DrawBox(0,0,HEIGHT,WIDTH);

	/* next block을 보여주는 공간의 태두리를 그린다.*/
	move(2,WIDTH+10);
	printw("NEXT BLOCK");
	DrawBox(3,WIDTH+10,4,8);
	DrawBox(9,WIDTH+10, 4, 8);

	/* score를 보여주는 공간의 태두리를 그린다.*/
	move(16,WIDTH+10);
	printw("SCORE");
	DrawBox(16,WIDTH+10,1,8);
}

int GetCommand(){
	int command;
	command = wgetch(stdscr);
	switch(command){
	case KEY_UP:
		break;
	case KEY_DOWN:
		break;
	case KEY_LEFT:
		break;
	case KEY_RIGHT:
		break;
	case ' ':	/* space key*/
		/*fall block*/
		break;
	case 'q':
	case 'Q':
		command = QUIT;
		break;
	default:
		command = NOTHING;
		break;
	}
	return command;
}

int ProcessCommand(int command){
	int ret=1;
	int drawFlag=0;
	switch(command){
	case QUIT:
		ret = QUIT;
		break;
	case KEY_UP:
		if((drawFlag = CheckToMove(field,nextBlock[0],(blockRotate+1)%4,blockY,blockX)))
			blockRotate=(blockRotate+1)%4;
		break;
	case KEY_DOWN:
		if ((drawFlag = CheckToMove(field,nextBlock[0],blockRotate,blockY+1,blockX)))
		blockY++;	
		break;
	case KEY_RIGHT:
		if((drawFlag = CheckToMove(field,nextBlock[0],blockRotate,blockY,blockX+1)))
			blockX++;
		break;
	case KEY_LEFT:
		if((drawFlag = CheckToMove(field,nextBlock[0],blockRotate,blockY,blockX-1)))
			blockX--;
		break;
	default:
		break;
	}
	if(drawFlag) DrawChange(field,command,nextBlock[0],blockRotate,blockY,blockX);
	return ret;	
}

void DrawField(){
	int i,j;
	for(j=0;j<HEIGHT;j++){
		move(j+1,1);
		for(i=0;i<WIDTH;i++){
			if(field[j][i]==1){
				attron(A_REVERSE);
				printw(" ");
				attroff(A_REVERSE);
			}
			else printw(".");
		}
	}
}


void PrintScore(int score){
	move(17,WIDTH+11);
	printw("%8d",score);
}

void DrawNextBlock(int *nextBlock){
	int i, j;
	for( i = 0; i < 4; i++ ){
		move(4+i,WIDTH+13);
		for( j = 0; j < 4; j++ ){
			if( block[nextBlock[1]][0][i][j] == 1 ){
				attron(A_REVERSE);
				printw(" ");
				attroff(A_REVERSE);
			}
			else printw(" ");
		}
		move(10+i, WIDTH+13);
		for( j = 0; j < 4; j++){
			if( block[nextBlock[2]][0][i][j] == 1){
				attron(A_REVERSE);
				printw(" ");
				attroff(A_REVERSE);
			}
			else printw(" ");
		}
	}
}

void DrawBlock(int y, int x, int blockID,int blockRotate,char tile){
	int i,j;
	for(i=0;i<4;i++)
		for(j=0;j<4;j++){
			if(block[blockID][blockRotate][i][j]==1 && i+y>=0){
				move(i+y+1,j+x+1);
				attron(A_REVERSE);
				printw("%c",tile);
				attroff(A_REVERSE);
			}
		}

	move(HEIGHT,WIDTH+10);
}

void DrawBox(int y,int x, int height, int width){
	int i,j;
	move(y,x);
	addch(ACS_ULCORNER);
	for(i=0;i<width;i++)
		addch(ACS_HLINE);
	addch(ACS_URCORNER);
	for(j=0;j<height;j++){
		move(y+j+1,x);
		addch(ACS_VLINE);
		move(y+j+1,x+width+1);
		addch(ACS_VLINE);
	}
	move(y+j+1,x);
	addch(ACS_LLCORNER);
	for(i=0;i<width;i++)
		addch(ACS_HLINE);
	addch(ACS_LRCORNER);
}

void play(){
	int command;
	clear();
	act.sa_handler = BlockDown;
	sigaction(SIGALRM,&act,&oact);
	InitTetris();
	do{
		if(timed_out==0){
			alarm(1);
			timed_out=1;
		}

		command = GetCommand();
		if(ProcessCommand(command)==QUIT){
			alarm(0);
			DrawBox(HEIGHT/2-1,WIDTH/2-5,1,10);
			move(HEIGHT/2,WIDTH/2-4);
			printw("Good-bye!!");
			refresh();
			getch();

			return;
		}
	}while(!gameOver);

	alarm(0);
	getch();
	DrawBox(HEIGHT/2-1,WIDTH/2-5,1,10);
	move(HEIGHT/2,WIDTH/2-4);
	printw("GameOver!!");
	refresh();
	getch();
	newRank(score);
}

char menu(){
	printw("1. play\n");
	printw("2. rank\n");
	printw("3. recommended play\n");
	printw("4. exit\n");
	return wgetch(stdscr);
}

int CheckToMove(char f[HEIGHT][WIDTH],int currentBlock,int blockRotate, int blockY, int blockX){
	int i, j;
	for(i = 0; i < 4; i++){ // Y
		for(j = 0; j < 4; j++){ // X
			if(block[currentBlock][blockRotate][i][j] == 1) {
				if(f[blockY+i][blockX+j] == 1) return 0;
				if(blockY + i >= HEIGHT) return 0;
				if(blockX + j < 0) return 0;
				if(blockX + j >= WIDTH) return 0;
			}
		}
	}
	return 1;
	// user code
}

void DrawChange(char f[HEIGHT][WIDTH],int command,int currentBlock,int blockRotate, int blockY, int blockX){
	int i, j;
	int rotate = blockRotate, y = blockY, x = blockX;
	switch(command){
	case KEY_UP:
		rotate = (rotate+3) % 4;
		break;
		
	case KEY_DOWN:
		y--;
		break;

	case KEY_LEFT:
		x++;
		break;

	case KEY_RIGHT:
		x--;
		break; 
	}
	for(i = 0; i < 4; i++){
		for(j = 0; j < 4 ; j++){
				if(block[currentBlock][rotate][i][j] == 1 && i+y>=0){// 쌓이기전 커맨드 입력전 브럭의 흔적을 지운다. 
				move(i +y+ 1, j +x+ 1);
				printw(".");
			}
		}
	}

	DrawField();
	DrawBlockWithFeatures(blockY, blockX, currentBlock, blockRotate);
	move(HEIGHT,WIDTH + 10);
	// user code
}


void BlockDown(int sig){
	int drawFlag = 0;
	int i;
	if(CheckToMove(field, nextBlock[0], blockRotate, blockY+1, blockX)){
		blockY++;
		DrawChange(field, KEY_DOWN, nextBlock[0], blockRotate, blockY, blockX);
		}

	else if(blockY == -1) gameOver = 1;

	else{
		score += AddBlockToField(field, nextBlock[0], blockRotate, blockY, blockX);
		score += DeleteLine(field);
		for(i = 0; i < VISIBLE_BLOCKS - 1; ++i){
			nextBlock[i] = nextBlock[i+1];
		}
		nextBlock[VISIBLE_BLOCKS - 1] = rand() % 7;
		blockRotate=0;
		blockY=-1;
		blockX=WIDTH/2-2;
		recommend();
		PrintScore(score);
		DrawNextBlock(nextBlock);
		DrawField();
		DrawBlockWithFeatures(blockY, blockX, nextBlock[0], blockRotate);
	}
	timed_out=0;

	// user code
}

int  AddBlockToField(char f[HEIGHT][WIDTH],int currentBlock,int blockRotate, int blockY, int blockX){
	int i, j, touched=0;
	for(i = blockY; i < blockY + 4; i++){
		for(j = blockX; j < blockX + 4; j++){
			if(block[currentBlock][blockRotate][i-blockY][j-blockX] == 1){
				f[i][j] = 1;
			
			if( i+1==HEIGHT || f[i+1][j] == 1){
			touched++;}
			}
		}
	}
	return touched * 10;
	// user code
}
int DeleteLine(char f[HEIGHT][WIDTH]){
	int i, j, count=0, temp;
	for(i = HEIGHT - 1; i > 0; i--){
		for(j = 0; j < WIDTH; j++)
			if(f[i][j] == 0) break;
		if(j == WIDTH)
			count++;
		else
			continue;  // j는 WIDTH와 같다

		for(j = 0; j < WIDTH; j++){
			f[i][j] = 0;;
		}

		for(; i > 0; i--){
			for(j = 0; j < WIDTH; j++){
				f[i][j] = f[i-1][j];
				if(f[i][j] == 0){
					move(i+1,j+1);
					printw(".");
				}
			}
		}
	
		i = HEIGHT - 1;
	}

	return count * 100 * count;
	// user code
}

void DrawShadow(int y, int x, int blockID,int blockRotate){
	int i, j;
	while(CheckToMove(field, blockID, blockRotate, ++y, x));
	if(y >= HEIGHT ) return;
	DrawBlock(--y, x, blockID, blockRotate, '/');
//	for(i = 0; i < 4; i++){
//		for(j = 0; j < 4; j++){
//			if(block[blockID][blockRotate][y][x] == 1 && field[y+1][x]==1){
//				move(i + y + 1, j + x + 1);
//				printw("/");
//			}
//	
//		}
//	}
}

void DrawRecommend() {
	if (CheckToMove(field, nextBlock[0], recommendR, recommendY, recommendX) == 1)
		DrawBlock(recommendY, recommendX, nextBlock[0], recommendR, 'R');
}
void DrawBlockWithFeatures(int y, int x, int blockID, int blockRotate){
	DrawRecommend();
	DrawShadow(y,x,blockID,blockRotate);
	DrawBlock(y,x,blockID,blockRotate,' ');
}

int recommend() {
	int ret;
	ret = recommendUsingTree(recRoot);
	return ret;
}
void constructRecTree(RecNode* root) {//재귀적으로 트리를 만듭니다. 루트(부모) 에서 재귀적으로 만듭니다. 
	int i, h;
	RecNode** c = root->c;
	for (i = 0; i < CHILDREN_MAX; ++i) {//일단 엄청 만듬. 최대 개수만큼..36//한층에 최대 모양*위치
		c[i] = (RecNode*)malloc(sizeof(RecNode));
		c[i]->lv = root->lv + 1;
		c[i]->f = (char(*)[WIDTH])malloc(sizeof(char) * HEIGHT * WIDTH);
		if (c[i]->lv < VISIBLE_BLOCKS) {//몇개까지 볼건지..
			constructRecTree(c[i]);
		}
	}
}

void destructRecTree(RecNode* root) {
	int i, h;
	RecNode** c = root->c;
	for (i = 0; i < CHILDREN_MAX; ++i) {
		if (c[i]->lv < VISIBLE_BLOCKS) {
			destructRecTree(c[i]);
		}
		free(c[i]->f);
		free(c[i]);
	}
}
//채우고 지우면서 상쇄.. 점수만 계산
int evalState(int lv, char f[HEIGHT][WIDTH], int r, int y, int x) {
	int i, j, k, count = 0, flag = 0, gift = 0;

	for(i = 0; i < HEIGHT; i++){
		for(j = 0; j < WIDTH; j++){
			if(f[i][j] == 1 && flag == 0){ 
				count = count + i * 5.5;
				flag = 1;	
			}
		}
		if(f[i][j] == 0)
			count = count+0.35;
	}

	
	return AddBlockToField(f, nextBlock[lv], r, y, x) + DeleteLine(f) + count;

}
int recommendUsingTree(RecNode* root) {

	int r, x, y, rBoundary, lBoundary, wts, wts_max = 0, wts_max2 = 0, wts_max3 = 0;
	int h, w;
	int eval;
	int max = 0;
	int solR, solY, solX;
	int recommended = 0;
	int i = 0;
	int lv = root->lv + 1;
	RecNode** c = root->c;
	for (r = 0; r < NUM_OF_ROTATE; ++r) {
		lBoundary = 3;
		for (h = 0; h < BLOCK_HEIGHT; ++h) {
			for (w = 0; w < BLOCK_WIDTH; ++w) {
				if (block[nextBlock[lv]][r][h][w]) {
					break;
				}
			}
			if (w < lBoundary) {
				lBoundary = w;
			}
		}
		lBoundary = 0 - lBoundary;
		rBoundary = 0;
		for (h = 0; h < BLOCK_HEIGHT; ++h) {
			for (w = BLOCK_WIDTH - 1; w >= 0; --w) {
				if (block[nextBlock[lv]][r][h][w]) {
					break;
				}
			}
			if (w > rBoundary) {
				rBoundary = w;
			}
		}

		rBoundary = WIDTH - 1 - rBoundary;

		for (x = lBoundary; x <= rBoundary; ++x, ++i) {
			for (h = 0; h < HEIGHT; ++h) {
				for (w = 0; w < WIDTH; ++w) {
					c[i]->f[h][w] = root->f[h][w];
				}
			}
			/* 현재 (r,x)에 대해 떨어질 수 있는 y를 구하기 */
			y = 0;
			if (CheckToMove(c[i]->f, nextBlock[lv], r, y, x)) {

				while (CheckToMove(c[i]->f, nextBlock[lv], r, ++y, x));

				--y;

			}

			else { /* 지금까지 구한 (r,x)에 대해 현재 레벨의 블럭이 놓일 곳 없음 */

				continue;

			}
			/* 지금까지 구한 (r,y,x)를 바탕으로,

			현재 레벨의 블럭을 field에 추가했을 때 얻을 수 있는 점수 */

			c[i]->score = root->score + evalState(lv, c[i]->f, r, y, x);
			spacet += sizeof(RecNode);
			if (lv > 0) {
				if (wts_max < c[i]->score) {
					wts_max = c[i]->score;
				}
				else if(wts_max2 < c[i]->score){
					wts_max2 = c[i]->score;
				}
				else if(wts_max3 < c[i]->score){
					wts_max3 = c[i]->score;
				}
				else
					continue;
			}
			if (lv < VISIBLE_BLOCKS - 1) {
				eval = recommendUsingTree(c[i]);
			}
			else {
				eval = c[i]->score;
			}
			if (max < eval) {
				recommended = 1;
				max = eval;
				solR = r;
				solY = y;
				solX = x;
			}
		}

	}
	if (lv == 0 && recommended) {
		recommendR = solR;
		recommendY = solY;
		recommendX = solX;
	}
	return max;
}

void insert(char nametmp[20], int scoretmp) { //링크드 리스트 핵심... 실습은 추가만 하는거라 insert만 구현합니다.
	count++;
	Node *new, *tmp, *pre;
	new = (Node *)malloc(sizeof(Node));
	/* Memory Allocation.*/
	//새로운 노드 new를 만든다.
	strcpy(new->name, nametmp);
	new->score = scoretmp;
	new->link = NULL;
	tmp = head;

	if (tmp == NULL){
		head = new;
	}// head가 비어있을 때
	else {
		if (tmp->score <= new->score) {	//맨 앞에 넣어야 할 때 tmp->link=null
			new->link = head;
			head = new;
		}
		else { 
			while(tmp->score > new->score){
				pre = tmp;
				tmp = tmp->link;
				if(tmp == NULL)
					break;
			}
			pre->link = new;
			new->link = tmp; 	
		}
	}
	return;
}
void createRankList(){
	FILE *fp;
	int num, i, scoretmp;
	char str[51], nametmp[NAMELEN];
	head = NULL;
	if((fp = fopen("rank.txt", "r"))==NULL){
		return ;
	}

	fscanf(fp, "%d", &num);
	user_num = num;
	fgetc(fp);
	for(i = 0; i < num; i++){
		fgets(str,50, fp);
		sscanf(str, "%s %d", nametmp, &scoretmp);
		insert(nametmp, scoretmp);
	}
	
	fclose(fp);
	// 구현한 자료구조에 따라서
	// 파일을 다 읽어들이면 됨.
	//엔터 먹을땐 fgetc(fp);
}

void rank(){
	int from=1, to, loop, i, del, flag = 1;
	char name[NAMELEN];
	Node *tmp;
	clear();
	move(0, 0);
	printw("1. list ranks from X to Y\n");
	printw("2. list ranks by a specific name\n");
	printw("3. delete a specific rank\n");
	switch(wgetch(stdscr)){
		case '1':
			createRankList();
			to = user_num;

			echo();
			printw("X: ");
			scanw("%d",&from);
			printw("Y: ");
			scanw("%d",&to);
			noecho();
			printw("       name       |   score   \n");
			printw("------------------------------\n");

			// 조건문 삽입 - 실습
			if (from < 0 || to < 0) {
				printw("search failure: no rank in the list\n");
				break;
			}
			else if (from > to) {
				printw("search failure: no rank in the list\n");
				break;
			}
			else if (from == 0 && to == 0) {
				tmp = head;
				while (tmp != NULL) {
					printw("%10s\t\t%8d\n", tmp->name, tmp->score);
					tmp = tmp->link;
				}
			}
			else {
				tmp = head;
				loop = to - from + 1;
				while(from > 1 && tmp != NULL){
					tmp = tmp->link;
					from--;
				}
				for(i = 0; i < loop && tmp != NULL; i++){
					printw("%10s\t\t%8d\n", tmp->name, tmp->score);
					tmp = tmp->link;
				}
				//여기서 print 하면됨.
			}
			break;
		case '2':
			flag = 0;
			printw("input the name: ");
			echo();
			getstr(name);
			noecho();
			printw("       name       |   score   \n");
			printw("------------------------------\n");
			createRankList();
			tmp = head;
			while(tmp != NULL){
				if(strcmp(tmp->name, name) == 0){
					printw("%10s\t\t%8d\n", tmp->name, tmp->score);
					flag = 1;
				}
				tmp = tmp->link;
			}
			// 조건문 삽입 - 과제
			if(tmp == NULL && flag == 0)
				printw("\nsearch failure: no name in the list\n");
			break;
		case '3':
			printw("input the rank: ");
			echo();
			scanw("%d",&del);
			noecho();
			// 조건문 삽입 - 과제
			createRankList();
			tmp = head;
			Node* pre;
			to = del;
			for(i = from; i < to; i++){
				if(tmp == NULL)
					break;
				
					pre = tmp;
					tmp = tmp->link;
			}			

			if(tmp != NULL && from <= to){
				if(del == 1)
					head = head->link;
				
				else
					pre->link = tmp->link;
		
				free(tmp);
				user_num--;
				writeRankFile();
				printw("\nresult: the rank deleted\n");	
			}
			else
				printw("\nsearch failure: the rank not in the list\n");
			
			break;
		default: break;
	}
	getch();
	// user code
}

void writeRankFile(){
	FILE *fp;
	Node *tmp;
	tmp = head;
	fp = fopen("rank.txt", "w");
	fprintf(fp, "%d\n", user_num);
	
	
	while(tmp != NULL){
		fprintf(fp, "%s %d\n", tmp->name, tmp->score);
		tmp = tmp->link;
	}
	
	fclose(fp);
	// rank.txt에 적절한 정보를 써줘야 함
	// 3                    랭킹정보의 개수 
	// gr120180187 1000     랭킹정보 ( 사용자 이름 , 점수 )
	// gr120180188 1001     랭킹정보 ( 사용자 이름 , 점수 )
	// gr120180189 1002     랭킹정보 ( 사용자 이름 , 점수 )
	//작성할곳
}

void newRank(int score){

	char nameTemp[NAMELEN];
	clear();
	printw("your name: ");
	echo();
	getstr(nameTemp);
	noecho();
	user_num++;

	insert(nameTemp, score);
	writeRankFile();
	//작성 새로운 정보를 링크드리스트에 집어넣고
	//writeRankFile 호출

}

void recommendedPlay(){
	// user code
	time_t start, stop;
	double duration;
	start = time(NULL);
	int command, command2;
	clear();
	act.sa_handler = BlockDown;
	sigaction(SIGALRM,&act,&oact);
	InitTetris();
	do{
		if(timed_out==0){
			alarm(1);
			timed_out=1;
		}
		move(25, WIDTH + 11);
		printw("time : %lf\n", duration);
		

		if(blockRotate != recommendR) command = KEY_UP;
		else if(blockX < recommendX) command = KEY_RIGHT;
		else if(blockX > recommendX) command = KEY_LEFT;
		else if(blockX == recommendX && blockRotate == recommendR) command = KEY_DOWN;
		command2 = wgetch(stdscr);
		if(ProcessCommand(command)==QUIT || command2 == 'q' || command2 == 'Q'){
			alarm(0);
			DrawBox(HEIGHT/2-1,WIDTH/2-5,1,10);
			move(HEIGHT/2,WIDTH/2-4);
			printw("Good-bye!!");
			refresh();
			DrawBox(0,0,HEIGHT,WIDTH);			getch();

			//newRank(score);
			return;
		}
		stop = time(NULL);
		duration = (double)difftime(stop, start);
		move(25, WIDTH+11);
		printw("time : %lf\n", duration);

	}while(!gameOver);

	alarm(0);
	getch();
	DrawBox(HEIGHT/2-1,WIDTH/2-5,1,10);
	move(HEIGHT/2,WIDTH/2-4);
	printw("GameOver!!");
	stop = time(NULL);
	duration = (double)difftime(stop, start);
	move(25, WIDTH + 11);
	printw("time : %lf\n", duration);
	move(26, WIDTH + 11);
	printw("score(t) : %lf\n", score);
	move(27, WIDTH + 11);
	printw("time(t) : %lf\n", duration);
	move(28, WIDTH + 11);
	printw("space(t) : %lf\n", spacet);
	move(29, WIDTH + 11);
	printw("time efficiency : %lf\n", (double)score / duration);
	move(30, WIDTH + 11);
	printw("space efficiency : %lf\n", (double)score / spacet);
	refresh();
	getch();
	newRank(score);
	// user code
}
