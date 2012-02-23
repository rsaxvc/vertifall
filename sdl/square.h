#define SQUARE_WIDTH 10
#define SQUARE_HEIGHT 10
//The square
class Square
{
    private:
    //The offsets
    int x, y;

    //The velocity of the square
    int xVel, yVel;

    public:
    //Initializes
    Square();

    //Handles key presses
    void handle_input();

    //Moves the square
    void move();

    //Shows the square on the screen
    void show();
};
