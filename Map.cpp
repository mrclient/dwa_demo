#include "Map.h"

void Map::create(wxSize world_size)
{
    const int box_size = 50; // must be even
    const int adding = 5;

    std::random_device rd;  //Will be used to obtain a seed for the random number engine
    std::mt19937_64 gen; //Standard mersenne_twister_engine seeded with rd()
    gen.seed(unsigned(std::time(nullptr)));
    std::uniform_int_distribution<int> random_num(10, 20);
    std::uniform_int_distribution<int> random_pos_x(box_size, world_size.GetWidth() - box_size);
    std::uniform_int_distribution<int> random_pos_y(box_size, world_size.GetHeight() - box_size);

    obstacle_num = random_num(gen);
    obstacles.resize(obstacle_num);
    bigger_obstacles.resize(obstacle_num);

    for(int i = 0; i < obstacle_num; i++)
    {
        obstacles[i].resize(4);
        bigger_obstacles[i].resize(4);
        int x = random_pos_x(gen);
        int y = random_pos_y(gen);
        obstacles[i][0].x = x-box_size/2;
        obstacles[i][0].y = y-box_size/2;
        bigger_obstacles[i][0].x = x - box_size/2 - adding;
        bigger_obstacles[i][0].y = y - box_size/2 - adding;
        obstacles[i][1].x = x+box_size/2;
        obstacles[i][1].y = y-box_size/2;
        bigger_obstacles[i][1].x = x + box_size/2 + adding;
        bigger_obstacles[i][1].y = y - box_size/2 - adding;
        obstacles[i][2].x = x+box_size/2;
        obstacles[i][2].y = y+box_size/2;
        bigger_obstacles[i][2].x = x + box_size/2 + adding;
        bigger_obstacles[i][2].y = y + box_size/2 + adding;
        obstacles[i][3].x = x-box_size/2;
        obstacles[i][3].y = y+box_size/2;
        bigger_obstacles[i][3].x = x - box_size/2 - adding;
        bigger_obstacles[i][3].y = y + box_size/2 + adding;
    }
}
