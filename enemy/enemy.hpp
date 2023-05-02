#include <vector>

namespace fnad
{
    enum class Status {susceptible, infectious, removed};

    class Enemy
    {
    private:
    Status status{Status::susceptible};
    std::vector<float> position;
    int floor;

    public:
    void move(float, float);
    void evolve();
    };
}