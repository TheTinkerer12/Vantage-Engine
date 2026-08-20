# Vantage Engine

A game engine I am building for creating highly optimized games with realistic graphics.

## Build

Building creates an executable and runs it once.
`./compile.sh`

## Usage

```C++
class MyGame : public VantageGame
{
    //Declare variables and override functions and stuff.
}

int main()
{
    MyGame game;
    game.start();
    return 0;
}
```

## Liscense

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.