// Copyright 2023 FUTU-RE Co. LTD.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef DUMMY_BMS_NODE_HPP
#define DUMMY_BMS_NODE_HPP

#include <thread>
#include <mutex>
#include <iostream>
#include "rclcpp/rclcpp.hpp" 
#include "std_msgs/msg/int16.hpp"


class DummyBmsNode : public rclcpp::Node
{
public:
  DummyBmsNode(); 
  using UIInt16 = std_msgs::msg::Int16;

private:
  void main_loop();
  void user_input_thread();

  // eHMI Publishers
  rclcpp::Publisher<UIInt16>::SharedPtr battery_rsoc_pub_;

  // Timer
  rclcpp::TimerBase::SharedPtr timer_;

  // SOC value and mutex for thread safety
  int16_t soc_value_;
  std::mutex soc_mutex_;
};

#endif
