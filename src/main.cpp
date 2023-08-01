/*==================================================================================*/
/*                                                                                  */
/* BBBBB   U     U   L      L        EEEEE   TTTTTT                                 */
/* B   B   U     U   L      L        E          T                                   */
/* BBBB    U     U   L      L        EEEE       T                                   */
/* B   B   U     U   L      L        E          T                                   */
/* BBBBB    UUUUU    LLLLL  LLLLL    EEEEE      T                                   */
/*                                                                                  */
/*                                                                                  */
/*PPPPP   RRRRR        OOOOOOO   OOOOOOO   FFFFF                                    */
/*P   P   R    R       O     O   O     O   F                                        */
/*PPPPP   RRRRRR       O     O   O     O   FFF                                      */
/*P       R     R      O     O   O     O   F                                        */
/*P       R      R     OOOOOOO   OOOOOOO   F                                        */
/*==================================================================================*/
/*BulletProof Is A Game That Where You're A Bullet And Have To Avoid Walls.         */
/*But You Only Can Move Up And Down. Also, Walls Have A Little Hole In Them.        */
/*You Have To Go Form Hole To Get Score.                                            */
/*==================================================================================*/
/*Main Rules :                                                                      */
/*Press 'KEY_W' Or 'KEY_UP' (Raylib Button Values : 87 Or 265) To Move Up.          */
/*Press 'KEY_S Or 'KEY_DOWN' (Raylib Button Values : 83 Or 264) To Move Down.       */
/*Avoid Brown Areas To Get Score.                                                   */
/*==================================================================================*/
/*Developer : ~cMard                                                                */
/*==================================================================================*/


//It's My First Game With C++ GUI(Raylib)!



//Main Code : 


//Libraries
#include <raylib.h>  //Raylib Library For Sprites, GUI, Textures, Audio And More
#include <iostream>  //Input-Output Stream For Debuging
#include <string>    //String Library For Using Functions Like ".c_str" And More
#include <vector>    //Vector Library To Store Elements
#include <algorithm> //Algorithm Library To Acces Functions For Vectors And More


using std::vector;
using std::sort;
using std::string;
//Ignore If There's Warning
//Comment Those Lines If It Gives Error
//Use This Instead : 
//using namespace std;


//Ball Class For Spawning, Moving And More For Bullet/Player
class Ball
{
public:
    Ball(); //Function To Start
    void Update(); //Updating Position Of Ball
    void Draw(Texture2D texture); //Drawing Ball On Screen

    
    //Coordinates, Speeds And Radius For Player
    int x;
    int y;
    int speedY;
    int radius;
};



//Functions For Player Here : 
Ball::Ball() //Initializing Player
{
    //Setting Postition, Speed And Radius Of Player/Bulletmm
    x = 100;
    y = 300;
    speedY = 6;
    radius = 30;
}

void Ball::Update()
{
    //If Key 'KEY_W' Or 'KEY_UP' Is Down(Down For Holding)
    if(IsKeyDown(KEY_W) || IsKeyDown(KEY_UP)) {
        y -= speedY; //Go Up
    }
    //If Key 'KEY_S' Or 'KEY_DOWN' Is Down(Down For Holding)
    if(IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN)) {
        y += speedY; //Go Down
    }

    //If Player Tries To Go Out Of Screen
    if (y + radius >= GetScreenHeight() || y - radius <= 0) {
        //Change Position To Other Side Of Screen
        if(y + radius >= GetScreenHeight() + 5) {
            y = radius + 1;
        }
        else if(y - radius <= -5) {
            y = GetScreenHeight() - radius - 1;
        }
    }
}


//Draw Texture For Player/Bullet
void Ball::Draw(Texture2D texture)
{
    //Make Circle's Color Blank
    //Meaning That It's Transparent And Only Has A Collider
    DrawCircle(x, y, radius, BLANK);
    DrawTexture(texture,  x - radius, y - radius, WHITE);
}


//Enemy Class For Walls
class enemy {
    public : 
        //Score For Player Showing How Many Walls It Passed
        int score = 0;

        //X And Y Positions For Wall
        int x = 600, y;

        //Set Speed To 5 When Starting
        int speed = 5;

        //Wall Variables
        Rectangle enemy1, enemy2;

        //Spawning Walls
        void spawn() {
            //Change Random's Seed To Time
            //So Rand() Will Always Return A Different Number
            srand(time(NULL));
            
            //Get Y As Random Until It's Betwewn 200 And 60
            do {
                y = rand();
            } while(y > 200 || y < 60);

            //Walls Have 3 Main Positions/Cases
            //Case 'A' : Y Is Between 60 Andsssdddsaw 100
            if(y >= 60 && y <= 100) {
                //Hole On Wall Will Be On The Center Of Them
                enemy1 = {float(x), 0, 30, float(400-y)};
                enemy2 = {float(x), float(400+y), 30, float(400-y)};
                //Attaching Them To A Rectangle To See If Player Collide With Them

                //Draw Walls On Screen
                //Every Time Height, Width, x And y Could Be A Weird Number That It Supposed To Be
                //That's What Makes These Cases Different
                DrawRectangle(x , 0, 30 , 400-y, RED);
                DrawRectangle(x , 400+y, 30 , 400-y, RED);
            }
            //Case 'B' : Y Is Between 100 And 150
            else if(y >= 100 && 150 > y) {
                //Hole On Wall Will Be On The Top Of Them
                enemy1 = {float(x), 0, 30, float(400-2*y)};
                enemy2 = {float(x), float(400-y), 30, float(400+y)};
                //Attaching Them To A Rectangle To See If Player Collide With Them

                //Again Weird Numbers When Drawing Walls
                DrawRectangle(x , 0, 30 , 400-2*y, RED);
                DrawRectangle(x , 400-y, 30 , 400+y, RED);
            }
            //The Last Case 'C' : Y Is More Than 150 (Actually Between 150 And 200)
            else {
                //Hole On Wall Will Be On The Bottom Of Them
                enemy1 = {float(x), 0, 30, float(400+y)};
                enemy2 = {float(x), float(400+2*y), 30, float(400-2*y)};
                //Attaching Them To A Rectangle To See If Player Collide With Them


                //Again Weird Numbers When Drawing Walls
                DrawRectangle(x , 0, 30 , 400+y, RED);
                DrawRectangle(x , 400+2*y, 30 , 400-2*y, RED);
            }
        }

        //Check If You Mut Spawn Walls Or Move Walls
        void check() {
            //If Enemy Is Out Of Screen
            if(enemy1.x < 0) {
                //Make Score Higher
                score += 1;
                //Spawn New Walls
                spawn();
            }
            //If Enemy Is On Screen
            else {
                //Make Them Go Left
                enemy1.x -= speed;
                enemy2.x -= speed;
                //Draw Them Again
                DrawRectangle(enemy1.x, enemy1.y, 30, enemy1.height, BROWN);
                DrawRectangle(enemy2.x, enemy2.y, 30, enemy2.height, BROWN);
            }

        }
};




//==================================================================================================================================================================================
//Main Function To Run On Start Of App
int main()
{
    //Variables : 
    
    //Background Color For Game
    Color darkGreen = Color{20, 160, 133, 255};

    //Vector That Stores Every Score To Select High Score
    vector<int> scores;

    //Make First Score '0' So High Score Way Will Not Be Empty
    scores.push_back(0);

    //Create Player
    Ball ball = Ball();

    //Check If Game Is Over Or Not
    bool gameIsOver = false;

    //Screen Dimensions
    const int screenWidth = 1000;
    const int screenHeight = 800;

    //Create Window With Given Dimensions And Name
    InitWindow(screenWidth, screenHeight, "BulletProof");

    //Start Audio Streaming
    InitAudioDevice();

    //Get Working Directory
    const char* gameDirectory = GetWorkingDirectory();

    //Get Game's Icon 
    string iconPath = string(gameDirectory) + "/icon.ico";

    //Get Music
    Music music = LoadMusicStream((string(gameDirectory) + "/Music.wav").c_str());
    //c_str Function Is Used To Turn C++ String To C Stle String : 
    //c_str : string -> const char*



    //Get Death Sound
    Sound deathSound = LoadSound((string(gameDirectory) + "/lastSound.wav").c_str());

    //Button Sound
    Sound buttonSound = LoadSound((string(gameDirectory) + "/ButtonSound.wav").c_str());

    //Load Icon
    Image icon = LoadImage(iconPath.c_str());


    //Set Icon
    SetWindowIcon(icon);
    //This Line Compiles Succesfuly ,But App's Icon Does Not Change

    //Get Player's Image Path
    string imagePath = string(gameDirectory) + "/PlayerTransparent.png";

    //Get Background's Image Path
    string backgroundPath = string(gameDirectory) + "/Background.png";
    
    //Load Background Image
    Image backgroundImage = LoadImage(backgroundPath.c_str());

    //Load Image As Texture For Background
    Texture2D background = LoadTextureFromImage(backgroundImage);

    //Load Image From Path
    Image image = LoadImage(imagePath.c_str());

    //Change Size Of Image
    ImageResize(&image, 30*2, 30*2);

    //Load Image As Texture To Display On Screen 
    Texture2D texture = LoadTextureFromImage(image);

    //Set Game's Target FPS To 60
    SetTargetFPS(60);

    //Check If It's The First Time Enemy/Walls Come
    bool firstTime = true;

    //Create Enemy Object To Spawn Walls
    enemy a;

    //Play Main Music Of Game
    PlayMusicStream(music);

    //Variable To Store How Much Of Music Has Played
    float timePlayed = 0.0f; 

    //Check If Player Is On Main Menu
    bool onMenu = true;

    //=============================================================================================================================================================================
    //Main Loop Of Game That Will Loop Until User Quits(Like ALT+F4)
    while (!WindowShouldClose())
    {
        BeginDrawing(); //Begin Drawing Screen/Textures/Spites
        ClearBackground(darkGreen); //Make Bacground Dark Green
        DrawTexture(background, 0, 0, WHITE);
        //If Player Is On Main Menu
        if(onMenu) {
            //If Music Has Done
            if (timePlayed > 0.27) {
                //Replay Music
                StopMusicStream(music);
                PlayMusicStream(music);
            }


            //Make Music Continue Playing
            UpdateMusicStream(music);

            //Change TimePlayed
            timePlayed = GetMusicTimePlayed(music)/GetMusicTimeLength(music);

            //Main Menu Text And Button
            DrawText("BulletProof", 200, 100, 100, RED);
            DrawRectangle(400, 480, 150, 50, RED);
            DrawText("Start", 400, 480, 50, DARKGRAY);
            Rectangle btn = {400, 480, 150, 50};
            //Check If User Pressed 'Start' Button
            if(CheckCollisionPointRec(GetMousePosition(), btn) && IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
                //Make User Not To Be In Main Menu
                onMenu = false;

                //Start Game
                gameIsOver = false;

                //Stop Music And Replay
                StopMusicStream(music);
                timePlayed = 0.0f;
                PlaySound(buttonSound);
                PlayMusicStream(music);
            }
        }
        //if Game Is Not Over
        else if(!gameIsOver) {
            //Change The Time Music Played
            timePlayed = GetMusicTimePlayed(music)/GetMusicTimeLength(music);

            //Draw Bullet/Player On Screen
            ball.Draw(texture);

            //Replay If Music Stoped
            if (timePlayed > 0.27) {
                StopMusicStream(music);
                PlayMusicStream(music);
            }

            //Continue Music
            UpdateMusicStream(music);

            //Update Ball's Position According To User's Input
            ball.Update();

            //If User Is Not Entering For First Time
            if(!firstTime) {
                //Check Enemy's Case
                a.check();
            }
            else {
                //Spawn New Enemy/Walls
                a.spawn();
            }
            //To Make Game Harder We Run This Algorithm
            //If Score Is Not Zero And Dividible By 15
            if(a.score != 0 && a.score % 15 == 0) {
                //Make Enemies Faster 
                a.speed += 1;

                //Add 1 To Score 
                //If We Don't Enemy Will Be Fast Every Frame Until You Go To Hole On Wall
                a.score += 1;
            }
            //If Score Is Not Zero And Dividible By 35
            if(a.score != 0 && a.score % 35 == 0) {
                //Make Player/Bullet Faster
                ball.speedY += 1;

                //Add 1 To Score 
                //If We Don't Player Will Be Fast Every Frame Until You Go To Hole On Wall
                a.score += 1;
            }

            //Show Score And High Score On Screen
            DrawRectangle(680, 50, 200, 50, WHITE);
            DrawText("Score : ", 680, 0, 50, BLACK);
            DrawText(std::to_string(a.score).c_str(), 680, 50, 50, BLACK);
            DrawText("High Score : ", 680, 100, 50, BLACK);
            DrawRectangle(680, 150, 200, 50, WHITE);
            sort(scores.begin(), scores.end());
            DrawText(std::to_string(scores[scores.size() - 1]).c_str(), 680, 150, 50, BLACK);

            //It's Second Time And Not First Time Anymore
            firstTime = false;

            //Check If Player/Bullet Touches Walls
            if(CheckCollisionCircleRec(Vector2{ float(ball.x), float(ball.y) }, ball.radius, a.enemy1) || CheckCollisionCircleRec(Vector2{ float(ball.x), float(ball.y) }, ball.radius, a.enemy2)) {
                //Game Is Over And Player Goes To Death Scene
                gameIsOver = true;
                a.speed = 5;
                ball.speedY = 6;
                scores.push_back(a.score);
                StopMusicStream(music);
                timePlayed = 0.0f;
                PlaySound(deathSound);
            }
        }
        //Death Scene Is Here
        else {
            //Create Game Over, Score And High-Score Sign, Retry And Menu Buttons
            DrawText("Game Over!", 300, 100, 100, DARKGRAY);
            DrawRectangle(400, 480, 150, 50, RED);
            DrawText("Retry", 400, 480, 50, DARKGRAY);
            Rectangle btn = {400, 480, 150, 50};
            DrawRectangle(400, 380, 150, 50, RED);
            DrawText("Menu", 400, 380, 50, DARKGRAY);
            Rectangle btn2 = {400, 380, 150, 50};
            DrawText(("Last Score : " + std::to_string(a.score)).c_str(), 300, 530, 50, DARKGRAY);
            sort(scores.begin(), scores.end());
            DrawText(("High Score : " + std::to_string(scores[scores.size() - 1])).c_str(), 300, 580, 50, DARKGRAY);
            //If User Pressed Retry
            if(CheckCollisionPointRec(GetMousePosition(), btn) && IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
                //Start Game Over
                firstTime = true;
                gameIsOver = false;
                a.score = 0;
                timePlayed = 0.0f;
                PlaySound(buttonSound);
                StopMusicStream(music);
                PlayMusicStream(music);
            }
            //If User Pressed Menu
            if(CheckCollisionPointRec(GetMousePosition(), btn2) && IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
                //Go To Main Menu
                firstTime = true;
                gameIsOver = true;
                a.score = 0;
                timePlayed = 0.0f;
                PlaySound(buttonSound);
                StopMusicStream(music);
                PlayMusicStream(music);
                onMenu = true;
            }
        }
        //End Rendering Frame
        EndDrawing();
    }
    //Unload Everything Loaded In Memory
    UnloadSound(buttonSound);
    UnloadSound(deathSound);
    UnloadMusicStream(music);
    CloseAudioDevice();
    CloseWindow();


    //Exit Console
    return 0;
}
