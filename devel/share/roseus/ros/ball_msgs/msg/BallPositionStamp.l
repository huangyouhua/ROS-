;; Auto-generated. Do not edit!


(when (boundp 'ball_msgs::BallPositionStamp)
  (if (not (find-package "BALL_MSGS"))
    (make-package "BALL_MSGS"))
  (shadow 'BallPositionStamp (find-package "BALL_MSGS")))
(unless (find-package "BALL_MSGS::BALLPOSITIONSTAMP")
  (make-package "BALL_MSGS::BALLPOSITIONSTAMP"))

(in-package "ROS")
;;//! \htmlinclude BallPositionStamp.msg.html
(if (not (find-package "GEOMETRY_MSGS"))
  (ros::roseus-add-msgs "geometry_msgs"))
(if (not (find-package "STD_MSGS"))
  (ros::roseus-add-msgs "std_msgs"))


(defclass ball_msgs::BallPositionStamp
  :super ros::object
  :slots (_header _Position ))

(defmethod ball_msgs::BallPositionStamp
  (:init
   (&key
    ((:header __header) (instance std_msgs::Header :init))
    ((:Position __Position) (let (r) (dotimes (i 0) (push (instance geometry_msgs::Point :init) r)) r))
    )
   (send-super :init)
   (setq _header __header)
   (setq _Position __Position)
   self)
  (:header
   (&rest __header)
   (if (keywordp (car __header))
       (send* _header __header)
     (progn
       (if __header (setq _header (car __header)))
       _header)))
  (:Position
   (&rest __Position)
   (if (keywordp (car __Position))
       (send* _Position __Position)
     (progn
       (if __Position (setq _Position (car __Position)))
       _Position)))
  (:serialization-length
   ()
   (+
    ;; std_msgs/Header _header
    (send _header :serialization-length)
    ;; geometry_msgs/Point[] _Position
    (apply #'+ (send-all _Position :serialization-length)) 4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; std_msgs/Header _header
       (send _header :serialize s)
     ;; geometry_msgs/Point[] _Position
     (write-long (length _Position) s)
     (dolist (elem _Position)
       (send elem :serialize s)
       )
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; std_msgs/Header _header
     (send _header :deserialize buf ptr-) (incf ptr- (send _header :serialization-length))
   ;; geometry_msgs/Point[] _Position
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _Position (let (r) (dotimes (i n) (push (instance geometry_msgs::Point :init) r)) r))
     (dolist (elem- _Position)
     (send elem- :deserialize buf ptr-) (incf ptr- (send elem- :serialization-length))
     ))
   ;;
   self)
  )

(setf (get ball_msgs::BallPositionStamp :md5sum-) "053027c5e2d72bc888b90c92a0752833")
(setf (get ball_msgs::BallPositionStamp :datatype-) "ball_msgs/BallPositionStamp")
(setf (get ball_msgs::BallPositionStamp :definition-)
      "std_msgs/Header header
geometry_msgs/Point[] Position

================================================================================
MSG: std_msgs/Header
# Standard metadata for higher-level stamped data types.
# This is generally used to communicate timestamped data 
# in a particular coordinate frame.
# 
# sequence ID: consecutively increasing ID 
uint32 seq
#Two-integer timestamp that is expressed as:
# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')
# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')
# time-handling sugar is provided by the client library
time stamp
#Frame this data is associated with
# 0: no frame
# 1: global frame
string frame_id

================================================================================
MSG: geometry_msgs/Point
# This contains the position of a point in free space
float64 x
float64 y
float64 z

")



(provide :ball_msgs/BallPositionStamp "053027c5e2d72bc888b90c92a0752833")


