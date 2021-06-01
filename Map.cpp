#include "Map.h"


// type of obstacles may be done more complicated;
// algorithm of adding of safety borders to boxes is not universal :(
void Map::create(wxSize world_size)
{
    const int box_size = 50; // must be even
    const int min_obst_num = 10;
    const int max_obst_num = 20;

    std::random_device rd;  //Will be used to obtain a seed for the random number engine
    std::mt19937_64 gen; //Standard mersenne_twister_engine seeded with rd()
    gen.seed(unsigned(std::time(nullptr)));
    std::uniform_int_distribution<int> random_num(min_obst_num, max_obst_num);
    std::uniform_int_distribution<int> random_pos_x(box_size, world_size.GetWidth() - box_size);
    std::uniform_int_distribution<int> random_pos_y(box_size, world_size.GetHeight() - box_size);

    obstacle_num = random_num(gen);
    obstacles.resize(obstacle_num);

    for(int i = 0; i < obstacle_num; i++)
    {
        obstacles[i].resize(4);
        int x = random_pos_x(gen);
        int y = random_pos_y(gen);
        obstacles[i][0].x = x - box_size/2;
        obstacles[i][0].y = y - box_size/2;
        obstacles[i][1].x = x + box_size/2;
        obstacles[i][1].y = y - box_size/2;
        obstacles[i][2].x = x + box_size/2;
        obstacles[i][2].y = y + box_size/2;
        obstacles[i][3].x = x - box_size/2;
        obstacles[i][3].y = y + box_size/2;
    }
    updateSafetyContours();
}

void Map::updateSafetyContours()
{
     bigger_obstacles.resize(obstacle_num);
     for(int i = 0; i < obstacle_num; i++)
    {
        bigger_obstacles[i].resize(4);
        bigger_obstacles[i][0].x = obstacles[i][0].x - safety_adding;
        bigger_obstacles[i][0].y = obstacles[i][0].y - safety_adding;
        bigger_obstacles[i][1].x = obstacles[i][1].x + safety_adding;
        bigger_obstacles[i][1].y = obstacles[i][1].y - safety_adding;
        bigger_obstacles[i][2].x = obstacles[i][2].x + safety_adding;
        bigger_obstacles[i][2].y = obstacles[i][2].y + safety_adding;
        bigger_obstacles[i][3].x = obstacles[i][3].x - safety_adding;
        bigger_obstacles[i][3].y = obstacles[i][3].y + safety_adding;
    }
}
