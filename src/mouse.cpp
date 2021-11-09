#include "../include/mouse/mouse.h"  
#include "../include/api/api.h"  
#include "../include/util/util.h"
#include <string>
#include <stack>
#include <vector>
#include <algorithm>
#include <iostream>

void rwa2::Mouse::display_walls() {
    for (int x = 0; x < m_maze_width; x += 1) {
        for (int y = 0; y < m_maze_height; y += 1) {
            if (m_maze.at(x).at(y).is_wall(direction::NORTH)) {
                //display this wall in the simulator
                API::setWall(x, y, 'n');
            }
                
            if (m_maze.at(x).at(y).is_wall(direction::EAST)) {
                //display this wall in the simulator
                API::setWall(x, y, 'e');
            }
                
            if (m_maze.at(x).at(y).is_wall(direction::SOUTH)) {
                //display this wall in the simulator
                API::setWall(x, y, 's');
            }
                
            if (m_maze.at(x).at(y).is_wall(direction::WEST)) {
                //display this wall in the simulator
                API::setWall(x, y, 'w');
            }
            //display the number of walls surrounding the current node
            API::setText(x, y, std::to_string(m_maze.at(x).at(y).compute_number_of_walls()));
        }
    }
}

bool rwa2::Mouse::find_in_vector(std::vector<std::vector<int>> v, std::vector<int> n){
    for(int i=0;i<v.size();i++){
        if(v.at(i)==n) return true;
    }
    return false;
}

bool rwa2::Mouse::search_maze(int& nx, int& ny, int gx, int gy, rwa2::Mouse& M, std::stack<std::vector<int>>& s, std::vector<std::vector<int>>& v){   
    if(nx == gx && ny == gy){
        //std::cerr << "10\n";
        return true;
    }
    else{
        if(s.empty()){
            s.push({nx, ny});
           // std::cerr << "1\n";
            //std::cerr << "stack size " << s.size() << "\n"; 
        }
    }
    //if(nx == gx && ny == gy) return true;
    //else{
    //    if(s.empty()){
    //        s.push({nx, ny});
    //    }
    //}
    if(!find_in_vector(v,{nx, ny})){
        v.push_back({nx, ny}); 
        //std::cerr << "2\n";
    }
    if(!(M.m_maze.at(nx).at(ny).is_wall(NORTH) || find_in_vector(v,{nx, ny+1}))){      //Check West
        ny+=1;
        s.push({nx, ny});
        //std::cerr << "4\n";
        //std::cerr << "stack size " << s.size() << "\n";
    }  
    else if(!(M.m_maze.at(nx).at(ny).is_wall(WEST) || find_in_vector(v,{nx-1, ny}))){    //Check North
        nx-=1;
        s.push({nx, ny});
        //std::cerr << "3\n";
        //std::cerr << "stack size " << s.size() << "\n";
    }
    else if(!(M.m_maze.at(nx).at(ny).is_wall(EAST) || find_in_vector(v,{nx+1, ny}))){    //Check East
        nx+=1;
        s.push({nx, ny});
        //std::cerr << "5\n";
        //std::cerr << "stack size " << s.size() << "\n";
    }
    else if(!(M.m_maze.at(nx).at(ny).is_wall(SOUTH) || find_in_vector(v,{nx, ny-1}))){    //Check South
        ny-=1;
        s.push({nx, ny});
        //std::cerr << "6\n";
        //std::cerr << "stack size " << s.size() << "\n";
    }
    else{
        if(!s.empty()){ 
            s.pop();
            //+v.pop_back();
            //std::cerr << "7\n";
            //std::cerr << "stack size " << s.size() << "\n";
        } 
        else return false;
    }
    if(!s.empty()){
        nx = s.top().at(0);
        ny = s.top().at(1);
        //std::cerr << "8\n";
        if(search_maze(nx, ny, gx, gy, M, s, v)) return true;
        else return false;
        //rwa2::Mouse::search_maze(nx,ny,gx,gy,M,s,v);
    }
    else return false;
    //std::cerr << "9\n";
}

void rwa2::Mouse::move_forward(rwa2::Mouse M){
    //if(M.m_direction == NORTH) M.m_y++;
    //else if(M.m_direction == EAST) M.m_x++;
    //else if(M.m_direction == SOUTH) M.m_y--; 
    //else M.m_x--;
    API::moveForward();
}

void rwa2::Mouse::turn_left(rwa2::Mouse M){
    //if(M.m_direction == NORTH) M.m_direction = WEST;
    //else if(M.m_direction == EAST) M.m_direction = NORTH;
    //else if(M.m_direction == SOUTH) M.m_direction = EAST;
    //else M.m_direction = SOUTH;
    API::turnLeft();
}

void rwa2::Mouse::turn_right(rwa2::Mouse M){
    //if(M.m_direction == NORTH) M.m_direction = EAST;
    //else if(M.m_direction == EAST) M.m_direction = SOUTH;
    //else if(M.m_direction == SOUTH) M.m_direction = WEST;
    //else M.m_direction = NORTH;
    API::turnRight();
}