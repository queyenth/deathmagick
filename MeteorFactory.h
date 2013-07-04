#pragma once

#define _USE_MATH_DEFINES 
#include "Meteor/OneFireMeteor.h"
#include "Meteor/OneIceMeteor.h"
#include "Meteor/OneLightMeteor.h"
#include "Meteor/TwoFireMeteor.h"
#include "Meteor/TwoIceMeteor.h"
#include "Meteor/TwoLightMeteor.h"
#include "Meteor/OneFireAndOneIceMeteor.h"
#include "Meteor/OneFireAndOneLightMeteor.h"
#include "Meteor/OneIceAndOneLightMeteor.h"
#include "Meteor/OneFireAndOneIceAndOneLightMeteor.h"
#include "Meteor/TwoIceAndOneFireMeteor.h"
#include "Meteor/TwoIceAndOneLightMeteor.h"
#include "Meteor/TwoLightAndOneFireMeteor.h"
#include "Meteor/TwoLightAndOneIceMeteor.h"
#include "Meteor/TwoFireAndOneLightMeteor.h"
#include "Meteor/TwoFireAndOneIceMeteor.h"
#include "Meteor/ThreeFireMeteor.h"
#include "Meteor/ThreeLightMeteor.h"
#include "Meteor/ThreeIceMeteor.h"

#include <cmath>

class MeteorFactory {
public:
  MeteorFactory() {}

  static std::shared_ptr<Meteor> MakeMeteor(tagIMPR impr) {
    if (impr.k1 == 1 && impr.k2 == 0 && impr.k3 == 0)
      return std::shared_ptr<Meteor>(new OneFireMeteor());
    else if (impr.k1 == 0 && impr.k2 == 1 && impr.k3 == 0)
      return std::shared_ptr<Meteor>(new OneIceMeteor());
    else if (impr.k1 == 0 && impr.k2 == 0 && impr.k3 == 1)
      return std::shared_ptr<Meteor>(new OneLightMeteor());
    else if (impr.k1 == 2 && impr.k2 == 0 && impr.k3 == 0)
      return std::shared_ptr<Meteor>(new TwoFireMeteor());
    else if (impr.k1 == 0 && impr.k2 == 2 && impr.k3 == 0)
      return std::shared_ptr<Meteor>(new TwoIceMeteor());
    else if (impr.k1 == 0 && impr.k2 == 0 && impr.k3 == 2)
      return std::shared_ptr<Meteor>(new TwoLightMeteor());
    else if (impr.k1 == 1 && impr.k2 == 1 && impr.k3 == 0)
      return std::shared_ptr<Meteor>(new OneFireAndOneIceMeteor());
    else if (impr.k1 == 1 && impr.k2 == 0 && impr.k3 == 1)
      return std::shared_ptr<Meteor>(new OneFireAndOneLightMeteor());
    else if (impr.k1 == 0 && impr.k2 == 1 && impr.k3 == 1)
      return std::shared_ptr<Meteor>(new OneIceAndOneLightMeteor());
    else if (impr.k1 == 1 && impr.k2 == 1 && impr.k3 == 1)
      return std::shared_ptr<Meteor>(new OneFireAndOneIceAndOneLightMeteor());
    else if (impr.k1 == 1 && impr.k2 == 2 && impr.k3 == 0)
      return std::shared_ptr<Meteor>(new TwoIceAndOneFireMeteor());
    else if (impr.k1 == 0 && impr.k2 == 2 && impr.k3 == 1)
      return std::shared_ptr<Meteor>(new TwoIceAndOneLightMeteor());
    else if (impr.k1 == 1 && impr.k2 == 0 && impr.k3 == 2)
      return std::shared_ptr<Meteor>(new TwoLightAndOneFireMeteor());
    else if (impr.k1 == 0 && impr.k2 == 1 && impr.k3 == 2)
      return std::shared_ptr<Meteor>(new TwoLightAndOneIceMeteor());
    else if (impr.k1 == 2 && impr.k2 == 0 && impr.k3 == 1)
      return std::shared_ptr<Meteor>(new TwoFireAndOneLightMeteor());
    else if (impr.k1 == 2 && impr.k2 == 1 && impr.k3 == 0)
      return std::shared_ptr<Meteor>(new TwoFireAndOneIceMeteor());
    else if (impr.k1 == 3 && impr.k2 == 0 && impr.k3 == 0)
      return std::shared_ptr<Meteor>(new ThreeFireMeteor());
    else if (impr.k1 == 0 && impr.k2 == 0 && impr.k3 == 3)
      return std::shared_ptr<Meteor>(new ThreeLightMeteor());
    else if (impr.k1 == 0 && impr.k2 == 3 && impr.k3 == 0)
      return std::shared_ptr<Meteor>(new ThreeIceMeteor());
    else
      return std::shared_ptr<Meteor>(new BaseMeteor());
  }
};