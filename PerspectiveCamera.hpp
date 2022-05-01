#ifndef PERSPECTIVE_CAMERA_HPP
#define PERSPECTIVE_CAMERA_HPP 1
#include "BaseCamera.hpp"

namespace EngineSpace
{
  class PerspectiveCamera: public BaseCamera
  {
  public:
    using BaseCamera::BaseCamera;

    virtual glm::mat4 getProjectionMatrix() const{return glm::perspective(glm::radians(getFov()), (float)window.getWidth()/(float)window.getHeight(), getNear(), getFar());}
  };
}
#endif
