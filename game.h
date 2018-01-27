class View;
class Model;

class Game {
    private:
    View &view;
    Model *model;

    public:
    Game(Model *m, View &v);
};