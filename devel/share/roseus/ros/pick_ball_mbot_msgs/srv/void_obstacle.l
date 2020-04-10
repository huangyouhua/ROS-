;; Auto-generated. Do not edit!


(when (boundp 'pick_ball_mbot_msgs::void_obstacle)
  (if (not (find-package "PICK_BALL_MBOT_MSGS"))
    (make-package "PICK_BALL_MBOT_MSGS"))
  (shadow 'void_obstacle (find-package "PICK_BALL_MBOT_MSGS")))
(unless (find-package "PICK_BALL_MBOT_MSGS::VOID_OBSTACLE")
  (make-package "PICK_BALL_MBOT_MSGS::VOID_OBSTACLE"))
(unless (find-package "PICK_BALL_MBOT_MSGS::VOID_OBSTACLEREQUEST")
  (make-package "PICK_BALL_MBOT_MSGS::VOID_OBSTACLEREQUEST"))
(unless (find-package "PICK_BALL_MBOT_MSGS::VOID_OBSTACLERESPONSE")
  (make-package "PICK_BALL_MBOT_MSGS::VOID_OBSTACLERESPONSE"))

(in-package "ROS")





(defclass pick_ball_mbot_msgs::void_obstacleRequest
  :super ros::object
  :slots (_obstacle ))

(defmethod pick_ball_mbot_msgs::void_obstacleRequest
  (:init
   (&key
    ((:obstacle __obstacle) nil)
    )
   (send-super :init)
   (setq _obstacle __obstacle)
   self)
  (:obstacle
   (&optional __obstacle)
   (if __obstacle (setq _obstacle __obstacle)) _obstacle)
  (:serialization-length
   ()
   (+
    ;; bool _obstacle
    1
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; bool _obstacle
       (if _obstacle (write-byte -1 s) (write-byte 0 s))
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; bool _obstacle
     (setq _obstacle (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;;
   self)
  )

(defclass pick_ball_mbot_msgs::void_obstacleResponse
  :super ros::object
  :slots (_result ))

(defmethod pick_ball_mbot_msgs::void_obstacleResponse
  (:init
   (&key
    ((:result __result) nil)
    )
   (send-super :init)
   (setq _result __result)
   self)
  (:result
   (&optional __result)
   (if __result (setq _result __result)) _result)
  (:serialization-length
   ()
   (+
    ;; bool _result
    1
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; bool _result
       (if _result (write-byte -1 s) (write-byte 0 s))
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; bool _result
     (setq _result (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;;
   self)
  )

(defclass pick_ball_mbot_msgs::void_obstacle
  :super ros::object
  :slots ())

(setf (get pick_ball_mbot_msgs::void_obstacle :md5sum-) "94e2952797301ac06963adb1824707fa")
(setf (get pick_ball_mbot_msgs::void_obstacle :datatype-) "pick_ball_mbot_msgs/void_obstacle")
(setf (get pick_ball_mbot_msgs::void_obstacle :request) pick_ball_mbot_msgs::void_obstacleRequest)
(setf (get pick_ball_mbot_msgs::void_obstacle :response) pick_ball_mbot_msgs::void_obstacleResponse)

(defmethod pick_ball_mbot_msgs::void_obstacleRequest
  (:response () (instance pick_ball_mbot_msgs::void_obstacleResponse :init)))

(setf (get pick_ball_mbot_msgs::void_obstacleRequest :md5sum-) "94e2952797301ac06963adb1824707fa")
(setf (get pick_ball_mbot_msgs::void_obstacleRequest :datatype-) "pick_ball_mbot_msgs/void_obstacleRequest")
(setf (get pick_ball_mbot_msgs::void_obstacleRequest :definition-)
      "bool obstacle
---
bool result
")

(setf (get pick_ball_mbot_msgs::void_obstacleResponse :md5sum-) "94e2952797301ac06963adb1824707fa")
(setf (get pick_ball_mbot_msgs::void_obstacleResponse :datatype-) "pick_ball_mbot_msgs/void_obstacleResponse")
(setf (get pick_ball_mbot_msgs::void_obstacleResponse :definition-)
      "bool obstacle
---
bool result
")



(provide :pick_ball_mbot_msgs/void_obstacle "94e2952797301ac06963adb1824707fa")


