//
// Created by andre on 30/03/22.
//

#ifndef P1_PACKAGE_H
#define P1_PACKAGE_H


class Package {
public:
    Package(int volume, int weight, int reward, float duration, int id);

    void setVolume(int volume);

    void setWeight(int weight);

    void setReward(int reward);

    void setDuration(int duration);

    void setId(int id);

    void setExpress(bool express);

    void setDone(bool done);

    int getVolume() const;

    int getWeight() const;

    int getReward() const;

    float getDuration() const;

    int getId() const;

    bool isDone() const;

private:
    int volume,weight,reward,id;
    bool done;
    float duration;
};


#endif //P1_PACKAGE_H
