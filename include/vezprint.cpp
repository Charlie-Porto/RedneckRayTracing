#ifndef vezprint_cpp
#define vezprint_cpp

#include <iostream>
#include <string>

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/ext/quaternion_double.hpp>

#include <ezprint.cpp>

/*
  Purpose: this module contains functions to speed up the printing of vector3s and quaternions. 
*/

namespace vezp {

void print_dquat(glm::dquat q) {
  ezp::print_labeled_item("w: ", q.w);
  ezp::print_labeled_item("x: ", q.x);
  ezp::print_labeled_item("y: ", q.y);
  ezp::print_labeled_item("z: ", q.z);
}

void print_dvec3(glm::dvec3 v) {
  ezp::print_labeled_item("x: ", v.x);
  ezp::print_labeled_item("y: ", v.y);
  ezp::print_labeled_item("z: ", v.z);
}

void print_dvec2(glm::dvec2 v) {
  ezp::print_labeled_item("x: ", v.x);
  ezp::print_labeled_item("y: ", v.y);
}

}

#endif /* vezprint_cpp */
