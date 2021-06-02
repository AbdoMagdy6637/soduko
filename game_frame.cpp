#include "game_frame.h"
#include <fstream>
#include <string>
#include "score.h"

game_frame::game_frame(int width, int height) {
    boredTex.loadFromFile("bored.png");
    bored.setTexture(boredTex);
    bored.setPosition(0, 0);
    bored.setScale(2, 2);
    font.loadFromFile("consola.ttf");

    Focus.setSize(Vector2f(45, 48));
    Focus.setFillColor(Color::Green);
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            nums[j][i].setFont(font);
            nums[j][i].setFillColor(Color::Blue);
            nums[j][i].setCharacterSize(30);
            nums[j][i].setPosition(46 * i + 32, 46 * j + 25);
            nums[j][i].setString(" ");
            nums[j][i].Bold;
        }
    }
}

int rank1 = 0; //save rank

int game_frame::save_file(int save_time, string game_diff) {

    int counter = 0;
    string curr_time;
    string file_name = game_diff;
    curr_time = save_time;

    if (file_name == "") {
        file_name = "easy";
    }
    cout << "game_diff is " << file_name << endl;

    /*****************open file***************/
    ofstream fs("texts/" + file_name + "/" + file_name + ".txt", std::ios_base::app | std::ios_base::in);
    if (fs.is_open()) {
        fs << "time : " << save_time << "\t" << "game difficulty : " << file_name << endl;
    }
    fs.close();
    /*****************close file***************/

    string number;
    /*****************open file***************/
    ifstream myfile;
    myfile.open("texts/" + file_name + "/" + file_name + ".txt");

    if (!myfile.is_open()) {
        perror("Error open");
        exit(EXIT_FAILURE);
    }

    vector < std::pair < int, string >> saveHighScore; // save score inside vextor

    while (getline(myfile, number)) {

        string scoreTime = "";
        string scoreName = "";
        counter++;

        if (number.find("easy") != string::npos) {
            scoreName = "easy";
        }

        else if (number.find("medium") != string::npos) {
            scoreName = "medium";
        }

        else if (number.find("hard") != string::npos) {
            scoreName = "hard";
        }

        for (int i = 0; i < number.length(); i++) {
            if (isdigit(number.at(i))) {
                scoreTime += number[i];
            }
        }

        int sTime = stoi(scoreTime); // convert to number
        saveHighScore.push_back(std::make_pair(sTime, scoreName));
    }
    /*****************close file***************/
    sort(saveHighScore.begin(), saveHighScore.end());//sort vector

    /***************top10 save****************/
    if (saveHighScore.size() < 10) {
        int rank = 0;
        ofstream fs("texts/" + file_name + "/" + file_name + "Top.txt");

        for (int i = 0; i < saveHighScore.size(); i++) {

            cout << "time : " << saveHighScore[i].first << "\t" << "game difficulty : " << saveHighScore[i].second << endl;

            if (fs.is_open()) {
                fs << saveHighScore[i].first << "\t" << saveHighScore[i].second << endl;
                if (saveHighScore[i].first == save_time) {
                    rank = i + 1;
                }
            }

        }
        rank1 = rank;
        cout << "rank :" << rank1;
        fs.close();

    }/***************top10 save****************/
    else {/***************normal save****************/
        int rank = 0;
        ofstream fs("texts/" + file_name + "/" + file_name + "Top.txt");

        for (int i = 0; i < 10; i++) {
            cout << saveHighScore[i].first << "\t" << saveHighScore[i].second << endl;

            if (fs.is_open()) {
                fs << "time : " << saveHighScore[i].first << "\t" << "game difficulty : " << saveHighScore[i].second << endl;
                if (saveHighScore[i].first == save_time) {
                    rank = i + 1;
                }
            }

        }
        rank1 = rank;
        cout << "your rank :" << rank1;
        fs.close();
        
    }

    cout << endl;
    return save_time;
}

int game_frame::check_finish(int sec, string game_diff) {
    string a;
    int k = 0;
    //cout << "done";
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            a = nums[i][j].getString();
            if (a != " ") {
                k++;
            }
        }
    }
    if (k == 81) {
        save_file(sec, game_diff);
        //cout << "saved k "<<k << endl;
        k += 1;
    }
    //cout<<k<<endl;
    return sec;
}

void game_frame::set_solve(string game_diff) {
    if (game_diff == "") {
        game_diff = "easy";
    }

    ifstream infile("texts/" + game_diff + "/" + game_diff + "solved.txt");

    if (infile.good()) {
        string sLine;
        getline(infile, sLine);

        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                nums[i][j].setString((char)sLine[j + i * 9]); //fill all sudoku parts
            }
        }
    }

    infile.close();

}
void game_frame::set_num(int x, int y) {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (x + 32 > nums[j][i].getPosition().x && x + 32 < nums[j][i].getPosition().x + 46) {
                if (y + 25 > nums[j][i].getPosition().y && y + 25 < nums[j][i].getPosition().y + 46) {

                    Focus_Pos.x = j;
                    Focus_Pos.y = i;

                }
            }
        }
    }
}
RectangleShape game_frame::get_Focus() {
    Focus.setPosition(Vector2f(nums[Focus_Pos.x][Focus_Pos.y].getPosition().x - 12, nums[Focus_Pos.x][Focus_Pos.y].getPosition().y - 8));
    return Focus;
}
void game_frame::set_Text(int j, int i, char c, string s, string game_diff) {
    nums[j][i].setString(c);
    //cout << "add number\n";

    string a;
    int k = 0;

    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            a = nums[i][j].getString();
            if (a != " ") {
                k++;
            }
        }
    }
    if (k != 81) {
        check_finish(std::stoi(s), game_diff);
        k += 1;
    }
    cout << game_diff << endl;
    //cout << "k : " << k << endl;
}
Text game_frame::get_Text(int j, int i) {
    return nums[j][i];
}
Sprite game_frame::get_Num() {
    return bored;
}
void game_frame::set_Easy() {

    ifstream infile("texts/easy/easysolved.txt");

    if (infile.good()) {
        string sLine;
        getline(infile, sLine);

        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                nums[i][j].setString(" ");
            }
            for (int k = 0; k < 2; k++) {
                int iRand = (rand() % 8) + 0;
                nums[i][iRand].setString((char)sLine[iRand + i * 9]);

            }
        }
    }

    infile.close();
}
void game_frame::set_Mid() {
    ifstream infile("texts/medium/mediumsolved.txt");

    if (infile.good()) {
        string sLine;
        getline(infile, sLine);

        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                nums[i][j].setString(" ");
            }
            for (int k = 0; k < 3; k++) {
                int iRand = (rand() % 8) + 0;
                nums[i][iRand].setString((char)sLine[iRand + i * 9]);

            }
        }
    }

    infile.close();
}
void game_frame::set_Hard() {
    ifstream infile("texts/hard/hardsolved.txt");

    if (infile.good()) {
        string sLine;
        getline(infile, sLine);

        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                nums[i][j].setString(" ");
            }
            for (int k = 0; k < 4; k++) {
                int iRand = (rand() % 8) + 0;
                nums[i][iRand].setString((char)sLine[iRand + i * 9]);

            }
        }
    }

    infile.close();
}
string game_frame::set_Rank() {
    return to_string(rank1);
}
game_frame::~game_frame() {

}