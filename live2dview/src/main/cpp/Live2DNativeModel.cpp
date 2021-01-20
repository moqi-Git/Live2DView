//
// Created by reol on 1/20/21.
//

#include "Live2DNativeModel.hpp"

Live2DNativeModel::Live2DNativeModel() {

}

Live2DNativeModel::~Live2DNativeModel() {

}

void Live2DNativeModel::initModel(std::string dir, std::string name) {
    this->dir = Csm::csmString(dir.c_str());

}

Csm::ICubismModelSetting *Live2DNativeModel::readModelConfig() {
    return nullptr;
}


