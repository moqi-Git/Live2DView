//
// Created by reol on 1/20/21.
//

#ifndef LIVE2DVIEWSAMPLE_LIVE2DNATIVEMODEL_H
#define LIVE2DVIEWSAMPLE_LIVE2DNATIVEMODEL_H


#include <Model/CubismUserModel.hpp>
#include <string>

class Live2DNativeModel : public Csm::CubismUserModel {

public:

    Live2DNativeModel();

    virtual ~Live2DNativeModel();

    void initModel(std::string dir, std::string name);

private:
    Csm::ICubismModelSetting* readModelConfig();

    Csm::csmString dir;
};


#endif //LIVE2DVIEWSAMPLE_LIVE2DNATIVEMODEL_H
