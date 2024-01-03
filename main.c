//IN GOD WE TRUST
//MINESWEEPER CODE

//TODO What??
//correction for near zero cells

//headers
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <Windows.h>
#include <mmsystem.h>

//functions prototypes
void welcome();
void guide_lines_and_profile();
void commanding_and_checking();
void open_menu();
void open_SOS();
void profile_info_printer();
void select_play_ground();
void resetting_shown_ground();
void resetting_shown_ground_16();
void arranging_secret_ground();
void arranging_secret_ground_16();
void random_maker_checker();
void random_maker_checker_16();
char extracting_char_of_decomposed_random(int index);
char convert_int_to_char(int should_be_converted);
void flipping_cell();
void flipping_cell_16(int x_axis, int y_axis);
char neighbor_counter(short x, short y);
void neighbor_counter_16(int x, int y);
void flagging_cell();
void flagging_cell_16();
void pulling_cell();
void pulling_cell_16();
void won_the_game();
void lost_the_game();
void shown_ground_printer();
void shown_ground_printer_16();
void secret_ground_printer();
void secret_ground_printer_16();
void reset_to_factory();
void play_winner_sound();
void play_explosion_sound();
void play_intro_sound();
void RED();
void GREEN();
void YELLOW();
void CYAN();
void PURPLE();
void WHITE();
void type_writer_printer(char must_be_printed[]);
void faster_type_writer_printer(char must_be_printed[]);

//structures
typedef struct
{
    char name[30];
    int how_much_played;
    int was_winner;
    int was_an_ass_loser;
} profile_type;
typedef struct
{
    char rows[20][70];
}play_ground;

//global variables
profile_type info;
play_ground shown_ground;
play_ground secret_ground;
play_ground shown_ground_16;
play_ground secret_ground_16;
unsigned int remaining_flags = 10;
unsigned int correct_flagged = 0;
unsigned int remaining_flags_16 = 40;
unsigned int correct_flagged_16 = 0;
unsigned int password_of_sudo = 7973;
int sudo_flag = 0;
int sixteen_ground_flag = 0;
int random_accepted[10];
int decomposed_random_accepted[20];
int random_accepted_16[40];
int decomposed_random_accepted_16[80];
int i = 0;
int m = 0;
int p = 0;
int s = 0;
char key_for_sudo[40];
                                                      //BUFFER_CHECKING  //SITUATION
//functions
void welcome()
{
    //prompt user a massage
    play_intro_sound();
    type_writer_printer("Hello dear user. Welcome to MineSweeper.\n");
    type_writer_printer("Read these guides to know how to play:\n");
}                                        //SAFE             //HEALTHY

void guide_lines_and_profile()
{
    //prompt user a massage
    YELLOW();
    type_writer_printer("First, Enter your name to make your profile:\n");
    WHITE();

    //getting username for profile and completing info
    fgets(info.name, 30, stdin);
    int size_of_username = strlen(info.name);
    info.name[size_of_username - 1] = '\0';
    info.how_much_played = 0;
    info.was_winner = 0;
    info.was_an_ass_loser = 0;

    //prompt user a massage
    faster_type_writer_printer("Each step, you have to command what you want based on menu.\n");
    faster_type_writer_printer("By the way, in the menu,");
    GREEN();
    faster_type_writer_printer("SOS command is for help.");
    WHITE();
    faster_type_writer_printer("I suggest to look it up for first.\n");
    printf("Good luck. :)\n\n");
}                        //SAFE             //HEALTHY

void commanding_and_checking()
{
    //linux copy for commanding shape
    if (sudo_flag == 1)
    {
        printf("%s (sudo):", info.name);
    }
    else
    {
        printf("%s:", info.name);
    }

    //getting order from user
    char command[4];
    PURPLE();
    scanf("%s", command);
    WHITE();
    //checking what user said and do what it wanted
    if      (strcmp(command, "1") == 0)
    {
        //it means SOS
        open_SOS();
    }
    else if (strcmp(command, "2") == 0)
    {
        //it means view profile
        profile_info_printer();
    }
    else if (strcmp(command, "3") == 0)
    {
        //it means wants to play
        faster_type_writer_printer("Ready to play? Select your map size:\n");
        select_play_ground();
    }
    else if (strcmp(command, "4") == 0)
    {
        //it means changing the name
        YELLOW();
        faster_type_writer_printer("Seems that you're boring from your name. Change it:\n");
        WHITE();
        scanf("%s", info.name);
        commanding_and_checking();
    }
    else if (strcmp(command, "CP") == 0)
    {
        if (sudo_flag)
        {
            CYAN();
            faster_type_writer_printer("Enter your new password please(only 9 digits):\n");
            WHITE();
            scanf("%d", &password_of_sudo);
        }
        else
        {
            RED();
            type_writer_printer("#Only my LORD can do this!\n");
            WHITE();
        }
        commanding_and_checking();
    }
    else if (strcmp(command, "seen") == 0)
    {
        //it means sudo wants to see secret ground
        if (sudo_flag == 1)
        {
            if (sixteen_ground_flag) secret_ground_printer_16();
            else secret_ground_printer();
        }
        else
        {
            RED();
            type_writer_printer("#Only my LORD can do this!\n");
            WHITE();
        }
        commanding_and_checking();
    }
    else if (strcmp(command, "menu") == 0)
    {
        //it means menu
        open_menu();
    }
    else if (strcmp(command, "EXIT") == 0)
    {
        //it means Exit
        exit(EXIT_SUCCESS);
    }
    else if (strcmp(command, "flag") == 0)
    {
        //it means flag a cell
        if (sixteen_ground_flag) flagging_cell_16();
        else flagging_cell();
    }
    else if (strcmp(command, "pull") == 0)
    {
        //it means pull the flag of a cell
        if (sixteen_ground_flag) pulling_cell_16();
        else pulling_cell();
    }
    else if (strcmp(command, "flip") == 0)
    {
        //it means flip a cell
        if (sixteen_ground_flag)
        {
            int x_axis;
            scanf("%d", &x_axis);
            int y_axis;
            scanf("%d", &y_axis);
            flipping_cell_16(y_axis, x_axis);
        }
        else flipping_cell();
    }
    else if (strcmp(command, "sudo") == 0)
    {
        //it means super doable mode is activated;
        int entered_password;
        scanf("%d", &entered_password);
        if (password_of_sudo == entered_password)
        {
            sudo_flag = 1;
            CYAN();
            type_writer_printer("#Welcome back Sir. :)\n");
            WHITE();
        }
        else
        {
            RED();
            faster_type_writer_printer("Wrong pass. Get out of here. :x\n");
            WHITE();
        }
        commanding_and_checking();
    }
    else if (strcmp(command, "ordo") == 0)
    {
        //it means super doable mode is off;
        int entered_password;
        scanf("%d", &entered_password);
        if (password_of_sudo == entered_password)
        {
            sudo_flag = 0;
        }
        else
        {
            RED();
            faster_type_writer_printer("Wrong pass. Get out of here. :x\n");
            WHITE();
        }
        commanding_and_checking();
    }
    else if (strcmp(command, "back") == 0)
    {
        //it means back to menu
        open_menu();
    }
    else
    {
        //input is meaningless
        if (sudo_flag == 1)
        {
            CYAN();
            type_writer_printer("#Sir, I couldn't understand your order. Can you say it again?\n");
            WHITE();
            commanding_and_checking();
        }
        else
        {
            RED();
            faster_type_writer_printer("WTF you said?! Pardon. :|\n");
            WHITE();
            commanding_and_checking();
        }
    }
}                        //WORM             //HEALTHY

void open_menu()
{
    //prompt user a massage
    if (sudo_flag == 1)
    {
        CYAN();
        type_writer_printer("#Your Majesty!\n");
        WHITE();
    }
    faster_type_writer_printer("(1)SOS   (2)View profile   (3)Play!   (4)Change profile name\n");
    commanding_and_checking();
}                                      //SAFE             //HEALTHY

void open_SOS()
{
    //prompt user a massage
    if (sudo_flag == 1)
    {
        CYAN();
        type_writer_printer("#Your Majesty, You don't need this. Cause you wrote me by your holy hands. :)\n");
        WHITE();
    }
    else
    {
        YELLOW();
        faster_type_writer_printer("Seems that you are confusing! here is the help. :)\n");
        WHITE();
    }
    faster_type_writer_printer("1. Flip a cell-----------------------> flip (x axis) (y axis)\n");
    faster_type_writer_printer("2. Flag a cell-----------------------> flag (x axis) (y axis)\n");
    faster_type_writer_printer("3. Pull up the flag of a cell--------> pull (x axis) (y axis)\n");
    faster_type_writer_printer("4. SuperDoable mode ON --------------> sudo (needs password)\n");
    faster_type_writer_printer("5. SuperDoable mode Off -------------> ordo (needs password)\n");
    faster_type_writer_printer("6. See bomb Planted ground-----------> seen (only for sudo)\n");
    faster_type_writer_printer("7. change password ------------------> CP   (only for sudo)\n");
    faster_type_writer_printer("8. Back to menu ---------------------> back\n");
    faster_type_writer_printer("9. Exit the program -----------------> EXIT\n");

    commanding_and_checking();
}                                       //SAFE             //HEALTHY

void profile_info_printer()
{
    //printing all profile data
    printf("Your name is %s.\n", info.name);
    printf("You have played %d time(s).\n", info.how_much_played);
    GREEN();
    printf("You have won %d time(s).\n", info.was_winner);
    RED();
    printf("You have lost %d time(s).\n", info.was_an_ass_loser);
    WHITE();

    //it analysis
    if (info.was_an_ass_loser < info.was_winner) type_writer_printer("I can smell some progress. :)\n");
    else if (info.was_an_ass_loser > info.was_winner) type_writer_printer("Are you Ok? :(\n");
    else if (info.was_an_ass_loser == info.was_winner && info.was_winner != 0 && info.was_an_ass_loser != 0)
        type_writer_printer("The Same?! come on! :|\n");
    printf("\n");
    commanding_and_checking();
}                           //SAFE             //HEALTHY

void select_play_ground()
{
    //prompt user a massage
    faster_type_writer_printer("(1)8*8 cells with 10 BOMBs!\t(2)16*16 cells with 40 BOMBs\n");

    //which map is wanted
    short ground_mok;
    if (sudo_flag == 1)
    {
        printf("%s (sudo):", info.name);
    }
    else
    {
        printf("%s:", info.name);
    }
    scanf("%hi", &ground_mok);
    if (ground_mok == 2)
    {
        //going to play 16*16
        reset_to_factory();
        sixteen_ground_flag = 1;
        shown_ground_printer_16();
    }
    if (ground_mok == 1)
    {
        //going to play 8*8
        reset_to_factory();
        shown_ground_printer();
    }
    else
    {
        RED();
        printf("Wrong input here!\n");
        WHITE();
    }
    commanding_and_checking();
}                             //SAFE             //HEALTHY

void resetting_shown_ground()
{
    //reset whole shown ground
    strcpy(shown_ground.rows[8], "8 * * * * * * * *");
    strcpy(shown_ground.rows[7], "7 * * * * * * * *");
    strcpy(shown_ground.rows[6], "6 * * * * * * * *");
    strcpy(shown_ground.rows[5], "5 * * * * * * * *");
    strcpy(shown_ground.rows[4], "4 * * * * * * * *");
    strcpy(shown_ground.rows[3], "3 * * * * * * * *");
    strcpy(shown_ground.rows[2], "2 * * * * * * * *");
    strcpy(shown_ground.rows[1], "1 * * * * * * * *");
    strcpy(shown_ground.rows[0], "  1 2 3 4 5 6 7 8");
}                         //SAFE             //HEALTHY

void resetting_shown_ground_16()
{
    //reset whole shown ground
    strcpy(shown_ground_16.rows[16], "16 *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *");
    strcpy(shown_ground_16.rows[15], "15 *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *");
    strcpy(shown_ground_16.rows[14], "14 *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *");
    strcpy(shown_ground_16.rows[13], "13 *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *");
    strcpy(shown_ground_16.rows[12], "12 *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *");
    strcpy(shown_ground_16.rows[11], "11 *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *");
    strcpy(shown_ground_16.rows[10], "10 *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *");
    strcpy(shown_ground_16.rows[9],  "9  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *");
    strcpy(shown_ground_16.rows[8],  "8  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *");
    strcpy(shown_ground_16.rows[7],  "7  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *");
    strcpy(shown_ground_16.rows[6],  "6  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *");
    strcpy(shown_ground_16.rows[5],  "5  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *");
    strcpy(shown_ground_16.rows[4],  "4  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *");
    strcpy(shown_ground_16.rows[3],  "3  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *");
    strcpy(shown_ground_16.rows[2],  "2  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *");
    strcpy(shown_ground_16.rows[1],  "1  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *  *");
    strcpy(shown_ground_16.rows[0],  "   1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16");
}                      //SAFE             //HEALTHY

void arranging_secret_ground()
{
    secret_ground = shown_ground;

    //decomposing of a number to X and Y
    for (int j = 0; j < 10; ++j)
    {
        int real_X = (random_accepted[j] % 8) + 1;
        int real_Y = (random_accepted[j] / 8) + 1;

        decomposed_random_accepted[s] = real_X;
        decomposed_random_accepted[s + 1] = real_Y;
        s += 2;
    }

    //creating key_for_sudo to be printed above grounds
    for (int l = 0; l < 40; ++l)
    {
        if      ((l % 4) == 0)
        {
            key_for_sudo[l] = extracting_char_of_decomposed_random(l / 2);
            continue;
        }
        else if ((l % 4) == 1)
        {
            key_for_sudo[l] = ' ';
            continue;
        }
        else if ((l % 4) == 2)
        {
            key_for_sudo[l] = extracting_char_of_decomposed_random(l / 2);
            continue;
        }
        else if ((l % 4) == 3)
        {
            key_for_sudo[l] = '\t';
            continue;
        }
    }

    //assignment for Bombs from random list
    for (int n = 0; n < 20; n += 2)
    {
          secret_ground.rows[(decomposed_random_accepted[n + 1])][(decomposed_random_accepted[n]) * 2] = 'B';
    }
}                        //SAFE             //HEALTHY

void arranging_secret_ground_16()
{
    secret_ground_16 = shown_ground_16;

    //decomposing of a number to X and Y
    for (int j = 0; j < 40; ++j)
    {
        int real_X = (random_accepted_16[j] % 16) + 1;
        int real_Y = (random_accepted_16[j] / 16) + 1;

        decomposed_random_accepted_16[p] = real_X;
        decomposed_random_accepted_16[p + 1] = real_Y;
        p += 2;
    }

    //assignment for Bombs from random list
    for (int n = 0; n < 80; n += 2)
    {
        secret_ground_16.rows[(decomposed_random_accepted_16[n + 1])][(decomposed_random_accepted_16[n]) * 3] = 'B';
    }
}                     //SAFE             //HEALTHY

void random_maker_checker()
{
    //how much random I want
    int count = 10;

    //seed the random optimizer
    srand(time(NULL));

    //imagination of all possible randoms
    int all_possible[64];
    for (int w = 0; w < 64; w++)
    {
        all_possible[w] = 0;
    }

    //preventing from being more than 3 bomb in a column based on remainder by 8
    int remainings[8] = {0, 0, 0, 0, 0, 0, 0, 0};

    //until we have 10 unique conditioned numbers
    while (i < count)
    {
        int made_random_number;

        //check for unique
        do
        {
            //random between 1 and 64
            made_random_number = (rand() % 63) + 1;
        }
        while (all_possible[made_random_number - 1] == 1);

        int remain_by_8 = made_random_number % 8;

        //check for condition
        if (remainings[remain_by_8] < 3)
        {
            random_accepted[i] = made_random_number;
            i += 1;
            remainings[remain_by_8] += 1;
            all_possible[made_random_number - 1] = 1;
        }
    }
}                           //SAFE             //HEALTHY

void random_maker_checker_16()
{
    //how much random I want
    int count_16 = 40;

    //seed the random optimizer
    srand(time(NULL));

    //imagination of all possible randoms to zero
    int all_possible_16[265];
    for (int w = 0; w < 256; w++)
    {
        all_possible_16[w] = 0;
    }

    //preventing from being more than 3 bomb in a column based on remainder by 8
    int remainings_16[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 , 0 , 0 , 0 , 0 , 0};

    //until we have 40 unique conditioned numbers
    while (m < count_16)
    {
        int made_random_number_16;

        made_random_number_16 = (rand() % 255) + 1;

        if (all_possible_16[made_random_number_16 - 1] == 1)
        {
            continue;
        }
        else
        {
            //check for unique
            int remain_by_16 = made_random_number_16 % 16;

            //check for condition
            if (remainings_16[remain_by_16] < 3)
            {
                random_accepted_16[m] = made_random_number_16;
                m += 1;
                remainings_16[remain_by_16] += 1;
                all_possible_16[made_random_number_16 - 1] = 1;
                continue;
            }
        }
    }
}                        //SAFE             //HEALTHY

char extracting_char_of_decomposed_random(int index)
{
    //converting a number to its ascii char to be shown in ground
    return (decomposed_random_accepted[index] + 48);
}  //SAFE             //HEALTHY

char convert_int_to_char(int should_be_converted)
{
    return (should_be_converted + 48);
}

void flipping_cell()
{
    //getting X and Y from user after commanding
    short x_axis;
    scanf("%hi", &x_axis);
    short y_axis;
    scanf("%hi", &y_axis);

    //check for validation of a number
    if (x_axis > 0 && x_axis < 9 && y_axis > 0 && y_axis < 9)
    {
        printf("\n");

        //check for being a bomb
        if (secret_ground.rows[y_axis][(2 * x_axis)] == 'B')
        {
            play_explosion_sound();
            RED();
            type_writer_printer("A Huge Bomb exploded!\n");
            WHITE();
            lost_the_game();
        }
        //check for not to flip a flagged cell
        if (shown_ground.rows[y_axis][(2 * x_axis)] == 'F')
        {
            YELLOW();
            printf("This cell flagged baby!\n");
            WHITE();
            commanding_and_checking();
        }
        else
        {
            //printing nearby bomb quantity
            shown_ground.rows[y_axis][(2 * x_axis)] = neighbor_counter(x_axis, y_axis);
            shown_ground_printer();
        }
    }
    else
    {
        RED();
        printf("Wrong input!\n");
        WHITE();
        commanding_and_checking();
    }
}                                  //SAFE             //HEALTHY

void flipping_cell_16(int y_axis, int x_axis)
{
    //check for validation of a number
    if (x_axis > 0 && x_axis < 17 && y_axis > 0 && y_axis < 17)
    {
        printf("\n");

        //check for being a bomb
        if (secret_ground_16.rows[y_axis][(3 * x_axis)] == 'B')
        {
            play_explosion_sound();
            RED();
            type_writer_printer("A Huge Bomb exploded!\n");
            WHITE();
            lost_the_game();
        }
        //check for not to flip a flagged cell
        if (shown_ground_16.rows[y_axis][(3 * x_axis)] == 'F')
        {
            YELLOW();
            printf("This cell flagged baby!\n");
            WHITE();
            commanding_and_checking();
        }
        else
        {
            //printing nearby bomb quantity
            neighbor_counter_16(x_axis, y_axis);
            shown_ground_printer_16();
        }
    }
    else
    {
        RED();
        printf("Wrong input!\n");
        WHITE();
        commanding_and_checking();
    }
}                                  //SAFE             //HEALTHY

char neighbor_counter(short x, short y)
{
    //declaration of array mode X and Y
    int neighbor_bomb = 0;
    int Y = y;
    int X = 2 * x;

    //my limitation char indexes:
    //in Y ----> if was 1 or 8
    //in X ----> if was 2 or 16

    //counting nearby bombs based on each location (corner, side, inside)
    if (Y == 8 && X == 2)
    {
        if (secret_ground.rows[7][2] == 'B') neighbor_bomb += 1;
        if (secret_ground.rows[7][4] == 'B') neighbor_bomb += 1;
        if (secret_ground.rows[8][4] == 'B') neighbor_bomb += 1;
        return (neighbor_bomb + 48);
    }
    if (Y == 8 && X == 16)
    {
        if (secret_ground.rows[7][16] == 'B') neighbor_bomb += 1;
        if (secret_ground.rows[7][14] == 'B') neighbor_bomb += 1;
        if (secret_ground.rows[8][14] == 'B') neighbor_bomb += 1;
        return (neighbor_bomb + 48);
    }
    if (Y == 1 && X == 2)
    {
        if (secret_ground.rows[2][2] == 'B') neighbor_bomb += 1;
        if (secret_ground.rows[2][4] == 'B') neighbor_bomb += 1;
        if (secret_ground.rows[1][4] == 'B') neighbor_bomb += 1;
        return (neighbor_bomb + 48);
    }
    if (Y == 1 && X == 16)
    {
        if (secret_ground.rows[2][16] == 'B') neighbor_bomb += 1;
        if (secret_ground.rows[2][14] == 'B') neighbor_bomb += 1;
        if (secret_ground.rows[1][14] == 'B') neighbor_bomb += 1;
        return (neighbor_bomb + 48);
    }
    if (Y == 8)
    {
        if (secret_ground.rows[8][X + 2] == 'B') neighbor_bomb += 1;
        if (secret_ground.rows[8][X - 2] == 'B') neighbor_bomb += 1;
        if (secret_ground.rows[7][X - 2] == 'B') neighbor_bomb += 1;
        if (secret_ground.rows[7][X] == 'B') neighbor_bomb += 1;
        if (secret_ground.rows[7][X + 2] == 'B') neighbor_bomb += 1;
        return (neighbor_bomb + 48);
    }
    if (y == 1)
    {
        if (secret_ground.rows[1][X + 2] == 'B') neighbor_bomb += 1;
        if (secret_ground.rows[1][X - 2] == 'B') neighbor_bomb += 1;
        if (secret_ground.rows[2][X - 2] == 'B') neighbor_bomb += 1;
        if (secret_ground.rows[2][X] == 'B') neighbor_bomb += 1;
        if (secret_ground.rows[2][X + 2] == 'B') neighbor_bomb += 1;
        return (neighbor_bomb + 48);
    }
    if (X == 2)
    {
        if (secret_ground.rows[Y + 1][X] == 'B') neighbor_bomb += 1;
        if (secret_ground.rows[Y - 1][X] == 'B') neighbor_bomb += 1;
        if (secret_ground.rows[Y + 1][X + 2] == 'B') neighbor_bomb += 1;
        if (secret_ground.rows[Y][X + 2] == 'B') neighbor_bomb += 1;
        if (secret_ground.rows[Y - 1][X + 2] == 'B') neighbor_bomb += 1;
        return (neighbor_bomb + 48);
    }
    if (X == 16)
    {
        if (secret_ground.rows[Y + 1][X] == 'B') neighbor_bomb += 1;
        if (secret_ground.rows[Y - 1][X] == 'B') neighbor_bomb += 1;
        if (secret_ground.rows[Y + 1][X - 2] == 'B') neighbor_bomb += 1;
        if (secret_ground.rows[Y][X - 2] == 'B') neighbor_bomb += 1;
        if (secret_ground.rows[Y - 1][X - 2] == 'B') neighbor_bomb += 1;
        return (neighbor_bomb + 48);
    }
    else
    {
        if (secret_ground.rows[Y + 1][X] == 'B') neighbor_bomb += 1;
        if (secret_ground.rows[Y - 1][X] == 'B') neighbor_bomb += 1;
        if (secret_ground.rows[Y][X + 2] == 'B') neighbor_bomb += 1;
        if (secret_ground.rows[Y][X - 2] == 'B') neighbor_bomb += 1;
        if (secret_ground.rows[Y + 1][X + 2] == 'B') neighbor_bomb += 1;
        if (secret_ground.rows[Y + 1][X - 2] == 'B') neighbor_bomb += 1;
        if (secret_ground.rows[Y - 1][X + 2] == 'B') neighbor_bomb += 1;
        if (secret_ground.rows[Y - 1][X - 2] == 'B') neighbor_bomb += 1;
        return (neighbor_bomb + 48);
    }
}               //SAFE             //HEALTHY

void neighbor_counter_16(int x, int y)
{
    //declaration of array mode X and Y
    int Y = y;
    int X = 3 * x;

    //my limitation char indexes:
    //in Y ----> if was 1 or 16
    //in X ----> if was 3 or 48

    //counting nearby bombs based on each location (corner, side, inside)
    if (Y == 16 && X == 3)
    {
        int neighbor_bomb = 0;
        if (secret_ground_16.rows[Y - 1][X] == 'B') neighbor_bomb += 1;
        if (secret_ground_16.rows[Y - 1][X + 3] == 'B') neighbor_bomb += 1;
        if (secret_ground_16.rows[Y][X + 3] == 'B') neighbor_bomb += 1;

        //cool_part_of_code
        if (neighbor_bomb == 0)
        {
            shown_ground_16.rows[Y][X] = '0';
            flipping_cell_16(Y - 1, X / 3);
            flipping_cell_16(Y - 1, (X + 3) / 3);
            flipping_cell_16(Y, (X + 3) / 3);
        }
        else
        {
            shown_ground_16.rows[Y][X] = convert_int_to_char(neighbor_bomb);
        }
    }
    if (Y == 16 && X == 48)
    {
        int neighbor_bomb = 0;
        if (secret_ground_16.rows[Y - 1][X] == 'B') neighbor_bomb += 1;
        if (secret_ground_16.rows[Y - 1][X - 3] == 'B') neighbor_bomb += 1;
        if (secret_ground_16.rows[Y][X - 3] == 'B') neighbor_bomb += 1;
        //cool_part_of_code
        if (neighbor_bomb == 0)
        {
            shown_ground_16.rows[Y][X] = '0';
            flipping_cell_16(Y - 1, X / 3);
            flipping_cell_16(Y - 1, (X - 3) / 3);
            flipping_cell_16(Y, (X - 3) / 3);
        }
        else
        {
            shown_ground_16.rows[Y][X] = convert_int_to_char(neighbor_bomb);
        }
    }
    if (Y == 1 && X == 3)
    {
        int neighbor_bomb = 0;
        if (secret_ground_16.rows[Y + 1][X] == 'B') neighbor_bomb += 1;
        if (secret_ground_16.rows[Y + 1][X + 3] == 'B') neighbor_bomb += 1;
        if (secret_ground_16.rows[Y][X + 3] == 'B') neighbor_bomb += 1;
        //cool_part_of_code
        if (neighbor_bomb == 0)
        {
            shown_ground_16.rows[Y][X] = '0';
            flipping_cell_16(Y + 1, X / 3);
            flipping_cell_16(Y + 1, (X + 3) / 3);
            flipping_cell_16(Y, (X + 3) / 3);
        }
        else
        {
            shown_ground_16.rows[Y][X] = convert_int_to_char(neighbor_bomb);
        }
    }
    if (Y == 1 && X == 48)
    {
        int neighbor_bomb = 0;
        if (secret_ground_16.rows[Y + 1][X] == 'B') neighbor_bomb += 1;
        if (secret_ground_16.rows[Y + 1][X - 3] == 'B') neighbor_bomb += 1;
        if (secret_ground_16.rows[Y][X - 3] == 'B') neighbor_bomb += 1;
        //cool_part_of_code
        if (neighbor_bomb == 0)
        {
            shown_ground_16.rows[Y][X] = '0';
            flipping_cell_16(Y + 1, X / 3);
            flipping_cell_16(Y + 1, (X - 3) / 3);
            flipping_cell_16(Y, (X - 3) / 3);
        }
        else
        {
            shown_ground_16.rows[Y][X] = convert_int_to_char(neighbor_bomb);
        }
    }
    if (Y == 16)
    {
        int neighbor_bomb = 0;
        if (secret_ground_16.rows[Y][X + 3] == 'B') neighbor_bomb += 1;
        if (secret_ground_16.rows[Y][X - 3] == 'B') neighbor_bomb += 1;
        if (secret_ground_16.rows[Y - 1][X - 3] == 'B') neighbor_bomb += 1;
        if (secret_ground_16.rows[Y - 1][X] == 'B') neighbor_bomb += 1;
        if (secret_ground_16.rows[y - 1][X + 3] == 'B') neighbor_bomb += 1;
        //cool_part_of_code
        if (neighbor_bomb == 0)
        {
            shown_ground_16.rows[Y][X] = '0';
            flipping_cell_16(Y, (X + 3) / 3);
            flipping_cell_16(Y, (X - 3) / 3);
            flipping_cell_16(Y - 1, (X - 3) / 3);
            flipping_cell_16(Y - 1, X / 3);
            flipping_cell_16(Y - 1, (X + 3) / 3);
        }
        else
        {
            shown_ground_16.rows[Y][X] = convert_int_to_char(neighbor_bomb);
        }
    }
    if (y == 1)
    {
        int neighbor_bomb = 0;
        if (secret_ground_16.rows[Y][X + 3] == 'B') neighbor_bomb += 1;
        if (secret_ground_16.rows[Y][X - 3] == 'B') neighbor_bomb += 1;
        if (secret_ground_16.rows[Y + 1][X - 3] == 'B') neighbor_bomb += 1;
        if (secret_ground_16.rows[Y + 1][X] == 'B') neighbor_bomb += 1;
        if (secret_ground_16.rows[Y + 1][X + 3] == 'B') neighbor_bomb += 1;
        //cool_part_of_code
        if (neighbor_bomb == 0)
        {
            shown_ground_16.rows[Y][X] = '0';
            flipping_cell_16(Y, (X + 3) / 3);
            flipping_cell_16(Y, (X - 3) / 3);
            flipping_cell_16(Y + 1, (X - 3) / 3);
            flipping_cell_16(Y + 1, X / 3);
            flipping_cell_16(Y + 1, (X + 3) / 3);
        }
        else
        {
            shown_ground_16.rows[Y][X] = convert_int_to_char(neighbor_bomb);
        }
    }
    if (X == 2)
    {
        int neighbor_bomb = 0;
        if (secret_ground_16.rows[Y + 1][X] == 'B') neighbor_bomb += 1;
        if (secret_ground_16.rows[Y - 1][X] == 'B') neighbor_bomb += 1;
        if (secret_ground_16.rows[Y + 1][X + 3] == 'B') neighbor_bomb += 1;
        if (secret_ground_16.rows[Y][X + 3] == 'B') neighbor_bomb += 1;
        if (secret_ground_16.rows[Y - 1][X + 3] == 'B') neighbor_bomb += 1;
        //cool_part_of_code
        if (neighbor_bomb == 0)
        {
            shown_ground_16.rows[Y][X] = '0';
            flipping_cell_16(Y + 1, X / 3);
            flipping_cell_16(Y - 1, X / 3);
            flipping_cell_16(Y + 1, (X + 3) / 3);
            flipping_cell_16(Y, (X + 3) / 3);
            flipping_cell_16(Y - 1, (X + 3) / 3);
        }
        else
        {
            shown_ground_16.rows[Y][X] = convert_int_to_char(neighbor_bomb);
        }
    }
    if (X == 48)
    {
        int neighbor_bomb = 0;
        if (secret_ground_16.rows[Y + 1][X] == 'B') neighbor_bomb += 1;
        if (secret_ground_16.rows[Y - 1][X] == 'B') neighbor_bomb += 1;
        if (secret_ground_16.rows[Y + 1][X - 3] == 'B') neighbor_bomb += 1;
        if (secret_ground_16.rows[Y][X - 3] == 'B') neighbor_bomb += 1;
        if (secret_ground_16.rows[Y - 1][X - 3] == 'B') neighbor_bomb += 1;
        //cool_part_of_code
        if (neighbor_bomb == 0)
        {
            shown_ground_16.rows[Y][X] = '0';
            flipping_cell_16(Y + 1, X / 3);
            flipping_cell_16(Y - 1, X / 3);
            flipping_cell_16(Y + 1, (X - 3) / 3);
            flipping_cell_16(Y, (X - 3) / 3);
            flipping_cell_16(Y - 1, (X - 3) / 3);
        }
        else
        {
            shown_ground_16.rows[Y][X] = convert_int_to_char(neighbor_bomb);
        }
    }
    else
    {
        int neighbor_bomb = 0;
        if (secret_ground_16.rows[Y + 1][X] == 'B') neighbor_bomb += 1;
        if (secret_ground_16.rows[Y - 1][X] == 'B') neighbor_bomb += 1;
        if (secret_ground_16.rows[Y][X + 3] == 'B') neighbor_bomb += 1;
        if (secret_ground_16.rows[Y][X - 3] == 'B') neighbor_bomb += 1;
        if (secret_ground_16.rows[Y + 1][X + 3] == 'B') neighbor_bomb += 1;
        if (secret_ground_16.rows[Y + 1][X - 3] == 'B') neighbor_bomb += 1;
        if (secret_ground_16.rows[Y - 1][X + 3] == 'B') neighbor_bomb += 1;
        if (secret_ground_16.rows[Y - 1][X - 3] == 'B') neighbor_bomb += 1;
        //cool_part_of_code
        if (neighbor_bomb == 0)
        {
            shown_ground_16.rows[Y][X] = '0';
            flipping_cell_16(Y + 1, X / 3);
            flipping_cell_16(Y - 1, X / 3);
            flipping_cell_16(Y, (X + 3) / 3);
            flipping_cell_16(Y, (X - 3) / 3);
            flipping_cell_16(Y + 1, (X + 3) / 3);
            flipping_cell_16(Y + 1, (X - 3) / 3);
            flipping_cell_16(Y - 1, (X + 3) / 3);
            flipping_cell_16(Y - 1, (X - 3) / 3);
        }
        else
        {
            shown_ground_16.rows[Y][X] = convert_int_to_char(neighbor_bomb);
        }
    }
}               //SAFE             //HEALTHY

void flagging_cell()
{
    //getting X and Y from user after commanding
    short x_axis;
    scanf("%hi", &x_axis);
    short y_axis;
    scanf("%hi", &y_axis);

    //check for validation of a number
    if (x_axis > 0 && x_axis < 9 && y_axis > 0 && y_axis < 9)
    {
        //preventing from reflagging
        if (shown_ground.rows[y_axis][(2 * x_axis)] != 'F')
        {

            printf("\n");

            //preventing from flag on otherwise of *
            if (shown_ground.rows[y_axis][2 * x_axis] == '*')
            {
                //if there is flag
                if (remaining_flags > 0)
                {
                    remaining_flags -= 1;

                    //counting corrected flaged cell
                    if (secret_ground.rows[y_axis][(2 * x_axis)] == 'B')
                    {
                        correct_flagged += 1;
                    }
                    shown_ground.rows[y_axis][(2 * x_axis)] = 'F';

                    //happening after flagging
                    if (correct_flagged != 10) shown_ground_printer();
                    else won_the_game();
                }
                else
                {
                    YELLOW();
                    printf("No more flag my dear. :(\n");
                    WHITE();
                    commanding_and_checking();
                }
            }
            else
            {
                YELLOW();
                printf("Don't waste your flag!\n");
                WHITE();
                commanding_and_checking();
            }
        }
        else
        {
            YELLOW();
            printf("This cell has a flag!\n");
            WHITE();
            commanding_and_checking();
        }
    }
    else
    {
        RED();
        printf("Wrong input!\n");
        WHITE();
        commanding_and_checking();
    }

}                                  //SAFE             //HEALTHY

void flagging_cell_16()
{
    //getting X and Y from user after commanding
    short x_axis;
    scanf("%hi", &x_axis);
    short y_axis;
    scanf("%hi", &y_axis);

    //check for validation of a number
    if (x_axis > 0 && x_axis < 17 && y_axis > 0 && y_axis < 17)
    {
        //preventing from reflagging
        if (shown_ground_16.rows[y_axis][(3 * x_axis)] != 'F')
        {

            printf("\n");

            //preventing from flag on otherwise of *
            if (shown_ground_16.rows[y_axis][3 * x_axis] == '*')
            {
                //if there is flag
                if (remaining_flags_16 > 0)
                {
                    remaining_flags_16 -= 1;

                    //counting corrected flaged cell
                    if (secret_ground_16.rows[y_axis][(3 * x_axis)] == 'B')
                    {
                        correct_flagged_16 += 1;
                    }
                    shown_ground_16.rows[y_axis][(3 * x_axis)] = 'F';

                    //happening after flagging
                    if (correct_flagged_16 != 40) shown_ground_printer_16();
                    else won_the_game();
                }
                else
                {
                    YELLOW();
                    printf("No more flag my dear. :(\n");
                    WHITE();
                    commanding_and_checking();
                }
            }
            else
            {
                YELLOW();
                printf("Don't waste your flag!\n");
                WHITE();
                commanding_and_checking();
            }
        }
        else
        {
            YELLOW();
            printf("This cell has a flag!\n");
            WHITE();
            commanding_and_checking();
        }
    }
    else
    {
        RED();
        printf("Wrong input!\n");
        WHITE();
        commanding_and_checking();
    }

}                                  //SAFE             //HEALTHY

void pulling_cell()
{
    //getting X and Y from user after commanding
    short x_axis;
    scanf("%hi", &x_axis);
    short y_axis;
    scanf("%hi", &y_axis);

    //check for validation of a number
    if (x_axis > 0 && x_axis < 9 && y_axis > 0 && y_axis < 9)
    {

        //preventing from jerk pulling
        if (shown_ground.rows[y_axis][(2 * x_axis)] == 'F')
        {
            printf("\n");

            //may be not necessary
            if (remaining_flags <= 10)
            {
                remaining_flags += 1;
                if (secret_ground.rows[y_axis][(2 * x_axis)] == 'B')
                {
                    correct_flagged -= 1;
                }
                shown_ground.rows[y_axis][(2 * x_axis)] = '*';
                shown_ground_printer();
            }
            else
            {
                YELLOW();
                printf("Nothing to pull up. :|\n");
                WHITE();
                if (sudo_flag == 0)
                {
                    RED();
                    type_writer_printer("Have you ever passed elementary? :x\n");
                    WHITE();
                }
                commanding_and_checking();
            }
        }
        else
        {
            RED();
            faster_type_writer_printer("Are you stupid?!\n");
            WHITE();
            commanding_and_checking();
        }
    }
    else
    {
        RED();
        printf("Wrong input!\n");
        WHITE();
        commanding_and_checking();
    }
}                                   //SAFE             //HEALTHY

void pulling_cell_16()
{
    //getting X and Y from user after commanding
    short x_axis;
    scanf("%hi", &x_axis);
    short y_axis;
    scanf("%hi", &y_axis);

    //check for validation of a number
    if (x_axis > 0 && x_axis < 17 && y_axis > 0 && y_axis < 17)
    {

        //preventing from jerk pulling
        if (shown_ground_16.rows[y_axis][(3 * x_axis)] == 'F')
        {
            printf("\n");

            //may be not necessary
            if (remaining_flags_16 <= 40)
            {
                remaining_flags_16 += 1;
                if (secret_ground_16.rows[y_axis][(3 * x_axis)] == 'B')
                {
                    correct_flagged_16 -= 1;
                }
                shown_ground_16.rows[y_axis][(3 * x_axis)] = '*';
                shown_ground_printer_16();
            }
            else
            {
                YELLOW();
                printf("Nothing to pull up. :|\n");
                WHITE();
                if (sudo_flag == 0)
                {
                    RED();
                    type_writer_printer("Have you ever passed elementary? :x\n");
                    WHITE();
                }
                commanding_and_checking();
            }
        }
        else
        {
            RED();
            faster_type_writer_printer("Are you stupid?!\n");
            WHITE();
            commanding_and_checking();
        }
    }
    else
    {
        RED();
        printf("Wrong input!\n");
        WHITE();
        commanding_and_checking();
    }
}                                   //SAFE             //HEALTHY

void won_the_game()
{
    //prompt user a massage
    GREEN();
    type_writer_printer("All Bombs defused! :)\n");
    play_winner_sound();
    type_writer_printer("Congratulation! I think you have to co_operate with NASA!\n");
    WHITE();

    //increasing info data
    info.was_winner += 1;
    info.how_much_played += 1;

    //happen
    open_menu();
}                                   //SAFE             //HEALTHY

void lost_the_game()
{
    //prompt user a massage
    YELLOW();
    type_writer_printer("Don't cry. May you've learned something. Think different!\n");
    WHITE();

    //increasing info data
    info.was_an_ass_loser += 1;
    info.how_much_played += 1;

    //happen
    if (sixteen_ground_flag) secret_ground_printer_16();
    else secret_ground_printer();
    open_menu();
}                                  //SAFE             //HEALTHY

void shown_ground_printer()
{
    //remain flags prompt
    printf("\n");
    printf("%d remaining flag(s).\n", remaining_flags);

    //some literary words and cheating
    if (sudo_flag == 1)
    {
        printf("\n");
        CYAN();
        faster_type_writer_printer("#Your Royal Highness! Secret map is in your hands.\n");
        WHITE();
        printf("%s\n", key_for_sudo);
    }

    //print whole hidden ground
    printf("%s\n", shown_ground.rows[8]);
    printf("%s\n", shown_ground.rows[7]);
    printf("%s\n", shown_ground.rows[6]);
    printf("%s\n", shown_ground.rows[5]);
    printf("%s\n", shown_ground.rows[4]);
    printf("%s\n", shown_ground.rows[3]);
    printf("%s\n", shown_ground.rows[2]);
    printf("%s\n", shown_ground.rows[1]);
    printf("%s\n", shown_ground.rows[0]);
    printf("\n");
    commanding_and_checking();
}                           //SAFE             //HEALTHY

void shown_ground_printer_16()
{
    //remain flags prompt
    printf("\n");
    printf("%d remaining flag(s).\n", remaining_flags_16);

    //some literary words and cheating
    if (sudo_flag == 1)
    {
        printf("\n");
        CYAN();
        faster_type_writer_printer("#Your Royal Highness! Secret map is in your hands.\n");
        WHITE();
        for (int l = 0; l < 160; ++l)
        {
            if      ((l % 4) == 0)
            {
                printf("%d", decomposed_random_accepted_16[l / 2]);
                continue;
            }
            else if ((l % 4) == 1)
            {
                printf(" ");
                continue;
            }
            else if ((l % 4) == 2)
            {
                printf("%d", decomposed_random_accepted_16[l / 2]);
                continue;
            }
            else if ((l % 4) == 3)
            {
                if (l == 79)
                {
                    printf("\n");
                }
                else
                {
                    printf("\t");
                }
                continue;
            }
        }
        printf("\n");
    }

    //print whole hidden ground
    printf("%s\n", shown_ground_16.rows[16]);
    printf("%s\n", shown_ground_16.rows[15]);
    printf("%s\n", shown_ground_16.rows[14]);
    printf("%s\n", shown_ground_16.rows[13]);
    printf("%s\n", shown_ground_16.rows[12]);
    printf("%s\n", shown_ground_16.rows[11]);
    printf("%s\n", shown_ground_16.rows[10]);
    printf("%s\n", shown_ground_16.rows[9]);
    printf("%s\n", shown_ground_16.rows[8]);
    printf("%s\n", shown_ground_16.rows[7]);
    printf("%s\n", shown_ground_16.rows[6]);
    printf("%s\n", shown_ground_16.rows[5]);
    printf("%s\n", shown_ground_16.rows[4]);
    printf("%s\n", shown_ground_16.rows[3]);
    printf("%s\n", shown_ground_16.rows[2]);
    printf("%s\n", shown_ground_16.rows[1]);
    printf("%s\n", shown_ground_16.rows[0]);
    printf("\n");
    commanding_and_checking();
}                           //SAFE             //HEALTHY

void secret_ground_printer()
{
    //printing whole planted ground
    printf("%s\n", secret_ground.rows[8]);
    printf("%s\n", secret_ground.rows[7]);
    printf("%s\n", secret_ground.rows[6]);
    printf("%s\n", secret_ground.rows[5]);
    printf("%s\n", secret_ground.rows[4]);
    printf("%s\n", secret_ground.rows[3]);
    printf("%s\n", secret_ground.rows[2]);
    printf("%s\n", secret_ground.rows[1]);
    printf("%s\n", secret_ground.rows[0]);
    printf("\n");
}                          //SAFE             //HEALTHY

void secret_ground_printer_16()
{
    //printing whole planted ground
    printf("%s\n", secret_ground_16.rows[16]);
    printf("%s\n", secret_ground_16.rows[15]);
    printf("%s\n", secret_ground_16.rows[14]);
    printf("%s\n", secret_ground_16.rows[13]);
    printf("%s\n", secret_ground_16.rows[12]);
    printf("%s\n", secret_ground_16.rows[11]);
    printf("%s\n", secret_ground_16.rows[10]);
    printf("%s\n", secret_ground_16.rows[9]);
    printf("%s\n", secret_ground_16.rows[8]);
    printf("%s\n", secret_ground_16.rows[7]);
    printf("%s\n", secret_ground_16.rows[6]);
    printf("%s\n", secret_ground_16.rows[5]);
    printf("%s\n", secret_ground_16.rows[4]);
    printf("%s\n", secret_ground_16.rows[3]);
    printf("%s\n", secret_ground_16.rows[2]);
    printf("%s\n", secret_ground_16.rows[1]);
    printf("%s\n", secret_ground_16.rows[0]);
    printf("\n");
}                          //SAFE             //HEALTHY

void reset_to_factory()
{
    //every thing to reset game for next use
    i = 0;
    s = 0;
    m = 0;
    p = 0;
    remaining_flags = 10;
    correct_flagged = 0;
    remaining_flags_16 = 40;
    correct_flagged_16 = 0;
    sixteen_ground_flag = 0;
    random_maker_checker();
    random_maker_checker_16();
    resetting_shown_ground();
    resetting_shown_ground_16();
    arranging_secret_ground();
    arranging_secret_ground_16();
}                               //SAFE             //HEALTHY

void play_winner_sound()
{
    PlaySoundA("D:\\colloge studies\\1st Term\\BP\\HW\\minsweeper\\sounds\\WINN.wav", NULL, SND_FILENAME | SND_SYNC);
}

void play_explosion_sound()
{
    PlaySoundA("D:\\colloge studies\\1st Term\\BP\\HW\\minsweeper\\sounds\\EXPO.wav", NULL, SND_FILENAME | SND_SYNC);
}

void play_intro_sound()
{
    PlaySoundA("D:\\colloge studies\\1st Term\\BP\\HW\\minsweeper\\sounds\\INTR.wav", NULL, SND_FILENAME | SND_SYNC);
}

void RED()
{
    printf("\033[1;31m");
}

void GREEN()
{
    printf("\033[1;32m");
}

void YELLOW()
{
    printf("\033[1;33m");
}

void CYAN()
{
    printf("\033[1;36m");
}

void PURPLE()
{
    printf("\033[1;35m");
}

void WHITE()
{
    printf("\033[0m");
}

void type_writer_printer(char must_be_printed[])
{
    //printing printf effectively
    for (int h= 0; must_be_printed[h] != '\0'; h++)
    {
        printf("%c", must_be_printed[h]);
        //force output to be displayed immediately
        fflush(stdout);
        usleep(25000);  //delay 25 ms
    }
}      //SAFE             //HEALTHY

void faster_type_writer_printer(char must_be_printed[])
{
    //printing printf effectively
    for (int h= 0; must_be_printed[h] != '\0'; h++)
    {
        printf("%c", must_be_printed[h]);
        //force output to be displayed immediately
        fflush(stdout);
        usleep(5000);  //delay 5 ms
    }
}//SAFE             //HEALTHY

int main()
{
    //start
    welcome();
    guide_lines_and_profile();
    open_menu();
    commanding_and_checking();

    //Made by Najjarzadegan
    //Deepest honor for Fatima :)
}                                            //SAFE             //HEALTHY

                                                            //90%              //100%