#include "MeteorFactory.h"

class SkillFactory {
public:
  SkillFactory() {}
  static std::shared_ptr<Skill> MakeSkill(KeySphere keySphere, tagIMPR impr) {
    if (keySphere == KeySphere(2, 1, 0)) {
      return MeteorFactory::MakeMeteor(impr);
    }
  }
};
