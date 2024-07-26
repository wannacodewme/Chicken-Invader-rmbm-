#include "Game.h"

Game::Game()
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
    {
        std::cerr << "Failed to initialize SDL: " << SDL_GetError() << std::endl;
        exit(1);
    }
    if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG)
    {
        std::cerr << "Failed to initialize SDL_image: " << IMG_GetError() << std::endl;
        exit(1);
    }
    if (TTF_Init() < 0)
    {
        std::cerr << "Failed to initialize SDL_ttf: " << TTF_GetError() << std::endl;
        exit(1);
    }
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    {
        std::cerr << "Failed to initialize SDL_mixer: " << Mix_GetError() << std::endl;
        exit(1);
    }

    isRunning = true;
    isGameOver = false;
    isPause = false;
    isReset = false;
    isPlay = false;
    isMute = false;

    background = new Background();
    moveObject = new MoveObject();
    menu = new Menu();
    score = new Score();
    playMusic("res/sounds/bkgr_audio.wav");
    Mix_VolumeMusic(17);
}
Game::~Game()
{
    delete background;
    delete moveObject;
    delete menu;
    delete score;
}
void Game::handleEvents()
{
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_QUIT:
            isRunning = false;
            break;
        case SDL_KEYDOWN:
            handleKeyBoard();
        case SDL_MOUSEBUTTONDOWN:
            handleMouseClick();
            break;
        default:
            break;
        }
        if (!isGameOver && !isPause)
        {
            moveObject->handleDinoEvent();
        }
    }
    if (isPlay)
    {
        handleCollision();
    }
}
void Game::update()
{
    if (isGameOver || isPause || !isPlay)
    {
        return;
    }
    background->update();
    score->update(100);
    gameUpdateLevel();
    moveObject->resetLevel();
    moveObject->update();
}
void Game::gameUpdateLevel()
{
    float tmpScore = score->getScore() * 10;
    if ((uint)tmpScore == 400)
    {
        VEL -= 1;
    }
    if ((uint)tmpScore % 400 == 0)
    {
        moveObject->upLevel();
    }
}

void Game::render()
{
    background->renderEntity(renderer);
    moveObject->render(renderer);
    score->render();
}
void Game::gameOver()
{
    background->renderGameOver(renderer);
    score->updateHiScore();
    isGameOver = true;

    if (isReset)
    {
        reset();
        isReset = false;
    }
}
void Game::reset()
{
    background->reset();
    moveObject->reset();
    score->reset();
    VEL = -12;
    isGameOver = false;
}
void Game::returnMenu()
{
    reset();

    isPlay = false;
}
void Game::paused()
{
    isPause = true;
    background->pauseBg();
}
void Game::resume()
{
    isPause = false;
    background->resumeBg();
}
void Game::mute()
{
    isMute = true;
    muteAudio();
    background->music->setRect(&buttons.musicSetting.mute);
}
void Game::unmute()
{
    isMute = false;
    unMuteAudio();
    Mix_VolumeMusic(17);
    background->music->setRect(&buttons.musicSetting.rect);
}
void Game::handleCollision()
{
    if (moveObject->isCollide())
    {
        moveObject->setDinoDied();
        gameOver();
    }
}
void Game::handleMouseClick()
{
    if (event.button.button == SDL_BUTTON_LEFT)
    {
        if (menu->play->isInside())
        {
            // playSound("res/sounds/click.wav");
            isPlay = true;
        }
        if (menu->exit->isInside())
        {
            isRunning = false;
        }
        if (background->pause->isInside())
        {
            if (!isGameOver)
            {
                if (!isPause)
                {
                    paused();
                }
                else
                {
                    resume();
                }
            }
        }
        if (background->music->isInside())
        {
            if (isMute)
            {
                unmute();
            }
            else
            {
                mute();
            }
        }
    }
}
void Game::handleKeyBoard()
{
    switch (event.key.keysym.sym)
    {
    case SDLK_ESCAPE:
        isRunning = false;
        break;
    case SDLK_p:
        if (!isGameOver)
        {
            if (!isPause)
            {
                paused();
            }
            else
            {
                resume();
            }
        }
        break;
    case SDLK_m:
        if (isMute)
        {
            unmute();
        }
        else
        {
            mute();
        }
        break;
    case SDLK_SPACE:
        if (isGameOver)
        {
            isReset = true;
        }
        if (isPause)
        {
            resume();
        }
        if (!isPlay)
        {
            isPlay = true;
        }
        break;
    case SDLK_1:
        background->setIsDay();
        break;
    case SDLK_2:
        background->setIsNight();
        break;
    case SDLK_b:
        if (isGameOver)
        {
            returnMenu();
        }
        break;
    default:
        break;
    }
}

void Game::run()
{
    while (isRunning)
    {
        if (!isPlay)
        {
            menu->render(renderer);
            menu->update();
        }
        else
        {
            background->renderBg(renderer);
            render();
            update();
        }

        handleEvents();

        SDL_RenderPresent(renderer);
        SDL_RenderClear(renderer);
    }
    clean();
}
void Game::clean()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    IMG_Quit();
    TTF_Quit();
    Mix_Quit();
}