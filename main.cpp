#include <iostream>
#include <random>

#include "Robot.h"

std::random_device rd;
std::mt19937 gen(rd());

void show(const cv::Mat& image) {
    cv::imshow("Map", image);
    cv::waitKey(0);
    cv::destroyAllWindows();
    cv::waitKey(1);
}

int main() {

    std::cout << "Welcome to Robot Navigation Demo" << std::endl;
    Map::Ptr map;
    Robot::Ptr robot;
    std::string choice;
    std::string filename;

    while (true) {
        try {
            std::cout << "Select an option:" << std::endl;
            std::cout << "1. Build map" << std::endl;
            std::cout << "2. Load map" << std::endl;
            std::cout << "Press q to quit." << std::endl;
            std::cin >> choice;
            if (choice == "1") {
                std::cout << "Specify map size (height width):" << std::endl;
                int height, width;
                std::cin >> height >> width;
                map = Map::createMap(height, width);
                break;
            } else if (choice == "2") {
                std::cout << "Enter full file path:" << std::endl;
                std::cin >> filename;
                map = Map::load(filename);
                break;
            } else if (choice == "q") {
                return 0;
            }
        } catch (std::exception &e) {
            std::cout << e.what() << std::endl;
        }
    }

    while (true) {
        try {
            std::cout << "Select an option:" << std::endl;
            std::cout << "1. Show map" << std::endl;
            std::cout << "2. Clear map" << std::endl;
            std::cout << "3. Add object" << std::endl;
            std::cout << "4. Delete object" << std::endl;
            std::cout << "5. Save map" << std::endl;
            std::cout << "6. Load map" << std::endl;
            std::cout << "7. Make robot" << std::endl;
            std::cout << "Press q to quit." << std::endl;
            std::cin >> choice;
            if (choice == "1") {
                show(map->display(false));
            } else if (choice == "2") {
                map->clearMap();
            } else if (choice == "3") {
                std::cout << "Select an option:" << std::endl;
                std::cout << "1. Manually place object" << std::endl;
                std::cout << "2. Add random objects" << std::endl;
                std::cin >> choice;
                if (choice == "1") {
                    std::cout << "Enter object position (x y) and radius:" << std::endl;
                    int x, y;
                    double radius;
                    std::cin >> x >> y >> radius;
                    map->addObject(x, y, radius);
                } else if (choice == "2") {
                    int num;
                    double min_radius, max_radius;
                    std::cout << "How many random objects:" << std::endl;
                    std::cin >> num;
                    std::cout << "Min radius:" << std::endl;
                    std::cin >> min_radius;
                    std::cout << "Max radius:" << std::endl;
                    std::cin >> max_radius;
                    std::uniform_int_distribution<int> x_dist(0, map->rows - 1);
                    std::uniform_int_distribution<int> y_dist(0, map->cols - 1);
                    std::uniform_real_distribution<double> r_dist(min_radius, max_radius);
                    for (int i = 0; i < num; i++) {
                        int x = x_dist(gen);
                        int y = y_dist(gen);
                        double radius = r_dist(gen);
                        map->addObject(x, y, radius);
                    }
                }
                std::cout << "Objects added." << std::endl;
            } else if (choice == "4") {
                std::cout << "List of objects:" << std::endl;
                std::vector<Object::Ptr> objects = map->getObstacles();
                for (int i = 0; i < objects.size(); i++) {
                    std::cout << i + 1 << ". (" << objects[i]->x() << ", " << objects[i]->y() << ") radius: "
                              << objects[i]->radius << std::endl;
                }
                std::cout << "Select an object to delete:" << std::endl;
                int object_num;
                std::cin >> object_num;
                if (object_num > 0 && object_num <= objects.size()) {
                    for (int i = 0; i < objects.size(); i++) {
                        if (object_num - 1 == i) {
                            map->removeObject(objects[i]);
                        }
                    }
                    std::cout << "Object deleted." << std::endl;
                } else {
                    std::cout << "Invalid input. No object was deleted." << std::endl;
                }
            } else if (choice == "5") {
                std::cout << "Enter full file path:" << std::endl;
                std::cin >> filename;
                map->save(filename);
            } else if (choice == "6") {
                std::cout << "Enter full file path:" << std::endl;
                std::cin >> filename;
                map = Map::load(filename);
            } else if (choice == "7") {
                std::cout << "Enter robot radius:" << std::endl;
                double radius;
                std::cin >> radius;
                robot = Robot::create(radius);
                robot->giveMap(map);
                break;
            } else if (choice == "q") {
                return 0;
            }
        } catch (std::exception &e) {
            std::cout << e.what() << std::endl;
        }
    }

    while (true) {
        try {
            std::cout << "Select an option:" << std::endl;
            std::cout << "1. Show Map" << std::endl;
            std::cout << "2. Clear map" << std::endl;
            std::cout << "3. Show Heat Map" << std::endl;
            std::cout << "4. Show robot parameters" << std::endl;
            std::cout << "5. Add object" << std::endl;
            std::cout << "6. Delete object" << std::endl;
            std::cout << "7. Set start" << std::endl;
            std::cout << "8. Set target" << std::endl;
            std::cout << "9. Find safest path" << std::endl;
            std::cout << "10. Save map" << std::endl;
            std::cout << "11. Load map" << std::endl;
            std::cout << "Press q to quit." << std::endl;
            std::cin >> choice;
            if (choice == "1") {
                show(map->display(false));
            } else if (choice == "2") {
                map->clearMap();
            } else if (choice == "3") {
                show(map->display(true));
            } else if (choice == "4") {
                robot->printParameters();
            } else if (choice == "5") {
                std::cout << "Select an option:" << std::endl;
                std::cout << "1. Manually place object" << std::endl;
                std::cout << "2. Add random objects" << std::endl;
                std::cin >> choice;
                if (choice == "1") {
                    std::cout << "Enter object position (x y) and radius:" << std::endl;
                    int x, y;
                    double radius;
                    std::cin >> x >> y >> radius;
                    map->addObject(x, y, radius);
                } else if (choice == "2") {
                    int num;
                    double min_radius, max_radius;
                    std::cout << "How many random objects:" << std::endl;
                    std::cin >> num;
                    std::cout << "Min radius:" << std::endl;
                    std::cin >> min_radius;
                    std::cout << "Max radius:" << std::endl;
                    std::cin >> max_radius;
                    std::uniform_int_distribution<int> x_dist(0, map->rows - 1);
                    std::uniform_int_distribution<int> y_dist(0, map->cols - 1);
                    std::uniform_real_distribution<double> r_dist(min_radius, max_radius);
                    for (int i = 0; i < num; i++) {
                        int x = x_dist(gen);
                        int y = y_dist(gen);
                        double radius = r_dist(gen);
                        map->addObject(x, y, radius);
                    }
                }
                std::cout << "Objects added." << std::endl;
            } else if (choice == "6") {
                std::cout << "List of objects:" << std::endl;
                std::vector<Object::Ptr> objects = map->getObstacles();
                for (int i = 0; i < objects.size(); i++) {
                    std::cout << i + 1 << ". (" << objects[i]->x() << ", " << objects[i]->y() << ") radius: "
                              << objects[i]->radius << std::endl;
                }
                std::cout << "Select an object to delete:" << std::endl;
                int object_num;
                std::cin >> object_num;
                if (object_num > 0 && object_num <= objects.size()) {
                    for (int i = 0; i < objects.size(); i++) {
                        if (object_num - 1 == i) {
                            map->removeObject(objects[i]);
                        }
                    }
                    std::cout << "Object deleted." << std::endl;
                } else {
                    std::cout << "Invalid input. No object was deleted." << std::endl;
                }
            } else if (choice == "7") {
                std::cout << "Set robot start position (x y)." << std::endl;
                int x, y;
                std::cin >> x >> y;
                robot->setStart(x, y);
            } else if (choice == "8") {
                std::cout << "Set robot target position (x y)." << std::endl;
                int x, y;
                std::cin >> x >> y;
                robot->setTarget(x, y);
            } else if (choice == "9") {
                bool save = false;
                while (true) {
                    std::cout << "Would you like to save a video of your robot's journey? (y/n)" << std::endl;
                    std::cin >> choice;
                    if (choice == "y") {
                        std::cout << "Enter full file path for video:" << std::endl;
                        std::cin >> filename;
                        save = true;
                        break;
                    } else if (choice == "n") {
                        break;
                    }
                }
                std::cout
                        << "Enter lambda search parameter. Value should be in range [0,1]. "
                           "The lower the lambda value, the faster your robot will find the "
                           "target, but it will be more careless!\n";
                double lambda;
                std::cin >> lambda;
                auto path = robot->pathFind(lambda, save, filename);
                show(robot->showOnMap(true, {path}, {cv::Vec3b(0.,0.,255.)}));
            } else if (choice == "10") {
                std::cout << "Enter full file path:" << std::endl;
                std::cin >> filename;
                map->save(filename);
            } else if (choice == "11") {
                std::cout << "Enter full file path:" << std::endl;
                std::cin >> filename;
                Map::Ptr new_map = Map::load(filename);
                robot->giveMap(new_map);
                map = new_map;
            } else if (choice == "q") {
                return 0;
            }
        } catch (std::exception &e) {
            std::cout << e.what() << std::endl;
        }
    }

}



