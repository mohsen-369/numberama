#include <iostream>
#include <cstring>
#include <conio.h>
#include <fstream>
#include <chrono>
#include <thread>
using namespace std;

#define KEY_UP 72
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define KEY_DOWN 80
#define KEY_SPACE 32
#define KEY_ENTER 13

struct Player{
    char username[10];
    char password[8];
    int score;
    char score0[3];
};

struct Game{    
    char** table;
    int rows;
    int columns;
    Player player;
};
bool users(Player);
bool pass(Player);
void put_user(Player);
bool check(Game &, int, int, int, int);
bool continue_the_game(Game);
void welcome(int);
void welcome_1(int);
void first_choose(char &, int &);
void second_choose(char &, int &);
void zero_page(int&, Player &);
void first_page(int);
void random_table(Game &);
void keyboard(Game, char&, int&, int&, int&, int&);
void print_table(Game, int, int, int, int);
void save_game(Game);
bool is_user(Player);


int main(){

    Game game;
    Player player;
    int k = 1;
    welcome(k);
    char key;
    key = getch();
    while (key != KEY_ENTER){
        key = getch();
        first_choose(key, k);
    }
    system("CLS");
    zero_page(k, player);
    k = 1;
    first_page(k);
    key;
    key = getch();
    system("CLS");
    while (key != KEY_ENTER){
        key = getch();
        second_choose(key, k);
    }
    while (true){
        if (k == 4) break;
        int score = 0;
        int rows, columns;
        system("CLS");
        cout << "\n        number of the rows (2, 100) : ";
        cin >> rows ;
        cout << "\n        number of the columns (2, 100) : ";
        cin >> columns;
        char* numberama[rows];
        for (int i = 0; i < rows; i++)
            numberama[i] = new char [columns];
        game.table = numberama;
        game.rows = rows;
        game.columns = columns;
        int x1 = 0 ,y1 = 0;
        int x2 = 0, y2 = 1;
        random_table(game);
        print_table(game, x1, y1, x2, y2);
        while (continue_the_game(game)){
            system("CLS");
            print_table(game, x1, y1, x2, y2);
            key = getch();;
            while (key != KEY_ENTER) 
                keyboard(game, key, x1, y1, x2, y2);

            system("CLS");
            print_table(game, x2, y2, x1, y1);
            key = getch();
            while (key != KEY_ENTER) 
                keyboard(game, key, x2, y2, x1, y1);
  
            if (check(game, x1, y1, x2, y2)){
                score++;
                numberama[x1][y1] = numberama[x2][y2] = ' ';
                print_table(game, x1, y1, x2, y2);
            }
        }
        player.score = score;
        game.player = player;
        system("CLS");
        cout << "\033[34m" << "\n        your score is " << score << " !" << "\033[0m";
        return 0;
    }
}
void put_user(Player player){
    char users[999][100];
    ifstream user("users.txt");
    int i = 0;
    while(user.getline(users[i], 100)) i++;
    user.close();
    char name[100];
    strcpy(users[i], player.username);
    strcpy(users[i+1], player.password);
    for (int q = strlen(player.score0); q < 100; q++)
        users[i+2][q] = '\0';
    ofstream uuser("users.txt");
    for (int j = 0; j <= i+1; j++)
    uuser << users[j] << endl;
    uuser.close();
}
bool users(Player player){
    char users[999][100];
    ifstream user("users.txt");
    int u = 0;
    while(user.getline(users[u], 100)) u++;
    user.close();
    for (int i = 0; i < u; i+=2)
        if (strcmp(player.username, users[i]) == 0)
            return false;
    return true;
}
bool is_user(Player player){
    char users[999][100];
    ifstream user("users.txt");
    int u = 0;
    while(user.getline(users[u], 100)) u++;
    user.close();
    for (int i = 0; i < u; i+=2)
        if (strcmp(player.username, users[i]) == 0)
            return true;
    return false;
}
bool pass(Player player){
    char users[999][100];
    ifstream user("users.txt");
    int u = 0;
    while(user.getline(users[u], 100)) u++;
    user.close();
    for (int i = 0; i < u; i+=2)
        if (strcmp(player.username, users[i]) == 0)
            if (strcmp(player.password, users[i+1]) == 0) 
                return true;
    return false;
}

void second_choose(char &key, int &k){
    switch (key){
        case KEY_DOWN:
            k++;
            if (k == 4) k = 1;
            first_page(k);
            break;
        case KEY_UP:
            k--;
            if (k == 0) k = 3;
            first_page(k);
            break;
        default:
            break;
    }
}

void zero_page(int &k, Player &player){
    switch (k){
        case 1:
            while (true){
                cout << "\n        Write your username :  ";
                //cin.ignore();
                cin >> player.username;
                if (users(player)) break;
                cout << "\n        This username is already exist, try another one\n";
            }
            cout << "\n        Create your password **must be 8 characters**  :  ";
            while (true){
                cin >> player.password;
                if (strlen(player.password) != 8){
                    cout << "\n        Password must be 8 characters :)  ";
                    continue;
                }
                cout << "\n        Your acount created successfully !!";
                put_user(player);
                break;
            }      
            break;
        case 2:
            while (true){
                cout << "\n        Enter your username :  ";
                cin >> player.username;
                if (is_user(player)) break;
                cout << "\n        This username is not exist :)\n";
            }
            while (true){
                cout << "\n        Enter your password :  ";
                cin >> player.password;
                if (pass(player)) break;
                cout << "\n        Password is incorrect\n";
            }
            break;
        default:
            break;
    }

}

void first_choose(char &key, int &k){
    switch (key){
        case KEY_DOWN:
            k++;
            if (k == 3) k = 1;
            welcome_1(k);
            break;
        case KEY_UP:
            k--;
            if (k == 0) k = 2;
            welcome_1(k);
            break;
        default:
            break;
    }
}

void random_table(Game &game){
    srand(time(0));
    for (int i = 0; i < game.rows; i++)
        for (int j = 0; j < game.columns; j++)
            game.table[i][j] = rand() % 9 + 49;
}

void first_page(int k){
    system("CLS");
    if (k == 1)
        cout << "\033[95m";
    cout << "        New game\n\n";
    cout << "\033[0m";
    if (k == 2)
        cout << "\033[95m";
    cout << "        See the scoreboard\n\n";
    cout << "\033[0m";
    if (k == 3)
        cout << "\033[95m";
    cout << "        Exit :(\n\n";
    cout << "\033[0m" << endl << endl;
}

bool check(Game &game, int x1, int y1, int x2, int y2){
    if (x1 == x2 && y1 > y2){
        y1 = y1 + y2;
        y2 = y1 - y2;
        y1 = y1 - y2;
    }
    if (y1 == y2 && x1 > x2){
        x1 = x1 + x2;
        x2 = x1 - x2;
        x1 = x1 - x2;
    }
    if (game.table[x1][y1] == game.table[x2][y2] || game.table[x1][y1] + game.table[x2][y2] == 106){
        if (x1 == x2){
            int y = y1 + 1, x = x1;
            while(game.table[x][y] == ' ')
                y++;
            if (y == y2)
                return true;
        }
        if (y1 == y2){
            int x = x1 + 1, y = y1;
            while(game.table[x][y] == ' ')
                x++;
            if (x == x2)
                return true;
        } 
    }       
    return false;
}

bool continue_the_game(Game game){
    for (int i = 0; i < game.rows; i++)
        for (int j = 0; j < game.columns - 1; j++){
            if (game.table[i][j] != ' '){
                int x = i, y = j + 1;
                while (game.table[x][y] == ' ' && y < game.columns)
                    y++;
                if (y < game.columns && (game.table[i][j] == game.table[i][y] || game.table[i][j] + game.table[i][y] == 106))
                    return true;   
            }
        }
    for (int i = 0; i < game.rows - 1; i++)
        for (int j = 0; j < game.columns; j++){
            if (game.table[i][j] != ' '){
                int x = i + 1, y = j;
                while (game.table[x][y] == ' ' && x < game.rows)
                    x++;
                if (x < game.rows && (game.table[i][j] == game.table[x][j] || game.table[i][j] + game.table[x][j] == 106))
                    return true;   
            }
        }
    return false;
}

void sleep(){	
	using namespace this_thread;
    using namespace chrono;
    sleep_for(milliseconds(50));
}

void sleep1(){	
	using namespace this_thread;
    using namespace chrono;
    sleep_for(milliseconds(1000));

}

void welcome(int k){
    //system("CLS");
    char a[100] = "        Welcome to Numberama game !!!";
    int i = 0;
    while (a[i] != 0){
        cout << a[i];
        i++;
        sleep();
    }
    cout << endl << endl << endl;    
    sleep1();
    char b[100] = "        New player";
    i = 0;
    if (k == 1)
        cout << "\033[95m";
    while (b[i] != 0){
        cout << b[i];
        i++;
        sleep();
    }
    cout << "\033[0m" << endl << endl;
    sleep1();
    if (k == 2)
        cout << "\033[95m";
    char c[100] = "        Have an acount";
    i = 0;
    while (c[i] != 0){
        cout << c[i];
        i++;
        sleep();
    }
    cout << "\033[0m" << endl << endl;
}

void welcome_1(int k){
    system("CLS");
    cout << "        Welcome to Numberama game !!!\n\n\n";
    if (k == 1)
        cout << "\033[95m";
    cout << "        New player\n\n" << "\033[0m";
    if (k == 2)
        cout << "\033[95m";
    cout << "        Have an acount\n\n" << "\033[0m" << endl << endl;
}

void print_table(Game game, int x1, int y1, int x2, int y2){
    int x = 0, y = 0;
    for (int i = 1; i <= 51; i++) cout << ' ';
    cout << (char)201;
    for (int i = 1; i <= game.columns-1; i++) cout << (char)205 << (char)205 << (char)205 << (char)203;
    cout << (char)205 << (char)205 << (char)205 << (char)187 << endl;
    for (int i = 1; i <= 51; i++) cout << ' ';
    for (int i = 1; i <= game.columns; i++){
        cout << (char)186;
        if ((x == x1 && y == y1) && (game.table[x][y] == ' ')) cout << ' ' << "\033[31m" << '!' << ' ' << "\033[0m";
        else if (x == x1 && y == y1) cout << ' ' << "\033[31m" << game.table[x][y] << ' ' << "\033[0m";
        else if (x == x2 && y == y2) cout << ' ' << "\033[32m" << game.table[x][y] << ' ' << "\033[0m";
        else cout << ' ' << game.table[x][y] << ' ';
        y++; 
    }
    cout << (char)186 << endl;
    x = 1;
    for (int i = 1; i <= game.rows-1; i++){
        for (int i = 1; i <= 51; i++) cout << ' ';
        cout << (char)204;
        for (int j = 1; j <= game.columns-1; j++) cout << (char)205 << (char)205 << (char)205 << (char)206;
        cout << (char)205 << (char)205 << (char)205 << (char)185 << endl;
        for (int i = 1; i <= 51; i++) cout << ' ';
        y = 0;
        for (int j = 1; j <= game.columns; j++){
            cout << (char)186;
            if ((x == x1 && y == y1) && (game.table[x][y] == ' ')) cout << ' ' << "\033[31m" << '!' << ' ' << "\033[0m";
            else if (x == x1 && y == y1) cout << ' ' << "\033[31m" << game.table[x][y] << ' ' << "\033[0m";
            else if (x == x2 && y == y2) cout << ' ' << "\033[32m" << game.table[x][y] << ' ' << "\033[0m";
            else cout << ' ' << game.table[x][y] << ' ';
            y++; 
        }
        x++;
        cout << (char)186 << endl;
    }
    for (int i = 1; i <= 51; i++) cout << ' ';
    cout << (char)200;
    for (int i = 1; i <= game.columns-1; i++) cout << (char)205 << (char)205 << (char)205 << (char)202;
    cout << (char)205 << (char)205 << (char)205 << (char)188 << endl << endl;  
}

void keyboard(Game game, char &key, int &x1, int &y1, int &x2, int &y2){
    key = getch();
    switch (key){
        case KEY_UP:
            x1--;
            if (x1 == -1) x1 = game.rows-1;
            system("CLS");
            print_table(game, x1, y1, x2, y2);           
            break;
        case KEY_DOWN:
            x1++;
            if (x1 == game.rows) x1 = 0;
            system("CLS");
            print_table(game, x1, y1, x2, y2);           
            break;
        case KEY_RIGHT:
            y1++;
            if (y1 == game.columns) y1 = 0;

            system("CLS");
            print_table(game, x1, y1, x2, y2);           
            break;
        case KEY_LEFT:
            y1--;
            if (y1 == -1) y1 = game.columns-1;

            system("CLS");
            print_table(game, x1, y1, x2, y2);           
            break;
        default:
            break;
    }
}