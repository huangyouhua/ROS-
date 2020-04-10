;; Auto-generated. Do not edit!


(when (boundp 'pick_ball_mbot_msgs::PathPlanning)
  (if (not (find-package "PICK_BALL_MBOT_MSGS"))
    (make-package "PICK_BALL_MBOT_MSGS"))
  (shadow 'PathPlanning (find-package "PICK_BALL_MBOT_MSGS")))
(unless (find-package "PICK_BALL_MBOT_MSGS::PATHPLANNING")
  (make-package "PICK_BALL_MBOT_MSGS::PATHPLANNING"))
(unless (find-package "PICK_BALL_MBOT_MSGS::PATHPLANNINGREQUEST")
  (make-package "PICK_BALL_MBOT_MSGS::PATHPLANNINGREQUEST"))
(unless (find-package "PICK_BALL_MBOT_MSGS::PATHPLANNINGRESPONSE")
  (make-package "PICK_BALL_MBOT_MSGS::PATHPLANNINGRESPONSE"))

(in-package "ROS")





(defclass pick_ball_mbot_msgs::PathPlanningRequest
  :super ros::object
  :slots (_Request ))

(defmethod pick_ball_mbot_msgs::PathPlanningRequest
  (:init
   (&key
    ((:Request __Request) nil)
    )
   (send-super :init)
   (setq _Request __Request)
   self)
  (:Request
   (&optional __Request)
   (if __Request (setq _Request __Request)) _Request)
  (:serialization-length
   ()
   (+
    ;; bool _Request
    1
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; bool _Request
       (if _Request (write-byte -1 s) (write-byte 0 s))
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; bool _Request
     (setq _Request (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;;
   self)
  )

(defclass pick_ball_mbot_msgs::PathPlanningResponse
  :super ros::object
  :slots (_Result ))

(defmethod pick_ball_mbot_msgs::PathPlanningResponse
  (:init
   (&key
    ((:Result __Result) nil)
    )
   (send-super :init)
   (setq _Result __Result)
   self)
  (:Result
   (&optional __Result)
   (if __Result (setq _Result __Result)) _Result)
  (:serialization-length
   ()
   (+
    ;; bool _Result
    1
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; bool _Result
       (if _Result (write-byte -1 s) (write-byte 0 s))
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; bool _Result
     (setq _Result (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;;
   self)
  )

(defclass pick_ball_mbot_msgs::PathPlanning
  :super ros::object
  :slots ())

(setf (get pick_ball_mbot_msgs::PathPlanning :md5sum-) "2b99074ee17510311b29260db3a8ae84")
(setf (get pick_ball_mbot_msgs::PathPlanning :datatype-) "pick_ball_mbot_msgs/PathPlanning")
(setf (get pick_ball_mbot_msgs::PathPlanning :request) pick_ball_mbot_msgs::PathPlanningRequest)
(setf (get pick_ball_mbot_msgs::PathPlanning :response) pick_ball_mbot_msgs::PathPlanningResponse)

(defmethod pick_ball_mbot_msgs::PathPlanningRequest
  (:response () (instance pick_ball_mbot_msgs::PathPlanningResponse :init)))

(setf (get pick_ball_mbot_msgs::PathPlanningRequest :md5sum-) "2b99074ee17510311b29260db3a8ae84")
(setf (get pick_ball_mbot_msgs::PathPlanningRequest :datatype-) "pick_ball_mbot_msgs/PathPlanningRequest")
(setf (get pick_ball_mbot_msgs::PathPlanningRequest :definition-)
      "bool Request
---
bool Result
")

(setf (get pick_ball_mbot_msgs::PathPlanningResponse :md5sum-) "2b99074ee17510311b29260db3a8ae84")
(setf (get pick_ball_mbot_msgs::PathPlanningResponse :datatype-) "pick_ball_mbot_msgs/PathPlanningResponse")
(setf (get pick_ball_mbot_msgs::PathPlanningResponse :definition-)
      "bool Request
---
bool Result
")



(provide :pick_ball_mbot_msgs/PathPlanning "2b99074ee17510311b29260db3a8ae84")


