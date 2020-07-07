/* GStreamer
 * Copyright (C) 2020 FIXME <fixme@example.com>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 51 Franklin St, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 */

#ifndef _GST_ROSAUDIOSRC_H_
#define _GST_ROSAUDIOSRC_H_

#include <gst/audio/audio-format.h>
#include <gst/base/gstbasesrc.h>

//include ROS and ROS message formats
#include "rclcpp/rclcpp.hpp"
#include "audio_msgs/msg/audio.hpp"


G_BEGIN_DECLS

#define GST_TYPE_ROSAUDIOSRC   (rosaudiosrc_get_type())
#define GST_ROSAUDIOSRC(obj)   (G_TYPE_CHECK_INSTANCE_CAST((obj),GST_TYPE_ROSAUDIOSRC,Rosaudiosrc))
#define GST_ROSAUDIOSRC_CLASS(klass)   (G_TYPE_CHECK_CLASS_CAST((klass),GST_TYPE_ROSAUDIOSRC,RosaudiosrcClass))
#define GST_IS_ROSAUDIOSRC(obj)   (G_TYPE_CHECK_INSTANCE_TYPE((obj),GST_TYPE_ROSAUDIOSRC))
#define GST_IS_ROSAUDIOSRC_CLASS(obj)   (G_TYPE_CHECK_CLASS_TYPE((klass),GST_TYPE_ROSAUDIOSRC))

typedef struct _Rosaudiosrc Rosaudiosrc;
typedef struct _RosaudiosrcClass RosaudiosrcClass;

struct _Rosaudiosrc
{
  GstBaseSrc parent;
  gchar* node_name;
  gchar* sub_topic;
  gchar* frame_id;
  gchar* encoding;
  gchar* init_caps;

  /* This set of variables and mutexes allow signalling for a message passed between threads
   * current_msg is set at the ROS callback and retrieved in gstreamer's push loop
   */
  bool msg_init;
  bool new_msg;
  audio_msgs::msg::Audio::ConstSharedPtr current_msg;
  GMutex data_mutex;
  GCond data_cond;




  rclcpp::Context::SharedPtr ros_context;
  rclcpp::executor::Executor::SharedPtr ros_executor;
  rclcpp::Node::SharedPtr node;
  rclcpp::Subscription<audio_msgs::msg::Audio>::SharedPtr sub;
  rclcpp::Logger logger;
  rclcpp::Clock::SharedPtr clock;

  int channels;    //number of audio channels
  int sample_rate; //sample rate in Hz
  size_t stride;   //bytes per frame
  gint endianness;  
  uint8_t layout;
};

struct _RosaudiosrcClass
{
  GstBaseSrcClass parent_class;

  // stick member function pointers here
  // along with member function pointers for signal handlers
};

GType rosaudiosrc_get_type (void);

G_END_DECLS

#endif