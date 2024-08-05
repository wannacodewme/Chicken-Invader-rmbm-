#include<GameManagement.h>

GameManagement::GameManagement()
{
	isRunning = true;
	g_window = NULL;
	g_screen = NULL;
    g_sound_explosion = NULL;
    g_sound_level_up = NULL;
    g_music_start = NULL;

    g_font_text = NULL;
    g_font_menu = NULL;
    g_font_announce = NULL;
    scrolling = 0;
    total_kill = 0;
    meat_score = 0;
    time_annouce = 0;
    current_level = 1;
    time_init_bat = 0;
}

GameManagement::~GameManagement()
{
    Close();
}

bool GameManagement::Init()
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
    {
        printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
        return false;
    }
    else
    {
        if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
        {
            printf("Warning: Linear texture filtering not enabled!");
        }

        g_window = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (g_window == NULL)
        {
            printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
            return false;
        }
        else
        {
            g_screen = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
            if (g_screen == NULL)
            {
                printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
                return false;
            }
            else
            {
                SDL_SetRenderDrawColor(g_screen, 0xFF, 0xFF, 0xFF, 0xFF);

                //Image
                int imgFlags = IMG_INIT_PNG;
                if (!(IMG_Init(imgFlags) & imgFlags))
                {
                    printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
                    return false;
                }

                //Audio
                if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
                {
                    printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
                    return false;
                }
                else
                {
                    g_sound_bullet[0] = Mix_LoadWAV("sound/blaster.wav");
                    g_sound_bullet[1] = Mix_LoadWAV("sound/neutron.wav");
                    g_sound_bullet[2] = Mix_LoadWAV("sound/boron.wav");                  
                    g_sound_level_up = Mix_LoadWAV("sound/level_up.wav");
                    g_sound_chicken_hit[0] = Mix_LoadWAV("sound/ChickenHit.wav");
                    g_sound_chicken_hit[1] = Mix_LoadWAV("sound/ChickenHit2.wav");
                    g_sound_chicken_hit[2] = Mix_LoadWAV("sound/ChickenHit3.wav");
                    g_sound_explosion = Mix_LoadWAV("sound/exp.wav");
                    g_sound_food = Mix_LoadWAV("sound/GET_FOOD.wav");
                    g_music_start = Mix_LoadMUS("sound/start.mp3");
                    if (g_sound_bullet[0] == NULL
                        || g_sound_bullet[1] == NULL
                        || g_sound_bullet[2] == NULL
                        || g_sound_level_up == NULL
                        || g_sound_chicken_hit[0] == NULL
                        || g_sound_chicken_hit[1] == NULL
                        || g_sound_chicken_hit[2] == NULL
                        || g_sound_explosion == NULL
                        || g_music_start == NULL
                        || g_sound_food == NULL)
                    {
                        printf("SDL_mixer could not initialize!\n");
                        return false;
                    }
                }

                //Font
                if (TTF_Init() == -1)
                {
                    printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
                    return false;
                }
                else
                {
                    g_font_text = TTF_OpenFont("font/font1.ttf", 24);
                    g_font_menu = TTF_OpenFont("font//font1.ttf", 50);
                    g_font_announce = TTF_OpenFont("font/RopaSans-Italic.ttf", 80);
                    if (g_font_text == NULL || g_font_menu == NULL || g_font_announce == NULL)
                    {
                        printf("SDL_ttf could not initialize!\n");
                        return false;
                    }
                }
            }
        }
    }
    return true;
}

bool GameManagement::LoadMedia()
{   
    //Init background
    bool ret = background.LoadImg("image/bkgmap.png", g_screen);
    if (!ret)
        return false;
    ret = background2.LoadImg("image/bkgmap.png", g_screen);
    if (!ret)
        return false;
    ret = menu_win.LoadImg("image/win.png", g_screen);
    if (!ret)
        return false;
    ret = menu_lose.LoadImg("image/lost.png", g_screen);
    if (!ret)
        return false;
    
    //Init spaceship
    ret = spaceship.LoadImg("image/ship_sprite.png", g_screen);
    if (!ret)
        return false;
    spaceship.SetClip();

    //Init shield
    ret = shield.LoadImg("image/shield0.png", g_screen);
    if (!ret)
        return false;

    //Init Chicken
    int t = 0;
    int pos_row = -20;
    int row = 0;
    for (int c = 0; c < NUMBER_OF_CHICKEN; c++)
    {
        Chicken* p_chicken = new Chicken;
        if (p_chicken)
        {
            ret = p_chicken->LoadImg("image/chicken123.png", g_screen);
            p_chicken->SetClip();
            if (!ret)
                return false;
            if (t % NUMBER_CHICKEN_PER_ROW == 0)
            {
                pos_row += DISTANCE_BETWEEN_PER_CHICKEN;
                t = 0;
                row++;
            }
            p_chicken->SetRect(162 + t * DISTANCE_BETWEEN_PER_CHICKEN, pos_row);
            p_chicken->SetXVal(CHICKEN_SPEED);
            p_chicken->SetOrderInRow(t);
            if (row % 2 == 0)
            {
                p_chicken->SetStatusRight();
            }
            else
            {
                p_chicken->SetStatusLeft();
            }           
            p_chicken_list.push_back(p_chicken);
            t++;
        }
    }

    //Init boss
    ret = boss.LoadImg("image/boss.png", g_screen);
    if (!ret)
        return false;

    //Init Explosion
    ret = explosion.LoadImg("image/exp.png", g_screen);
    if (!ret)
        return false;

    //Init scoreboard and text
    ret = scoreboard.LoadImg("image/scoreboard.png", g_screen);
    if (!ret)
        return false;
    scoreboard.SetRect(-20, 10);
    score_text.SetColor(Text::WHITE);
    score_text.SetRect(50, 15);
    heart_text.SetColor(Text::WHITE);
    heart_text.SetRect(195, 15);
    bullet_level_text.SetColor(Text::WHITE);
    bullet_level_text.SetRect(280, 15);
    text_annouce.SetColor(Text::WHITE);

    //Init asteroid
    for (int i = 0; i < NUMBER_OF_ASTEROID; i++)
    {
        Asteroid* p_asteroid = new Asteroid;
        if (p_asteroid)
        {            
            p_asteroid->LoadImgAsteroid(g_screen);
            p_asteroid_list.push_back(p_asteroid);
        }
    }

    return true;
}

void GameManagement::Close()
{
    SDL_DestroyRenderer(g_screen);
    SDL_DestroyWindow(g_window);
    g_window = NULL;
    g_screen = NULL;

    TTF_Quit();
    Mix_Quit();
    IMG_Quit();
    SDL_Quit();
}

void GameManagement::HandleBackground()
{
    scrolling += SCREEN_SPEED;
    if (scrolling >= SCREEN_HEIGHT)
        scrolling = 0;
    background.SetRect(0, scrolling);
    background.Render(g_screen);
    background2.SetRect(0, scrolling - SCREEN_HEIGHT);
    background2.Render(g_screen);
}

void GameManagement::HandleSpaceship()
{
    spaceship.HandleMove();
    spaceship.Show(g_screen);
    spaceship.MakeBullet(g_screen);
    if (spaceship.GetIsProtected() == true )
    {
        if (SDL_GetTicks() - spaceship.GetTimeProtected() <= 2500)
        {
            shield.SetRect(spaceship.GetRectFrame().x + MAIN_WIDTH / 2 - SHIELD_WIDTH/ 2, spaceship.GetRectFrame().y + MAIN_HEIGHT / 2 - SHIELD_HEIGHT / 2);
            shield.Show(g_screen);
        }
        else
        {
            spaceship.SetIsProtected(false);
        }
    }
    if (spaceship.GetAlive() == false && spaceship.GetHeart() > 0)
    {
        text_annouce.SetText("Press 'ENTER' to revive!");
        text_annouce.SetRect((SCREEN_WIDTH - text_annouce.GetRect().w) / 2, (SCREEN_HEIGHT - text_annouce.GetRect().h) / 2);
        text_annouce.ShowText(g_font_announce, g_screen);
    }
}

void GameManagement::HandleChicken()
{
    for (int i = 0; i < p_chicken_list.size(); i++)
    {
        Chicken* p_chicken = p_chicken_list.at(i);
        p_chicken->HandleMove();
        p_chicken->Show(g_screen);
        p_chicken->MakeEgg(g_screen);
        p_chicken->ShowEggBreak(g_screen);

        //Collison spaceship and chicken's bullet       
        std::vector<Egg*> egg_list = p_chicken->GetEggList();       
        bool col1 = false;
        for (int e = 0; e < egg_list.size(); e++)
        {
            Egg* p_egg = egg_list.at(e);
            if (p_egg)
            {
                if (!spaceship.GetIsProtected())
                {
                    col1 = CheckCollision(p_egg->GetRect(), spaceship.GetRectFrame());
                    if (col1)
                    {
                        p_chicken->RemoveEgg(e);
                        break;
                    }
                }
                else
                {
                    col1 = CheckCollision(p_egg->GetRect(), shield.GetRect());
                    if (col1)
                    {
                        p_chicken->RemoveEgg(e);
                        break;
                    }
                }
            }
        }

        //Collision between spaceship and chicken
        bool col2 = CheckCollision(spaceship.GetRectFrame(), p_chicken->GetRectFrame());
        if ((col1 || col2) && !spaceship.GetIsProtected())
        {
            Mix_PlayChannel(-1, g_sound_explosion, 0);
            explosion.SetRect(spaceship.GetRect().x + MAIN_WIDTH / 2 - EXPLOSION_WIDTH / 2, spaceship.GetRect().y + MAIN_HEIGHT / 2 - EXPLOSION_HEIGHT / 2);
            explosion.SetFrame(0);

            spaceship.SetRect(SCREEN_WIDTH * 2, SCREEN_HEIGHT * 2);
            spaceship.SetAlive(false);
            spaceship.DecreaseBulletLevel();
            spaceship.DecreaseHeart();
        }

        //Collison between spaceship's bullet and chicken
        std::vector<Bullet*> s_bullet_list = spaceship.GetBulletList();
        for (int s = 0; s < s_bullet_list.size(); s++)
        {
            Bullet* p_bullet = s_bullet_list.at(s);
            if (p_bullet)
            {
                bool col3 = CheckCollision(p_bullet->GetRect(), p_chicken->GetRectFrame());
                if (col3)
                {
                    Mix_PlayChannel(-1, g_sound_chicken_hit[rand() % 2], 0);                   
                    spaceship.RemoveBullet(s);
                    p_chicken->DecreaseHeart(spaceship.GetBulletDamage() + spaceship.GetBulletLevel());
                    if (p_chicken->GetHeart() <= 0)
                    {
                        total_kill++;

                        //Add meat
                        Meat* p_meat = new Meat;
                        bool ret = p_meat->LoadImg("image/meat_copy.png", g_screen);
                        if (ret)
                        {
                            p_meat->SetRect(p_chicken->GetRectFrame().x + CHICKEN_WIDTH / 2 - MEAT_WIDTH / 2, p_chicken->GetRectFrame().y + CHICKEN_HEIGHT);
                            p_meat->SetIsMove(true);
                            p_meat_list.push_back(p_meat);
                        }

                        //Add gift
                        if (total_kill % ONE_TURN_GIFT == 0)
                        {
                            Gift* p_gift = new Gift;
                            int type = rand() % 5;
                            if (type < 2)
                                p_gift->SetType(3);
                            else
                                p_gift->SetType(type % 3);
                            p_gift->LoadImgGift(g_screen);
                            p_gift_list.push_back(p_gift);
                        }
                        
                        //Delete chicken
                        p_chicken->SetAlive(false);
                        p_chicken->SetRect(-SCREEN_WIDTH, -SCREEN_HEIGHT);
                        p_chicken_list.erase(p_chicken_list.begin() + i);
                        i--;
                    }
                }
            }
        }
    }
}

void GameManagement::HandleBoss()
{    
    boss.HandleMove();
    boss.Show(g_screen);
    boss.ShowHeart(g_screen, (int)boss.GetHeart(), 6);
    boss.MakeEgg(g_screen);

    //Collison spaceship and boss's bullet
    std::vector<Egg*> egg_list = boss.GetEggList();
    bool coll1 = false;
    for (int e = 0; e < egg_list.size(); e++)
    {
        Egg* p_egg = egg_list.at(e);
        if (p_egg)
        {
            if (!spaceship.GetIsProtected())
            {
                coll1 = CheckCollision(p_egg->GetRect(), spaceship.GetRectFrame());
                if (coll1)
                {
                    boss.RemoveEgg(e);
                    break;
                }
            }
            else
            {
                coll1 = CheckCollision(p_egg->GetRect(), shield.GetRect());
                if (coll1)
                {
                    boss.RemoveEgg(e);
                    break;
                }
            }
        }
    }

    //Check collison boss and spaceship
    bool coll2 = CheckCollision(spaceship.GetRectFrame(), boss.GetRectFrame());
    if ((coll1 || coll2) && !spaceship.GetIsProtected())
    {
        Mix_PlayChannel(-1, g_sound_explosion, 0);
        explosion.SetRect(spaceship.GetRect().x + MAIN_WIDTH / 2 - EXPLOSION_WIDTH / 2, spaceship.GetRect().y + MAIN_HEIGHT / 2 - EXPLOSION_HEIGHT / 2);
        explosion.SetFrame(0);

        spaceship.SetRect(SCREEN_WIDTH * 2, SCREEN_HEIGHT * 2);
        spaceship.SetAlive(false);
        spaceship.DecreaseBulletLevel();
        spaceship.DecreaseHeart();
    }

    //Collison between spaceship's bullet and chicken
    bool coll3 = false;
    std::vector<Bullet*> s_bullet_list = spaceship.GetBulletList();
    for (int s = 0; s < s_bullet_list.size(); s++)
    {
        Bullet* p_bullet = s_bullet_list.at(s);
        if (p_bullet)
        {
            coll2 = CheckCollision(boss.GetRectFrame(), p_bullet->GetRect());
            if (coll2)
            {
                spaceship.RemoveBullet(s);
                boss.DecreaseHeart(spaceship.GetBulletDamage() + spaceship.GetBulletLevel());
            }
        }
    }
}

void GameManagement::HandleBat()
{        
    if (SDL_GetTicks() - time_init_bat > 900)
    {
        Bat* p_bat = new Bat;
        bool ret = p_bat->LoadImg("image/bat.png", g_screen);
        if (!ret)
            return;
        p_bat->SetFrame(0);
        p_bat->SetClip();
        p_bat_list.push_back(p_bat);
        time_init_bat = SDL_GetTicks();
    }

    for (int i = 0; i < p_bat_list.size(); i++)
    {
        Bat* p_bat = p_bat_list.at(i);             
        p_bat->HandleMove(g_screen);
        if (p_bat->GetFrame() < BAT_NUMBER_FRAME * 5)
            p_bat->Show(g_screen);
        p_bat->MakeEgg(g_screen);
        p_bat->ShowEggBreak(g_screen);
        if (p_bat->GetFrame() >= BAT_NUMBER_FRAME * 5 && p_bat->GetEggList().empty() && p_bat->GetEggBreakList().empty())
        {
            p_bat->SetRect(-SCREEN_WIDTH, -SCREEN_HEIGHT);
            p_bat_list.erase(p_bat_list.begin() + i);
            i--;
        }

        //Collison spaceship and bat's bullet       
        std::vector<Egg*> egg_list = p_bat->GetEggList();
        bool col1 = false;
        for (int e = 0; e < egg_list.size(); e++)
        {
            Egg* p_egg = egg_list.at(e);
            if (p_egg)
            {
                if (!spaceship.GetIsProtected())
                {
                    col1 = CheckCollision(p_egg->GetRect(), spaceship.GetRectFrame());
                    if (col1)
                    {
                        p_bat->RemoveEgg(e);
                        break;
                    }
                }
                else
                {
                    col1 = CheckCollision(p_egg->GetRect(), shield.GetRect());
                    if (col1)
                    {
                        p_bat->RemoveEgg(e);
                        break;
                    }
                }
            }
        }

        //Collision between spaceship and bat
        bool col2 = CheckCollision(spaceship.GetRectFrame(), p_bat->GetRectFrame());
        if ((col1 || col2) && !spaceship.GetIsProtected())
        {
            Mix_PlayChannel(-1, g_sound_explosion, 0);
            explosion.SetRect(spaceship.GetRect().x + MAIN_WIDTH / 2 - EXPLOSION_WIDTH / 2, spaceship.GetRect().y + MAIN_HEIGHT / 2 - EXPLOSION_HEIGHT / 2);
            explosion.SetFrame(0);

            spaceship.SetRect(SCREEN_WIDTH * 2, SCREEN_HEIGHT * 2);
            spaceship.SetAlive(false);
            spaceship.DecreaseBulletLevel();
            spaceship.DecreaseHeart();
        }

        //Collison between spaceship's bullet and bat
        std::vector<Bullet*> s_bullet_list = spaceship.GetBulletList();
        for (int s = 0; s < s_bullet_list.size(); s++)
        {
            Bullet* p_bullet = s_bullet_list.at(s);
            if (p_bullet)
            {
                bool col3 = CheckCollision(p_bullet->GetRect(), p_bat->GetRectFrame());
                if (col3 && p_bat->GetFrame() < (BAT_NUMBER_FRAME - 1) * 5)
                {
                    spaceship.RemoveBullet(s);
                    total_kill++;

                    p_bat->SetAlive(false);
                    p_bat->SetFrame((BAT_NUMBER_FRAME - 1) * 5);
                    Egg * p1_egg = new Egg;
                    p_bat->InitEgg(p1_egg, g_screen);

                    //Add gift
                    if (total_kill % ONE_TURN_GIFT == 0)
                    {
                        Gift* p_gift = new Gift;
                        int type = rand() % 5;
                        if (type < 2)
                            p_gift->SetType(3);
                        else
                            p_gift->SetType(type % 3);
                        p_gift->LoadImgGift(g_screen);
                        p_gift_list.push_back(p_gift);
                    }
                }
            }
        }
    }
}

void GameManagement::HandleAsteroid()
{
    for (int a = 0; a < p_asteroid_list.size(); a++)
    {
        Asteroid* p_asteroid = p_asteroid_list.at(a);
        if (p_asteroid)
        {
            p_asteroid->HandleMove();
            p_asteroid->Show(g_screen);

            //Collision between spaceship and asteroid
            bool col4 = CheckCollision(spaceship.GetRectFrame(), p_asteroid->GetRect());
            if (col4 && !spaceship.GetIsProtected())
            {
                Mix_PlayChannel(-1, g_sound_explosion, 0);
                explosion.SetRect(spaceship.GetRect().x + MAIN_WIDTH / 2 - EXPLOSION_WIDTH / 2, spaceship.GetRect().y + MAIN_HEIGHT / 2 - EXPLOSION_HEIGHT / 2);
                explosion.SetFrame(0);

                spaceship.SetRect(SCREEN_WIDTH * 2, SCREEN_HEIGHT * 2);
                spaceship.SetAlive(false);
                spaceship.DecreaseBulletLevel();
                spaceship.DecreaseHeart();               
            }

            //Collision between spaceship's bullet and asteroid
            bool col5 = false;
            std::vector<Bullet*> s_bullet_list = spaceship.GetBulletList();
            for (int s = 0; s < s_bullet_list.size(); s++)
            {
                Bullet* p_bullet = s_bullet_list.at(s);
                if (p_bullet)
                {
                    col5 = CheckCollision(p_bullet->GetRect(), p_asteroid->GetRect());
                    if (col5)
                    {
                        spaceship.RemoveBullet(s);
                        p_asteroid->DecreaseHeart();
                        if (p_asteroid->GetHeart() <= 0)
                        {
                            total_kill++;

                            //Add gift
                            if (total_kill % ONE_TURN_GIFT == 0)
                            {
                                Gift* p_gift = new Gift;
                                int type = rand() % 5;
                                if (type < 2)
                                    p_gift->SetType(3);
                                else
                                    p_gift->SetType(type % 3);
                                p_gift->LoadImgGift(g_screen);
                                p_gift_list.push_back(p_gift);
                            }

                            p_asteroid->SetRect(-SCREEN_WIDTH, -SCREEN_HEIGHT);
                            p_asteroid_list.erase(p_asteroid_list.begin() + a);
                            a--;
                        }
                        else if (p_asteroid->GetHeart() == 2)
                        {
                            p_asteroid->SetWidthHeight(0.8);
                        }
                        else
                        {
                            p_asteroid->SetWidthHeight(0.6);
                        }
                    }
                }               
            }
        }
    }
}

void GameManagement::HandleMeat()
{
    for (int m = 0; m < p_meat_list.size(); m++)
    {
        Meat* p_meat = p_meat_list.at(m);
        if (p_meat)
        {
            if (p_meat->GetIsMove())
            {
                p_meat->HandleMove();
                p_meat->Render(g_screen);
                //Check collision with spaceship
                bool col = CheckCollision(p_meat->GetRect(), spaceship.GetRectFrame());
                if(col)
                {
                    Mix_PlayChannel(-1, g_sound_food, 0);
                    p_meat->SetIsMove(false);
                    meat_score++;
                }
            }
            else
            {
                p_meat_list.erase(p_meat_list.begin() + m);
                p_meat = NULL;
                delete p_meat;
                m--;
            }
        }
    }
}

void GameManagement::HandleGift()
{    
    for (int g = 0; g < p_gift_list.size(); g++)
    {
        Gift* p_gift = p_gift_list.at(g);
        if (p_gift)
        {
            if (p_gift->GetIsMove())
            {
                p_gift->HandleMove();
                p_gift->Show(g_screen);

                //Check Collision with spaceship
                bool coll = false;
                if (p_gift->GetType() == 3)
                {
                    coll = CheckCollision(spaceship.GetRect(), p_gift->GetRectFrame());
                    if (coll)
                    {
                        Mix_PlayChannel(-1, g_sound_level_up, 0);
                        p_gift->SetIsMove(false);
                        spaceship.IncreaseBulletLevel();
                    }
                }
                else
                {
                    coll = CheckCollision(spaceship.GetRect(), p_gift->GetRect());
                    if (coll)
                    {
                        Mix_PlayChannel(-1, g_sound_level_up, 0);
                        p_gift->SetIsMove(false);
                        spaceship.SetBulletType(p_gift->GetType());
                    }
                }
            }
            else
            {
                p_gift_list.erase(p_gift_list.begin() + g);
                p_gift = NULL;
                delete p_gift;
                g--;
            }
        }
    }
}

void GameManagement::ResetGame()
{
    p_gift_list.clear();
    p_meat_list.clear();
    p_asteroid_list.clear();
    p_chicken_list.clear();
    p_bat_list.clear();
    LoadMedia();
    current_level = 1;
    spaceship.SetHeart(MAIN_HEART);
    spaceship.SetBulletLevel(0);
    spaceship.SetBulletType(Bullet::BLASTER);
    spaceship.SetAlive(true);
    boss.SetHeart(BOSS_HEART);
    time_annouce = SDL_GetTicks();
    total_kill = 0;
}

void GameManagement::GameLoop()
{
    if (!Init())
        return;

    srand(time(0));
    if (!LoadMedia())
        return;

    isRunning = menu.ShowMenu(g_event, "Play", g_screen, g_font_menu, g_music_start, g_sound_level_up);
    
    time_annouce = SDL_GetTicks();
    while (isRunning)
    {
        while (SDL_PollEvent(&g_event) != 0)
        {
            if (g_event.type == SDL_QUIT)
            {
                isRunning = false;
            }
            spaceship.HandleEvent(g_event, g_screen, g_sound_bullet, g_sound_level_up);
        }

        //Clear Screen
        SDL_SetRenderDrawColor(g_screen, 0xFF, 0, 0xFF, 0xFF);
        SDL_RenderClear(g_screen);   

        HandleBackground();
        HandleGift();

        if (current_level == 1)
        {
            if (SDL_GetTicks() - time_annouce <= 3000)
            {
                text_annouce.SetText("Get Ready!");
                text_annouce.SetRect((SCREEN_WIDTH - text_annouce.GetRect().w) / 2, (SCREEN_HEIGHT - text_annouce.GetRect().h) / 2);
                text_annouce.ShowText(g_font_announce, g_screen);
            }
            else
            {
                if (total_kill < NUMBER_OF_CHICKEN)
                {
                    HandleChicken();
                    HandleMeat();
                    if (spaceship.GetHeart() <= 0)
                    {
                        time_annouce = SDL_GetTicks();
                        current_level = 0;                        
                    }
                }
                else
                {
                    current_level++;
                    time_annouce = SDL_GetTicks();
                }
            }
        }       
        else if (current_level == 2)
        {            
            if (SDL_GetTicks() - time_annouce <= 3000)
            {
                text_annouce.SetText("Watch out for the asteroid rain!");
                text_annouce.SetRect((SCREEN_WIDTH - text_annouce.GetRect().w) / 2, (SCREEN_HEIGHT - text_annouce.GetRect().h) / 2);
                text_annouce.ShowText(g_font_announce, g_screen);
            }
            else
            {
                if (total_kill < NUMBER_OF_CHICKEN + NUMBER_OF_ASTEROID)
                {
                    HandleAsteroid();
                    if (spaceship.GetHeart() <= 0)
                    {
                        time_annouce = SDL_GetTicks();
                        current_level = 0;
                    }
                }
                else
                {
                    current_level++;
                    time_annouce = SDL_GetTicks();
                }
            }
        }
        else if (current_level == 3)
        {
            if (SDL_GetTicks() - time_annouce <= 3000)
            {
                text_annouce.SetText("Final level!");
                text_annouce.SetRect((SCREEN_WIDTH - text_annouce.GetRect().w) / 2, (SCREEN_HEIGHT - text_annouce.GetRect().h) / 2);
                text_annouce.ShowText(g_font_announce, g_screen);
            }
            else
            {
                if (boss.GetHeart() > 0)
                {
                    HandleBoss();
                    HandleBat();
                    if (spaceship.GetHeart() <= 0)
                    {
                        time_annouce = SDL_GetTicks();
                        current_level = 0;
                    }
                }
                else
                {
                    current_level++;
                    time_annouce = SDL_GetTicks();
                }
            }
        }

        HandleSpaceship();
             
        //Show explosion
        if (explosion.GetFrame() < EXPLOSION_NUMBER_FRAME * 2)
        {
            explosion.Show(g_screen);
        }

        //Show text
        scoreboard.Render(g_screen);
        score_text.SetText(std::to_string(meat_score));
        score_text.ShowText(g_font_text, g_screen);
        heart_text.SetText(std::to_string(spaceship.GetHeart()));
        heart_text.ShowText(g_font_text, g_screen);
        bullet_level_text.SetText(std::to_string(spaceship.GetBulletLevel()));
        bullet_level_text.ShowText(g_font_text, g_screen);

        //Game Win
        if (current_level == 4)
        {
            if (SDL_GetTicks() - time_annouce <= 3000)
            {
                menu_win.Render(g_screen);
            }
            else
            {
                isRunning = menu.ShowMenu(g_event, "Play again", g_screen, g_font_menu, g_music_start, g_sound_level_up);
                if (isRunning)
                {
                    ResetGame();
                }
            }
        }

        //Game Over
        if (current_level == 0)
        {
            if (SDL_GetTicks() - time_annouce <= 3000)
            {
                menu_lose.Render(g_screen);
            }
            else
            {
                isRunning = menu.ShowMenu(g_event, "Play again", g_screen, g_font_menu, g_music_start, g_sound_level_up);
                if (isRunning)
                {
                    ResetGame();
                    meat_score = 0;
                }
            }
        }

        //Update Screen
        SDL_RenderPresent(g_screen);
    }
    Close();
}