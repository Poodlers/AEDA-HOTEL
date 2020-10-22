#include <string>

using namespace std;

class Room{
    public:
        int getFloor() const;
        int getroomNumber() const;
        int getCapacity() const;
        virtual int getPricePerNight() const = 0; //implementar em cada classe
        void setFloor(const int floor);
        void setRoomNumber(const int roomNumber);
        void setCapacity(const int capacity);
        void setPricePerNight(const int pricePerNight);
        int generateID(){
            return ++roomId;
}
    private:
        int floor;
        int roomNumber; //maneira de acessar numero de quarto a partir de roomId
        static int roomId;
        int capacity;
        int pricePerNight; //guarda o preço-base
};

class Suite: public Room{

};

class ViewRoom: public Room{
    
};

class NoViewRoom: public Room{
    
};