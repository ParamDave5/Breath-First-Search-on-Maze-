#include <iostream>
#include <array>

#include "../include/mouse/mouse.h"
#include "../include/api/api.h"


int main() {
	rwa2::Mouse mouse;
	mouse.display_walls();
	int nx;
	int ny;
	int gx = 8;
	int gy = 8;
	std::stack<std::vector<int>> s;
	std::stack<std::vector<int>> p;
	std::vector<std::vector<int>> v;
	bool path_found = false;
	while(true){
		//while(!s.empty()){
		//	s.pop();
		//}
		while(!p.empty()){
			p.pop();
		}
		//while(!v.empty()){
		//	v.pop_back();
		//}
		API::clearAllColor();
		API::setColor(gx,gy,'g');
		nx = mouse.m_x;
		//std::cerr << "Mousex " << nx << "\n";
		ny = mouse.m_y;
		//std::cerr << "Mousey " << ny << "\n";
		//if(API::wallFront()){ 
		//	mouse.m_maze.at(nx).at(ny).set_wall(mouse.m_direction, true);
		//}
		path_found=mouse.search_maze(nx,ny,gx,gy,mouse,s,v);
		if(!path_found){
			break;
		}
		while(!v.empty()){
			v.pop_back();
		}
		//std::cerr << s.size() << " Stack Size\n";
		int stack_size = s.size();
		for(int i=0;i<stack_size;i++){
			API::setColor(s.top().at(0),s.top().at(1), 'y');
			//std::cerr << "Stack S " << s.top().at(0) << " " << s.top().at(1) << "\n";
			p.push(s.top());
			//std::cerr << "p stack size " << p.size() << "\n";
			s.pop();
			//std::cerr << "stack size " << s.size() << "\n";
		}
		v.push_back(p.top());
		s.push(p.top());
		p.pop();
		stack_size = p.size();
		//std::cerr << "p stack size " << p.size() << "\n";
		for(int i=0;i<stack_size;i++){
			std::cerr << "Stack P " << p.top().at(0) << " " << p.top().at(1) << "\n";
			//std::cerr << "Stack V " << v << " " << p.top().at(1) << "\n";
			std::cerr << "mouse pos " << mouse.m_x << " " << mouse.m_y << "\n";
			if(p.top().at(1)==mouse.m_y+1){
				if(mouse.m_direction==NORTH){
					if(API::wallFront()){
						API::setWall(mouse.m_x,mouse.m_y,mouse.m_direction);
						mouse.m_maze.at(mouse.m_x).at(mouse.m_y).set_wall(mouse.m_direction, true);
						std::cerr << "Call search_maze from 1";
						
						break;
					}
					mouse.move_forward(mouse);
					mouse.m_y = mouse.m_y + 1;
				} 
				else if(mouse.m_direction==EAST){
					mouse.turn_left(mouse);
					mouse.m_direction=NORTH;
					if(API::wallFront()){
						API::setWall(mouse.m_x,mouse.m_y,mouse.m_direction);
						mouse.m_maze.at(mouse.m_x).at(mouse.m_y).set_wall(mouse.m_direction, true);
						std::cerr << "Call search_maze from 2";
						break;
					}
					mouse.move_forward(mouse);
					mouse.m_y = mouse.m_y + 1;
				}
				else if(mouse.m_direction==WEST){
					mouse.turn_right(mouse);
					mouse.m_direction=NORTH;
					if(API::wallFront()){
						API::setWall(mouse.m_x,mouse.m_y,mouse.m_direction);
						mouse.m_maze.at(mouse.m_x).at(mouse.m_y).set_wall(mouse.m_direction, true);
						std::cerr << "Call search_maze from 3";
						break;
					}
					mouse.move_forward(mouse);
					mouse.m_y = mouse.m_y + 1;
				}
				else{
					mouse.turn_right(mouse);
					mouse.turn_right(mouse);
					mouse.m_direction=NORTH;
					if(API::wallFront()){
						API::setWall(mouse.m_x,mouse.m_y,mouse.m_direction);
						mouse.m_maze.at(mouse.m_x).at(mouse.m_y).set_wall(mouse.m_direction, true);
						std::cerr << "Call search_maze from 4";
						break;
					}
					mouse.move_forward(mouse);
					mouse.m_y = mouse.m_y + 1;
				}
				
			}
			else if(p.top().at(1)==mouse.m_y-1){
				if(mouse.m_direction==SOUTH){
					if(API::wallFront()){
						API::setWall(mouse.m_x,mouse.m_y,mouse.m_direction);
						mouse.m_maze.at(mouse.m_x).at(mouse.m_y).set_wall(mouse.m_direction, true);
						std::cerr << "Call search_maze from 5";
						break;
					}
					mouse.move_forward(mouse);
					mouse.m_y=mouse.m_y-1;
				} 
				else if(mouse.m_direction==EAST){
					mouse.turn_right(mouse);
					mouse.m_direction=SOUTH;
					if(API::wallFront()){
						API::setWall(mouse.m_x,mouse.m_y,mouse.m_direction);
						mouse.m_maze.at(mouse.m_x).at(mouse.m_y).set_wall(mouse.m_direction, true);
						std::cerr << "Call search_maze from 6";
						break;
					}
					mouse.move_forward(mouse);
					mouse.m_y=mouse.m_y-1;
				}
				else if(mouse.m_direction==WEST){
					mouse.turn_left(mouse);
					mouse.m_direction=SOUTH;
					if(API::wallFront()){
						API::setWall(mouse.m_x,mouse.m_y,mouse.m_direction);
						mouse.m_maze.at(mouse.m_x).at(mouse.m_y).set_wall(mouse.m_direction, true);
						std::cerr << "Call search_maze from 7";
						break;
					}
					mouse.move_forward(mouse);
					mouse.m_y=mouse.m_y-1;
				}
				else{
					mouse.turn_right(mouse);
					mouse.turn_right(mouse);
					mouse.m_direction=SOUTH;
					if(API::wallFront()){
						API::setWall(mouse.m_x,mouse.m_y,mouse.m_direction);
						mouse.m_maze.at(mouse.m_x).at(mouse.m_y).set_wall(mouse.m_direction, true);
						std::cerr << "Call search_maze from 8";
						break;
					}
					mouse.move_forward(mouse);
					mouse.m_y=mouse.m_y-1;
				}
				
			}
			else if(p.top().at(0)==mouse.m_x+1){
				if(mouse.m_direction==EAST){
					if(API::wallFront()){
						API::setWall(mouse.m_x,mouse.m_y,mouse.m_direction);
						mouse.m_maze.at(mouse.m_x).at(mouse.m_y).set_wall(mouse.m_direction, true);
						std::cerr << "Call search_maze from 9";
						break;
					}
					mouse.move_forward(mouse);
					mouse.m_x=mouse.m_x+1;
				}
				else if(mouse.m_direction==SOUTH){
					mouse.turn_left(mouse);
					mouse.m_direction=EAST;
					if(API::wallFront()){
						API::setWall(mouse.m_x,mouse.m_y,mouse.m_direction);
						mouse.m_maze.at(mouse.m_x).at(mouse.m_y).set_wall(mouse.m_direction, true);
						std::cerr << "Call search_maze from 10";
						break;
					}
					mouse.move_forward(mouse);
					mouse.m_x=mouse.m_x+1;
				}
				else if(mouse.m_direction==NORTH){
					mouse.turn_right(mouse);
					mouse.m_direction=EAST;
					if(API::wallFront()){
						API::setWall(mouse.m_x,mouse.m_y,mouse.m_direction);
						mouse.m_maze.at(mouse.m_x).at(mouse.m_y).set_wall(mouse.m_direction, true);
						std::cerr << "Call search_maze from 11";
						break;
					}
					mouse.move_forward(mouse);
					mouse.m_x=mouse.m_x+1;
				}
				else{
					mouse.turn_right(mouse);
					mouse.turn_right(mouse);
					mouse.m_direction=EAST;
					if(API::wallFront()){
						API::setWall(mouse.m_x,mouse.m_y,mouse.m_direction);
						mouse.m_maze.at(mouse.m_x).at(mouse.m_y).set_wall(mouse.m_direction, true);
						std::cerr << "Call search_maze from 12";
						break;
					}
					mouse.move_forward(mouse);
					mouse.m_x=mouse.m_x+1;
				}
				
			}
			else{
				if(mouse.m_direction==WEST){
					if(API::wallFront()){
						API::setWall(mouse.m_x,mouse.m_y,mouse.m_direction);
						mouse.m_maze.at(mouse.m_x).at(mouse.m_y).set_wall(mouse.m_direction, true);
						std::cerr << "Call search_maze from 13";
						break;
					}
					mouse.move_forward(mouse);
					mouse.m_x=mouse.m_x-1;
				} 
				else if(mouse.m_direction==NORTH){
					mouse.turn_left(mouse);
					mouse.m_direction=WEST;
					if(API::wallFront()){
						API::setWall(mouse.m_x,mouse.m_y,mouse.m_direction);
						mouse.m_maze.at(mouse.m_x).at(mouse.m_y).set_wall(mouse.m_direction, true);
						std::cerr << "Call search_maze from 14";
						break;
					}
					mouse.move_forward(mouse);
					mouse.m_x=mouse.m_x-1;
				}
				else if(mouse.m_direction==SOUTH){
					mouse.turn_right(mouse);
					mouse.m_direction=WEST;
					if(API::wallFront()){
						API::setWall(mouse.m_x,mouse.m_y,mouse.m_direction);
						mouse.m_maze.at(mouse.m_x).at(mouse.m_y).set_wall(mouse.m_direction, true);
						std::cerr << "Call search_maze from 15";
						break;
					}
					mouse.move_forward(mouse);
					mouse.m_x=mouse.m_x-1;
				}
				else{
					mouse.turn_right(mouse);
					mouse.turn_right(mouse);
					mouse.m_direction=WEST;
					if(API::wallFront()){
						API::setWall(mouse.m_x,mouse.m_y,mouse.m_direction);
						mouse.m_maze.at(mouse.m_x).at(mouse.m_y).set_wall(mouse.m_direction, true);
						std::cerr << "Call search_maze from 16";
						break;
					}
					mouse.move_forward(mouse);
					mouse.m_x=mouse.m_x-1;
				}
			}
			v.push_back(p.top());
			s.push(p.top());
			p.pop();
		}
		
	}

}

